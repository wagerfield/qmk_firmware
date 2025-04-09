// clang-format off
#include <quantum_keycodes.h>
#include "helpers.h"

char get_keycode_char(uint16_t keycode) {
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