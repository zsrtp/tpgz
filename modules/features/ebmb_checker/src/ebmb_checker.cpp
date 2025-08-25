#include "ebmb_checker.h"
#include "controller.h"
#include "fifo_queue.h"
#include <cstdio>
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/f_op/f_op_actor_mng.h"
#include "libtp_c/include/m_Do/m_Do_printf.h"
#include "libtp_c/include/d/d_procname.h"
#include "libtp_c/include/SSystem/SComponent/c_counter.h"

char msg_buffer[40];     // buffer for the message to be printed
u16 previous_action;     // tracks the previous action
s32 eb_frame_delta;      // tracks the active (unpaused) frames since Ending Blow started
bool ib_on;              // tracks whether or not IB are equipped
bool ib_on_last_frame;   // tracks whether or not IB was equipped on the last frame

void checkFrame(daAlink_c* link) {
    switch (link->mActionID) {
    case daAlink_c::PROC_ATN_ACTOR_WAIT:
        previous_action = daAlink_c::PROC_ATN_ACTOR_WAIT;
        break;
    case daAlink_c::PROC_CUT_DOWN:
        if (previous_action == daAlink_c::PROC_ATN_ACTOR_WAIT) {
            eb_frame_delta = 0;
        }

        ib_on = link->checkEquipHeavyBoots();

        if (g_dComIfG_gameInfo.play.mPauseFlag) {
#if DEBUG
            OSReport("game paused!\n");
#endif
        } else {
            eb_frame_delta++;
#if DEBUG
            OSReport("frame delta: %d\n", eb_frame_delta);
            OSReport("ib on: %d\n", ib_on);
            OSReport("ib on last frame: %d\n", ib_on_last_frame);
#endif
            
            if (!ib_on && ib_on_last_frame) {
                if (eb_frame_delta == 4) {
                    FIFOQueue::push("<3", Queue, 0x00CC0000);
                } else if (eb_frame_delta > 4 && eb_frame_delta <= 10) {
                    snprintf(msg_buffer, sizeof(msg_buffer), "late by %df", (eb_frame_delta - 4));
                    FIFOQueue::push(msg_buffer, Queue, 0xCC000000);
                }
            } else if (!ib_on && eb_frame_delta == 3) {
                FIFOQueue::push("did you forget to equip iron boots?", Queue, 0x00CC0000);
            }

            ib_on_last_frame = ib_on;
            
        }
        previous_action = daAlink_c::PROC_CUT_DOWN;
        break;
    default:
        break;
    }
}

KEEP_FUNC void EBMBChecker::execute() {
    daAlink_c* link = dComIfGp_getPlayer();

    if (!link) {
#if DEBUG
        OSReport("Player is not loaded\n");
#endif
        return;
    }

    checkFrame(link);
}