// clang-format off
#include QMK_KEYBOARD_H
#include "rolltap.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Letters
    [0] = LAYOUT_split_3x5_2(
        KC_B      , KC_L      , KC_D      , KC_W      , KC_Z      ,
        KC_QUOTE  , KC_F      , KC_O      , KC_U      , KC_J      ,
        LCTL_KC_N , LOPT_KC_R , LCMD_KC_T , LSFT_KC_S , HYPR_KC_G ,
        HYPR_KC_Y , RSFT_KC_H , RCMD_KC_A , ROPT_KC_E , RCTL_KC_I ,
        KC_Q      , KC_X      , KC_M      , KC_C      , KC_V      ,
        KC_K      , KC_P      , KC_COMMA  , KC_MINUS  , KC_DOT    ,
        LSFT_OSM  , LAY1_BSPC ,
        LAY2_SPC  , LAY3_ENT
    ),
    // Symbols
    [1] = LAYOUT_split_3x5_2(
        KC_ESC    , KC_AT     , KC_HASH   , KC_ASTR   , KC_GRAVE  ,
        KC_AMPR   , KC_CIRC   , KC_DOLLAR , KC_COMMA  , KC_SCLN   ,
        LCTL_TAB  , LOPT_EXLM , LCMD_EQL  , LSFT_LABK , HYPR_SLSH ,
        HYPR_PIPE , RSFT_LPRN , RCMD_LCBR , ROPT_LBRC , RCTL_COLN ,
        KC_MINUS  , KC_PLUS   , KC_QUES   , KC_RABK   , KC_BSLS   ,
        KC_TILDE  , KC_RPRN   , KC_RCBR   , KC_RBRC   , KC_PERC   ,
        KC_POUND  , KC_NO     ,
        KC_SPACE  , KC_ENTER
    ),
    // Numbers & Navigation
    [2] = LAYOUT_split_3x5_2(
        KC_ASTR   , KC_1      , KC_2      , KC_3      , KC_PLUS   ,
        MS_WHLR   , MS_WHLU   , MS_WHLD   , MS_WHLL   , KC_BSPC   ,
        LCTL_KC_0 , LOPT_KC_4 , LCMD_KC_5 , LSFT_KC_6 , HYPR_DOT  ,
        KC_LEFT   , KC_DOWN   , KC_UP     , KC_RIGHT  , KC_ENTER  ,
        KC_SLASH  , KC_7      , KC_8      , KC_9      , KC_MINUS  ,
        MS_LEFT   , MS_DOWN   , MS_UP     , MS_RGHT   , KC_SPACE  ,
        LSFT_EQL  , LCTL_MBTN ,
        KC_NO     , DB_TOGG
    ),
    // Media & Function Keys
    [3] = LAYOUT_split_3x5_2(
        KC_MCTL   , MDIA_PREV , MDIA_NEXT , MDIA_PLAY , LOCK_SCRN ,
        CAPT_SCRN , KC_F1     , KC_F2     , KC_F3     , KC_F4     ,
        LCTL_MUTE , LOPT_VOLD , LCMD_VOLU , BWSR_BACK , BWSR_FWRD ,
        CAPT_AREA , RSFT_F5   , RCMD_F6   , ROPT_F7   , RCTL_F8   ,
        KC_SLEP   , KC_BRID   , KC_BRIU   , PREV_TAB  , NEXT_TAB  ,
        CAPT_WNDW , KC_F9     , KC_F10    , KC_F11    , KC_F12    ,
        KC_LSFT   , KC_LCTL   ,
        QK_BOOT   , KC_NO
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return process_rolltap(keycode, record);
}
