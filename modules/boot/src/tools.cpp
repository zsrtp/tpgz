#include "tools.h"
#include "libtp_c/include/d/a/d_a_alink.h"
#include "libtp_c/include/defines.h"

#include "commands.h"
#include "global_data.h"
#include "settings.h"

int g_tunic_color;

KEEP_FUNC void GZ_handleTools() {
    if (GZStng_getSettingData(STNG_TOOLS_FRAME_ADVANCE, false) && !GZCmd_getCmd(CMD_FRAME_PAUSE)) {
        GZCmd_addCmd(new Command{CMD_FRAME_PAUSE, FRAME_PAUSE_BUTTONS, GZCmd_pauseFrame});
    } else if (!GZStng_getSettingData(STNG_TOOLS_FRAME_ADVANCE, false) &&
               GZCmd_getCmd(CMD_FRAME_PAUSE)) {
        auto* cmd = GZCmd_removeCmd(CMD_FRAME_PAUSE);
        delete cmd;
    }

    if (!(GZStng_getSettingData(STNG_TOOLS_TIMER, false) ||
          GZStng_getSettingData(STNG_TOOLS_IGT_TIMER, false)) &&
        GZCmd_getCmd(CMD_TIMER_TOGGLE)) {
        auto* cmd = GZCmd_removeCmd(CMD_TIMER_TOGGLE);
        delete cmd;
    }

    if (!(GZStng_getSettingData(STNG_TOOLS_TIMER, false) ||
          GZStng_getSettingData(STNG_TOOLS_IGT_TIMER, false) ||
          GZStng_getSettingData(STNG_TOOLS_LOAD_TIMER, false)) &&
        GZCmd_getCmd(CMD_TIMER_RESET)) {
        auto* cmd = GZCmd_removeCmd(CMD_TIMER_RESET);
        delete cmd;
    }

    if (GZStng_getSettingData(STNG_TOOLS_TIMER, false) && !GZCmd_getCmd(CMD_TIMER_TOGGLE)) {
        GZCmd_addCmd(new Command{CMD_TIMER_TOGGLE, TIMER_TOGGLE_BUTTONS, GZCmd_toggleTimer});
    }

    if (GZStng_getSettingData(STNG_TOOLS_TIMER, false) && !GZCmd_getCmd(CMD_TIMER_RESET)) {
        GZCmd_addCmd(new Command{CMD_TIMER_RESET, TIMER_RESET_BUTTONS, GZCmd_resetTimer});
    }

    if (GZStng_getSettingData(STNG_TOOLS_IGT_TIMER, false) && !GZCmd_getCmd(CMD_TIMER_TOGGLE)) {
        GZCmd_addCmd(new Command{CMD_TIMER_TOGGLE, TIMER_TOGGLE_BUTTONS, GZCmd_toggleTimer});
    }

    if (GZStng_getSettingData(STNG_TOOLS_IGT_TIMER, false) && !GZCmd_getCmd(CMD_TIMER_RESET)) {
        GZCmd_addCmd(new Command{CMD_TIMER_RESET, TIMER_RESET_BUTTONS, GZCmd_resetTimer});
    }

    if (GZStng_getSettingData(STNG_TOOLS_LOAD_TIMER, false) && !GZCmd_getCmd(CMD_TIMER_RESET)) {
        GZCmd_addCmd(new Command{CMD_TIMER_RESET, TIMER_RESET_BUTTONS, GZCmd_resetTimer});
    }

    if (GZStng_getSettingData(STNG_TOOLS_TELEPORT, false) && !GZCmd_getCmd(CMD_STORE_POSITION)) {
        GZCmd_addCmd(new Command{CMD_STORE_POSITION, STORE_POSITION_BUTTONS, GZCmd_storePosition});
    } else if (!GZStng_getSettingData(STNG_TOOLS_TELEPORT, false) &&
               GZCmd_getCmd(CMD_STORE_POSITION)) {
        auto* cmd = GZCmd_removeCmd(CMD_STORE_POSITION);
        delete cmd;
    }

    if (GZStng_getSettingData(STNG_TOOLS_TELEPORT, false) && !GZCmd_getCmd(CMD_LOAD_POSITION)) {
        GZCmd_addCmd(new Command{CMD_LOAD_POSITION, LOAD_POSITION_BUTTONS, GZCmd_loadPosition});
    } else if (!GZStng_getSettingData(STNG_TOOLS_TELEPORT, false) &&
               GZCmd_getCmd(CMD_LOAD_POSITION)) {
        auto* cmd = GZCmd_removeCmd(CMD_LOAD_POSITION);
        delete cmd;
    }

    if (GZStng_getSettingData(STNG_TOOLS_RELOAD_AREA, false) && !GZCmd_getCmd(CMD_RELOAD_AREA)) {
        GZCmd_addCmd(new Command{CMD_RELOAD_AREA, RELOAD_AREA_BUTTONS, GZCmd_reloadArea});
    } else if (!GZStng_getSettingData(STNG_TOOLS_RELOAD_AREA, false) &&
               GZCmd_getCmd(CMD_RELOAD_AREA)) {
        auto* cmd = GZCmd_removeCmd(CMD_RELOAD_AREA);
        delete cmd;
    }

    if (GZStng_getSettingData(STNG_TOOLS_FREE_CAM, false) && !GZCmd_getCmd(CMD_FREE_CAM)) {
        GZCmd_addCmd(new Command{CMD_FREE_CAM, FREE_CAM_BUTTONS, GZCmd_toggleFreeCam});
        g_freeCamEnabled = false;
    } else if (!GZStng_getSettingData(STNG_TOOLS_FREE_CAM, false) && GZCmd_getCmd(CMD_FREE_CAM)) {
        auto* cmd = GZCmd_removeCmd(CMD_FREE_CAM);
        delete cmd;
        g_freeCamEnabled = false;
    }

    if (GZStng_getSettingData(STNG_TOOLS_MOVE_LINK, false) && !GZCmd_getCmd(CMD_MOVE_LINK)) {
        GZCmd_addCmd(new Command{CMD_MOVE_LINK, MOVE_LINK_BUTTONS, GZCmd_toggleMoveLink});
        g_moveLinkEnabled = false;
    } else if (!GZStng_getSettingData(STNG_TOOLS_MOVE_LINK, false) && GZCmd_getCmd(CMD_MOVE_LINK)) {
        auto* cmd = GZCmd_removeCmd(CMD_MOVE_LINK);
        delete cmd;
        g_moveLinkEnabled = false;
    }

    if (GZStng_getSettingData(STNG_TOOLS_FAST_MOVEMENT, false)) {
        daAlinkHIO_frontRoll.mSpeedRate = 3.0f;
        daAlinkHIO_swim.mMaxUnderwaterSpeed = 50;
        daAlinkHIO_swim.mMaxBackwardSpeed = 50;
        daAlinkHIO_swim.mMaxStrafeSpeed = 50;
        daAlinkHIO_swim.mDashMaxSpeed = 50;
        daAlinkHIO_swim.mMaxForwardSpeed = 50;
        daAlinkHIO_swim.mUnderwaterMaxSinkSpeed = 50;
        daAlinkHIO_swim.mBootsMaxSinkSpeed = -50;
        daAlinkHIO_swim.mBootsGravity = -50;
        daAlinkHIO_wlMove.mDashInitSpeed = 100;
        daAlinkHIO_wlMove.mDashMaxSpeed = 100;
        daAlinkHIO_wlMove.mDashInitSpeedSlow = 70;
        daAlinkHIO_wlMove.mDashMaxSpeedSlow = 70;
        daAlinkHIO_wlSwim.mMaxSpeed = 50;
        daAlinkHIO_wlSwim.mMaxSpeedWeak = 50;
    } else {
        daAlinkHIO_frontRoll.mSpeedRate = 1.3;
        daAlinkHIO_swim.mMaxUnderwaterSpeed = 12;
        daAlinkHIO_swim.mMaxForwardSpeed = 8;
        daAlinkHIO_swim.mMaxBackwardSpeed = 6;
        daAlinkHIO_swim.mMaxStrafeSpeed = 8;
        daAlinkHIO_swim.mDashMaxSpeed = 13;
        daAlinkHIO_swim.mUnderwaterMaxSinkSpeed = 8;
        daAlinkHIO_swim.mBootsMaxSinkSpeed = -20;
        daAlinkHIO_swim.mBootsGravity = -0.699999988;
        daAlinkHIO_wlMove.mDashInitSpeed = 65;
        daAlinkHIO_wlMove.mDashMaxSpeed = 45;
        daAlinkHIO_wlMove.mDashInitSpeedSlow = 35;
        daAlinkHIO_wlMove.mDashMaxSpeedSlow = 33;
        daAlinkHIO_wlSwim.mMaxSpeed = 20;
        daAlinkHIO_wlSwim.mMaxSpeedWeak = 9;
    }

    if (GZStng_getSettingData(STNG_TOOLS_FAST_BONK, false)) {
        daAlinkHIO_frontRoll.mCrashAnm.field_0x04 = 50.0f;
        daAlinkHIO_frontRoll.mCrashAnm.field_0x08 = 0.0f;
    } else {
        daAlinkHIO_frontRoll.mCrashAnm.field_0x04 = 3.0f;
        daAlinkHIO_frontRoll.mCrashAnm.field_0x08 = 0.800000012f;
    }
}