#include "menus/tools_menu.h"
#include "commands.h"
#include "free_cam.h"
#include "gorge.h"
#ifdef WII_PLATFORM
#include "bit.h"
#endif
#include "libtp_c/include/msl_c/string.h"
#include "movelink.h"
#include "rollcheck.h"
#include "timer.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "umd.h"
#include "gz_flags.h"
#include "rels/include/defines.h"

#define MAX_TUNIC_COLORS 7

ToolsMenu::ToolsMenu()
    : Menu(),
      lines{{"area reload", RELOAD_AREA_INDEX, "Use " RELOAD_AREA_TEXT " to reload current area",
             true, &g_tools[RELOAD_AREA_INDEX].active},
            {"frame advance", FRAME_ADVANCE_INDEX, "Use " FRAME_ADVANCE_TEXT " to frame advance",
             true, &g_tools[FRAME_ADVANCE_INDEX].active},
            {"fast bonk recovery", FAST_BONK_INDEX, "Reduces bonk animation significantly", true,
             &g_tools[FAST_BONK_INDEX].active},
            {"fast movement", FAST_MOVEMENT_INDEX, "Link's movement is much faster", true,
             &g_tools[FAST_MOVEMENT_INDEX].active},
            {"gorge checker", GORGE_INDEX, "Use " GORGE_VOID_TEXT " to warp to Kakariko Gorge",
             true, &g_tools[GORGE_INDEX].active},
#ifdef WII_PLATFORM
            {"bit checker", BIT_INDEX, "Use " BACK_IN_TIME_TEXT " to warp to Ordon Bridge", true,
             &g_tools[BIT_INDEX].active},
#endif
            {"coro td checker", COROTD_INDEX, "Show frame info when doing coro td", true,
             &g_tools[COROTD_INDEX].active},
            {"umd checker", UMD_INDEX, "Practice Snowpeak UMD timing", true,
             &g_tools[UMD_INDEX].active},
            {"input viewer", INPUT_VIEWER_INDEX, "Show current inputs", true,
             &g_tools[INPUT_VIEWER_INDEX].active},
            {"link debug info", LINK_DEBUG_INDEX, "Show Link's position, angle, and speed", true,
             &g_tools[LINK_DEBUG_INDEX].active},
            {"heap debug info", HEAP_DEBUG_INDEX, "Show Heap size info", true,
             &g_tools[HEAP_DEBUG_INDEX].active},
            {"no sinking in sand", SAND_INDEX, "Link won't sink in sand", true,
             &g_tools[SAND_INDEX].active},
            {"roll checker", ROLL_INDEX, "Frame counter for chaining rolls", true,
             &g_tools[ROLL_INDEX].active},
            {"teleport", TELEPORT_INDEX,
             STORE_POSITION_TEXT " to set, " LOAD_POSITION_TEXT " to load", true,
             &g_tools[TELEPORT_INDEX].active},
            {"turbo mode", TURBO_MODE_INDEX, "Simulates turbo controller inputs", true,
             &g_tools[TURBO_MODE_INDEX].active},
            {"timer", TIMER_INDEX,
             "Frame timer: " TIMER_TOGGLE_TEXT " to start/stop, " TIMER_RESET_TEXT " to reset",
             true, &g_tools[TIMER_INDEX].active},
            {"load timer", LOAD_TIMER_INDEX, "Loading zone timer: " TIMER_RESET_TEXT " to reset",
             true, &g_tools[LOAD_TIMER_INDEX].active},
            {"igt timer", IGT_TIMER_INDEX,
             "In-game time timer: " TIMER_TOGGLE_TEXT " to start/stop, " TIMER_RESET_TEXT
             " to reset",
             true, &g_tools[IGT_TIMER_INDEX].active},
            {"free cam", FREE_CAM_INDEX,
             FREE_CAM_TEXT " to activate, " FREE_CAM_MOVEMENT_TEXT " to move, " FREE_CAM_VIEW_TEXT
                           " to view, Z to speed",
             true, &g_tools[FREE_CAM_INDEX].active},
            {"move link", MOVE_LINK_INDEX,
             MOVE_LINK_TEXT " to activate. " MOVE_LINK_MOVEMENT_TEXT
                            " to move, " MOVE_LINK_ANGLE_TEXT " to change angle",
             true, &g_tools[MOVE_LINK_INDEX].active},
            {"link tunic color:", TUNIC_COLOR_INDEX, "Changes Link's tunic color", false, nullptr,
             MAX_TUNIC_COLORS}} {
}

int g_tunic_color;

Tool g_tools[TOOL_AMNT] = {
    {RELOAD_AREA_INDEX, false},   {FRAME_ADVANCE_INDEX, false}, {FAST_BONK_INDEX, false},
    {FAST_MOVEMENT_INDEX, false}, {GORGE_INDEX, false},
#ifdef WII_PLATFORM
    {BIT_INDEX, false},
#endif
    {COROTD_INDEX, false},        {UMD_INDEX, false},           {INPUT_VIEWER_INDEX, false},
    {LINK_DEBUG_INDEX, false},    {HEAP_DEBUG_INDEX, false},    {SAND_INDEX, false},
    {ROLL_INDEX, false},          {TELEPORT_INDEX, false},      {TURBO_MODE_INDEX, false},
    {TIMER_INDEX, false},         {LOAD_TIMER_INDEX, false},    {IGT_TIMER_INDEX, false},
    {FREE_CAM_INDEX, false},      {MOVE_LINK_INDEX, false},
};

void ToolsMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        GZ_setMenu(GZ_MAIN_MENU);
        return;
    }

    ListMember tunicCol_opt[MAX_TUNIC_COLORS] = {"green",  "blue",  "red",  "orange",
                                                 "yellow", "white", "cycle"};

    if (cursor.y == TUNIC_COLOR_INDEX) {
        cursor.x = l_tunicCol_idx;
        cursor.move(MAX_TUNIC_COLORS, MENU_LINE_NUM);

        if (cursor.y == TUNIC_COLOR_INDEX) {
            l_tunicCol_idx = cursor.x;
        }
        g_tunic_color = l_tunicCol_idx;
    } else {
        cursor.move(0, MENU_LINE_NUM);
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        g_tools[cursor.y].active = !g_tools[cursor.y].active;
        if (g_tools[cursor.y].active) {
            switch (cursor.y) {
            case FRAME_ADVANCE_INDEX:
                GZCmd_enable(Commands::CMD_FRAME_PAUSE);
                break;
            case TIMER_INDEX:
                g_tools[LOAD_TIMER_INDEX].active = false;
                g_tools[IGT_TIMER_INDEX].active = false;
                GZCmd_enable(Commands::CMD_TIMER_TOGGLE);
                GZCmd_enable(Commands::CMD_TIMER_RESET);
                break;
            case LOAD_TIMER_INDEX:
                g_tools[TIMER_INDEX].active = false;
                g_tools[IGT_TIMER_INDEX].active = false;
                GZCmd_enable(Commands::CMD_TIMER_RESET);
                break;
            case IGT_TIMER_INDEX:
                g_tools[TIMER_INDEX].active = false;
                g_tools[LOAD_TIMER_INDEX].active = false;
                GZCmd_enable(Commands::CMD_TIMER_TOGGLE);
                GZCmd_enable(Commands::CMD_TIMER_RESET);
                break;
            case GORGE_INDEX:
                GZCmd_enable(Commands::CMD_GORGE_VOID);
                break;
#ifdef WII_PLATFORM
            case BIT_INDEX:
                GZCmd_enable(Commands::CMD_BIT);
                break;
#endif
            case TELEPORT_INDEX:
                GZCmd_enable(Commands::CMD_STORE_POSITION);
                GZCmd_enable(Commands::CMD_LOAD_POSITION);
                break;
            case RELOAD_AREA_INDEX:
                GZCmd_enable(Commands::CMD_RELOAD_AREA);
                break;
            case FAST_MOVEMENT_INDEX:
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
                break;
            case FAST_BONK_INDEX:
                daAlinkHIO_frontRoll.mCrashAnm.field_0x04 = 50.0f;
                daAlinkHIO_frontRoll.mCrashAnm.field_0x08 = 0.0f;
                break;
            case SAND_INDEX:
                if (dComIfGp_getPlayer() != nullptr) {
                    dComIfGp_getPlayer()->field_0x2ba8 = 0;
                }
                break;
            case FREE_CAM_INDEX:
                GZCmd_enable(Commands::CMD_FREE_CAM);
                g_freeCamEnabled = false;
                break;
            case MOVE_LINK_INDEX:
                GZCmd_enable(Commands::CMD_MOVE_LINK);
                g_moveLinkEnabled = false;
                break;
            }
        } else {
            switch (cursor.y) {
            case FRAME_ADVANCE_INDEX:
                GZCmd_disable(Commands::CMD_FRAME_PAUSE);
                break;
            case TELEPORT_INDEX:
                GZCmd_disable(Commands::CMD_STORE_POSITION);
                GZCmd_disable(Commands::CMD_LOAD_POSITION);
                break;
            case RELOAD_AREA_INDEX:
                GZCmd_disable(Commands::CMD_RELOAD_AREA);
                break;
            case FAST_MOVEMENT_INDEX:
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
                break;
            case FAST_BONK_INDEX:
                daAlinkHIO_frontRoll.mCrashAnm.field_0x04 = 3.0f;
                daAlinkHIO_frontRoll.mCrashAnm.field_0x08 = 0.800000012f;
                break;
            case FREE_CAM_INDEX:
                GZCmd_disable(Commands::CMD_FREE_CAM);
                g_freeCamEnabled = false;
                break;
            case MOVE_LINK_INDEX:
                GZCmd_disable(Commands::CMD_MOVE_LINK);
                g_moveLinkEnabled = false;
                break;
            case GORGE_INDEX:
                GZCmd_disable(Commands::CMD_GORGE_VOID);
                break;
#ifdef WII_PLATFORM
            case BIT_INDEX:
                GZCmd_disable(Commands::CMD_BIT);
                break;
#endif
            }
        }
    }

    tp_sprintf(lines[TUNIC_COLOR_INDEX].value, " <%s>", tunicCol_opt[l_tunicCol_idx].member);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}

KEEP_FUNC void ToolsMenu::setTunicColor() {
    static int16_t cycle_r = 0;
    static int16_t cycle_g = 0;
    static int16_t cycle_b = 0;

    if (dComIfGp_getPlayer()) {
        int16_t r = 0;
        int16_t g = 0;
        int16_t b = 0;

        switch (g_tunic_color) {
        case GREEN:
        default:
            r = 0x10;
            g = 0x10;
            b = 0x10;
            break;
        case BLUE:
            r = 0x00;
            g = 0x08;
            b = 0x20;
            break;
        case RED:
            r = 0x18;
            g = 0x00;
            b = 0x00;
            break;
        case ORANGE:
            r = 0x20;
            g = 0x10;
            b = 0x00;
            break;
        case YELLOW:
            r = 0x20;
            g = 0x20;
            b = 0x00;
            break;
        case WHITE:
            r = 0x20;
            g = 0x1C;
            b = 0x20;
            break;
        case CYCLE:
            if (cycle_r < 0x0010 && (cycle_g == 0x0000 && cycle_b == 0x0000)) {
                cycle_r += 0x0001;
            } else if (cycle_g < 0x0010 && (cycle_b == 0x0000 && cycle_r == 0x0010)) {
                cycle_g += 0x0001;
            } else if (cycle_b < 0x0010 && (cycle_g == 0x0010 && cycle_r == 0x0010)) {
                cycle_b += 0x0001;
            } else if (cycle_r > 0x0000 && (cycle_g == 0x0010 && cycle_b == 0x0010)) {
                cycle_r -= 0x0001;
            } else if (cycle_g > 0x0000 && (cycle_b == 0x0010 && cycle_r == 0x0000)) {
                cycle_g -= 0x0001;
            } else {
                cycle_b -= 0x0001;
            }

            r = cycle_r;
            g = cycle_g;
            b = cycle_b;
            break;
        }

        dComIfGp_getPlayer()->field_0x32a0[0].mColor.r = r - 0x10;
        dComIfGp_getPlayer()->field_0x32a0[0].mColor.g = g - 0x10;
        dComIfGp_getPlayer()->field_0x32a0[0].mColor.b = b - 0x10;
        dComIfGp_getPlayer()->field_0x32a0[1].mColor.r = r - 0x10;
        dComIfGp_getPlayer()->field_0x32a0[1].mColor.g = g - 0x10;
        dComIfGp_getPlayer()->field_0x32a0[1].mColor.b = b - 0x10;
    }
}