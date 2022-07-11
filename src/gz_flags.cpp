#include "gz_flags.h"
#include "fifo_queue.h"
#include "gorge.h"
#include "bit.h"
#include "menus/scene_menu.h"
#include "menus/settings_menu.h"
#include "menus/tools_menu.h"
#include "rollcheck.h"
#include "utils/audio.h"
#include "utils/lines.h"
#include "utils/link.h"
#include "utils/loading.h"
#include "flaglog.h"
#include "save_manager.h"
#include "menus/memfiles_menu.h"
#include "corotdcheck.h"
#include "umd.h"
#include "utils/draw.h"

bool g_injectSave = false;
bool g_framePaused = false;

GZFlag g_gzFlags[MAX_GZ_FLAGS] = {
    {&g_tools[GORGE_INDEX].active, GAME_LOOP, GorgeVoidIndicator::execute},
#ifdef WII_PLATFORM
    {&g_tools[BIT_INDEX].active, GAME_LOOP, BiTIndicator::execute},
#endif
    {&g_tools[ROLL_INDEX].active, GAME_LOOP, RollIndicator::execute},
    {&g_tools[COROTD_INDEX].active, GAME_LOOP, CoroTDChecker::execute},
    {&g_tools[UMD_INDEX].active, POST_GAME_LOOP, UMDIndicator::execute},
    {&g_injectSave, GAME_LOOP, SaveManager::triggerLoad},
    {&g_sceneFlags[FREEZE_ACTOR_INDEX].active, GAME_LOOP, GZ_freezeActors, GZ_unfreezeActors},
    {&g_sceneFlags[HIDE_ACTOR_INDEX].active, GAME_LOOP, GZ_hideActors, GZ_showActors},
    {&g_sceneFlags[FREEZE_CAMERA_INDEX].active, GAME_LOOP, GZ_freezeCamera, GZ_unfreezeCamera},
    {&g_sceneFlags[HIDE_HUD_INDEX].active, GAME_LOOP, GZ_hideHUD, GZ_showHUD},
    {&g_sceneFlags[FREEZE_TIME_INDEX].active, GAME_LOOP, GZ_freezeTime},
    {&g_sceneFlags[DISABLE_BG_INDEX].active, GAME_LOOP, GZ_disableBGM, GZ_enableBGM},
    {&g_sceneFlags[DISABLE_SFX_INDEX].active, GAME_LOOP, GZ_disableSFX, GZ_enableSFX},
    {&g_injectMemfile, GAME_LOOP, GZMemfile_setLinkPosition}
};

void GZ_frameAdvance() {
    sPauseTimer = 1;
    tp_cPadInfo[0].mPressedButtonFlags = tp_cPadInfo[0].mButtonFlags;

    if (GZ_getButtonTrig(FRAME_ADVANCE_BTN)) {
        // this sets pause timer to 0 for 1 frame,
        // which lets 1 frame pass before pausing again
        sPauseTimer = 0;
    }
}

void GZ_drawFrameTex(Texture* pauseTex, Texture* playTex) {
    if (g_framePaused) {
        if (sPauseTimer == 1) {
            Draw::drawRect(0xFFFFFFFF, {550.0f, 5.0f}, {32, 32}, &pauseTex->_texObj);
        } else {
            Draw::drawRect(0xFFFFFFFF, {550.0f, 5.0f}, {32, 32}, &playTex->_texObj);
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

    GZ_setCursorColor();
    ToolsMenu::setTunicColor();

    if (g_framePaused) {
        GZ_frameAdvance();
    }
}