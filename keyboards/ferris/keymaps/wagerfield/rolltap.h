// clang-format off
#pragma once

#include "action.h"
#include "quantum_keycodes.h"

#define MATRIX_HALF MATRIX_ROWS / 2

// Timing Configuration

#define MRT_TAPPING_TERM  200
#define MRT_ROLLING_TERM  200
#define MRT_MODIFIER_TERM 120

// Bit Positions

#define MRT_KEYCODE_BITS  0 // Bits 00-07: Basic Keycode (8 bits)
#define MRT_MODIFIER_BITS 8 // Bits 08-11: Modifiers (4 bits)
#define MRT_STATE_BITS   12 // Bits 12-13: State (2 bits)

// Bit Masks

#define MRT_KEYCODE_MASK  0x00FF // 0000 0000 1111 1111
#define MRT_MODIFIER_MASK 0x0F00 // 0000 1111 0000 0000
#define MRT_STATE_MASK    0x3000 // 0011 0000 0000 0000
#define MRT_MAGIC_MASK    0xC000 // 1100 0000 0000 0000
#define MRT_MAGIC_VALUE   0x8000 // 1000 0000 0000 0000 (QMK user space)

// State Macro

#define MRT_EXTRACT_STATE(keycode) ( \
    ((QK_MODS_GET_MODS(keycode) & MOD_LSFT) ? 0x1 : 0) | \
    ((QK_MODS_GET_MODS(keycode) & MOD_LALT) ? 0x2 : 0) \
)

// Mod Roll Tap Macro

#define MRT(modifier, keycode) (uint16_t) ( \
    (QK_MODS_GET_BASIC_KEYCODE(keycode) << MRT_KEYCODE_BITS) | /* bits 00-07: basic keycode */ \
    (MRT_EXTRACT_STATE(keycode) << MRT_STATE_BITS)               | /* bits 12-13: state         */ \
    ((modifier) << MRT_MODIFIER_BITS)                            | /* bits 08-11: modifiers     */ \
    MRT_MAGIC_VALUE                                            /* bits 14-15: magic value   */ \
)

// Modifier Macros

#define LCTL_RT(keycode) MRT(MOD_LCTL, keycode) // 0x01
#define LSFT_RT(keycode) MRT(MOD_LSFT, keycode) // 0x02
#define LOPT_RT(keycode) MRT(MOD_LALT, keycode) // 0x04
#define LCMD_RT(keycode) MRT(MOD_LGUI, keycode) // 0x08

#define RCTL_RT(keycode) LCTL_RT(keycode)
#define RSFT_RT(keycode) LSFT_RT(keycode)
#define ROPT_RT(keycode) LOPT_RT(keycode)
#define RCMD_RT(keycode) LCMD_RT(keycode)

#define HYPR_RT(keycode) MRT(MOD_HYPR, keycode) // 0x0F

// Decoder Macros

#define IS_MRT(keycode) (((keycode) & MRT_MAGIC_MASK) == MRT_MAGIC_VALUE)

#define MRT_GET_KEYCODE(keycode) (((keycode) & MRT_KEYCODE_MASK) >> MRT_KEYCODE_BITS)
#define MRT_GET_STATE(keycode) ((((keycode) & MRT_STATE_MASK) >> MRT_STATE_BITS) << 1)
#define MRT_GET_MODS(keycode) (((keycode) & MRT_MODIFIER_MASK) >> MRT_MODIFIER_BITS)

// Function Declarations

bool process_rolltap(uint16_t keycode, keyrecord_t *record);

static inline char* to_binary_string(uint16_t value) {
    static char str[20]; // 16 bits + 3 spaces + null terminator
    char *p = str;

    for (int i = 15; i >= 0; i--) {
        *p++ = ((value >> i) & 1) ? '1' : '0';
        if (i % 4 == 0 && i != 0) *p++ = ' ';
    }
    *p = '\0';
    return str;
}

static inline char get_keycode_char(uint16_t keycode) {
    switch (keycode) {
        // Letters
        case KC_A ... KC_Z: return 'A' + (keycode - KC_A);

        // Numbers
        case KC_1 ... KC_0: return '1' + (keycode - KC_1);

        // Symbols
        case KC_GRV:  return '`';
        case KC_MINS: return '-';
        case KC_EQL:  return '=';
        case KC_LBRC: return '[';
        case KC_RBRC: return ']';
        case KC_BSLS: return '\\';
        case KC_SCLN: return ';';
        case KC_QUOT: return '\'';
        case KC_COMM: return ',';
        case KC_DOT:  return '.';
        case KC_SLSH: return '/';

        // Shifted Symbols
        case KC_TILD: return '~';
        case KC_EXLM: return '!';
        case KC_AT:   return '@';
        case KC_HASH: return '#';
        case KC_DLR:  return '$';
        case KC_PERC: return '%';
        case KC_CIRC: return '^';
        case KC_AMPR: return '&';
        case KC_ASTR: return '*';
        case KC_LPRN: return '(';
        case KC_RPRN: return ')';
        case KC_UNDS: return '_';
        case KC_PLUS: return '+';
        case KC_LCBR: return '{';
        case KC_RCBR: return '}';
        case KC_PIPE: return '|';
        case KC_COLN: return ':';
        case KC_DQUO: return '"';
        case KC_LABK: return '<';
        case KC_RABK: return '>';
        case KC_QUES: return '?';

        default: return '?';
    }
}
