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

    uint16_t tap_keycode = map_keycode(keycode);
    register_code16(tap_keycode);
    unregister_code16(tap_keycode);
    tapped[index] = true;
}

bool pre_process_modtap(uint16_t keycode, keyrecord_t *record) {
    uint8_t index = GET_INDEX((*record));

    // Handle key release - clear tapped flag
    if (!record->event.pressed) {
        if (tapped[index]) {
            tapped[index] = false;
            return false; // Skip QMK processing for tapped keys
        }
        return true;
    }

    // Handle key press
    if (tapped[index]) {
        return false; // Skip QMK processing if already tapped
    }

    prev_keycode = curr_keycode;
    curr_keycode = keycode;

    prev_record = curr_record;
    curr_record = *record;

    // Only apply custom logic to mod-tap keys
    if (!IS_MOD_TAP(keycode)) {
        return true;
    }

    uint16_t elapsed = GET_ELAPSED(prev_record);
    bool is_rolling = IS_ROLLING(elapsed);

    // Rule 1: Mod-tap key pressed immediately after a non-mod-tap key -> tap
    if (is_rolling && prev_keycode != KC_NO && !IS_MOD_TAP(prev_keycode)) {
        tap(keycode, *record);
        return false;
    }

    return true;
}

bool process_modtap(uint16_t keycode, keyrecord_t *record) {
    // Check if this is a symbol layer key that should always tap
    bool is_symbol_modtap = (keycode == LOPT_EXLM || keycode == LSFT_LABK ||
                             keycode == HYPR_PIPE || keycode == RSFT_LPRN ||
                             keycode == RCMD_LCBR || keycode == ROPT_LBRC ||
                             keycode == RCTL_COLN || keycode == LCTL_TAB ||
                             keycode == LCMD_EQL || keycode == HYPR_SLSH);

    // Force symbol mod-tap keys to always produce their tap symbols
    if (is_symbol_modtap && record->event.pressed) {
        uint16_t tap_keycode = map_keycode(keycode);
        register_code16(tap_keycode);
        unregister_code16(tap_keycode);
        return false;
    }

    if (!record->event.pressed) {
        return true;
    }

    // Rule 2: Non-mod-tap key pressed immediately after mod-tap key on same hand -> tap the mod-tap
    if (prev_keycode != KC_NO && IS_MOD_TAP(prev_keycode) && !IS_MOD_TAP(keycode)) {
        uint16_t elapsed = GET_ELAPSED(prev_record);
        bool is_rolling = IS_ROLLING(elapsed);
        bool is_same_side = IS_SAME_SIDE((*record), prev_record);

        if (is_rolling && is_same_side) {
            tap(prev_keycode, prev_record);
        }
    }

    return true;
}
