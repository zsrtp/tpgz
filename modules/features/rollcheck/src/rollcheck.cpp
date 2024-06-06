#include "rollcheck.h"
#include <cstdio>
#include "controller.h"
#include "fifo_queue.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/d/menu/d_menu_window.h"
#include "libtp_c/include/SSystem/SComponent/c_counter.h"
#include "libtp_c/include/m_Do/m_Do_printf.h"

s32 roll_start_frame;       // The frame the roll started on. Dynamically updated based on game pausing
u8 current_frame_delta;     // The current frame delta between the current frame and the roll start frame.
u8 roll_end_frame;          // The frame the roll ends on. Dynamically updated based on the previous action
u8 roll_early_check_frame;  // The earliest frame the early check should be performed on. Dynamically updated based on the previous action.
u8 roll_late_check_frame;   // The latest frame the late check should be performed on. Dynamically updated based on the previous action.
u16 previous_action;        // Tracks the previous action for adjusting the frame timing window, because some actions like land dive cut the beginning of the roll short
bool game_paused;           // Whether the game is paused or not. Used to determine if the roll start frame should be incremented.
char msg_buffer[20];        // Buffer for the message to be printed.

#if DEBUG
KEEP_FUNC void RollIndicator_debug() {
    OSReport("roll start frame: %d\n", roll_start_frame);
    OSReport("current frame: %d\n", cCt_getFrameCount());
    OSReport("current frame delta: %d\n", current_frame_delta);
}
#endif

KEEP_FUNC void RollIndicator::execute() {
    // Only run the flow if the game is not in an event, 
    // the player is in human form,
    // and the player pointer is valid
    if (dComIfGp_getEvent().mHalt == false && dComIfGs_getTransformStatus() == STATUS_HUMAN && dComIfGp_getPlayer()) {
        #if DEBUG
        OSReport("-------\n");
        OSReport("running!\n");
        OSReport("current action: %d\n", dComIfGp_getPlayer()->mActionID);
        #endif

        switch (dComIfGp_getPlayer()->mActionID) {
        case daAlink_c::PROC_FRONT_ROLL:
        // this may need to be change to a switch in the future
        // if more actions are found that cut the roll short
            if (previous_action == daAlink_c::PROC_DIVE_JUMP) {
                roll_end_frame = 13;
                roll_early_check_frame = 7;
                roll_late_check_frame = 18;
            } else {
                roll_end_frame = 18;
                roll_early_check_frame = 12;
                roll_late_check_frame = 23;
            }

            #if DEBUG
            OSReport("target roll end frame: %d\n", roll_end_frame);
            OSReport("front roll!\n");
            #endif

            /* Got it check */
            if (current_frame_delta == roll_end_frame) {
                #if DEBUG
                OSReport("exactly %d frames!\n", roll_end_frame);
                #endif

                if (g_dComIfG_gameInfo.play.mPauseFlag) {
                    #if DEBUG
                    OSReport("game paused, incrementing start frame!\n");
                    #endif

                    roll_start_frame += 1;
                    current_frame_delta = cCt_getFrameCount() - roll_start_frame;
                    game_paused = true;
                } else {
                    if (game_paused) {
                        game_paused = false;
                        roll_start_frame++;
                    }

                    if (GZ_getButtonPressed(A) && !GZ_getButtonHold(A)) {
                        FIFOQueue::push("<3", Queue, 0x00CC0000);
                        current_frame_delta = 0;
                    } else {
                        current_frame_delta = cCt_getFrameCount() - roll_start_frame;
                        #if DEBUG
                        RollIndicator_debug();
                        #endif
                    }
                }

            /* Early check */
            } else if (current_frame_delta > roll_early_check_frame && current_frame_delta < roll_end_frame) {
                #if DEBUG
                OSReport("between %d and %d frames!\n", roll_early_check_frame, roll_end_frame);
                #endif
                if (g_dComIfG_gameInfo.play.mPauseFlag) {
                    #if DEBUG
                    OSReport("game paused, incrementing start frame!\n");
                    #endif
                    roll_start_frame += 1;
                    current_frame_delta = cCt_getFrameCount() - roll_start_frame;
                    #if DEBUG
                    RollIndicator_debug();
                    #endif
                    game_paused = true;
                } else {
                    if (game_paused) {
                        game_paused = false;
                        roll_start_frame++;
                    }

                    if (GZ_getButtonPressed(A) && !GZ_getButtonHold(A)) {
                        snprintf(msg_buffer, sizeof(msg_buffer), "early by %d", (roll_end_frame - current_frame_delta));
                        FIFOQueue::push(msg_buffer, Queue, 0x0000FF00);
                        current_frame_delta = cCt_getFrameCount() - roll_start_frame;
                    } else {
                        current_frame_delta = cCt_getFrameCount() - roll_start_frame;
                        #if DEBUG
                        RollIndicator_debug();
                        #endif
                    }
                }

            /* Lower bounds check */
            } else if (current_frame_delta > 0 && current_frame_delta <= roll_early_check_frame) {
                #if DEBUG
                OSReport("too low to print!\n");
                #endif
                if (g_dComIfG_gameInfo.play.mPauseFlag) {
                    #if DEBUG
                    OSReport("game paused, incrementing start frame!\n");
                    #endif
                    roll_start_frame += 1;
                    current_frame_delta = cCt_getFrameCount() - roll_start_frame;
                    #if DEBUG
                    RollIndicator_debug();
                    #endif
                    game_paused = true;
                } else {
                    if (game_paused) {
                        game_paused = false;
                        roll_start_frame++;
                    }

                    current_frame_delta = cCt_getFrameCount() - roll_start_frame;
                    #if DEBUG
                    RollIndicator_debug();
                    #endif
                }
            } else {
                roll_start_frame = cCt_getFrameCount();
                current_frame_delta = cCt_getFrameCount()+1 - roll_start_frame;
                #if DEBUG          
                RollIndicator_debug();
                #endif
            }

            break;
        default:
            #if DEBUG
            OSReport("Default!\n");
            #endif
            /* Upper and lower bounds check */
            if (current_frame_delta > roll_late_check_frame || current_frame_delta <= roll_end_frame) {
                roll_start_frame = 0;
                current_frame_delta = 0;
            
            /* Late check */
            } else if (current_frame_delta > roll_end_frame) {
                #if DEBUG
                OSReport("Between %d and %d frames!\n", roll_end_frame, roll_late_check_frame);
                #endif

                if (g_dComIfG_gameInfo.play.mPauseFlag) {
                    #if DEBUG
                    OSReport("game paused, incrementing start frame!\n");
                    #endif
                    roll_start_frame += 1;
                    current_frame_delta = cCt_getFrameCount() - roll_start_frame;
                    game_paused = true;
                    #if DEBUG
                    RollIndicator_debug();
                    #endif
                } else {
                    if (game_paused) {
                        game_paused = false;
                        roll_start_frame++;
                    }

                    if (GZ_getButtonPressed(A) && !GZ_getButtonHold(A)) {
                        snprintf(msg_buffer, sizeof(msg_buffer), "late by %d", (current_frame_delta - roll_end_frame));
                        FIFOQueue::push(msg_buffer, Queue, 0x99000000);
                        current_frame_delta = 0;
                    } else {
                        current_frame_delta = cCt_getFrameCount() - roll_start_frame;
                        #if DEBUG
                        RollIndicator_debug();
                        #endif
                    }
                }
            }

            // Update the previous action to the current action
            previous_action = dComIfGp_getPlayer()->mActionID;
        }
    } else {
        roll_start_frame = 0;
        current_frame_delta = 0;
    }
}