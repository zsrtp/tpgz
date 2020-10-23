#include "frame_advance.h"
#include "libtp_c/include/tp.h"
#include "libtp_c/include/controller.h"
#include "libtp_c/include/system.h"
#include "menu.h"
#include "commands.h"
#include "controller.h"

using namespace Controller;

bool frame_advance_active;
bool pause_game;

namespace FrameAdvance {
    void handle_frame_advance() {

        

        if (frame_advance_active) {
            tp_osReport("af %d",tp_mPadStatus.sval);
            tp_jutgamepadread();
            if (tp_mPadStatus.sval != Pad::Z) {
                pause_game = true;
            }

            do {
                tp_jutgamepadread();

                if (tp_mPadStatus.sval & (1 << (4))) {
                    pause_game = false;
                    pad_test = tp_mPadStatus.sval;
                    //tp_mPadStatus.sval = 0x0000;
                }

                if (tp_mPadStatus.sval == Pad::B) {
                    pause_game = false;
                    frame_advance_active = false;
                }

            } while (pause_game);
            tp_osReport("bf %d",tp_mPadStatus.sval);
        }
    }
}  // namespace FrameAdvance