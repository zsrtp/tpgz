#include "menus/main_menu.h"
#include "fifo_queue.h"
#include "gz_flags.h"

MainMenu::MainMenu() : Menu(), lines{
    {"cheats", CHEAT_INDEX, "Toggle cheats", false},
    {"flags", FLAGS_INDEX, "Toggle in-game flags", false},
    {"inventory", INVENTORY_INDEX, "Set items and equipment", false},
    {"memory", MEMORY_INDEX, "View/edit memory, add watches, and save/load memfiles", false},
    {"practice", PRACTICE_INDEX, "Load practice files", false},
    {"scene", SCENE_INDEX, "Adjust current scene settings", false},
    {"settings", SETTINGS_INDEX, "Configure settings", false},
    {"tools", TOOLS_INDEX, "Use various tools for practice and testing", false},
    {"warping", WARPING_INDEX, "Warp to any area", false},
} {}

void MainMenu::draw() {
    cursor.move(0, MENU_LINE_NUM);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        GZ_clearMenu();
        GZ_setFifoVisible(true);
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        switch (cursor.y) {
        case CHEAT_INDEX:
            GZ_setMenu(GZ_CHEAT_MENU);
            return;
        case FLAGS_INDEX:
            GZ_setMenu(GZ_FLAGS_MENU);
            return;
        case INVENTORY_INDEX:
            GZ_setMenu(GZ_INVENTORY_MENU);
            return;
        case MEMORY_INDEX:
            GZ_setMenu(GZ_MEMORY_MENU);
            return;
        case PRACTICE_INDEX:
            GZ_setMenu(GZ_PRACTICE_MENU);
            return;
        case SCENE_INDEX:
            GZ_setMenu(GZ_SCENE_MENU);
            return;
        case SETTINGS_INDEX:
            GZ_setMenu(GZ_SETTINGS_MENU);
            return;
        case TOOLS_INDEX:
            GZ_setMenu(GZ_TOOLS_MENU);
            return;
        case WARPING_INDEX:
            GZ_setMenu(GZ_WARP_MENU);
            return;
        }
    }

    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
