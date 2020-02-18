#include <stdio.h>
#include "gorge.h"
#include <string.h>
#include "libtp_c/include/tp.h"
#include "libtp_c/include/controller.h"
#include "libtp_c/include/system.h"
#include "fifo_queue.h"

namespace GorgeVoidIndicator {
    using namespace Controller;

    static int before_cs_val = 0;
    static int after_cs_val = 0;
    static bool held_last_frame = false;
    static bool got_it = false;
    static char buf[20];

    void render() {}
    void run() {
        if (tp_gameInfo.freeze_game == 1 && tp_gameInfo.cs_val == 0x128 && strcmp((const char *)tp_gameInfo.current_stage, "F_SP121") == 0) {
            before_cs_val++;
        } else if (before_cs_val == 132 && (tp_gameInfo.freeze_game == 2 || tp_gameInfo.cs_val == 0x900) && strcmp((const char *)tp_gameInfo.current_stage, "F_SP121") == 0) {
            after_cs_val++;
        }

        if (before_cs_val > 122 && after_cs_val < 10) {
            // only report if you didn't hold it last frame
            if (tp_mPadStatus.sval != (Pad::L | Pad::A)) {
                held_last_frame = false;
            }

            if (got_it == false && held_last_frame == false && before_cs_val < 132 && tp_mPadStatus.sval == (Pad::L | Pad::A)) {
                // went early
                int final_val = 132 - before_cs_val;
                sprintf(buf, "%df early", final_val);
                FIFOQueue::push(buf, Queue);
                held_last_frame = true;
                Controller::set_buttons_down(0x0);
                Controller::set_buttons_pressed(0x0);
                tp_mPadButton.sval = 0x0;
                tp_mPadStatus.sval = 0x0;
            }

            else if (got_it == false && held_last_frame == false && before_cs_val == 132 &&
                     tp_mPadStatus.sval == (Pad::L | Pad::A) && after_cs_val == 0) {
                held_last_frame = true;
                FIFOQueue::push("<3", Queue);
                Controller::set_buttons_down(0x0);
                Controller::set_buttons_pressed(0x0);
                tp_mPadButton.sval = 0x0;
                tp_mPadStatus.sval = 0x0;
                got_it = true;
            }

            else if (got_it == false && held_last_frame == false && after_cs_val > 0 && tp_mPadStatus.sval == (Pad::L | Pad::A)) {
                // went late
                sprintf(buf, "%df late", after_cs_val);
                FIFOQueue::push(buf, Queue);
                held_last_frame = true;
                Controller::set_buttons_down(0x0);
                Controller::set_buttons_pressed(0x0);
                tp_mPadButton.sval = 0x0;
                tp_mPadStatus.sval = 0x0;
            }
        }
    }
}  // namespace GorgeVoidIndicator