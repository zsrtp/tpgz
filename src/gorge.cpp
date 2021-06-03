#include "gorge.h"
#include "controller.h"
#include "fifo_queue.h"
#include "fs.h"
#include "libtp_c/include/JSystem/JUtility/JUTGamePad.h"
#include "libtp_c/include/msl_c/string.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/SSystem/SComponent/c_counter.h"
#include "libtp_c/include/f_op/f_op_scene_req.h"

#define WARP_CS_FRAMES 132
#ifdef WII_PLATFORM
#define TARGET_BUTTON Z
#endif
#ifdef GCN_PLATFORM
#define TARGET_BUTTON L
#endif

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
    dComIfGs_onSwitch(21, dComIfGp_getPlayer()->mOrig.mRoomNo);
    dComIfGp_getEvent().event_order.field_0x10 = 9;
    inject_gorge_flag = false;
}

void warp_to_gorge() {
    // set gorge map info
    g_dComIfG_gameInfo.mInfo.mMemory.mMemBit.mSwitch[0] = 0; // optimize later
    dComIfGs_putSave(g_dComIfG_gameInfo.mInfo.mDan.mStageNo);

    // change form to wolf
    dComIfGs_setTransformStatus(STATUS_WOLF);

    // set loading info
    g_dComIfG_gameInfo.play.mNextStage.wipe = 13;
    g_dComIfG_gameInfo.play.mNextStage.mPoint = 0;
    g_dComIfG_gameInfo.mInfo.mRestart.mRoomParam = 0;
    g_dComIfG_gameInfo.mInfo.mRestart.mLastMode = 0;
    g_dComIfG_gameInfo.play.mNextStage.mPoint = 2;
    g_dComIfG_gameInfo.play.mNextStage.mRoomNo = 3;
    g_dComIfG_gameInfo.play.mNextStage.mLayer = 0xE;
    tp_strcpy((char*)g_dComIfG_gameInfo.play.mNextStage.mStage, "F_SP121");

    // reset health, item
    g_dComIfG_gameInfo.mInfo.mRestart.mLastMode |= 0x28000000;
    dComIfGs_setLife(12);  // 3 hearts

    // trigger loading, convert some of these to const later
    g_dComIfG_gameInfo.mInfo.mRestart.mStartPoint = 2;
    cXyz pos(-11856.857f, -5700.0f, 56661.5);
    g_dComIfG_gameInfo.mInfo.mRestart.mRoomPos = pos;
    g_dComIfG_gameInfo.mInfo.mRestart.mRoomAngleY = 24169;
}
void run() {
    // reset counters on load
    if (tp_fopScnRq.isLoading == 1) {
        counter_difference = 0;
        after_cs_val = 0;
        got_it = false;
        start_timer = false;
    }

    current_counter = cCt_getFrameCount();

    // situation specific frame counters
    if (start_timer == false && dComIfGp_getEvent().mHalt == 1 && dComIfGp_getEvent().event_order.field_0x10 == 0x1 &&
        tp_strcmp((const char*)g_dComIfG_gameInfo.play.mStartStage.mStage, "F_SP121") == 0) {
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
        tp_sprintf(buf, "inputs: %d", Controller::get_current_inputs());

        // only care about 10f before and after
        if (counter_difference > 123 && after_cs_val < 10) {
            // went early
            if (!got_it && !(button_is_held(TARGET_BUTTON) && button_is_held(A)) &&
                (counter_difference < WARP_CS_FRAMES) &&
                (button_is_down(A) && button_is_down(TARGET_BUTTON))) {
                int final_val = WARP_CS_FRAMES - counter_difference;
                tp_sprintf(buf, "%df early", final_val);
                FIFOQueue::push(buf, Queue, 0x0000FF00);
            }

            // got it
            else if (!got_it && !(button_is_held(TARGET_BUTTON) && button_is_held(A)) &&
                     (counter_difference == WARP_CS_FRAMES) &&
                     (button_is_down(A) && button_is_down(TARGET_BUTTON))) {
                FIFOQueue::push("got it", Queue, 0x00CC0000);
                got_it = true;
            }

            // went late
            else if (!got_it && !(button_is_held(TARGET_BUTTON) && button_is_held(A)) &&
                     after_cs_val > 0 && (button_is_down(A) && button_is_down(TARGET_BUTTON))) {
                tp_sprintf(buf, "%df late", after_cs_val);
                FIFOQueue::push(buf, Queue, 0x99000000);
            }
        }
    }
}
}  // namespace GorgeVoidIndicator