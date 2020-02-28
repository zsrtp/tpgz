#include <stdio.h>
#include "gorge.h"
#include <string.h>
#include "libtp_c/include/tp.h"
#include "libtp_c/include/system.h"
#include "libtp_c/include/controller.h"
#include "fifo_queue.h"
#include "controller.h"
#include "log.h"
#include "utils.h"
#define WARP_CS_FRAMES 132
bool g_gorge_active;

namespace GorgeVoidIndicator {
    using namespace Controller;

    static bool start_timer = false;
    uint32_t previous_counter = 0;
    uint32_t current_counter = 0;
    uint32_t counter_difference = 0;
    static int after_cs_val = 0;
    static bool got_it = false;
    static char buf[20];

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
        Utilities::trigger_load(Gorge);
    }
    void run() {
        if (g_gorge_active) {
            Log log;  // instantiate logger for debugging

            // execute warp
            if (button_is_down(L) && button_is_down(Z)) {
                warp_to_gorge();
            }
            // reset counters on load
            if (tp_fopScnRq.isLoading == 1) {
                counter_difference = 0;
                after_cs_val = 0;
                got_it = false;
                start_timer = false;
            }

            current_counter = TP::get_frame_count();
            // situation specific frame counters
            if (start_timer == false && tp_gameInfo.freeze_game == 1 && tp_gameInfo.cs_val == 0x128 && strcmp((const char *)tp_gameInfo.current_stage, "F_SP121") == 0) {
                start_timer = true;
                previous_counter = current_counter;
                counter_difference = 0;
            }

            if (start_timer == true) {
                counter_difference += current_counter - previous_counter;
                previous_counter = current_counter;

                if (counter_difference > WARP_CS_FRAMES) {
                    after_cs_val = counter_difference - WARP_CS_FRAMES;
                }

                sprintf(buf, "counter: %d", counter_difference);
                log.PrintLog(buf, DEBUG);
                sprintf(buf, "inputs: %d", tp_mPadStatus.sval);
                log.PrintLog(buf, DEBUG);

                // only care about 10f before and after
                if (counter_difference > 123 && after_cs_val < 10) {
                    // went early
                    if (!got_it && !(button_is_held(L) && button_is_held(A)) && (counter_difference < WARP_CS_FRAMES) &&
                        (button_is_down(A) && button_is_down(L))) {
                        int final_val = WARP_CS_FRAMES - counter_difference;
                        sprintf(buf, "%df early", final_val);
                        FIFOQueue::push(buf, Queue);
                    }

                    // got it
                    else if (!got_it && !(button_is_held(L) && button_is_held(A)) && (counter_difference == WARP_CS_FRAMES) &&
                             (button_is_down(A) && button_is_down(L))) {
                        FIFOQueue::push("got it", Queue);
                        got_it = true;
                    }

                    // went late
                    else if (!got_it && !(button_is_held(L) && button_is_held(A)) && after_cs_val > 0 &&
                             (button_is_down(A) && button_is_down(L))) {
                        sprintf(buf, "%df late", after_cs_val);
                        FIFOQueue::push(buf, Queue);
                    }
                }
            }
        }
    }
}  // namespace GorgeVoidIndicator