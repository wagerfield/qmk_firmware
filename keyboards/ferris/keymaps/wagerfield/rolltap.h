// clang-format off
#pragma once

#include "action.h"
#include "quantum_keycodes.h"

#define EVENTS_SIZE 14
#define MATRIX_HALF MATRIX_ROWS / 2

// Sides

#define LHS 'L'
#define RHS 'R'

// Fingers

#define PINKIE 'P'
#define RING   'R'
#define MIDDLE 'M'
#define INDEX  'I'
#define THUMB  'T'


// Timing Configuration

#define MRT_ROLLING_TERM 200
#define MRT_TAPPING_TERM 150

// Bit Positions

#define MRT_TAP_CODE_BITS  0 // Bits 00-07: Basic Keycode (8 bits)
#define MRT_HOLD_MODS_BITS 8 // Bits 08-11: Hold Mods (4 bits)
#define MRT_TAP_MODS_BITS 12 // Bits 12-13: Tap Mods (2 bits)

// Bit Masks

#define MRT_TAP_CODE_MASK  0x00FF // 0000 0000 1111 1111
#define MRT_HOLD_MODS_MASK 0x0F00 // 0000 1111 0000 0000
#define MRT_TAP_MODS_MASK  0x3000 // 0011 0000 0000 0000
#define MRT_MAGIC_MASK     0xC000 // 1100 0000 0000 0000
#define MRT_MAGIC_VALUE    0x8000 // 1000 0000 0000 0000 (QMK user space)

// Map Tap Mods Macro

#define MRT_MAP_TAP_MODS(keycode) ( \
    ((QK_MODS_GET_MODS(keycode) & MOD_LSFT) ? 0x1 : 0) | \
    ((QK_MODS_GET_MODS(keycode) & MOD_LALT) ? 0x2 : 0) \
)

// Mod Roll Tap Macro

#define MRT(modifier, keycode) (uint16_t) ( \
    (QK_MODS_GET_BASIC_KEYCODE(keycode) << MRT_TAP_CODE_BITS) | \
    (MRT_MAP_TAP_MODS(keycode) << MRT_TAP_MODS_BITS) | \
    ((modifier) << MRT_HOLD_MODS_BITS) | \
    MRT_MAGIC_VALUE \
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

#define MRT_GET_TAP_CODE(keycode) (((keycode) & MRT_TAP_CODE_MASK) >> MRT_TAP_CODE_BITS)
#define MRT_GET_TAP_MODS(keycode) ((((keycode) & MRT_TAP_MODS_MASK) >> MRT_TAP_MODS_BITS) << 1)
#define MRT_GET_HOLD_MODS(keycode) (((keycode) & MRT_HOLD_MODS_MASK) >> MRT_HOLD_MODS_BITS)

// Function Declarations

bool process_rolltap(uint16_t keycode, keyrecord_t *record);
