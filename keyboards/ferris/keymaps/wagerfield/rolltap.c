// clang-format off
#include "rolltap.h"
#include "action_util.h"
#include "debug.h"

bool process_rolltap(uint16_t keycode, keyrecord_t *record) {
    if (!IS_MRT(keycode)) return true;

    if (record->event.pressed) {
        uint8_t code = MRT_GET_KEYCODE(keycode);
        uint8_t mods = 0;

        bool shifted = MRT_GET_SHIFTED(keycode);
        bool altered = MRT_GET_ALTERED(keycode);

        if (shifted) mods |= MOD_LSFT;
        if (altered) mods |= MOD_LALT;

        dprintf("[%c] C:%u M:%u S:%u A:%u\n", get_keycode_char(code), code, mods, shifted, altered);

        set_mods(mods);
        tap_code(code);
        unregister_mods(mods);
    }

    return false;
}
