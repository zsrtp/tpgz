#include "main_menu.h"
#include "fifo_queue.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

KEEP_FUNC MainMenu::MainMenu(Cursor& cursor)
    : Menu(),
      m_cursor(cursor), lines{
                            {"cheats", CHEAT_INDEX, "Toggle cheats", false},
                            {"flags", FLAGS_INDEX, "Toggle in-game flags", false},
                            {"inventory", INVENTORY_INDEX, "Set items and equipment", false},
                            {"memory", MEMORY_INDEX,
                             "View/edit memory, add watches, and save/load memfiles", false},
                            {"practice", PRACTICE_INDEX, "Load practice files", false},
                            {"scene", SCENE_INDEX, "Adjust current scene settings", false},
                            {"settings", SETTINGS_INDEX, "Configure settings", false},
                            {"tools", TOOLS_INDEX, "Use various tools for practice and testing",
                             false},
                            {"warping", WARPING_INDEX, "Warp to any area", false},
                        } {}

KEEP_FUNC MainMenu::~MainMenu() {}

void MainMenu::draw() {
    m_cursor.move(0, MENU_LINE_NUM);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        switch (m_cursor.y) {
        case CHEAT_INDEX:
            g_menuMgr->push(MN_CHEAT_INDEX);
            return;
        case FLAGS_INDEX:
            g_menuMgr->push(MN_FLAGS_INDEX);
            return;
        case INVENTORY_INDEX:
            g_menuMgr->push(MN_INVENTORY_INDEX);
            return;
        case MEMORY_INDEX:
            g_menuMgr->push(MN_MEMORY_INDEX);
            return;
        case PRACTICE_INDEX:
            g_menuMgr->push(MN_PRACTICE_INDEX);
            return;
        case SCENE_INDEX:
            g_menuMgr->push(MN_SCENE_INDEX);
            return;
        case SETTINGS_INDEX:
            g_menuMgr->push(MN_SETTINGS_INDEX);
            return;
        case TOOLS_INDEX:
            g_menuMgr->push(MN_TOOLS_INDEX);
            return;
        case WARPING_INDEX:
            g_menuMgr->push(MN_WARPING_INDEX);
            return;
        }
    }

    GZ_drawMenuLines(lines, m_cursor.y, MENU_LINE_NUM);
}
