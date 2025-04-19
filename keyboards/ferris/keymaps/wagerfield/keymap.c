// clang-format off
#include QMK_KEYBOARD_H
#include "caps_word.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Letters
    [0] = LAYOUT_split_3x5_2(
        KC_B      , KC_L      , KC_D      , KC_W      , KC_Z      ,
        KC_QUOTE  , KC_F      , KC_O      , KC_U      , KC_J      ,
        LOPT_KC_N , LCTL_KC_R , LCMD_KC_T , LSFT_KC_S , HYPR_KC_G ,
        HYPR_KC_Y , RSFT_KC_H , RCMD_KC_A , RCTL_KC_E , ROPT_KC_I ,
        KC_Q      , KC_X      , KC_M      , KC_C      , KC_V      ,
        KC_K      , KC_P      , KC_COMMA  , KC_MINUS  , KC_DOT    ,
        LSFT_OSM  , LAY1_BSPC ,
        LAY2_SPC  , LAY3_ENT
    ),
    // Symbols
    [1] = LAYOUT_split_3x5_2(
        KC_ESC    , KC_AT     , KC_HASH   , KC_ASTR   , KC_GRAVE  ,
        KC_AMPR   , KC_CIRC   , KC_DOLLAR , KC_COMMA  , KC_SCLN   ,
        LOPT_TAB  , LCTL_EXLM , LCMD_EQL  , LSFT_LABK , HYPR_SLSH ,
        HYPR_PIPE , RSFT_LPRN , RCMD_LCBR , RCTL_LBRC , ROPT_COLN ,
        KC_MINUS  , KC_PLUS   , KC_QUES   , KC_RABK   , KC_BSLS   ,
        KC_TILDE  , KC_RPRN   , KC_RCBR   , KC_RBRC   , KC_PERC   ,
        KC_POUND  , KC_NO     ,
        KC_SPACE  , KC_ENTER
    ),
    // Numbers & Navigation
    [2] = LAYOUT_split_3x5_2(
        KC_ASTR   , KC_1      , KC_2      , KC_3      , KC_PLUS   ,
        MS_WHLR   , MS_WHLU   , MS_WHLD   , MS_WHLL   , KC_BSPC   ,
        LOPT_KC_0 , LCTL_KC_4 , LCMD_KC_5 , LSFT_KC_6 , HYPR_DOT  ,
        KC_LEFT   , KC_DOWN   , KC_UP     , KC_RIGHT  , KC_ENTER  ,
        KC_SLASH  , KC_7      , KC_8      , KC_9      , KC_MINUS  ,
        MS_LEFT   , MS_DOWN   , MS_UP     , MS_RGHT   , KC_SPACE  ,
        LSFT_EQL  , LCTL_MBTN ,
        KC_NO     , DB_TOGG
    ),
    // Media & Function Keys
    [3] = LAYOUT_split_3x5_2(
        KC_MCTL   , MDIA_PREV , MDIA_NEXT , MDIA_PLAY , LOCK_SCRN ,
        CAPT_AREA , KC_F1     , KC_F2     , KC_F3     , KC_F4     ,
        LOPT_MUTE , LCTL_VOLD , LCMD_VOLU , BWSR_BACK , BWSR_FWRD ,
        CAPT_WNDW , RSFT_F5   , RCMD_F6   , RCTL_F7   , ROPT_F8   ,
        KC_SLEP   , KC_BRID   , KC_BRIU   , PREV_TAB  , NEXT_TAB  ,
        CAPT_SCRN , KC_F9     , KC_F10    , KC_F11    , KC_F12    ,
        KC_LSFT   , KC_LCTL   ,
        QK_BOOT   , KC_NO
    )
};

static uint16_t curr_time;
static uint16_t prev_time;

static uint8_t curr_group;
static uint8_t prev_group;

static uint8_t curr_mods;
static uint8_t prev_mods;

// static char curr_char;
// static char prev_char;

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

// static char get_char(uint16_t keycode) {
//     switch (keycode & 0xFF) {
//         case KC_A ... KC_Z: return 'A' + (keycode - KC_A);
//         case KC_SPACE: return '_';
//         default: return '?';
//     }
// }

static bool tap(uint16_t keycode) {
    bool caps = is_caps_word_on();
    // dprintf("TAP [%c] %s\n", get_char(keycode), caps ? "CAPS" : "");
    if (caps) register_mods(MOD_LSFT);
    tap_code16(keycode);
    if (caps) unregister_mods(MOD_LSFT);
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        prev_time = curr_time;
        // prev_char = curr_char;
        prev_mods = curr_mods;
        prev_group = curr_group;

        curr_time = record->event.time;
        // curr_char = get_char(keycode);
        curr_mods = QK_MOD_TAP_GET_MODS(keycode);
        curr_group = get_group(record);

        uint16_t elapsed = timer_elapsed(prev_time);

        bool is_rolling = elapsed < 250;
        bool same_group = curr_group == prev_group;
        bool both_mods = curr_mods && prev_mods;

        // if (curr_char == '_') dprintf("\n");
        // else if (prev_char != '_') {
        //     dprintf("[%c:%u] -> [%c:%u] %3ums %s\n",
        //         prev_char, prev_group,
        //         curr_char, curr_group,
        //         elapsed, is_rolling ? "-> ROLL" : ""
        //     );
        // }

        if (is_rolling && (!same_group || !both_mods)) {
            return tap(keycode);
        }

        switch (keycode) {
            case CAPT_WNDW:
                tap(CAPT_AREA);
                wait_ms(50);
                tap(KC_SPACE);
                return false;
        }

        if (record->tap.count) {
            switch (keycode) {
                case LCTL_EXLM: return tap(KC_EXLM);
                case LSFT_LABK: return tap(KC_LABK);
                case HYPR_PIPE: return tap(KC_PIPE);
                case RSFT_LPRN: return tap(KC_LPRN);
                case RCMD_LCBR: return tap(KC_LCBR);
                case ROPT_COLN: return tap(KC_COLN);
            }
        }
    }

    return true;
}
