#include "gorge.h"
#include <string.h>
#include "libtp_c/include/tp.h"
#include "libtp_c/include/controller.h"
#include "libtp_c/include/system.h"

namespace GorgeVoidIndicator {
    using namespace Controller;

    static int before_cs_val = 0;
    static int after_cs_val = 0;
    static bool held_last_frame = false;
    static bool got_it = false;

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
                tp_osReport("%df early", final_val);
                held_last_frame = true;
                Controller::set_buttons_down(0x0);
                Controller::set_buttons_pressed(0x0);
                tp_mPadButton.sval = 0x0;
                tp_mPadStatus.sval = 0x0;
            }

            else if (got_it == false && held_last_frame == false && before_cs_val == 132 &&
                     tp_mPadStatus.sval == (Pad::L | Pad::A) && after_cs_val == 0) {
                // got it
                held_last_frame = true;
                tp_osReport("<3");
                Controller::set_buttons_down(0x0);
                Controller::set_buttons_pressed(0x0);
                tp_mPadButton.sval = 0x0;
                tp_mPadStatus.sval = 0x0;
                got_it = true;
            }

            else if (got_it == false && held_last_frame == false && after_cs_val > 0 && tp_mPadStatus.sval == (Pad::L | Pad::A)) {
                // went late
                tp_osReport("%df late", after_cs_val);
                held_last_frame = true;
                Controller::set_buttons_down(0x0);
                Controller::set_buttons_pressed(0x0);
                tp_mPadButton.sval = 0x0;
                tp_mPadStatus.sval = 0x0;
            }

            if (tp_mPadStatus.sval == (Pad::R | Pad::A)) {
                Inventory::set_rupee_flags();
                Controller::set_buttons_down(0x0);
                Controller::set_buttons_pressed(0x0);
                tp_mPadButton.sval = 0x0;
                tp_mPadStatus.sval = 0x0;
            }
        }
    }
}  // namespace GorgeVoidIndicator