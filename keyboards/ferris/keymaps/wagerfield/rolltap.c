// clang-format off
#include "action_util.h"
#include "debug.h"
#include "rolltap.h"
#include "helpers.h"

bool process_rolltap(uint16_t keycode, keyrecord_t *record) {
    if (!IS_MRT(keycode)) return true;

    if (record->event.pressed) {
        uint8_t code = MRT_GET_KEYCODE(keycode);
        uint8_t mods = MRT_GET_MODS(keycode);
        uint8_t state = MRT_GET_STATE(keycode);

        dprintf("%s [%c] C:%u S:%u M:%u\n",
            to_binary_string(keycode),
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
