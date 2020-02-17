#include <string.h>
#include "libtp_c/include/tp.h"
#include "libtp_c/include/controller.h"
#include "libtp_c/include/system.h"

namespace RollIndicator {
    using namespace Controller;
    static int roll_counter = 0;
    static int missed_counter = 0;
    static bool held_last_frame = false;

    void roll_check() {
        // if normal human link gameplay
        if (tp_gameInfo.freeze_game == 0 && tp_gameInfo.link.is_wolf == false) {
            if (tp_mPadStatus.sval != (Pad::A)) {
                held_last_frame = false;
            }
            if (tp_zelAudio.link_debug_ptr->current_action_id == 14) {
                // reset counter cause next frame is either a new roll or a miss
                if (roll_counter > 20) {
                    roll_counter = 0;
                }
                roll_counter++;
                if (missed_counter > 0 && held_last_frame == false) {
                    tp_osReport("%df late", missed_counter);
                    missed_counter = 0;
                } else {
                    if (roll_counter > 15 && roll_counter < 20 && tp_mPadStatus.sval == Pad::A && held_last_frame == false) {
                        tp_osReport("%df early", 20 - roll_counter);
                        held_last_frame = true;
                    } else if (roll_counter == 20 && tp_mPadStatus.sval == Pad::A && held_last_frame == false) {
                        tp_osReport("<3");
                        held_last_frame = true;
                    }
                }
            } else if (roll_counter > 0 || missed_counter > 0) {
                missed_counter++;
                if (missed_counter > 5) {
                    missed_counter = 0;
                }
            }
            // account for roll interupt
            if (roll_counter > 0 && roll_counter < 21 && tp_zelAudio.link_debug_ptr->current_action_id != 14) {
                roll_counter = 0;
            }
        }
    }
}  // namespace RollIndicator