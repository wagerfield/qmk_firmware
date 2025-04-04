#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_split_3x5_2( // Letters
/* 0 */ KC_B        , KC_L      , KC_D      , KC_W      , KC_Z      ,
/* 1 */ KC_QUOTE    , KC_F      , KC_O      , KC_U      , KC_J      ,
/* 2 */ KC_N        , KC_R      , KC_T      , KC_S      , KC_G      ,
/* 4 */ KC_Y        , KC_H      , KC_A      , KC_E      , KC_I      ,
/* 5 */ KC_Q        , KC_X      , KC_M      , KC_C      , KC_V      ,
/* 6 */ KC_K        , KC_P      , KC_COMMA  , KC_MINUS  , KC_DOT    ,
/* 3 */ QK_BOOT     , KC_BSPC   ,
/* 7 */ KC_SPC      , KC_ENT
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}
