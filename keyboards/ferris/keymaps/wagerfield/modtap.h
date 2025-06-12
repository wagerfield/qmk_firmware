// clang-format off

#include "action.h"
#include "quantum_keycodes.h"

#define ROLLING_TERM 150

// 0 1 2 3 4 L   R 0 1 2 3 4
// F F F F F 0   4 F F F F F
// F F F F F 1   5 F F F F F
// F F F F F 2   6 F F F F F
//       T T 3   7 T T

// 0 = Left Finger
// 1 = Right Finger
// 2 = Left Thumb
// 3 = Right Thumb
#define GET_GROUP(r) ( \
    (r.event.key.row == 3) ? 2 : \
    (r.event.key.row == 7) ? 3 : \
    (r.event.key.row <= 2) ? 0 : 1)

#define GET_INDEX(r) ( \
    IS_LFG(r) ? (r.event.key.col) : \
    IS_RFG(r) ? ((r.event.key.col) + 5) : \
    IS_LTG(r) ? ((r.event.key.col) + 10) : \
    IS_RTG(r) ? ((r.event.key.col) + 12) : -1)

#define IS_LFG(r) (GET_GROUP(r) == 0) // Left Finger Group
#define IS_RFG(r) (GET_GROUP(r) == 1) // Right Finger Group
#define IS_LTG(r) (GET_GROUP(r) == 2) // Left Thumb Group
#define IS_RTG(r) (GET_GROUP(r) == 3) // Right Thumb Group

#define IS_LHR(r) (r.event.key.row == 1) // Left Home Row
#define IS_RHR(r) (r.event.key.row == 5) // Right Home Row

#define IS_HOME_ROW(r) (IS_LHR(r) || IS_RHR(r))

#define IS_CAG(k) ((k) & (QK_LCTL|QK_LALT|QK_LGUI))
#define IS_SFT(k) ((k) & (QK_LSFT|QK_RSFT))

#define IS_MOD_TAP(k) (IS_QK_MOD_TAP(k))
#define IS_MOD_CAG(k) (IS_MOD_TAP(k) && IS_CAG(k))

#define GET_ELAPSED(r) timer_elapsed(r.event.time)
#define IS_ROLLING(elapsed) (elapsed < ROLLING_TERM)

/**
 * @brief Check if the current keyrecord is on the home row and the previous keyrecord is not on the home row
 *
 * @param curr Pointer to the current keyrecord
 * @param prev Pointer to the previous keyrecord
 * @return true if the current keyrecord is on the home row and the previous keyrecord is not on the home row, false otherwise
 */
#define IS_HOME_ROLL(curr, prev) (IS_HOME_ROW(curr) && !IS_HOME_ROW(prev))

/**
 * @brief Check if the current keyrecord is on the home row and same side of the keyboard as the previous keyrecord
 *
 * @param curr Pointer to the current keyrecord
 * @param prev Pointer to the previous keyrecord
 * @return true if the current keyrecord is on the home row and same side of the keyboard as the previous keyrecord, false otherwise
 */
#define IS_SAME_SIDE(curr, prev) ((IS_LHR(curr) && IS_LFG(prev)) || (IS_RHR(curr) && IS_RFG(prev)))

bool pre_process_modtap(uint16_t keycode, keyrecord_t *record);
bool process_modtap(uint16_t keycode, keyrecord_t *record);