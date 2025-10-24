// clang-format off
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Letters (Graphite Layout)
    // https://github.com/rdavison/graphite-layout#readme
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
        KC_TILDE  , KC_CIRC   , KC_DOLLAR , KC_COMMA  , KC_SCLN   ,
        LCTL_TAB  , LOPT_EXLM , LCMD_EQL  , LSFT_LABK , HYPR_SLSH ,
        HYPR_PIPE , RSFT_LPRN , RCMD_LCBR , ROPT_LBRC , RCTL_COLN ,
        KC_MINUS  , KC_PLUS   , KC_QUES   , KC_RABK   , KC_BSLS   ,
        KC_AMPR   , KC_RPRN   , KC_RCBR   , KC_RBRC   , KC_PERC   ,
        KC_POUND  , KC_NO     ,
        RCMD_SPC  , RSFT_ENT
    ),
    // Numbers & Navigation
    [2] = LAYOUT_split_3x5_2(
        KC_ASTR   , KC_1      , KC_2      , KC_3      , KC_PLUS   ,
        BWSR_BACK , PREV_TAB  , NEXT_TAB  , BWSR_FWRD , KC_TILDE  ,
        LCTL_KC_0 , LOPT_KC_4 , LCMD_KC_5 , LSFT_KC_6 , HYPR_EQL  ,
        KC_LEFT   , KC_DOWN   , KC_UP     , KC_RIGHT  , KC_COLON  ,
        KC_SLASH  , KC_7      , KC_8      , KC_9      , KC_MINUS  ,
        KC_PERC   , KC_CIRC   , KC_DOLLAR , KC_COMMA  , KC_DOT    ,
        LSFT_PND  , LCTL_DEL  ,
        KC_NO     , DB_TOGG
    ),
    // Media & Function Keys
    [3] = LAYOUT_split_3x5_2(
        KC_MCTL   , KC_MUTE   , KC_VOLD   , KC_VOLU   , MDIA_PREV ,
        CAPT_AREA , KC_F1     , KC_F2     , KC_F3     , KC_F4     ,
        BWSR_BACK , BWSR_FWRD , PREV_TAB  , NEXT_TAB  , MDIA_PLAY ,
        CAPT_WNDW , RSFT_F5   , RCMD_F6   , ROPT_F7   , RCTL_F8   ,
        LOCK_SCRN , KC_SLEP   , KC_BRID   , KC_BRIU   , MDIA_NEXT ,
        CAPT_SCRN , KC_F9     , KC_F10    , KC_F11    , KC_F12    ,
        KC_LSFT   , KC_DICT   ,
        QK_BOOT   , KC_NO
    )
};

static bool tap(uint16_t keycode) {
    tap_code16(keycode);
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) return true;

    switch (keycode) {
        case CAPT_WNDW:
            SEND_STRING(SS_LCMD(SS_LSFT("4")) SS_DELAY(100) SS_TAP(X_SPACE));
            return false;
    }

    if (!record->tap.count) return true;

    switch (keycode) {
        case LOPT_EXLM: return tap(KC_EXLM);
        case LSFT_LABK: return tap(KC_LABK);
        case HYPR_PIPE: return tap(KC_PIPE);
        case RSFT_LPRN: return tap(KC_LPRN);
        case RCMD_LCBR: return tap(KC_LCBR);
        case RCTL_COLN: return tap(KC_COLN);
    }

    return true;
}

// https://docs.qmk.fm/tap_hold#flow-tap
bool is_flow_tap_key(uint16_t keycode) {
    if (get_mods()) return false;

    switch (get_tap_keycode(keycode)) {
        case KC_A ... KC_Z:
        case KC_SPACE:
        case KC_QUOTE:
        case KC_COMMA:
        case KC_MINUS:
        case KC_DOT:
            return true;
    }

    return false;
}

uint16_t get_flow_tap_term(uint16_t curr_keycode, keyrecord_t* record, uint16_t prev_keycode) {
    if (!is_flow_tap_key(curr_keycode)) return 0;
    if (!is_flow_tap_key(prev_keycode)) return 0;

    bool is_curr_space = curr_keycode == LAY2_SPC;
    bool is_prev_space = prev_keycode == LAY2_SPC;

    if (is_curr_space && is_prev_space) return 0;

    switch (curr_keycode) {
        case LCTL_KC_N:
        case LOPT_KC_R:
        case ROPT_KC_E:
        case RCTL_KC_I:
            return 175; // 175ms
        case LCMD_KC_T:
        case LSFT_KC_S:
        case RSFT_KC_H:
        case RCMD_KC_A:
            return 125; // 125ms
        case LAY2_SPC:
            return 100; // 100ms
        default:
            return 150; // 150ms
    }
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_OSM:
            return 250; // 250ms
        default:
            return 200; // 200ms
    }
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LOPT_KC_R:
        case ROPT_KC_E:
            return false;
        default:
            return true;
    }
}
