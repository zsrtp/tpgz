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
                        {"attack colliders", VIEW_AT_CC, "view hitbox colliders", true,
                         &g_collisionFlags[VIEW_AT_CC].active},
                        {"target colliders", VIEW_TG_CC, "view hurtbox colliders", true,
                         &g_collisionFlags[VIEW_TG_CC].active},
                        {"push colliders", VIEW_CO_CC, "view push colliders", true,
                         &g_collisionFlags[VIEW_CO_CC].active},
                        {"ground polys", VIEW_POLYGON_GROUND, "view ground polygons", true,
                         &g_collisionFlags[VIEW_POLYGON_GROUND].active},
                        {"roof polys", VIEW_POLYGON_ROOF, "view roof polygons", true,
                         &g_collisionFlags[VIEW_POLYGON_ROOF].active},
                        {"wall polys", VIEW_POLYGON_WALL, "view wall polygons", true,
                         &g_collisionFlags[VIEW_POLYGON_WALL].active},
                        {"poly edges", VIEW_POLYGON_EDGES, "view polygon edges", true,
                         &g_collisionFlags[VIEW_POLYGON_EDGES].active},                         
                        {"poly draw range:", 7, "max range for polygons to draw"},
                        {"poly draw raise:", 8, "amount to raise the drawn polygon by"},
                        {"opacity:", 9, "opacity of drawn geometry"},
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
        Cursor::moveList(g_collisionRange);
        break;
    case 8:
        Cursor::moveList(g_collisionRaise);
        break;
    case 9:
        Cursor::moveList(g_geometryOpacity);
        break;
    }

    if (g_collisionRange > 1000)
        g_collisionRange = 0;

    lines[7].printf(" <%d>", g_collisionRange);
    lines[8].printf(" <%d>", g_collisionRaise);
    lines[9].printf(" <%d>", g_geometryOpacity);

    cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
