// clang-format off
#include "quantum.h"

#include "helpers.h"
#include "rolltap.h"

// P = Pinky
// R = Ring
// M = Middle
// I = Index
// T = Thumb

// 0 1 2 3 4 L   R 0 1 2 3 4
// P R M I I 0   4 I I M R P
// P R M I I 1   5 I I M R P
// P R M I I 2   6 I I M R P
//       T T 3   7 T T

static uint8_t curr_index = 0;
static uint8_t prev_index = 0;

static struct {
  uint16_t time;
  uint16_t key_code;
  uint16_t tap_code;
  uint8_t hold_mods;
  uint8_t tap_mods;
  char keychar;
  char finger;
  char side;
} events[EVENTS_SIZE];

static void clear_event(uint8_t index) {
  events[index].key_code = 0;
  events[index].tap_code = 0;
  events[index].tap_mods = 0;
  events[index].hold_mods = 0;
}

static void clear_events(void) {
  for (uint8_t i = 0; i < EVENTS_SIZE; i++) clear_event(i);
}

static char get_side(keyrecord_t *record) {
    return record->event.key.row < MATRIX_HALF ? LHS : RHS;
}

static char get_finger(keyrecord_t *record) {
    uint8_t col = record->event.key.col;
    uint8_t row = record->event.key.row;

    if (row == 3 || row == 7) return THUMB;
    if (get_side(record) == RHS) col = 4 - col;

    switch (col) {
        case 0: return PINKIE;
        case 1: return RING;
        case 2: return MIDDLE;
        default: return INDEX;
    }
}

static uint8_t get_index(keyrecord_t *record) {
    uint8_t col = record->event.key.col;
    uint8_t row = record->event.key.row;
    if (row > 3 && row < 7) col += 5; // Right Fingers
    if (row == 3) col += 10; // Left Thumb
    if (row == 7) col += 12; // Right Thumb
    return col; // Left Fingers
}

static uint16_t get_elapsed(uint8_t index) {
  return events[index].time ? timer_elapsed(events[index].time) : 0;
}

static uint16_t get_tap_code(uint16_t keycode) {
    return IS_MRT(keycode) ? MRT_GET_TAP_CODE(keycode) : keycode;
}

static uint8_t get_tap_mods(uint16_t keycode) {
    return IS_MRT(keycode) ? MRT_GET_TAP_MODS(keycode) : 0;
}

static uint8_t get_hold_mods(uint16_t keycode) {
    return IS_MRT(keycode) ? MRT_GET_HOLD_MODS(keycode) : 0;
}

static uint8_t get_event_mods(uint8_t index, uint16_t term) {
  uint8_t mods = events[index].tap_mods;
  for (uint8_t i = 0; i < EVENTS_SIZE; i++) {
    if (i == index || !events[i].hold_mods) continue;
    if (term && get_elapsed(i) <= term) continue;
    mods |= events[i].hold_mods;
  }
  // dprintf("mods: 0x%02X\n", mods);
  return mods;
}

static bool is_rolling(uint8_t curr_index, uint8_t prev_index, uint8_t roll_term) {
  if (curr_index == prev_index) return false;

  uint16_t elapsed = get_elapsed(prev_index);

  bool rolling = elapsed <= roll_term;

  dprintf("[0] %c -> %c T:%ums E:%ums %s\n",
          events[prev_index].keychar,
          events[curr_index].keychar,
          roll_term,
          elapsed,
          rolling ? "ROLL" : "");

  return rolling;
}

static void apply_event(uint8_t index, uint8_t term) {
    if (!events[index].key_code) return;
    set_mods(term ? get_event_mods(index, term) : events[index].tap_mods);
    tap_code16(events[index].tap_code);
    clear_event(index);
    register_mods(get_event_mods(index, 0));
}

bool process_rolltap(uint16_t keycode, keyrecord_t *record) {
    // TODO: Handle thumb roll tapping
    if (get_finger(record) == THUMB) return true;

    if (record->event.pressed) {
        prev_index = curr_index;
        curr_index = get_index(record);

        uint8_t tapcode = get_tap_code(keycode);

        events[curr_index].key_code = keycode;
        events[curr_index].tap_code = tapcode;
        events[curr_index].tap_mods = get_tap_mods(keycode);
        events[curr_index].hold_mods = get_hold_mods(keycode);
        events[curr_index].keychar = get_key_char(tapcode);
        events[curr_index].finger = get_finger(record);
        events[curr_index].side = get_side(record);
        events[curr_index].time = record->event.time;

        char curr_finger = events[curr_index].finger != 'T';
        char prev_finger = events[prev_index].finger != 'T';
        bool both_finger = curr_finger && prev_finger;

        // char curr_char = events[curr_index].keychar;
        // char prev_char = events[prev_index].keychar;

        char curr_side = events[curr_index].side;
        char prev_side = events[prev_index].side;
        bool same_side = curr_side == prev_side;

        uint8_t curr_mods = events[curr_index].hold_mods;
        uint8_t prev_mods = events[prev_index].hold_mods;
        bool both_mods = curr_mods && prev_mods;

        uint8_t rolling_term = same_side && both_finger ? 200 : 120;
        bool rolling = is_rolling(curr_index, prev_index, rolling_term);

        if (curr_mods) {
           // dprintf("[1] %c -> %c register mods 0x%02X\n", prev_char, curr_char, curr_mods);
           register_mods(curr_mods);
        }

        // Same hand modifier chording eg. LCTL_KC_N -> LOPT_KC_R
        if (both_mods && same_side && rolling) {
            // dprintf("[2] %c -> %c same side chording\n", prev_char, curr_char);
            return false;
        }

        // Same hand modifier tapping eg. LCTL_KC_N -> LOPT_KC_R
        if (both_mods && same_side && !rolling) {
            // dprintf("[2] %c -> %c same side chording\n", prev_char, curr_char);
            apply_event(curr_index, rolling_term);
            return false;
        }

        // Opposite hand modifier tapping eg. LSFT_KC_S -> RCTL_KC_I
        if (both_mods && !same_side && !rolling) {
            // dprintf("[3] %c -> %c opposite side tapping\n", prev_char, curr_char);
            apply_event(curr_index, rolling_term);
            return false;
        }

        // Roll keys applying NO modifiers eg. LSFT_KC_S -> KC_O
        if (rolling) {
            // dprintf("[4] %c -> %c rolling keys\n", prev_char, curr_char);
            apply_event(prev_index, 0);
            apply_event(curr_index, 0);
            return false;
        }

        // Tap keys with no modifiers eg. KC_O
        if (!curr_mods) {
            // dprintf("[5] %c -> %c tapping keys\n", prev_char, curr_char);
            apply_event(curr_index, rolling_term);
            return false;
        }

        return false;
    }

    uint8_t index = get_index(record);
    uint8_t mods = events[index].hold_mods;

    if (mods) {
        unregister_mods(mods);

        uint16_t elapsed = get_elapsed(index);

        bool tapped = elapsed <= 200;

        // dprintf("[6] %c released %ums %s\n",
        //         events[index].keychar, elapsed,
        //         tapped ? "TAP" : "NOOP");

        if (tapped) apply_event(index, 200);
    }

    clear_event(index);

    return true;
}

void matrix_init_user(void) {
  clear_events();
}
