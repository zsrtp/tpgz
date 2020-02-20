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
    static bool execute_loading_prep = false;
    static bool loading_initiated = false;

    void reset_controller_loop() {
        held_last_frame = true;
        Controller::set_buttons_down(0x0);
        Controller::set_buttons_pressed(0x0);
        tp_mPadButton.sval = 0x0;
        tp_mPadStatus.sval = 0x0;
    }

    void prep_rupee_roll() {
        // set respawn location for rupee roll and clear flags
        tp_gameInfo.respawn_next_spawn_id = 2;
        tp_gameInfo.respawn_position = {-11856.857f, -5700.0f, 56661.5};
        tp_gameInfo.respawn_angle = 24169;
        Inventory::clear_rupee_flags();

        if (tp_fopScnRq.isLoading == 1) {
            loading_initiated = true;
        }
        if (loading_initiated == true) {
            if (tp_fopScnRq.isLoading == 0) {
                // jump straight into warp after loading is done
                tp_gameInfo.temp_flags.temp_flag_bit_field_14 = 0x20;
                tp_gameInfo.cs_val = 0x900;
                execute_loading_prep = false;
            }
        }
    }

    void warp_to_gorge() {
        // set gorge map info
        tp_gameInfo.warps.kak_gorge_warp = 0;
        tp_gameInfo.temp_flags.temp_flag_bit_field_13 = 0;
        tp_gameInfo.temp_flags.temp_flag_bit_field_14 = 0;
        tp_gameInfo.warps.kak_gorge_unk = 0;

        // change form to wolf
        tp_gameInfo.link.is_wolf = true;

        // set loading info
        tp_gameInfo.warp.entrance.void_flag = 0;
        tp_gameInfo.event_to_play = 0;
        tp_gameInfo.respawn_animation = 0;
        tp_gameInfo.warp.entrance.spawn = 2;
        tp_gameInfo.warp.entrance.room = 3;
        tp_gameInfo.warp.entrance.state = 0xE;
        strcpy((char *)tp_gameInfo.warp.entrance.stage, "F_SP121");

        // reset health, item
        tp_gameInfo.respawn_item_id = 40;
        tp_gameInfo.link.heart_quarters = 12;  // 3 hearts

        // trigger loading
        tp_gameInfo.warp.enabled = true;
    }
    void run() {
        // runs after button combo is pressed
        if (execute_loading_prep == true) {
            prep_rupee_roll();
        };

        // execute warp
        if (tp_mPadStatus.sval == (Pad::R | Pad::L)) {
            execute_loading_prep = true;
            warp_to_gorge();
        }
        // reset counters on load
        if (tp_fopScnRq.isLoading == 1) {
            before_cs_val = 0;
            after_cs_val = 0;
            got_it = false;
        }

        // situation specific frame counters
        if (tp_gameInfo.freeze_game == 1 && tp_gameInfo.cs_val == 0x128 && strcmp((const char *)tp_gameInfo.current_stage, "F_SP121") == 0) {
            before_cs_val++;
        } else if (before_cs_val == 132 && (tp_gameInfo.freeze_game == 2 || tp_gameInfo.cs_val == 0x900) && strcmp((const char *)tp_gameInfo.current_stage, "F_SP121") == 0) {
            after_cs_val++;
        }

        // only care about 10f before and after
        if (before_cs_val > 122 && after_cs_val < 10) {

            // only report if you didn't hold it last frame
            if (tp_mPadStatus.sval != (Pad::L | Pad::A)) {
                held_last_frame = false;
            }

            // went early
            if (got_it == false && held_last_frame == false && before_cs_val < 132 && tp_mPadStatus.sval == (Pad::L | Pad::A)) {
                int final_val = 132 - before_cs_val;
                sprintf(buf, "%df early", final_val);
                FIFOQueue::push(buf, Queue);
                reset_controller_loop();
            }
            
            // got it
            else if (got_it == false && held_last_frame == false && before_cs_val == 132 &&
                     tp_mPadStatus.sval == (Pad::L | Pad::A) && after_cs_val == 0) {
                FIFOQueue::push("<3", Queue);
                reset_controller_loop();
                got_it = true;
            }

            // went late
            else if (got_it == false && held_last_frame == false && after_cs_val > 0 && tp_mPadStatus.sval == (Pad::L | Pad::A)) {
                // went late
                sprintf(buf, "%df late", after_cs_val);
                FIFOQueue::push(buf, Queue);
                reset_controller_loop();
            }
        }
    }
}  // namespace GorgeVoidIndicator