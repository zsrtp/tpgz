#include "gz_flags.h"
#include <cstring>
#include "controller.h"
#include "fifo_queue.h"
#include "gorge.h"
#include "bit.h"
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
#include "umd.h"
#include "utils/draw.h"
#include "libtp_c/include/JSystem/JUtility/JUTGamePad.h"
#include "libtp_c/include/f_op/f_op_scene_req.h"
#include "rels/include/defines.h"

bool g_framePaused = false;

GZFlag g_gzFlags[MAX_GZ_FLAGS] = {
    {&g_tools[GORGE_INDEX].active, GAME_LOOP, GorgeVoidIndicator::execute},
#ifdef WII_PLATFORM
    {&g_tools[BIT_INDEX].active, GAME_LOOP, BiTIndicator::execute},
#endif
    {&g_tools[ROLL_INDEX].active, GAME_LOOP, RollIndicator::execute},
    {&g_tools[COROTD_INDEX].active, GAME_LOOP, CoroTDChecker::execute},
    {&g_tools[UMD_INDEX].active, POST_GAME_LOOP, UMDIndicator::execute},
    {&g_sceneFlags[FREEZE_ACTOR_INDEX].active, GAME_LOOP, GZ_freezeActors, GZ_unfreezeActors},
    {&g_sceneFlags[HIDE_ACTOR_INDEX].active, GAME_LOOP, GZ_hideActors, GZ_showActors},
    {&g_sceneFlags[FREEZE_CAMERA_INDEX].active, GAME_LOOP, GZ_freezeCamera, GZ_unfreezeCamera},
    {&g_sceneFlags[HIDE_HUD_INDEX].active, GAME_LOOP, GZ_hideHUD, GZ_showHUD},
    {&g_sceneFlags[FREEZE_TIME_INDEX].active, GAME_LOOP, GZ_freezeTime},
    {&g_sceneFlags[DISABLE_BG_INDEX].active, GAME_LOOP, GZ_disableBGM, GZ_enableBGM},
    {&g_sceneFlags[DISABLE_SFX_INDEX].active, GAME_LOOP, GZ_disableSFX, GZ_enableSFX},
};

#ifdef GCN_PLATFORM
#define HOLD_BTNS cPadInfo[0].mButtonFlags
#define TRIG_BTNS cPadInfo[0].mPressedButtonFlags
#endif

#ifdef WII_PLATFORM
#define HOLD_BTNS mPad.mHoldButton
#define TRIG_BTNS mPad.mTrigButton
#endif

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
    for (int i = 0; i < MAX_GZ_FLAGS; i++) {
        if (g_gzFlags[i].mPhase == phase && g_gzFlags[i].mpFlag != nullptr) {
            if (*g_gzFlags[i].mpFlag && g_gzFlags[i].mpActiveFunc) {
                g_gzFlags[i].mpActiveFunc();
            } else if (g_gzFlags[i].mpDeactiveFunc) {
                g_gzFlags[i].mpDeactiveFunc();
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
