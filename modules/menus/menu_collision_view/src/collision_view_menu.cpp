#include <cstdio>
#include "collision_view.h"
#include "menus/menu_collision_view/include/collision_view_menu.h"
#include "settings.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/f_op/f_op_actor_mng.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

KEEP_FUNC CollisionViewMenu::CollisionViewMenu(Cursor& cursor)
    : Menu(cursor), lines{
                        {"view ground polys", VIEW_POLYGON_GROUND, "", true,
                         &g_collisionFlags[VIEW_POLYGON_GROUND].active},
                        {"view wall polys", VIEW_POLYGON_WALL, "", true,
                         &g_collisionFlags[VIEW_POLYGON_WALL].active},
                        {"view roof polys", VIEW_POLYGON_ROOF, "", true,
                         &g_collisionFlags[VIEW_POLYGON_ROOF].active},
                        {"view poly edges", VIEW_POLYGON_EDGES, "", true,
                         &g_collisionFlags[VIEW_POLYGON_EDGES].active}, 
                        {"view attack colliders", VIEW_AT_CC, "", true,
                         &g_collisionFlags[VIEW_AT_CC].active},
                        {"view target colliders", VIEW_TG_CC, "", true,
                         &g_collisionFlags[VIEW_TG_CC].active},
                         {"view push colliders", VIEW_CO_CC, "", true,
                         &g_collisionFlags[VIEW_CO_CC].active},
                         {"opacity:", 7, "the opacity of drawn geometry"},
                    } {}

CollisionViewMenu::~CollisionViewMenu() {}

void CollisionViewMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        g_collisionFlags[cursor.y].active = !g_collisionFlags[cursor.y].active;
    }

    switch (cursor.y) {
    case 7:
        Cursor::moveList(g_geometryOpacity);
        break;
    }

    lines[7].printf(" <%d>", g_geometryOpacity);

    cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
