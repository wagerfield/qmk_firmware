// clang-format off

#include "modtap.h"
#include "quantum.h"
#include "debug.h"

// Home row mods are beneficial on compact split keyboards, and their accuracy can be improved
// through context-aware settings. By evaluating the keys typed before and after a mod-tap key,
// we can refine QMK's Tap-Hold functionality with these simple rules:
//
// - When a mod-tap key is pressed [immediately] after a non-mod-tap key, it registers as a tap.
// - When a mod-tap key is followed [immediately] by a non-mod-tap key on the same hand, it registers as a tap.
// - Otherwise, the mod-tap key registers as a hold in combination with any other key.
//
// Note that [immediately] is defined as within the ROLLING_TERM via the IS_ROLLING macro.

static bool tapped[14];

static uint16_t curr_keycode;
static uint16_t prev_keycode;

static keyrecord_t curr_record;
static keyrecord_t prev_record;

static char get_keychar(uint16_t keycode) {
    switch (keycode & 0xFF) {
        case KC_A ... KC_Z: return 'A' + (keycode - KC_A);
        case KC_1 ... KC_0: return '1' + (keycode - KC_1);
        case KC_QUOTE: return '"';
        case KC_MINUS: return '-';
        case KC_SPACE: return '_';
        case KC_COMMA: return ',';
        case KC_DOT: return '.';
        default: return '?';
    }
}

static uint16_t map_keycode(uint16_t keycode) {
    switch (keycode) {
        case LOPT_EXLM: return KC_EXLM;
        case LSFT_LABK: return KC_LABK;
        case HYPR_PIPE: return KC_PIPE;
        case RSFT_LPRN: return KC_LPRN;
        case RCMD_LCBR: return KC_LCBR;
        case RCTL_COLN: return KC_COLN;
        default: return QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
    }
}

static void tap(uint16_t keycode, keyrecord_t record) {
    uint8_t index = GET_INDEX(record);
    if (tapped[index] || !IS_MOD_TAP(keycode)) return;
    dprintf("  TAP %c\n", get_keychar(keycode));
    clear_mods();
    tap_code16(map_keycode(keycode));
    tapped[index] = true;
}

bool pre_process_modtap(uint16_t keycode, keyrecord_t *record) {
    // return true;

    keyrecord_t copy = *record;
    uint8_t index = GET_INDEX(copy);

    if (tapped[index]) {
        tapped[index] = false;
        return false;
    }

    if (record->event.pressed) {
        prev_keycode = curr_keycode;
        curr_keycode = keycode;

        prev_record = curr_record;
        curr_record = *record;

        uint16_t elapsed = GET_ELAPSED(prev_record);

        char prev_keychar = get_keychar(prev_keycode);
        char curr_keychar = get_keychar(curr_keycode);

        bool is_home_roll = IS_HOME_ROLL(curr_record, prev_record);
        bool is_same_side = IS_SAME_SIDE(curr_record, prev_record);
        bool is_rolling = IS_ROLLING(elapsed);

        dprintf("%c -> %c %4ums is_rolling: %u, is_same_side: %u, is_home_roll: %u\n",
                prev_keychar, curr_keychar, elapsed,
                is_rolling, is_same_side, is_home_roll);

        if (is_rolling && (is_home_roll || is_same_side)) {
            tap(prev_keycode, prev_record);
            tap(curr_keycode, curr_record);
            return false;
        }
    }

    return true;
}

bool process_modtap(uint16_t keycode, keyrecord_t *record) {
    return true;
}
