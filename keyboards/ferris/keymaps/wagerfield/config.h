// clang-format off
#define RP2040_FLASH_GD25Q64CS
#pragma once

// Tap Hold
// https://docs.qmk.fm/tap_hold
#define QUICK_TAP_TERM 0
#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY

// Caps Word
// https://docs.qmk.fm/features/caps_word
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD
#define CAPS_WORD_IDLE_TIMEOUT 5000 // Time in milliseconds before caps word turns off

// Mouse Keys
// https://docs.qmk.fm/features/mouse_keys#accelerated-mode
// #define MOUSEKEY_DELAY 100       // Delay between pressing a movement key and cursor movement (default: 10)
// #define MOUSEKEY_INTERVAL 16     // Time between cursor movements in milliseconds (default: 20)
// #define MOUSEKEY_MOVE_DELTA 8    // Step size (default: 8)
// #define MOUSEKEY_MAX_SPEED 20    // Maximum cursor speed at which acceleration stops (default: 10)
// #define MOUSEKEY_TIME_TO_MAX 100 // Time until maximum cursor speed is reached (default: 30)

// #define MOUSEKEY_WHEEL_DELAY 10        // Delay between pressing a wheel key and wheel movement (default: 10)
// #define MOUSEKEY_WHEEL_INTERVAL 50     // Time between wheel movements (default: 80)
// #define MOUSEKEY_WHEEL_DELTA 0.1       // Wheel movement step size (default: 1)
// #define MOUSEKEY_WHEEL_MAX_SPEED 10    // Maximum number of scroll steps per scroll action (default: 8)
// #define MOUSEKEY_WHEEL_TIME_TO_MAX 100 // Time until maximum scroll speed is reached (default: 40)

// Keycode Aliases
// https://docs.qmk.fm/keycodes
// Layer 0: Letters

#define LCTL_KC_N LCTL_T(KC_N)
#define LOPT_KC_R LOPT_T(KC_R)
#define LCMD_KC_T LCMD_T(KC_T)
#define LSFT_KC_S LSFT_T(KC_S)
#define HYPR_KC_G HYPR_T(KC_G)

#define HYPR_KC_Y HYPR_T(KC_Y)
#define RSFT_KC_H RSFT_T(KC_H)
#define RCMD_KC_A RCMD_T(KC_A)
#define ROPT_KC_E ROPT_T(KC_E)
#define RCTL_KC_I RCTL_T(KC_I)

#define LSFT_OSM  OSM(MOD_LSFT)
#define LAY1_BSPC LT(1, KC_BSPC)
#define LAY2_SPC  LT(2, KC_SPC)
#define LAY3_ENT  LT(3, KC_ENT)

// Layer 1: Symbols

#define KC_PND A(KC_3)  // £
#define KC_POUND KC_PND // £

#define LCTL_TAB  LCTL_T(KC_TAB)
#define LOPT_EXLM LOPT_T(KC_EXLM) // !
#define LCMD_EQL  LCMD_T(KC_EQL)  // =
#define LSFT_LABK LSFT_T(KC_LABK) // <
#define HYPR_SLSH HYPR_T(KC_SLSH) // /

#define HYPR_PIPE HYPR_T(KC_PIPE) // |
#define RSFT_LPRN RSFT_T(KC_LPRN) // (
#define RCMD_LCBR RCMD_T(KC_LCBR) // {
#define ROPT_LBRC ROPT_T(KC_LBRC) // [
#define RCTL_COLN RCTL_T(KC_COLN) // :

// Layer 2: Numbers & Navigation

#define LCTL_KC_0 LCTL_T(KC_0)
#define LOPT_KC_4 LOPT_T(KC_4)
#define LCMD_KC_5 LCMD_T(KC_5)
#define LSFT_KC_6 LSFT_T(KC_6)
#define HYPR_DOT  HYPR_T(KC_DOT)

#define LCTL_MBTN LCTL_T(MS_BTN1)
#define LSFT_EQL  LSFT_T(KC_EQL)

// Layer 3: Media & Function Keys

#define CAPT_SCRN LCMD(LSFT(KC_3))
#define CAPT_AREA LCMD(LSFT(KC_4))
#define CAPT_WNDW QK_MACRO_0

#define LCTL_MUTE LCTL_T(KC_MUTE)
#define LOPT_VOLD LOPT_T(KC_VOLD)
#define LCMD_VOLU LCMD_T(KC_VOLU)

#define RSFT_F5 RSFT_T(KC_F5)
#define RCMD_F6 RCMD_T(KC_F6)
#define ROPT_F7 ROPT_T(KC_F7)
#define RCTL_F8 RCTL_T(KC_F8)

#define MDIA_PLAY KC_MPLY
#define MDIA_PREV KC_MPRV
#define MDIA_NEXT KC_MNXT

#define BWSR_BACK LCMD(KC_LBRC)
#define BWSR_FWRD LCMD(KC_RBRC)

#define PREV_TAB LCMD(LSFT(KC_LBRC))
#define NEXT_TAB LCMD(LSFT(KC_RBRC))

#define LOCK_SCRN LCTL(LCMD(KC_Q))
