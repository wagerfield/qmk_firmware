// clang-format off
#include "rolltap.h"

static struct {
  bool is_lrt;
  bool is_mrt;
  char key_char;
  uint8_t group;
  uint16_t time;
  uint16_t key_code;
  uint16_t tap_code;
  uint8_t hold_data;
} events[EVENTS_SIZE];

static void clear_event(uint8_t index) {
  events[index].hold_data = 0;
  events[index].key_code = 0;
  events[index].tap_code = 0;
}

static void clear_events(void) {
  for (uint8_t i = 0; i < EVENTS_SIZE; i++) clear_event(i);
}

// 0 1 2 3 4 L   R 0 1 2 3 4
// F F F F F 0   4 F F F F F
// F F F F F 1   5 F F F F F
// F F F F F 2   6 F F F F F
//       T T 3   7 T T

static uint8_t get_group(keyrecord_t *record) {
    uint8_t row = record->event.key.row;
    if (row == 3) return 2; // Left Thumb
    if (row == 7) return 3; // Right Thumb
    if (row < 3) return 0; // Left Finger
    return 1; // Right Finger
}

static uint8_t get_index(keyrecord_t *record) {
    uint8_t col = record->event.key.col;
    uint8_t row = record->event.key.row;
    if (row > 3 && row < 7) col += 5; // Right Fingers
    if (row == 3) col += 10; // Left Thumb
    if (row == 7) col += 12; // Right Thumb
    return col; // Left Fingers
}

static char get_char(uint16_t keycode) {
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

void rolltap_init(void) {
    clear_events();
}

void rolltap_scan(void) {

}

bool process_rolltap(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        uint8_t index = get_index(record);

        events[index].key_code = keycode;
        events[index].key_char = get_char(keycode);
        events[index].tap_code = RT_GET_TAP_CODE(keycode);
        events[index].hold_data = RT_GET_HOLD_DATA(keycode);
        events[index].time = record->event.time;
        events[index].group = get_group(record);
        events[index].is_lrt = IS_LRT(keycode);
        events[index].is_mrt = IS_MRT(keycode);
    }
    return true;
}
