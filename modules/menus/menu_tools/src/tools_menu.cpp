#include "menus/menu_tools/include/tools_menu.h"
#include <cstdio>
#include "commands.h"
#include "global_data.h"
#include "gorge.h"
#ifdef WII_PLATFORM
#include "bit.h"
#endif
#include "rollcheck.h"
#include "timer.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "umd.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

#ifdef GCN_PLATFORM
#define FREE_CAM_MOVEMENT_TEXT "Stick/L/R"
#define FREE_CAM_VIEW_TEXT "C-stick"
#define MOVE_LINK_MOVEMENT_TEXT "Stick/C"
#define MOVE_LINK_ANGLE_TEXT "C-left/right"
#define PREVIOUS_TUNIC_COLOR GZPad::Y
#define PREVIOUS_TUNIC_COLOR_TEXT "Y"
#define NEXT_TUNIC_COLOR GZPad::X
#define NEXT_TUNIC_COLOR_TEXT "X"
#endif
#ifdef WII_PLATFORM
#define FREE_CAM_MOVEMENT_TEXT "Stick+DPad"
#define FREE_CAM_VIEW_TEXT "C+Stick"
#define MOVE_LINK_MOVEMENT_TEXT "Stick"
#define MOVE_LINK_ANGLE_TEXT "C+Stick"
#define PREVIOUS_TUNIC_COLOR GZPad::ONE
#define PREVIOUS_TUNIC_COLOR_TEXT "ONE"
#define NEXT_TUNIC_COLOR GZPad::TWO
#define NEXT_TUNIC_COLOR_TEXT "TWO"
#endif

#ifdef GCN_PLATFORM
#endif
#ifdef WII_PLATFORM
#endif

#define MAX_TUNIC_COLORS 7

KEEP_FUNC ToolsMenu::ToolsMenu(Cursor& cursor, ToolsData& data)
    : Menu(cursor), l_tunicCol_idx(data.l_tunicCol_idx),
      lines{{"area reload", RELOAD_AREA_INDEX, "use " RELOAD_AREA_TEXT " to reload current area",
             true, &g_tools[RELOAD_AREA_INDEX].active},
            {"frame advance", FRAME_ADVANCE_INDEX, "use " FRAME_ADVANCE_TEXT " to frame advance",
             true, &g_tools[FRAME_ADVANCE_INDEX].active},
            {"fast bonk recovery", FAST_BONK_INDEX, "teduces bonk animation significantly", true,
             &g_tools[FAST_BONK_INDEX].active},
            {"fast movement", FAST_MOVEMENT_INDEX, "link's movement is much faster", true,
             &g_tools[FAST_MOVEMENT_INDEX].active},
            {"gorge checker", GORGE_INDEX, "use " GORGE_VOID_TEXT " to warp to kakariko gorge",
             true, &g_tools[GORGE_INDEX].active},
#ifdef WII_PLATFORM
            {"bit checker", BIT_INDEX, "use " BACK_IN_TIME_TEXT " to warp to ordon bridge", true,
             &g_tools[BIT_INDEX].active},
#endif
            {"coro td checker", COROTD_INDEX, "show frame info when doing coro td", true,
             &g_tools[COROTD_INDEX].active},
            {"umd checker", UMD_INDEX, "practice snowpeak universal map delay timing", true,
             &g_tools[UMD_INDEX].active},
            {"input viewer", INPUT_VIEWER_INDEX, "show current inputs", true,
             &g_tools[INPUT_VIEWER_INDEX].active},
            {"link debug info", LINK_DEBUG_INDEX, "show Link's position, angle, and speed", true,
             &g_tools[LINK_DEBUG_INDEX].active},
            {"heap debug info", HEAP_DEBUG_INDEX, "show Heap size info", true,
             &g_tools[HEAP_DEBUG_INDEX].active},
            {"no sinking in sand", SAND_INDEX, "link won't sink in sand", true,
             &g_tools[SAND_INDEX].active},
            {"roll checker", ROLL_INDEX, "frame counter for chaining rolls", true,
             &g_tools[ROLL_INDEX].active},
            {"mash checker", MASH_CHECKER_INDEX, "display A/B button mashing speeds", true,
             &g_tools[MASH_CHECKER_INDEX].active},
            {"teleport", TELEPORT_INDEX,
             STORE_POSITION_TEXT " to set, " LOAD_POSITION_TEXT " to load", true,
             &g_tools[TELEPORT_INDEX].active},
            {"turbo mode", TURBO_MODE_INDEX, "simulates turbo controller inputs", true,
             &g_tools[TURBO_MODE_INDEX].active},
            {"timer", TIMER_INDEX,
             "frame timer: " TIMER_TOGGLE_TEXT " to start/stop, " TIMER_RESET_TEXT " to reset",
             true, &g_tools[TIMER_INDEX].active},
            {"load timer", LOAD_TIMER_INDEX, "loading zone timer: " TIMER_RESET_TEXT " to reset",
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
            {"link tunic color:", TUNIC_COLOR_INDEX, "changes link's tunic color. " NEXT_TUNIC_COLOR_TEXT "/" PREVIOUS_TUNIC_COLOR_TEXT " to cycle through colors", false, nullptr,
             MAX_TUNIC_COLORS}} {
}

ToolsMenu::~ToolsMenu() {}

void ToolsMenu::draw() {
    l_tunicCol_idx = g_tunic_color;

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    ListMember tunicCol_opt[MAX_TUNIC_COLORS] = {"green",  "blue",  "red",  "orange",
                                                 "yellow", "white", "cycle"};

    if (cursor.y == TUNIC_COLOR_INDEX) {
        cursor.x = l_tunicCol_idx;
        cursor.move(MAX_TUNIC_COLORS, MENU_LINE_NUM);

        if (GZ_getButtonRepeat(NEXT_TUNIC_COLOR)) {
            l_tunicCol_idx++;

            if (l_tunicCol_idx >= MAX_TUNIC_COLORS)
                l_tunicCol_idx = 0;
        }

        if (GZ_getButtonRepeat(PREVIOUS_TUNIC_COLOR)) {
            l_tunicCol_idx--;

            if (l_tunicCol_idx >= MAX_TUNIC_COLORS)
                l_tunicCol_idx = MAX_TUNIC_COLORS - 1;
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

    lines[TUNIC_COLOR_INDEX].printf(" <%s>", tunicCol_opt[l_tunicCol_idx].member);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
