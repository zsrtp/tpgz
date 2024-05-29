#include <cstdio>
#include "menus/menu_projection_view/include/projection_view_menu.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"
#include "collision_view.h"

KEEP_FUNC ProjectionViewMenu::ProjectionViewMenu(Cursor& cursor)
    : Menu(cursor), lines{
                         {"lja", VIEW_LJA_PROJECTION, "display projected path taken of an LJA", true,
                         &g_projectionViewFlags[VIEW_LJA_PROJECTION].active},
                         {"midna charge", VIEW_MIDNA_CHARGE_PROJECTION, "display projected path taken by a super jump", true,
                         &g_projectionViewFlags[VIEW_MIDNA_CHARGE_PROJECTION].active},
                    } {}

ProjectionViewMenu::~ProjectionViewMenu() {}

void ProjectionViewMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        g_projectionViewFlags[cursor.y].active = !g_projectionViewFlags[cursor.y].active;
    }

    switch (cursor.y) {
    case PROJECTION_VIEW_MAX:
        Cursor::moveList(g_geometryOpacity);
        break;
    }

    lines[PROJECTION_VIEW_MAX].printf(" <%d>", g_geometryOpacity);

    cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
