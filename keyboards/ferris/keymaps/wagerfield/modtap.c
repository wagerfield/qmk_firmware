// clang-format off

#include "modtap.h"
#include "quantum.h"
#include "debug.h"

// Home row mods are beneficial on compact split keyboards, and their accuracy can be improved
// through context-aware settings. By evaluating the keys typed before and after a mod-tap key,
// we can refine QMK's Tap-Hold functionality with these simple rules:
//
// 1. When a mod-tap key is pressed immediately after a non-mod-tap key, it registers as a tap.
// 2. When a mod-tap key is followed immediately by a non-mod-tap key on the same hand, it registers as a tap.
// 3. Otherwise, the mod-tap key registers as a hold in combination with any other key.
//
// Note that [immediately] is defined as within the ROLLING_TERM via the IS_ROLLING macro.

static bool tapped[COLUMNS];

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

static void tap_keycode(uint16_t keycode, keyrecord_t record) {
    uint8_t index = GET_INDEX(record);

    if (tapped[index] || !IS_MOD_TAP(keycode)) return;

    uint16_t mapped_keycode = map_keycode(keycode);

    tap_code16(mapped_keycode);

    dprintf("[2] %c TAP\n", get_keychar(mapped_keycode));

    tapped[index] = true;
}

bool pre_process_modtap(uint16_t keycode, keyrecord_t *record) {

    // KEY RELEASED

    if (!record->event.pressed) return true;

    // KEY PRESSED

    prev_keycode = curr_keycode;
    curr_keycode = keycode;

    prev_record = curr_record;
    curr_record = *record;

    if (IS_MOD_TAP(prev_keycode)) return true;
    if (!IS_MOD_TAP(curr_keycode)) return true;

    char prev_char = get_keychar(prev_keycode);
    char curr_char = get_keychar(curr_keycode);

    uint16_t elapsed = GET_ELAPSED(prev_record);
    bool is_rolling = IS_ROLLING(elapsed);

    dprintf("[1] %c -> %c %ums %s\n", prev_char, curr_char, elapsed, is_rolling ? "ROLL" : "");

    // Rule 1: Mod-tap key pressed immediately after a non-mod-tap key -> tap
    if (is_rolling) tap_keycode(curr_keycode, curr_record);

    return true;
}

bool process_modtap(uint16_t keycode, keyrecord_t *record) {
    uint8_t index = GET_INDEX((*record));

    // KEY RELEASED

    if (!record->event.pressed) {
        tapped[index] = false;
        return true;
    }

    // KEY PRESSED

    // Rule 2: Non-mod-tap key pressed immediately after mod-tap key on same hand -> tap the mod-tap
    // if (IS_MOD_TAP(prev_keycode) && !IS_MOD_TAP(keycode)) {

    //     uint16_t elapsed = GET_ELAPSED(prev_record);
    //     bool is_rolling = IS_ROLLING(elapsed);
    //     bool is_same_side = IS_SAME_SIDE((*record), prev_record);

    //     if (is_rolling && is_same_side) {
    //         tap_keycode(prev_keycode, prev_record);
    //     }
    // }

    tap_keycode(keycode, (*record));

    return !tapped[index];
}