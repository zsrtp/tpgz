#include <string.h>
#include "libtp_c/include/tp.h"
#include "libtp_c/include/controller.h"
#include "libtp_c/include/system.h"
#include "controller.h"
#include "fifo_queue.h"
#include "rollcheck.h"
#include "log.h"
#include <stdio.h>
#define ROLL_FRAMES 19

namespace RollIndicator {
    using namespace Controller;
    static int current_counter = 0;
    static int counter_difference = 0;
    static int previous_counter = 0;
    static int missed_counter = 0;
    static char buf[20];
    static bool start_counter = false;
    static bool missed_pressed_a = false;
    uint16_t action_id = 0x0000;
    Log log;

    void run() {
        // if normal human link gameplay
        if (tp_gameInfo.freeze_game == 0 && tp_gameInfo.link.is_wolf == false) {
            current_counter = TP::get_frame_count();
            if (tp_zelAudio.link_debug_ptr) {
                action_id = tp_zelAudio.link_debug_ptr->current_action_id;
            }

            if (start_counter) {
                counter_difference += current_counter - previous_counter;
                previous_counter = current_counter;

                if (counter_difference > 24 && action_id != 14) {
                    counter_difference = 0;
                    previous_counter = 0;
                    current_counter = 0;
                    missed_counter = 0;
                    start_counter = false;
                } else if (counter_difference > 19 && action_id != 14) {
                    missed_pressed_a = false;
                    missed_counter = counter_difference - 19;
                }
            }

            sprintf(buf, "counter: %d", counter_difference);
            log.PrintLog(buf, DEBUG);
            sprintf(buf, "missed: %d", missed_counter);
            log.PrintLog(buf, DEBUG);
            sprintf(buf, "inputs: %d", tp_mPadStatus.sval);
            log.PrintLog(buf, DEBUG);
            sprintf(buf, "action: %d", action_id);
            log.PrintLog(buf, DEBUG);

            if (action_id == 14) {
                if (counter_difference > 20) {
                    counter_difference = 1;
                }
                if (!start_counter) {
                    start_counter = true;
                    previous_counter = current_counter;
                    counter_difference = 0;
                }
                
                if (counter_difference > 15 && counter_difference < 19 && Controller::button_is_down(A) && !Controller::button_is_held(A)) {
                    sprintf(buf, "%df early", ROLL_FRAMES - counter_difference);
                    FIFOQueue::push(buf, Queue, 0x0000FF00);
                } else if (counter_difference == 19 && Controller::button_is_down(A) && !Controller::button_is_held(A)) {
                    FIFOQueue::push("<3", Queue, 0x00CC0000);
                } else if (missed_counter > 0 && missed_pressed_a == false) {
                    sprintf(buf, "%df late", missed_counter);
                    FIFOQueue::push(buf, Queue, 0x99000000);
                    missed_counter = 0;
                    counter_difference = 0;
                    missed_pressed_a = true;
                }

                //account for roll interupt via bonks or other means
                // if (counter_difference > 20) {
                //     counter_difference = 0;
                //     previous_counter = 0;
                //     current_counter = 0;
                //     missed_counter = 0;
                // }
            }
        }
    }
}  // namespace RollIndicator