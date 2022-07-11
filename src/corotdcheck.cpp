#include "corotdcheck.h"
#include "controller.h"
#include "fifo_queue.h"
#include "libtp_c/include/msl_c/string.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/SSystem/SComponent/c_counter.h"
#include "libtp_c/include/f_op/f_op_scene_req.h"

#ifdef GCN_PLATFORM
#define ITEM_BUTTON_HELD_CHECK (!GZ_getButtonHold(GZPad::Y) || !GZ_getButtonHold(GZPad::X))
#define ITEM_BUTTON_DOWN_CHECK (GZ_getButtonPressed(GZPad::Y) || GZ_getButtonPressed(GZPad::X))
#define PAD Pad
#endif  // GCN_PLATFORM
#ifdef WII_PLATFORM
#define ITEM_BUTTON_HELD_CHECK                                                                     \
    (!GZ_getButtonHold(GZPad::B) || !GZ_getButtonHold(GZPad::DPAD_LEFT) ||                               \
     !GZ_getButtonHold(GZPad::DPAD_RIGHT) || !GZ_getButtonHold(GZPad::DPAD_DOWN))
#define ITEM_BUTTON_DOWN_CHECK                                                                     \
    (GZ_getButtonPressed(GZPad::B) || GZ_getButtonPressed(GZPad::DPAD_LEFT) ||                                 \
     GZ_getButtonPressed(GZPad::DPAD_RIGHT) || GZ_getButtonPressed(GZPad::DPAD_DOWN))
#define PAD Mote
#endif  // WII_PLATFORM

void CoroTDChecker::execute() {
    static bool sTimerStarted = false;
    static bool sGoalHit = false;
    static uint32_t sFrameCount = 0;

    // reset counters on load
    if (tp_fopScnRq.isLoading) {
        sFrameCount = 0;
        sGoalHit = false;
        sTimerStarted = false;
    }

    if (!sTimerStarted && GZ_getButtonPressed(GZPad::A) && daAlink_c__checkStageName("F_SP108")) {
        sTimerStarted = true;
    }

    if (sTimerStarted) {
        sFrameCount++;

        if (sFrameCount < 20) {
            if (!sGoalHit && ITEM_BUTTON_HELD_CHECK && ITEM_BUTTON_DOWN_CHECK) {
                char buf[20];
                if (sFrameCount < 10) {
                    tp_sprintf(buf, "%df early", 10 - sFrameCount);
                    FIFOQueue::push(buf, Queue, 0x0000FF00);
                }
                else if (sFrameCount == 10) {
                    FIFOQueue::push("got it", Queue, 0x00CC0000);
                    sGoalHit = true;
                }
                else if (sFrameCount > 10) {
                    tp_sprintf(buf, "%df late", sFrameCount - 10);
                    FIFOQueue::push(buf, Queue, 0x99000000);
                }
            }
        } else {
            sFrameCount = 0;
            sGoalHit = false;
            sTimerStarted = false;
        }
    }
}