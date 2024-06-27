#include "menus/menu_tools/include/tools_menu.h"
#include <cstdio>
#include "commands.h"
#include "global_data.h"
#include "timer.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
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
#define PREVIOUS_TUNIC_COLOR GZPad::TWO
#define PREVIOUS_TUNIC_COLOR_TEXT "TWO"
#define NEXT_TUNIC_COLOR GZPad::ONE
#define NEXT_TUNIC_COLOR_TEXT "ONE"
#endif

#define MAX_TUNIC_COLORS 7

const char l_descTemplates[TOOLS_COUNT][100] = {
    "use %s to reload current area",
    "use %s to pause, %s to frame advance",
    "reduces bonk animation significantly",
    "link's movement is much faster",
    "use %s to warp to kakariko gorge",
#ifdef WII_PLATFORM
    "use %s to warp to ordon bridge",
#endif
    "show frame info when doing coro td",
    "practice snowpeak universal map delay timing",
    "show current inputs",
    "show Link's position, angle, and speed",
    "show Heap size info",
    "link won't sink in sand",
    "frame counter for chaining rolls",
    "display A/B button mashing speeds",
    "%s to set, %s to load",
    "simulates turbo controller inputs",
    "frame timer: %s to start/stop, %s to reset",
    "loading zone timer: %s to reset",
    "In-game time timer: %s to start/stop, %s to reset",
    FREE_CAM_TEXT " to activate, " FREE_CAM_MOVEMENT_TEXT " to move, " FREE_CAM_VIEW_TEXT
                  " to view, Z to speed",
    MOVE_LINK_TEXT " to activate. " MOVE_LINK_MOVEMENT_TEXT " to move, " MOVE_LINK_ANGLE_TEXT
                   " to change angle",
    "changes link's tunic color. " NEXT_TUNIC_COLOR_TEXT "/" PREVIOUS_TUNIC_COLOR_TEXT
    " to cycle through colors",
};

KEEP_FUNC ToolsMenu::ToolsMenu(Cursor& cursor, ToolsData& data)
    : Menu(cursor), l_tunicCol_idx(data.l_tunicCol_idx),
      lines{{"area reload", RELOAD_AREA_INDEX, "use " RELOAD_AREA_TEXT " to reload current area",
             true, ACTIVE_FUNC(STNG_TOOLS_RELOAD_AREA)},
            {"frame advance", FRAME_ADVANCE_INDEX, "use " FRAME_ADVANCE_TEXT " to pause, " FRAME_PAUSE_TEXT " to frame advance",
             true, ACTIVE_FUNC(STNG_TOOLS_FRAME_ADVANCE)},
            {"fast bonk recovery", FAST_BONK_INDEX, "reduces bonk animation significantly", true,
             ACTIVE_FUNC(STNG_TOOLS_FAST_BONK)},
            {"fast movement", FAST_MOVEMENT_INDEX, "link's movement is much faster", true,
             ACTIVE_FUNC(STNG_TOOLS_FAST_MOVEMENT)},
            {"gorge checker", GORGE_INDEX, "use " GORGE_VOID_TEXT " to warp to kakariko gorge",
             true, ACTIVE_FUNC(STNG_TOOLS_GORGE)},
#ifdef WII_PLATFORM
            {"bit checker", BIT_INDEX, "use " BACK_IN_TIME_TEXT " to warp to ordon bridge", true,
             ACTIVE_FUNC(STNG_TOOLS_BIT)},
#endif
            {"coro td checker", COROTD_INDEX, "show frame info when doing coro td", true,
             ACTIVE_FUNC(STNG_TOOLS_COROTD)},
            {"umd checker", UMD_INDEX, "practice snowpeak universal map delay timing", true,
             ACTIVE_FUNC(STNG_TOOLS_UMD)},
            {"input viewer", INPUT_VIEWER_INDEX, "show current inputs", true,
             ACTIVE_FUNC(STNG_TOOLS_INPUT_VIEWER)},
            {"link debug info", LINK_DEBUG_INDEX, "show Link's position, angle, and speed", true,
             ACTIVE_FUNC(STNG_TOOLS_LINK_DEBUG)},
            {"heap debug info", HEAP_DEBUG_INDEX, "show Heap size info", true,
             ACTIVE_FUNC(STNG_TOOLS_HEAP_DEBUG)},
            {"no sinking in sand", SAND_INDEX, "link won't sink in sand", true,
             ACTIVE_FUNC(STNG_TOOLS_SAND)},
            {"roll checker", ROLL_INDEX, "frame counter for chaining rolls", true,
             ACTIVE_FUNC(STNG_TOOLS_ROLL)},
            {"mash checker", MASH_CHECKER_INDEX, "display A/B button mashing speeds", true,
             ACTIVE_FUNC(STNG_TOOLS_MASH_CHECKER)},
            {"teleport", TELEPORT_INDEX,
             STORE_POSITION_TEXT " to set, " LOAD_POSITION_TEXT " to load", true,
             ACTIVE_FUNC(STNG_TOOLS_TELEPORT)},
            {"turbo mode", TURBO_MODE_INDEX, "simulates turbo controller inputs", true,
             ACTIVE_FUNC(STNG_TOOLS_TURBO_MODE)},
            {"timer", TIMER_INDEX,
             "frame timer: " TIMER_TOGGLE_TEXT " to start/stop, " TIMER_RESET_TEXT " to reset",
             true, ACTIVE_FUNC(STNG_TOOLS_TIMER)},
            {"load timer", LOAD_TIMER_INDEX, "loading zone timer: " TIMER_RESET_TEXT " to reset",
             true, ACTIVE_FUNC(STNG_TOOLS_LOAD_TIMER)},
            {"igt timer", IGT_TIMER_INDEX,
             "In-game time timer: " TIMER_TOGGLE_TEXT " to start/stop, " TIMER_RESET_TEXT
             " to reset",
             true, ACTIVE_FUNC(STNG_TOOLS_IGT_TIMER)},
            {"free cam", FREE_CAM_INDEX,
             FREE_CAM_TEXT " to activate, " FREE_CAM_MOVEMENT_TEXT " to move, " FREE_CAM_VIEW_TEXT
                           " to view, Z to speed",
             true, ACTIVE_FUNC(STNG_TOOLS_FREE_CAM)},
            {"move link", MOVE_LINK_INDEX,
             MOVE_LINK_TEXT " to activate. " MOVE_LINK_MOVEMENT_TEXT
                            " to move, " MOVE_LINK_ANGLE_TEXT " to change angle",
             true, ACTIVE_FUNC(STNG_TOOLS_MOVE_LINK)},
            {"link tunic color:", TUNIC_COLOR_INDEX,
             "changes link's tunic color. " NEXT_TUNIC_COLOR_TEXT "/" PREVIOUS_TUNIC_COLOR_TEXT
             " to cycle through colors",
             false, nullptr, MAX_TUNIC_COLORS}} {
}

ToolsMenu::~ToolsMenu() {}

GZSettingID l_mapping[] = {
    STNG_TOOLS_RELOAD_AREA,   STNG_TOOLS_FRAME_ADVANCE, STNG_TOOLS_FAST_BONK,
    STNG_TOOLS_FAST_MOVEMENT, STNG_TOOLS_GORGE,
#ifdef WII_PLATFORM
    STNG_TOOLS_BIT,
#endif
    STNG_TOOLS_COROTD,        STNG_TOOLS_UMD,           STNG_TOOLS_INPUT_VIEWER,
    STNG_TOOLS_LINK_DEBUG,    STNG_TOOLS_HEAP_DEBUG,    STNG_TOOLS_SAND,
    STNG_TOOLS_ROLL,          STNG_TOOLS_MASH_CHECKER,  STNG_TOOLS_TELEPORT,
    STNG_TOOLS_TURBO_MODE,    STNG_TOOLS_TIMER,         STNG_TOOLS_LOAD_TIMER,
    STNG_TOOLS_IGT_TIMER,     STNG_TOOLS_FREE_CAM,      STNG_TOOLS_MOVE_LINK,
};

#define set_active(id, status)                                                                     \
    ({                                                                                             \
        auto* stng = GZStng_get(id);                                                        \
        if (stng)                                                                                  \
            *(bool*)stng->data = status;                                                           \
    })

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
        GZSettingEntry* stng = nullptr;
        if (cursor.y < TOOLS_COUNT && cursor.y != TUNIC_COLOR_INDEX) {
            stng = GZStng_get(l_mapping[cursor.y]);
            if (!stng) {
                stng = new GZSettingEntry{l_mapping[cursor.y], sizeof(bool), new bool};
                g_settings.push_back(stng);
            }
        }
        if (stng) {
            *(bool*)stng->data = !*(bool*)stng->data;
            if (*(bool*)stng->data) {
                switch (cursor.y) {
                case TIMER_INDEX:
                    set_active(STNG_TOOLS_LOAD_TIMER, false);
                    set_active(STNG_TOOLS_IGT_TIMER, false);
                    break;
                case LOAD_TIMER_INDEX:
                    set_active(STNG_TOOLS_TIMER, false);
                    set_active(STNG_TOOLS_IGT_TIMER, false);
                    break;
                case IGT_TIMER_INDEX:
                    set_active(STNG_TOOLS_TIMER, false);
                    set_active(STNG_TOOLS_LOAD_TIMER, false);
                    break;
                }
            }
        }
    }

    char buf[100];
    switch (cursor.y) {
    case RELOAD_AREA_INDEX: {
        uint16_t combo = GZStng_getData<uint16_t>(STNG_CMD_RELOAD_AREA, RELOAD_AREA_BUTTONS);
        char* comboStr = new char[GZCmd_getComboLen(combo) + 1];
        GZCmd_comboToStr(combo, comboStr);
        snprintf(buf, sizeof(buf), l_descTemplates[cursor.y], comboStr);
        delete[] comboStr;
        break;
    }
    case FRAME_ADVANCE_INDEX: {
        uint16_t comboPause =
            GZStng_getData<uint16_t>(STNG_CMD_FRAME_PAUSE, FRAME_PAUSE_BUTTONS);
        char* comboPauseStr = new char[GZCmd_getComboLen(comboPause) + 1];
        GZCmd_comboToStr(comboPause, comboPauseStr);
        uint16_t comboAdvance =
            GZStng_getData<uint16_t>(STNG_CMD_FRAME_ADVANCE, FRAME_ADVANCE_BUTTONS);
        char* comboAdvanceStr = new char[GZCmd_getComboLen(comboAdvance) + 1];
        GZCmd_comboToStr(comboAdvance, comboAdvanceStr);
        snprintf(buf, sizeof(buf), l_descTemplates[cursor.y], comboPauseStr, comboAdvanceStr);
        delete[] comboAdvanceStr;
        delete[] comboPauseStr;
        break;
    }
    case GORGE_INDEX: {
        uint16_t combo = GZStng_getData<uint16_t>(STNG_CMD_GORGE_VOID, GORGE_VOID_BUTTONS);
        char* comboStr = new char[GZCmd_getComboLen(combo) + 1];
        GZCmd_comboToStr(combo, comboStr);
        snprintf(buf, sizeof(buf), l_descTemplates[cursor.y], comboStr);
        delete[] comboStr;
        break;
    }
#ifdef WII_PLATFORM
    case BIT_INDEX: {
        uint16_t combo = GZStng_getData<uint16_t>(STNG_CMD_BIT, BACK_IN_TIME_BUTTONS);
        char* comboStr = new char[GZCmd_getComboLen(combo) + 1];
        GZCmd_comboToStr(combo, comboStr);
        snprintf(buf, sizeof(buf), l_descTemplates[cursor.y], comboStr);
        delete[] comboStr;
        break;
    }
#endif
    case TELEPORT_INDEX: {
        uint16_t comboPause =
            GZStng_getData<uint16_t>(STNG_CMD_STORE_POSITION, STORE_POSITION_BUTTONS);
        char* comboPauseStr = new char[GZCmd_getComboLen(comboPause) + 1];
        GZCmd_comboToStr(comboPause, comboPauseStr);
        uint16_t comboAdvance =
            GZStng_getData<uint16_t>(STNG_CMD_LOAD_POSITION, LOAD_POSITION_BUTTONS);
        char* comboAdvanceStr = new char[GZCmd_getComboLen(comboAdvance) + 1];
        GZCmd_comboToStr(comboAdvance, comboAdvanceStr);
        snprintf(buf, sizeof(buf), l_descTemplates[cursor.y], comboPauseStr, comboAdvanceStr);
        delete[] comboAdvanceStr;
        delete[] comboPauseStr;
        break;
    }
    case IGT_TIMER_INDEX: // fallthrough
    case TIMER_INDEX: {
        uint16_t comboPause =
            GZStng_getData<uint16_t>(STNG_CMD_TIMER_TOGGLE, TIMER_TOGGLE_BUTTONS);
        char* comboPauseStr = new char[GZCmd_getComboLen(comboPause) + 1];
        GZCmd_comboToStr(comboPause, comboPauseStr);
        uint16_t comboAdvance =
            GZStng_getData<uint16_t>(STNG_CMD_TIMER_RESET, TIMER_RESET_BUTTONS);
        char* comboAdvanceStr = new char[GZCmd_getComboLen(comboAdvance) + 1];
        GZCmd_comboToStr(comboAdvance, comboAdvanceStr);
        snprintf(buf, sizeof(buf), l_descTemplates[cursor.y], comboPauseStr, comboAdvanceStr);
        delete[] comboAdvanceStr;
        delete[] comboPauseStr;
        break;
    }
    case LOAD_TIMER_INDEX: {
        uint16_t combo = GZStng_getData<uint16_t>(STNG_CMD_TIMER_RESET, TIMER_RESET_BUTTONS);
        char* comboStr = new char[GZCmd_getComboLen(combo) + 1];
        GZCmd_comboToStr(combo, comboStr);
        snprintf(buf, sizeof(buf), l_descTemplates[cursor.y], comboStr);
        delete[] comboStr;
        break;
    }
    default: {
        snprintf(buf, sizeof(buf), l_descTemplates[cursor.y]);
        break;
    }
    }
    strncpy(lines[cursor.y].description, buf, sizeof(lines[cursor.y].description));

    lines[TUNIC_COLOR_INDEX].printf(" <%s>", tunicCol_opt[l_tunicCol_idx].member);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
