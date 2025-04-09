#include "action.h"
#include "debug.h"

bool process_rolltap(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        dprintf("rolltap.c: %u\n", keycode);
    }
    return true;
}
