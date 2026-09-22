#include "menus/menu_tools_link/include/tools_link_menu.h"
#include <cstdio>
#include "commands.h"
#include "global_data.h"
#include "timer.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

#ifdef GCN_PLATFORM
#define MOVE_LINK_MOVEMENT_TEXT "Stick/C"
#define MOVE_LINK_ANGLE_TEXT "C-left/right"
#define PREVIOUS_TUNIC_COLOR GZPad::Y
#define PREVIOUS_TUNIC_COLOR_TEXT "Y"
#define NEXT_TUNIC_COLOR GZPad::X
#define NEXT_TUNIC_COLOR_TEXT "X"
#endif
#ifdef WII_PLATFORM
#define MOVE_LINK_MOVEMENT_TEXT "Stick"
#define MOVE_LINK_ANGLE_TEXT "C+Stick"
#define PREVIOUS_TUNIC_COLOR GZPad::TWO
#define PREVIOUS_TUNIC_COLOR_TEXT "TWO"
#define NEXT_TUNIC_COLOR GZPad::ONE
#define NEXT_TUNIC_COLOR_TEXT "ONE"
#endif

#define MAX_TUNIC_COLORS 7

const char l_descTemplates[TOOLS_LINK_COUNT][100] = {
    "reduces bonk animation significantly",
    "link's movement is much faster",
    "show Link's position, angle, and speed",
    "show Link's current stage info",
    "link won't sink in sand",
    "%s to set, %s to load",
    "%s to set",
    MOVE_LINK_TEXT " to activate. " MOVE_LINK_MOVEMENT_TEXT " to move, " MOVE_LINK_ANGLE_TEXT
                   " to change angle",
    "changes link's tunic color. " NEXT_TUNIC_COLOR_TEXT "/" PREVIOUS_TUNIC_COLOR_TEXT
    " to cycle through colors",
};

KEEP_FUNC ToolsLinkMenu::ToolsLinkMenu(Cursor& cursor, ToolsLinkData& data)
    : Menu(cursor), l_tunicCol_idx(data.l_tunicCol_idx),
      lines{{"fast bonk recovery", FAST_BONK_INDEX, "reduces bonk animation significantly", true,
             ACTIVE_FUNC(STNG_TOOLS_FAST_BONK)},
            {"fast movement", FAST_MOVEMENT_INDEX, "link's movement is much faster", true,
             ACTIVE_FUNC(STNG_TOOLS_FAST_MOVEMENT)},
            {"link debug info", LINK_DEBUG_INDEX, "show Link's position, angle, and speed", true,
             ACTIVE_FUNC(STNG_TOOLS_LINK_DEBUG)},
            {"stage info", LINK_STAGE_INFO_INDEX, "show Link's current stage info", true,
             ACTIVE_FUNC(STNG_TOOLS_STAGE_INFO)},
            {"no sinking in sand", SAND_INDEX, "link won't sink in sand", true,
             ACTIVE_FUNC(STNG_TOOLS_SAND)},
            {"teleport", TELEPORT_INDEX,
             STORE_POSITION_TEXT " to set, " LOAD_POSITION_TEXT " to load", true,
             ACTIVE_FUNC(STNG_TOOLS_TELEPORT)},
            {"displacement", DISPLACEMENT_INDEX,
             STORE_POSITION_TEXT " to set", true,
             ACTIVE_FUNC(STNG_TOOLS_DISPLACEMENT)},
            {"move link", MOVE_LINK_INDEX,
             MOVE_LINK_TEXT " to activate. " MOVE_LINK_MOVEMENT_TEXT
                            " to move, " MOVE_LINK_ANGLE_TEXT " to change angle",
             true, ACTIVE_FUNC(STNG_TOOLS_MOVE_LINK)},
            {"link tunic color:", TUNIC_COLOR_INDEX,
             "changes link's tunic color. " NEXT_TUNIC_COLOR_TEXT "/" PREVIOUS_TUNIC_COLOR_TEXT
             " to cycle through colors",
             false, nullptr, MAX_TUNIC_COLORS}} {
}

ToolsLinkMenu::~ToolsLinkMenu() {}

GZSettingID l_mapping[] = {
    STNG_TOOLS_FAST_BONK,
    STNG_TOOLS_FAST_MOVEMENT,
    STNG_TOOLS_LINK_DEBUG,
    STNG_TOOLS_STAGE_INFO,
    STNG_TOOLS_SAND,
    STNG_TOOLS_TELEPORT,
    STNG_TOOLS_DISPLACEMENT,
    STNG_TOOLS_MOVE_LINK
};

#define set_active(id, status)                                                                     \
    ({                                                                                             \
        auto* stng = GZStng_get(id);                                                        \
        if (stng)                                                                                  \
            *(bool*)stng->data = status;                                                           \
    })

void ToolsLinkMenu::draw() {
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
        
        stng = GZStng_get(l_mapping[cursor.y]);

        if (!stng) {
            stng = new GZSettingEntry{l_mapping[cursor.y], sizeof(bool), new bool};
            g_settings.push_back(stng);
        }

        if (stng)
            *(bool*)stng->data = !*(bool*)stng->data;
    }

    char buf[100];

    switch (cursor.y) {
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
    case DISPLACEMENT_INDEX: {
        uint16_t comboPause =
            GZStng_getData<uint16_t>(STNG_CMD_STORE_POSITION, STORE_POSITION_BUTTONS);
        char* comboPauseStr = new char[GZCmd_getComboLen(comboPause) + 1];
        GZCmd_comboToStr(comboPause, comboPauseStr);
        snprintf(buf, sizeof(buf), l_descTemplates[cursor.y], comboPauseStr);
        delete[] comboPauseStr;
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
