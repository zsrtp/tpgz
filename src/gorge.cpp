
#include "gorge.h"
#include "controller.h"
#include "fifo_queue.h"
#include "fs.h"
#include "libtp_c/include/controller.h"
#include "libtp_c/include/system.h"
#include "libtp_c/include/tp.h"
#define WARP_CS_FRAMES 132

bool inject_gorge_flag = false;

namespace GorgeVoidIndicator {
using namespace Controller;

static bool start_timer = false;
uint32_t previous_counter = 0;
uint32_t current_counter = 0;
uint32_t counter_difference = 0;
static int after_cs_val = 0;
static bool got_it = false;
static char buf[20];

void prep_rupee_roll() {
    tp_gameInfo.temp_flags.flags[9] = 0x20;
    tp_gameInfo.cs_val = 0x900;
    inject_gorge_flag = false;
}

void warp_to_gorge() {
    // set gorge map info
    tp_gameInfo.overworld_flags.hyrule_field_flags.flags[9] = 0;
    tp_gameInfo.temp_flags.flags[8] = 0;
    tp_gameInfo.temp_flags.flags[9] = 0;
    tp_gameInfo.overworld_flags.hyrule_field_flags.flags[8] = 0;

    // change form to wolf
    tp_gameInfo.link.is_wolf = true;

    // set loading info
    tp_gameInfo.warp.entrance.void_flag = 0;
    tp_gameInfo.event_to_play = 0;
    tp_gameInfo.respawn_animation = 0;
    tp_gameInfo.warp.entrance.spawn = 2;
    tp_gameInfo.warp.entrance.room = 3;
    tp_gameInfo.warp.entrance.state = 0xE;
    tp_strcpy((char*)tp_gameInfo.warp.entrance.stage, "F_SP121");

    // reset health, item
    tp_gameInfo.respawn_item_id = 40;
    tp_gameInfo.link.heart_quarters = 12;  // 3 hearts

    // trigger loading, convert some of these to const later
    tp_gameInfo.special_spawn_id = 2;
    tp_gameInfo.respawn_position = {-11856.857f, -5700.0f, 56661.5};
    tp_gameInfo.respawn_angle = 24169;
    Inventory::clear_rupee_flags();
}
void run() {
    // reset counters on load
    if (tp_fopScnRq.isLoading == 1) {
        counter_difference = 0;
        after_cs_val = 0;
        got_it = false;
        start_timer = false;
    }

    current_counter = TP::get_frame_count();

    // situation specific frame counters
    if (start_timer == false && tp_gameInfo.freeze_game == 1 && tp_gameInfo.cs_val == 0x128 &&
        tp_strcmp((const char*)tp_gameInfo.current_stage, "F_SP121") == 0) {
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

        tp_sprintf(buf, "counter: %d", counter_difference);
        tp_sprintf(buf, "inputs: %d", tp_mPadStatus.sval);

        // only care about 10f before and after
        if (counter_difference > 123 && after_cs_val < 10) {
            // went early
            if (!got_it && !(button_is_held(L) && button_is_held(A)) &&
                (counter_difference < WARP_CS_FRAMES) && (button_is_down(A) && button_is_down(L))) {
                int final_val = WARP_CS_FRAMES - counter_difference;
                tp_sprintf(buf, "%df early", final_val);
                FIFOQueue::push(buf, Queue, 0x0000FF00);
            }

            // got it
            else if (!got_it && !(button_is_held(L) && button_is_held(A)) &&
                     (counter_difference == WARP_CS_FRAMES) &&
                     (button_is_down(A) && button_is_down(L))) {
                FIFOQueue::push("got it", Queue, 0x00CC0000);
                got_it = true;
            }

            // went late
            else if (!got_it && !(button_is_held(L) && button_is_held(A)) && after_cs_val > 0 &&
                     (button_is_down(A) && button_is_down(L))) {
                tp_sprintf(buf, "%df late", after_cs_val);
                FIFOQueue::push(buf, Queue, 0x99000000);
            }
        }
    }
}
}  // namespace GorgeVoidIndicator