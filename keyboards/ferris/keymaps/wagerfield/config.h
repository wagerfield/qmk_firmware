// clang-format off
// #include "quantum_keycodes.h"
#define RP2040_FLASH_GD25Q64CS
#pragma once

// Tap Hold
// https://docs.qmk.fm/tap_hold
#define PERMISSIVE_HOLD
#define TAPPING_TERM 175
#define FLOW_TAP_TERM 150

// Caps Word
// https://docs.qmk.fm/features/caps_word
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD
#define CAPS_WORD_IDLE_TIMEOUT 5000

// Keycode Aliases
// https://docs.qmk.fm/keycodes
// Layer 0: Letters

#define LCTL_KC_N LCTL_T(KC_N)
#define LOPT_KC_R LOPT_T(KC_R)
#define LCMD_KC_T LCMD_T(KC_T)
#define LSFT_KC_S LSFT_T(KC_S)
#define HYPR_KC_G HYPR_T(KC_G)

#define HYPR_KC_Y HYPR_T(KC_Y)
#define RSFT_KC_H LSFT_T(KC_H)
#define RCMD_KC_A LCMD_T(KC_A)
#define ROPT_KC_E LOPT_T(KC_E)
#define RCTL_KC_I LCTL_T(KC_I)

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
#define RSFT_LPRN LSFT_T(KC_LPRN) // (
#define RCMD_LCBR LCMD_T(KC_LCBR) // {
#define ROPT_LBRC LOPT_T(KC_LBRC) // [
#define RCTL_COLN LCTL_T(KC_COLN) // :

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

#define RSFT_F5 LSFT_T(KC_F5)
#define RCMD_F6 LCMD_T(KC_F6)
#define ROPT_F7 LOPT_T(KC_F7)
#define RCTL_F8 LCTL_T(KC_F8)

#define MDIA_PLAY KC_MPLY
#define MDIA_PREV KC_MPRV
#define MDIA_NEXT KC_MNXT

#define BWSR_BACK LCMD(KC_LBRC)
#define BWSR_FWRD LCMD(KC_RBRC)

#define PREV_TAB LCMD(LSFT(KC_LBRC))
#define NEXT_TAB LCMD(LSFT(KC_RBRC))

#define LOCK_SCRN LCTL(LCMD(KC_Q))
