#include "gz_flags.h"
#include <cstring>
#include "controller.h"
#include "fifo_queue.h"
#include "gorge.h"
#include "scene.h"
#include "tools.h"
#include "rollcheck.h"
#include "utils/audio.h"
#include "utils/lines.h"
#include "utils/link.h"
#include "utils/loading.h"
#include "flaglog.h"
#include "save_manager.h"
#include "memfiles.h"
#include "corotdcheck.h"
#include "utils/draw.h"
#include "libtp_c/include/JSystem/JUtility/JUTGamePad.h"
#include "libtp_c/include/f_op/f_op_scene_req.h"
#include "rels/include/defines.h"

bool g_framePaused = false;

// Initialized in the "init" module
KEEP_VAR tpgz::containers::deque<GZFlag*> g_gzFlags;

#ifdef GCN_PLATFORM
#define HOLD_BTNS cPadInfo[0].mButtonFlags
#define TRIG_BTNS cPadInfo[0].mPressedButtonFlags
#endif

#ifdef WII_PLATFORM
#define HOLD_BTNS mPad.mHoldButton
#define TRIG_BTNS mPad.mTrigButton
#endif

KEEP_FUNC void GZFlg_addFlag(GZFlag* flag) {
    g_gzFlags.push_back(flag);
}

KEEP_FUNC GZFlag* GZFlg_removeFlag(GZFlags flag_id) {
    auto it = g_gzFlags.begin();
    for (;it != g_gzFlags.end(); ++it) {
        if ((*it)->id == flag_id) {
            break;
        }
    }
    auto* flag = *it;
    g_gzFlags.erase(it);
    return flag;
}

KEEP_FUNC void GZ_frameAdvance() {
    if (!g_framePaused) {
        return;
    }
    static int holdCounter = 0;
    static uint32_t buttonsPrev = 0;
    sPauseTimer = 1;

    TRIG_BTNS = HOLD_BTNS & ~buttonsPrev;

    if (HOLD_BTNS & FRAME_ADVANCE_PAD) {
        holdCounter++;
    } else {
        holdCounter = 0;
    }

    if (GZ_getButtonTrig(FRAME_ADVANCE_BTN)) {
        // this sets pause timer to 0 for 1 frame,
        // which lets 1 frame pass before pausing again
        sPauseTimer = 0;
        buttonsPrev = HOLD_BTNS;
        HOLD_BTNS &= ~FRAME_ADVANCE_PAD;
    }

    // frames start passing at normal speed after holding for 30 frames
    if (holdCounter >= 30) {
        sPauseTimer = 0;
        buttonsPrev = HOLD_BTNS;
        HOLD_BTNS &= ~FRAME_ADVANCE_PAD;
    }
}

#ifdef WII_PLATFORM
extern bool isWidescreen;
#else
#define isWidescreen (false)
#endif
void GZ_drawFrameTex(Texture* pauseTex, Texture* playTex) {
    if (g_framePaused) {
        if (sPauseTimer == 1) {
            Draw::drawRect(0xFFFFFFFF, {550.0f, 5.0f}, {32 * (isWidescreen ? 0.75f : 1.0f), 32},
                           &pauseTex->_texObj);
        } else {
            Draw::drawRect(0xFFFFFFFF, {550.0f, 5.0f}, {32 * (isWidescreen ? 0.75f : 1.0f), 32},
                           &playTex->_texObj);
        }
    }
}

void GZ_execute(int phase) {
    for (auto gzFlag : g_gzFlags) {
        if (gzFlag->mPhase == phase && gzFlag->mpFlag != nullptr) {
            if (*gzFlag->mpFlag && gzFlag->mpActiveFunc) {
                gzFlag->mpActiveFunc();
            } else if (gzFlag->mpDeactiveFunc) {
                gzFlag->mpDeactiveFunc();
            }
        }
    }

    if (g_tools[SAND_INDEX].active) {
        if (dComIfGp_getPlayer() != nullptr) {
            dComIfGp_getPlayer()->field_0x2ba8 = 0.0f;
        }
    }

    // Timer set after dScnPly__phase_4, delay until objects are fully loaded
    if (!fopScnRq.isLoading && SaveManager::s_applyAfterTimer > 0) {
        SaveManager::s_applyAfterTimer--;
    } else if (SaveManager::s_applyAfterTimer == 0) {
        if (gSaveManager.mPracticeFileOpts.inject_options_after_load) {
            gSaveManager.mPracticeFileOpts.inject_options_after_load();
        }
        SaveManager::s_applyAfterTimer = -1;
    }

    // normally oxygen doesn't get set until going to the file select screen
    // so this fixes oxygen issues when loading a save from title screen directly after boot
    if (g_dComIfG_gameInfo.play.mMaxOxygen == 0) {
        dComIfGs_setOxygen(600);
        dComIfGs_setNowOxygen(600);
        dComIfGs_setMaxOxygen(600);
    }
}
