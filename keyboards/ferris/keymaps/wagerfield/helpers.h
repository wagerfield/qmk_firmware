// clang-format off
#pragma once

#include <stdint.h>

#define BINARY_PATTERN_INT8 "%c%c%c%c %c%c%c%c "
#define BYTE_TO_BINARY_INT8(i)    \
    (((i) & 0x80) ? '1' : '0'), \
    (((i) & 0x40) ? '1' : '0'), \
    (((i) & 0x20) ? '1' : '0'), \
    (((i) & 0x10) ? '1' : '0'), \
    (((i) & 0x08) ? '1' : '0'), \
    (((i) & 0x04) ? '1' : '0'), \
    (((i) & 0x02) ? '1' : '0'), \
    (((i) & 0x01) ? '1' : '0')

#define BINARY_PATTERN_INT16 BINARY_PATTERN_INT8 BINARY_PATTERN_INT8
#define BYTE_TO_BINARY_INT16(i)    \
    BYTE_TO_BINARY_INT8((i) >> 8), \
    BYTE_TO_BINARY_INT8(i)

char get_keycode_char(uint16_t keycode);