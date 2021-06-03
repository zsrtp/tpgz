#include "corotdcheck.h"
#include "controller.h"
#include "fifo_queue.h"
#include "fs.h"
#include "libtp_c/include/JSystem/JUtility/JUTGamePad.h"
#include "libtp_c/include/msl_c/string.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/SSystem/SComponent/c_counter.h"
#include "libtp_c/include/f_op/f_op_scene_req.h"

namespace CoroTDChecker {
using namespace Controller;

static bool start_timer = false;
uint32_t current_counter = 0;
static bool got_it = false;
static char buf[20];

void run() {
    // reset counters on load
    if (tp_fopScnRq.isLoading == 1) {
        current_counter = 0;
        got_it = false;
        start_timer = false;
    }

    if (start_timer == false && button_is_down(A) &&
        tp_strcmp((const char*)g_dComIfG_gameInfo.play.mStartStage.mStage, "F_SP108") == 0) {
        start_timer = true;
    }

    if (start_timer == true) {
        current_counter++;

        if (current_counter < 20) {
            // went early
            if (!got_it && (!button_is_held(Y) || !button_is_held(X)) && (current_counter < 10) && (button_is_down(Y) || button_is_down(X))) {
                int final_val = 10 - current_counter;
                tp_sprintf(buf, "%df early", final_val);
                FIFOQueue::push(buf, Queue, 0x0000FF00);
            }

            // got it
            else if (!got_it && (!button_is_held(Y) || !button_is_held(X)) && (current_counter == 10) && (button_is_down(Y) || button_is_down(X))) {
                FIFOQueue::push("got it", Queue, 0x00CC0000);
                got_it = true;
            }

            // went late
            else if (!got_it && (!button_is_held(Y) || !button_is_held(X)) && current_counter > 10 && (button_is_down(Y) || button_is_down(X))) {
                int final_val = current_counter - 10;
                tp_sprintf(buf, "%df late", final_val);
                FIFOQueue::push(buf, Queue, 0x99000000);
            }
        } else {
            current_counter = 0;
            got_it = false;
            start_timer = false;
        }
    }
}
}  // namespace CoroTDChecker