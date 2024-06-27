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
                         {"attention distances", VIEW_ATTN_DISTS, "view actor attention ranges", true,
                         [](){return g_triggerViewFlags[VIEW_ATTN_DISTS].active;}},
                         {"event areas", VIEW_EVENT_AREAS, "view event triggers", true,
                         [](){return g_triggerViewFlags[VIEW_EVENT_AREAS].active;}},
                         {"load zones", VIEW_LOAD_ZONES, "view load triggers", true,
                         [](){return g_triggerViewFlags[VIEW_LOAD_ZONES].active;}},
                         {"midna stops", VIEW_MIDNA_STOPS, "view midna talk triggers", true,
                         [](){return g_triggerViewFlags[VIEW_MIDNA_STOPS].active;}},
                         {"paths", VIEW_PATHS, "view all stage/room paths", true,
                         [](){return g_triggerViewFlags[VIEW_PATHS].active;}},
                         {"purple mist avoid", VIEW_MIST_AVOID, "view purple mist safe area", true,
                         [](){return g_triggerViewFlags[VIEW_MIST_AVOID].active;}},
                         {"restart changes", VIEW_CHG_RESTARTS, "view spawn location update triggers", true,
                         [](){return g_triggerViewFlags[VIEW_CHG_RESTARTS].active;}},
                         {"switch areas", VIEW_SWITCH_AREAS, "view switch activation triggers", true,
                         [](){return g_triggerViewFlags[VIEW_SWITCH_AREAS].active;}},
                         {"transform distances", VIEW_TRANSFORM_DISTS, "view actor transform blocking distances", true,
                         [](){return g_triggerViewFlags[VIEW_TRANSFORM_DISTS].active;}},
                         {"twilight gates", VIEW_TW_GATES, "view twilight gate triggers", true,
                         [](){return g_triggerViewFlags[VIEW_TW_GATES].active;}},
                         {"opacity:", TRIGGER_VIEW_MAX, "the opacity of drawn geometry"},
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
    case TRIGGER_VIEW_MAX:
        Cursor::moveList(g_geometryOpacity);
        break;
    }

    lines[TRIGGER_VIEW_MAX].printf(" <%d>", g_geometryOpacity);

    cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
