#include <cstdio>
#include "menus/menu_projection_view/include/projection_view_menu.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"
#include "collision_view.h"
#include "settings.h"

KEEP_FUNC ProjectionViewMenu::ProjectionViewMenu(Cursor& cursor)
    : Menu(cursor), lines{
                         {"lja", VIEW_LJA_PROJECTION, "display projected path taken of an LJA", true,
                         ACTIVE_FUNC(STNG_SCENE_LJA_PROJECTION)},
                         {"midna charge", VIEW_MIDNA_CHARGE_PROJECTION, "display projected path taken by a super jump", true,
                         ACTIVE_FUNC(STNG_SCENE_MIDNA_CHARGE_PROJECTION)},
                    } {}

ProjectionViewMenu::~ProjectionViewMenu() {}

GZSettingID l_mapping[] = {STNG_SCENE_LJA_PROJECTION, STNG_SCENE_MIDNA_CHARGE_PROJECTION};

void ProjectionViewMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        auto* stng [[maybe_unused]] = GZStng_getSetting(l_mapping[cursor.y]);
        if (!stng) {
            stng = new GZSettingEntry{l_mapping[cursor.y], sizeof(bool), new bool};
            g_settings.push_back(stng);
        }
        *static_cast<bool*>(stng->data) = !*static_cast<bool*>(stng->data);
    }

    cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
