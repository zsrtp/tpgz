#include <cstdio>
#include "collision_view.h"
#include "trigger_view.h"
#include "menus/menu_trigger_view/include/trigger_view_menu.h"
#include "settings.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/f_op/f_op_actor_mng.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

KEEP_FUNC TriggerViewMenu::TriggerViewMenu(Cursor& cursor)
    : Menu(cursor), lines{
                        {"view load zones", VIEW_LOAD_ZONES, "", true,
                         &g_triggerViewFlags[VIEW_LOAD_ZONES].active},
                         {"view midna stops", VIEW_MIDNA_STOPS, "", true,
                         &g_triggerViewFlags[VIEW_MIDNA_STOPS].active},
                         {"view switch areas", VIEW_SWITCH_AREAS, "", true,
                         &g_triggerViewFlags[VIEW_SWITCH_AREAS].active},
                         {"view twilight gates", VIEW_TW_GATES, "", true,
                         &g_triggerViewFlags[VIEW_TW_GATES].active},
                         {"opacity:", 4, "the opacity of drawn triggers"},
                    } {}

TriggerViewMenu::~TriggerViewMenu() {}

void TriggerViewMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        g_triggerViewFlags[cursor.y].active = !g_triggerViewFlags[cursor.y].active;
    }

    switch (cursor.y) {
    case 4:
        Cursor::moveList(g_triggerOpacity);
        break;
    }

    lines[4].printf(" <%d>", g_triggerOpacity);

    cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
