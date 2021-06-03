#include "rollcheck.h"
#include "controller.h"
#include "fifo_queue.h"
#include "libtp_c/include/JSystem/JUtility/JUTGamePad.h"
#include "libtp_c/include/msl_c/string.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/SSystem/SComponent/c_counter.h"

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

void run() {
    // if normal human link gameplay
    if (dComIfGp_getEvent().mHalt == false && dComIfGs_getTransformStatus() == STATUS_HUMAN) {
        current_counter = cCt_getFrameCount();
        if (dComIfGp_getPlayer()) {
            action_id = dComIfGp_getPlayer()->mActionID;
        }

        if (start_counter) {
            counter_difference += current_counter - previous_counter;
            previous_counter = current_counter;

            if (counter_difference > 24 && action_id != daAlink_c::FRONT_ROLL) {
                counter_difference = 0;
                previous_counter = 0;
                current_counter = 0;
                missed_counter = 0;
                start_counter = false;
            } else if (counter_difference > 19 && action_id != daAlink_c::FRONT_ROLL) {
                missed_pressed_a = false;
                missed_counter = counter_difference - 19;
            }
        }

        tp_sprintf(buf, "counter: %d", counter_difference);
        tp_sprintf(buf, "missed: %d", missed_counter);
        tp_sprintf(buf, "inputs: %d", Controller::get_current_inputs());
        tp_sprintf(buf, "action: %d", action_id);

        if (action_id == daAlink_c::FRONT_ROLL) {
            if (counter_difference > 20) {
                counter_difference = 1;
            }
            if (!start_counter) {
                start_counter = true;
                previous_counter = current_counter;
                counter_difference = 0;
            }

            if (counter_difference > 15 && counter_difference < 19 &&
                Controller::button_is_down(A) && !Controller::button_is_held(A)) {
                tp_sprintf(buf, "%df early", ROLL_FRAMES - counter_difference);
                FIFOQueue::push(buf, Queue, 0x0000FF00);
            } else if (counter_difference == 19 && Controller::button_is_down(A) &&
                       !Controller::button_is_held(A)) {
                FIFOQueue::push("<3", Queue, 0x00CC0000);
            } else if (missed_counter > 0 && missed_pressed_a == false) {
                tp_sprintf(buf, "%df late", missed_counter);
                FIFOQueue::push(buf, Queue, 0x99000000);
                missed_counter = 0;
                counter_difference = 0;
                missed_pressed_a = true;
            }

            // account for roll interupt via bonks or other means
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