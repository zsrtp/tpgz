#include "commands.h"
#include "controller.h"
#include "free_cam.h"
#include "fs.h"
#include "gorge.h"
#ifdef WII_PLATFORM
#include "bit.h"
#endif
#include "lib.h"
#include "libtp_c/include/JSystem/JUtility/JUTGamePad.h"
#include "libtp_c/include/msl_c/string.h"
#include "menus/practice_menu.h"
#include "menus/settings_menu.h"
#include "menus/hundo_saves_menu.h"
#include "movelink.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/f_op/f_op_draw_tag.h"
#include "timer.h"
#include "utils/loading.h"
#include "gz_flags.h"

bool reload_area_flag = false;
bool g_timerEnabled = false;
bool g_resetTimer = false;

bool g_commandStates[COMMANDS_AMNT];

static Vec sSavePlayerPos = {0.0f, 0.0f, 0.0f};
static int16_t sSavePlayerAngle = 0;
static Vec sSaveCamPos = {0.0f, 0.0f, 0.0f};
static Vec sSaveCamTarget = {0.0f, 0.0f, 0.0f};

static int sLastInputs;
static int sCurInputs;

bool GZCmd_checkTrig(int combo) {
    if (sCurInputs == combo && sLastInputs != combo) {
        return true;
    }
    return false;
}

void GZCmd_pauseFrame() {
    if (GZCmd_checkTrig(FRAME_PAUSE_BUTTONS)) {
        g_framePaused = !g_framePaused;
    }
}

void GZCmd_storePosition() {
    if (dComIfGp_getPlayer()) {
        sSavePlayerPos = dComIfGp_getPlayer()->mCurrent.mPosition;
        sSavePlayerAngle = dComIfGp_getPlayer()->mCollisionRot.mY;
    }

    if (tp_matrixInfo.matrix_info) {
        sSaveCamPos = tp_matrixInfo.matrix_info->pos;
        sSaveCamTarget = tp_matrixInfo.matrix_info->target;
    }
}

void GZCmd_loadPosition() {
    if (dComIfGp_getPlayer()) {
        dComIfGp_getPlayer()->mCurrent.mPosition = sSavePlayerPos;
        dComIfGp_getPlayer()->mCollisionRot.mY = sSavePlayerAngle;
    }

    if (tp_matrixInfo.matrix_info) {
        tp_matrixInfo.matrix_info->pos = sSaveCamPos;
        tp_matrixInfo.matrix_info->target = sSaveCamTarget;
    }
}

void GZCmd_moonJump() {
    if (dComIfGp_getPlayer()) {
        dComIfGp_getPlayer()->mSpeed.y = 56.0f;
    }
}

void GZCmd_toggleTimer() {
    if (GZCmd_checkTrig(TIMER_TOGGLE_BUTTONS)) {
        g_timerEnabled = !g_timerEnabled;
    }
}

void GZCmd_resetTimer() {
    g_resetTimer = true;
}

void GZCmd_reloadArea() {
    g_injectSave = true;

    if (g_reloadType == LOAD_AREA) {
        // restore last set of saved temp flags
        tp_memcpy(&g_dComIfG_gameInfo.info.mMemory, 
                  gSaveManager.mAreaReloadOpts.temp_flags,
                  sizeof(gSaveManager.mAreaReloadOpts.temp_flags));

        // restore last tear count
        for (int i = 0; i < 4; i++) {
            dComIfGs_setLightDropNum(i, gSaveManager.mAreaReloadOpts.tears[i]);
        }

        gSaveManager.mPracticeFileOpts.inject_options_before_load = SaveManager::injectDefault_before;
        gSaveManager.mPracticeFileOpts.inject_options_during_load = nullptr;
        gSaveManager.mPracticeFileOpts.inject_options_after_load = nullptr;
    } else {
        SaveManager::loadSave(last_save_index, last_category, last_special_ptr, 0xFF);
    }
}

void GZCmd_loadGorgeVoid() {
    if (GZCmd_checkTrig(GORGE_VOID_BUTTONS)) {
        SaveManager::loadSavefile("tpgz/save_files/any/gorge_void.bin");
        gSaveManager.mPracticeFileOpts.inject_options_before_load =
            SaveManager::injectDefault_before;
        gSaveManager.mPracticeFileOpts.inject_options_during_load =
            GorgeVoidIndicator::warpToPosition;
        gSaveManager.mPracticeFileOpts.inject_options_after_load =
            GorgeVoidIndicator::initState;
        g_injectSave = true;
    }
}

#ifdef WII_PLATFORM
void GZCmd_bitPractice() {
    if (GZCmd_checkTrig(BACK_IN_TIME_BUTTONS)) {
        SaveManager::loadSavefile("tpgz/save_files/any/ordon_gate_clip.bin");
        gSaveManager.mPracticeFileOpts.inject_options_before_load =
            SaveManager::injectDefault_before;
        gSaveManager.mPracticeFileOpts.inject_options_during_load =
            SaveManager::injectDefault_during;
        gSaveManager.mPracticeFileOpts.inject_options_after_load =
            BiTIndicator::setPosition;
        gSaveManager.mPracticeFileOpts.inject_options_after_counter = 10;
        g_injectSave = true;
    }
}
#endif

void GZCmd_toggleFreeCam() {
    if (GZCmd_checkTrig(FREE_CAM_BUTTONS)) {
        g_freeCamEnabled = !g_freeCamEnabled;
    }
}

void GZCmd_toggleMoveLink() {
    if (GZCmd_checkTrig(MOVE_LINK_BUTTONS)) {
        g_moveLinkEnabled = !g_moveLinkEnabled;
    }
}

static Command sCommands[COMMANDS_AMNT] = {
    {g_commandStates[CMD_STORE_POSITION], STORE_POSITION_BUTTONS, GZCmd_storePosition},
    {g_commandStates[CMD_LOAD_POSITION], LOAD_POSITION_BUTTONS, GZCmd_loadPosition},
    {g_commandStates[CMD_MOON_JUMP], MOON_JUMP_BUTTONS, GZCmd_moonJump},
    {g_commandStates[CMD_RELOAD_AREA], RELOAD_AREA_BUTTONS, GZCmd_reloadArea},
    {g_commandStates[CMD_TIMER_TOGGLE], TIMER_TOGGLE_BUTTONS, GZCmd_toggleTimer},
    {g_commandStates[CMD_TIMER_RESET], TIMER_RESET_BUTTONS, GZCmd_resetTimer},
    {g_commandStates[CMD_GORGE_VOID], GORGE_VOID_BUTTONS, GZCmd_loadGorgeVoid},
#ifdef WII_PLATFORM
    {g_commandStates[CMD_BIT], BACK_IN_TIME_BUTTONS, GZCmd_bitPractice},
#endif
    {g_commandStates[CMD_FREE_CAM], FREE_CAM_BUTTONS, GZCmd_toggleFreeCam},
    {g_commandStates[CMD_MOVE_LINK], MOVE_LINK_BUTTONS, GZCmd_toggleMoveLink},
    {g_commandStates[CMD_FRAME_PAUSE], FRAME_PAUSE_BUTTONS, GZCmd_pauseFrame},
};

void GZCmd_processInputs() {
    sCurInputs = GZ_getButtonStatus();
    for (auto c : sCommands) {
        if (c.active && GZ_getButtonStatus() == c.buttons) {
            c.command();
            setGamepadButtons(0x0);
            setGamepadTrig(0x0);
            tp_mPadButton.mRepeat = 0x0;
            tp_mPadStatus.button = 0x0;
        }
    }
    sLastInputs = sCurInputs;
}

void GZCmd_enable(int idx) {
    sCommands[idx].active = true;
}

void GZCmd_disable(int idx) {
    sCommands[idx].active = false;
}