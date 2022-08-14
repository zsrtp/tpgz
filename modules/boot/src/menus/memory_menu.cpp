#include "menus/memory_menu.h"
#include "gz_flags.h"

MemoryMenu::MemoryMenu()
    : Menu(), lines{
                  {"watches", 0, "Manage memory watches", false},
                  {"memory editor", 1, "View/edit memory", false},
                  {"mem files", 2, "Save/Load memory files", false},
              } {}

void MemoryMenu::draw() {
    if (GZ_getButtonTrig(BACK_BUTTON)) {
        GZ_setMenu(GZ_MAIN_MENU);
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        switch (cursor.y) {
        case 0:
            GZ_setMenu(GZ_WATCHES_MENU);
            return;
        case 1:
            GZ_setMenu(GZ_MEM_EDITOR_MENU);
            return;
        case 2:
            GZ_setMenu(GZ_MEMFILES_MENU);
            return;
        }
    }

    cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
