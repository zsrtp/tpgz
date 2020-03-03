#include <string.h>
#include "libtp_c/include/tp.h"
#include "libtp_c/include/controller.h"
#include "libtp_c/include/system.h"
#include "controller.h"
#include "fifo_queue.h"
#include "rollcheck.h"
#include "log.h"
#include <stdio.h>
#define ROLL_FRAMES 20

namespace RollIndicator {
    using namespace Controller;
    static int current_counter = 0;
    static int counter_difference = 0;
    static int previous_counter = 0;
    static int missed_counter = 0;
    static char buf[20];

    void run() {
        if (g_roll_check_active) {
            // if normal human link gameplay
            if (tp_gameInfo.freeze_game == 0 && tp_gameInfo.link.is_wolf == false) {
                Log log;

                current_counter = TP::get_frame_count();

                if (counter_difference >= 20 && tp_zelAudio.link_debug_ptr->current_action_id == 4) {
                    if (counter_difference > 24) {
                        counter_difference = 0;
                        missed_counter = 0;
                        previous_counter = 0;
                        current_counter = 0;
                    } else {
                        missed_counter++;
                        counter_difference++;
                    }
                }
                if (tp_zelAudio.link_debug_ptr->current_action_id == 14) {
                    if (previous_counter == 0) {
                        previous_counter = current_counter - 1;
                    }
                    counter_difference += current_counter - previous_counter;
                    previous_counter = current_counter;

                    sprintf(buf, "counter: %d", counter_difference);
                    log.PrintLog(buf, DEBUG);
                    sprintf(buf, "missed: %d", missed_counter);
                    log.PrintLog(buf, DEBUG);
                    sprintf(buf, "inputs: %d", tp_mPadStatus.sval);
                    log.PrintLog(buf, DEBUG);

                    if (counter_difference > 15 && counter_difference < 20 && Controller::button_is_down(A) && !Controller::button_is_held(A)) {
                        sprintf(buf, "%df early", ROLL_FRAMES - counter_difference);
                        FIFOQueue::push(buf, Queue, 0x0000FF00);
                    } else if (counter_difference == 20 && Controller::button_is_down(A) && !Controller::button_is_held(A)) {
                        FIFOQueue::push("<3", Queue, 0x00CC0000);
                        counter_difference = 0;
                    } else if (missed_counter > 0 && Controller::button_is_down(A) && !Controller::button_is_held(A)) {
                        sprintf(buf, "%df late", missed_counter);
                        FIFOQueue::push(buf, Queue, 0x99000000);
                    }

                    //account for roll interupt via bonks or other means
                    if (counter_difference > 0 && counter_difference < 20 && tp_zelAudio.link_debug_ptr->current_action_id != 14) {
                        counter_difference = 0;
                        previous_counter = 0;
                        current_counter = 0;
                        missed_counter = 0;
                    }
                }
            }
        }
    }
}  // namespace RollIndicator