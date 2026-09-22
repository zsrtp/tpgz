#ifdef WII_PLATFORM

#include <cstdio>
#include "slash_checker.h"
#include "controller.h"
#include "fifo_queue.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/SSystem/SComponent/c_counter.h"
#include "libtp_c/include/f_op/f_op_scene_req.h"
#include "libtp_c/include/m_Do/m_Re_controller_pad.h"

#define ITEM_BUTTON_HELD_CHECK (!GZ_getButtonHold(GZPad::A) || !GZ_getButtonHold(GZPad::MINUS))
#define ITEM_BUTTON_DOWN_CHECK (GZ_getButtonPressed(GZPad::A) || GZ_getButtonPressed(GZPad::MINUS))
#define PAD Pad

KEEP_FUNC void SlashChecker::execute() {
    static bool sTimerStarted = false;
    static bool didFirstSwing = false;
    static uint32_t sFrameCount = 0;

    if (dComIfGp_getPlayer() == nullptr) {
        return;
    }

    // reset counters on load
    if (fopScnRq.isLoading) {
        sFrameCount = 0;
        sTimerStarted = false;
        didFirstSwing = false;
    }

    if (ITEM_BUTTON_HELD_CHECK && ITEM_BUTTON_DOWN_CHECK && dComIfGp_getPlayer()->mActionID != 33) {
        sTimerStarted = true;
        sFrameCount = 0;
        didFirstSwing = false;
    }

    uint32_t correctFrames = 7;

    if (sTimerStarted) {
        sFrameCount++;

        if (sFrameCount < 15) {
            if (mPad.m_remAcc.m_swing > 0) { // slash

                if (!didFirstSwing) {
                    FIFOQueue::push("<", Queue);
                    didFirstSwing = true;
                }

                char buf[20];
                if (sFrameCount < correctFrames) {
                    snprintf(buf, sizeof(buf), "%df early", correctFrames - sFrameCount);
                    FIFOQueue::push(buf, Queue, 0x0000FF00);
                } else if (sFrameCount == correctFrames) {
                    FIFOQueue::push("got it", Queue, 0x00CC0000);
                } else if (sFrameCount > correctFrames) {
                    if (sFrameCount - correctFrames == 1) {
                        FIFOQueue::push("1f late", Queue, 0xFF757500);
                    } else {
                        snprintf(buf, sizeof(buf), "%df late", sFrameCount - correctFrames);
                        FIFOQueue::push(buf, Queue, 0x99000000);
                    }
                }
            }
        } else {
            sFrameCount = 0;
            sTimerStarted = false;
            if (didFirstSwing) {
                FIFOQueue::push(">", Queue);
                didFirstSwing = false;
            }
            
        }
    }
}

#endif