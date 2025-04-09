// clang-format off
#include "action_util.h"
#include "debug.h"

#include "helpers.h"
#include "rolltap.h"

// static char get_side(keyrecord_t *record) {
//     uint8_t row = record->event.key.row;
//     return row < MATRIX_HALF ? 'L' : 'R';
// }

// static bool is_thumb(keyrecord_t *record) {
//     uint8_t row = record->event.key.row;
//     return row == 3 || row == 7;
// }

bool process_rolltap(uint16_t keycode, keyrecord_t *record) {
    if (!IS_MRT(keycode)) return true;

    if (record->event.pressed) {
        uint8_t mods = MRT_GET_MODS(keycode);
        uint8_t code = MRT_GET_KEYCODE(keycode);
        uint8_t state = MRT_GET_STATE(keycode);

        dprintf(BINARY_PATTERN_INT16 "[%c] C:%u S:%u M:%u\n",
            BYTE_TO_BINARY_INT16(keycode),
            get_keycode_char(code),
            code,
            state,
            mods
        );

        set_mods(state);
        tap_code(code);
        unregister_mods(state);
    }

    return false;
}
