#include "menus/main_menu.h"
#include "fifo_queue.h"
#include "gz_flags.h"
#include "rels/include/defines.h"

KEEP_FUNC MainMenu::MainMenu()
    : Menu(), lines{
                  {"cheats", CHEAT_INDEX, "Toggle cheats", false},
                  {"flags", FLAGS_INDEX, "Toggle in-game flags", false},
                  {"inventory", INVENTORY_INDEX, "Set items and equipment", false},
                  {"memory", MEMORY_INDEX, "View/edit memory, add watches, and save/load memfiles",
                   false},
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
            GZ_setMenu(MN_CHEAT_INDEX);
            return;
        case FLAGS_INDEX:
            GZ_setMenu(MN_FLAGS_INDEX);
            return;
        case INVENTORY_INDEX:
            GZ_setMenu(MN_INVENTORY_INDEX);
            return;
        case MEMORY_INDEX:
            GZ_setMenu(MN_MEMORY_INDEX);
            return;
        case PRACTICE_INDEX:
            GZ_setMenu(MN_PRACTICE_INDEX);
            return;
        case SCENE_INDEX:
            GZ_setMenu(MN_SCENE_INDEX);
            return;
        case SETTINGS_INDEX:
            GZ_setMenu(MN_SETTINGS_INDEX);
            return;
        case TOOLS_INDEX:
            GZ_setMenu(MN_TOOLS_INDEX);
            return;
        case WARPING_INDEX:
            GZ_setMenu(MN_WARPING_INDEX);
            return;
        }
    }

    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
