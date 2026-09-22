#include <cstdio>
#include "gorge.h"
#include "commands.h"
#include "controller.h"
#include "fifo_queue.h"
#include "fs.h"
#include "save_manager.h"
#include "menus/menu_any_saves/include/any_saves_menu.h"
#include "libtp_c/include/JSystem/JUtility/JUTGamePad.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/SSystem/SComponent/c_counter.h"
#include "libtp_c/include/f_op/f_op_scene_req.h"
#include "libtp_c/include/f_op/f_op_actor_mng.h"
#include "libtp_c/include/utils.h"
#include "libtp_c/include/m_Do/m_Do_printf.h"
#include "settings.h"
#include "modules.h"

#ifdef WII_PLATFORM
#define TARGET_BUTTON Z
#define WARP_CS_FRAMES 132
#endif

#ifdef GCN_PLATFORM
#define TARGET_BUTTON L
#define WARP_CS_FRAMES 132
#endif

KEEP_FUNC void GZCmd_loadGorgeVoid() {
    if (GZCmd_checkTrig(GZStng_getData<uint16_t>(STNG_CMD_GORGE_VOID, GORGE_VOID_BUTTONS))) {
        // TODO: maybe simplify this
#ifdef WII_PLATFORM
        special sp[] = {
            special(2, GorgeVoidIndicator::warpToPosition, GorgeVoidIndicator::initState),
        };

        SaveManager::triggerLoad(2, "any", sp, 1);
#else
        if (gorge_wolf_active()) {
            special sp[] = {
                special(GORGE_VOID_INDEX, GorgeVoidIndicator::warpToPosition, GorgeVoidIndicator::initState),
            };
            SaveManager::triggerLoad(GORGE_VOID_INDEX, "any", sp, 1);
        } else if (gorge_human_active()) {
            special sp[] = {
                special(FRST_BIT_INDEX, GorgeVoidIndicator::warpToPosition, GorgeVoidIndicator::initState),
            };
            SaveManager::triggerLoad(FRST_BIT_INDEX, "any", sp, 1);
        }
        
#endif
    }
}

namespace GorgeVoidIndicator {
static bool start_timer = false;
uint32_t previous_counter = 0;
uint32_t current_counter = 0;
uint32_t counter_difference = 0;
static int after_cs_val = 0;
static bool got_it = false;
static char buf[21];

void actorFastCreateAtLink(short id, uint32_t parameters, int8_t subtype) {
    fopAcM_create(id, parameters, &dComIfGp_getPlayer()->current.pos,
                  dComIfGp_getPlayer()->current.roomNo, &dComIfGp_getPlayer()->current.angle,
                  nullptr, subtype);
}

#if defined(WII_NTSCU_10) || defined(WII_PAL)
#define KYTAG09_ACTOR_ID 0x2B1
#else
#define KYTAG09_ACTOR_ID 0x2B3
#endif

void initState() {
    dComIfGs_onSwitch(21, 3);  // turn on portal flag
    dComIfGp_getEvent().mOrder[0].mEventId = 9;
#ifdef WII_PLATFORM
    actorFastCreateAtLink(KYTAG09_ACTOR_ID, -1, -1);
#endif
    if (GZ_checkSwapEquips()) {
        dComIfGs_setSelectItemIndex(SELECT_ITEM_X, SLOT_3);
    } else {
        dComIfGs_setSelectItemIndex(SELECT_ITEM_Y, SLOT_3);
    }
}

void warpToPosition() {
    // set gorge map info
    g_dComIfG_gameInfo.info.mMemory.mBit.mSwitch[0] = 0;  // optimize later
    dComIfGs_putSave(g_dComIfG_gameInfo.info.mDan.mStageNo);

    // set loading info
    g_dComIfG_gameInfo.play.mNextStage.wipe = 13;
    g_dComIfG_gameInfo.info.mRestart.mRoomParam = 0;
    g_dComIfG_gameInfo.info.mRestart.mLastMode = 0;
    setNextStagePoint(2);
    setNextStageRoom(3);
    setNextStageLayer(0xE);
    setNextStageName("F_SP121");

    // reset health, item
    g_dComIfG_gameInfo.info.mRestart.mLastMode |= 0x28000000;
    dComIfGs_setLife(12);  // 3 hearts

    // trigger loading, convert some of these to const later
    g_dComIfG_gameInfo.info.mRestart.mStartPoint = 2;
    cXyz pos(-11856.857f, -5700.0f, 56661.5);
    g_dComIfG_gameInfo.info.mRestart.mRoomPos = pos;
    g_dComIfG_gameInfo.info.mRestart.mRoomAngleY = 24169;
}

KEEP_FUNC void execute() {
    // reset counters on load
    if (fopScnRq.isLoading == 1) {
        counter_difference = 0;
        after_cs_val = 0;
        got_it = false;
        start_timer = false;
    }

    current_counter = cCt_getFrameCount();

    // situation specific frame counters
    if (start_timer == false && dComIfGp_getEvent().mHalt == 1 &&
        daAlink_c__checkStageName("F_SP121")) {
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

        // only care about 10f before and after
        if (counter_difference > 123 && after_cs_val < 10) {

            if (isAPressed()) {
                // went early
                if (counter_difference < WARP_CS_FRAMES) {
                    int final_val = WARP_CS_FRAMES - counter_difference;
                    snprintf(buf, sizeof(buf), "Jump attack %df early", final_val);
                    FIFOQueue::push(buf, Queue, 0x0000FF00);
                }

                // got it
                else if (!got_it && counter_difference == WARP_CS_FRAMES) {
                    FIFOQueue::push("Jump attack got it", Queue, 0x00CC0000);
                    got_it = true;
                }

                // went late
                else if (!got_it && after_cs_val > 0) {
                    snprintf(buf, sizeof(buf), "Jump attack %df late", after_cs_val);
                    FIFOQueue::push(buf, Queue, 0x99000000);
                }
            }

            if (gorge_human_active() && isBootsPressed()) {
                // went early
                if (counter_difference < WARP_CS_FRAMES) {
                    int final_val = WARP_CS_FRAMES - counter_difference;
                    snprintf(buf, sizeof(buf), "Boots %df early", final_val);
                    FIFOQueue::push(buf, Queue, 0x0000FF00);
                }

                // got it
                else if (counter_difference == WARP_CS_FRAMES) {
                    FIFOQueue::push("Boots got it", Queue, 0x00CC0000);
                    got_it = true;
                }

                // went late
                else if (after_cs_val > 0) {
                    snprintf(buf, sizeof(buf), "Boots %df late", after_cs_val);
                    FIFOQueue::push(buf, Queue, 0x99000000);
                }
            }
        }
    }
}

KEEP_FUNC bool isAPressed() {
    return !(GZ_getButtonHold(TARGET_BUTTON) && GZ_getButtonHold(A)) 
    && (GZ_getButtonPressed(A) && GZ_getButtonPressed(TARGET_BUTTON));
}

KEEP_FUNC bool isBootsPressed() {
    #ifdef GCN_PLATFORM
    return (!GZ_getButtonHold(X) && GZ_getButtonPressed(X)) || (!GZ_getButtonHold(Y) && GZ_getButtonPressed(Y));
    #else
    return false;
    #endif
}

}  // namespace GorgeVoidIndicator