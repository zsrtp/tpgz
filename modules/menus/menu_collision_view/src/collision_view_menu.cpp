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
                        {"view polygon collision", VIEW_POLYGON_INDEX, "", true,
                         &g_collisionFlags[VIEW_POLYGON_INDEX].active},
                        {"view attack colliders", VIEW_AT_INDEX, "", true,
                         &g_collisionFlags[VIEW_AT_INDEX].active},
                        {"view target colliders", VIEW_TG_INDEX, "", true,
                         &g_collisionFlags[VIEW_TG_INDEX].active},
                         {"view push colliders", VIEW_CO_INDEX, "", true,
                         &g_collisionFlags[VIEW_CO_INDEX].active},
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

    char str[50];
    snprintf(str, sizeof(str), "Active Draw Packets: %d", l_drawPacketListNum);
    GZ_drawText(str, 25.0f, 160.f, 0xFFFFFFFF, GZ_checkDropShadows());

    cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
