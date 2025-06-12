// clang-format off

#include "modtap.h"
#include "quantum.h"

// Home row mods are beneficial on compact split keyboards, and their accuracy can be improved
// through context-aware settings. By evaluating the keys typed before and after a mod-tap key,
// we can refine QMK's Tap-Hold functionality with these simple rules:
//
// - When a mod-tap key is pressed immediately after a non-mod-tap key, it registers as a tap.
// - When a mod-tap key is followed immediately by a non-mod-tap key on the same hand, it registers as a tap.
// - Otherwise, the mod-tap key registers as a hold in combination with any other key.
//
// Note that [immediately] is defined as within the ROLLING_TERM via the IS_ROLLING macro.

static bool tapped[14];

static uint16_t curr_keycode;
static uint16_t prev_keycode;

static keyrecord_t curr_record;
static keyrecord_t prev_record;

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

    if (index < 0 || tapped[index] || !IS_MOD_TAP(keycode)) return;

    // Send the tap keycode - QMK handles all keycode types correctly
    clear_mods();
    tap_code16(map_keycode(keycode));
    tapped[index] = true;
}

bool pre_process_modtap(uint16_t keycode, keyrecord_t *record) {
    uint8_t index = GET_INDEX((*record));

    if (index < 0) return true;

    // KEY RELEASED

    if (!record->event.pressed) {
        if (tapped[index]) {
            tapped[index] = false;
            return false; // Skip QMK processing for tapped keys
        }
        return true;
    }

    // KEY PRESSED

    // Skip QMK processing if already tapped
    if (tapped[index]) return false;

    prev_keycode = curr_keycode;
    curr_keycode = keycode;

    prev_record = curr_record;
    curr_record = *record;

    // Apply rolling logic only to mod-tap keys
    if (!IS_MOD_TAP(curr_keycode)) return true;

    // Rule 1: Mod-tap key pressed immediately after a non-mod-tap key -> tap
    if (IS_ROLLING(GET_ELAPSED(prev_record)) && !IS_MOD_TAP(prev_keycode)) {
        tap_keycode(curr_keycode, curr_record);
        return false;
    }

    // Let QMK handle normally (becomes hold if held long enough, or tap based on QMK's logic)
    return true;
}

bool process_modtap(uint16_t keycode, keyrecord_t *record) {
    uint8_t index = GET_INDEX((*record));

    if (index < 0) return true;
    if (tapped[index]) return false;

    // KEY RELEASED

    if (!record->event.pressed) return true;

    // KEY PRESSED

    // Rule 2: Non-mod-tap key pressed immediately after mod-tap key on same hand -> tap the mod-tap
    if (IS_MOD_TAP(prev_keycode) && !IS_MOD_TAP(keycode)) {

        uint16_t elapsed = GET_ELAPSED(prev_record);
        bool is_rolling = IS_ROLLING(elapsed);
        bool is_same_side = IS_SAME_SIDE((*record), prev_record);

        if (is_rolling && is_same_side) {
            tap_keycode(prev_keycode, prev_record);
        }
    }

    return true;
}