#include "commands.h"
#include "controller.h"
#include "global_data.h"
#include "fs.h"
#include "boot.h"
#include "libtp_c/include/JSystem/JUtility/JUTGamePad.h"
#include "practice.h"
#include "settings.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/f_op/f_op_draw_tag.h"
#include "timer.h"
#include "utils/loading.h"
#include "gz_flags.h"
#include "save_manager.h"

bool reload_area_flag = false;
bool g_timerEnabled = false;
bool g_resetTimer = false;

KEEP_VAR bool g_commandStates[COMMANDS_AMNT];

static Vec sSavePlayerPos = {0.0f, 0.0f, 0.0f};
static int16_t sSavePlayerAngle = 0;
static Vec sSaveCamPos = {0.0f, 0.0f, 0.0f};
static Vec sSaveCamTarget = {0.0f, 0.0f, 0.0f};

static int sLastInputs;
static int sCurInputs;

KEEP_FUNC bool GZCmd_checkTrig(int combo) {
    if (sCurInputs == combo && sLastInputs != combo) {
        return true;
    }
    return false;
}

KEEP_FUNC void GZCmd_pauseFrame() {
    if (GZCmd_checkTrig(FRAME_PAUSE_BUTTONS)) {
        g_framePaused = !g_framePaused;
    }
}

KEEP_FUNC void GZCmd_storePosition() {
    if (dComIfGp_getPlayer()) {
        sSavePlayerPos = dComIfGp_getPlayer()->current.pos;
        sSavePlayerAngle = dComIfGp_getPlayer()->shape_angle.y;
    }

    if (matrixInfo.matrix_info) {
        sSaveCamPos = matrixInfo.matrix_info->pos;
        sSaveCamTarget = matrixInfo.matrix_info->target;
    }
}

KEEP_FUNC void GZCmd_loadPosition() {
    if (dComIfGp_getPlayer()) {
        dComIfGp_getPlayer()->current.pos = sSavePlayerPos;
        dComIfGp_getPlayer()->shape_angle.y = sSavePlayerAngle;
    }

    if (matrixInfo.matrix_info) {
        matrixInfo.matrix_info->pos = sSaveCamPos;
        matrixInfo.matrix_info->target = sSaveCamTarget;
    }
}

KEEP_FUNC void GZCmd_toggleTimer() {
    if (GZCmd_checkTrig(TIMER_TOGGLE_BUTTONS)) {
        g_timerEnabled = !g_timerEnabled;
    }
}

KEEP_FUNC void GZCmd_resetTimer() {
    g_resetTimer = true;
}

KEEP_FUNC void GZCmd_reloadArea() {
    g_dComIfG_gameInfo.play.mNextStage.enabled = true;
    SaveManager::s_injectSave = true;

    uint32_t reloadType = GZStng_getSettingData(STNG_TOOLS_RELOAD_AREA, 0);
    if (reloadType == LOAD_AREA) {
        // restore last set of saved temp flags
        memcpy(&g_dComIfG_gameInfo.info.mMemory, gSaveManager.mAreaReloadOpts.temp_flags,
               sizeof(gSaveManager.mAreaReloadOpts.temp_flags));

        // restore last tear count
        for (int i = 0; i < 4; i++) {
            dComIfGs_setLightDropNum(i, gSaveManager.mAreaReloadOpts.tears[i]);
        }

        gSaveManager.mPracticeFileOpts.inject_options_before_load =
            SaveManager::injectDefault_before;
        gSaveManager.mPracticeFileOpts.inject_options_during_load = nullptr;
        gSaveManager.mPracticeFileOpts.inject_options_after_load = nullptr;
    } else {
        SaveManager::loadSave(last_save_index, last_category, last_special_ptr, 0xFF);
    }
}

KEEP_FUNC void GZCmd_toggleFreeCam() {
    if (GZCmd_checkTrig(FREE_CAM_BUTTONS)) {
        g_freeCamEnabled = !g_freeCamEnabled;
    }
}

KEEP_FUNC void GZCmd_toggleMoveLink() {
    if (GZCmd_checkTrig(MOVE_LINK_BUTTONS)) {
        g_moveLinkEnabled = !g_moveLinkEnabled;
    }
}

KEEP_VAR tpgz::containers::deque<Command*> g_commands;

KEEP_FUNC void GZCmd_addCmd(Command* cmd) {
    g_commands.push_back(cmd);
}

KEEP_FUNC Command* GZCmd_removeCmd(Commands cmdId) {
    auto it = g_commands.begin();
    for (; it != g_commands.end(); ++it) {
        if ((*it)->id == cmdId) {
            break;
        }
    }
    auto* cmd = *it;
    g_commands.erase(it);
    return cmd;
}

KEEP_FUNC Command* GZCmd_getCmd(int id) {
    auto it = g_commands.begin();
    for (;it != g_commands.end(); ++it) {
        if ((*it)->id == id) {
            return *it;
        }
    }
    return nullptr;
}

KEEP_FUNC void GZCmd_processInputs() {
    sCurInputs = GZ_getButtonStatus();
    for (auto c : g_commands) {
        if (sCurInputs == c->buttons) {
            c->command();
            setGamepadButtons(0x0);
            setGamepadTrig(0x0);
            mPadButton.mRepeat = 0x0;
            mPadStatus.button = 0x0;
        }
    }
    sLastInputs = sCurInputs;
}