// clang-format off
#pragma once

#include "action.h"

// 0 1 2 3 4   5 6 7 8 9
// F F F F F   F F F F F
// F F F F F   F F F F F
// F F F F F   F F F F F
//       T T   T T
//      10 11 12 13

#define EVENTS_SIZE 14

// 0000 0000 1111 1111 -> Tap Code
// 0000 0011 0000 0000 -> Tap Mods (LALT, LSFT)
// 0011 1100 0000 0000 -> Hold Data (Mods or Layer)
// 1100 0000 0000 0000 -> Roll Tap Base Value

#define LRT_BASE 0x8000 // 1000 0000 0000 0000
#define MRT_BASE 0xC000 // 1100 0000 0000 0000

#define RT(base, data, kc) ((base) | (((data) & 0xF) << 10) | (((kc) & 0x600) >> 1) | ((kc) & 0xFF))
#define RT_GET_TAP_CODE(kc) ((((kc) & 0x300) << 1) | ((kc) & 0xFF))
#define RT_GET_HOLD_DATA(kc) (((kc) >> 10) & 0xF)
#define RT_GET_BASE(kc) ((kc) & 0xC000)

#define LRT(layer, kc) (RT(LRT_BASE, layer, kc))
#define MRT(mods, kc) (RT(MRT_BASE, mods, kc))

#define IS_RT(kc) ((kc) & LRT_BASE)
#define IS_LRT(kc) (RT_GET_BASE(kc) == LRT_BASE)
#define IS_MRT(kc) (RT_GET_BASE(kc) == MRT_BASE)

#define LCTL_RT(kc) MRT(MOD_LCTL, kc)
#define LSFT_RT(kc) MRT(MOD_LSFT, kc)
#define LOPT_RT(kc) MRT(MOD_LALT, kc)
#define LCMD_RT(kc) MRT(MOD_LGUI, kc)

#define HYPR_RT(kc) MRT(MOD_HYPR, kc)

#define RCTL_RT(kc) MRT(MOD_LCTL, kc)
#define RSFT_RT(kc) MRT(MOD_LSFT, kc)
#define ROPT_RT(kc) MRT(MOD_LALT, kc)
#define RCMD_RT(kc) MRT(MOD_LGUI, kc)

void rolltap_init(void);
void rolltap_scan(void);
bool process_rolltap(uint16_t keycode, keyrecord_t *record);
