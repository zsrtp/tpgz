#include "menus/menu_memory/include/memory_menu.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

KEEP_FUNC MemoryMenu::MemoryMenu(Cursor& cursor)
    : Menu(cursor), lines{
                        {"watches", 0, "Manage memory watches", false},
                        {"memory editor", 1, "View/edit memory", false},
                        {"mem files", 2, "Save/Load memory files", false},
                    } {}

MemoryMenu::~MemoryMenu() {}

void MemoryMenu::draw() {
    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        switch (cursor.y) {
        case 0:
            g_menuMgr->push(MN_WATCHES_INDEX);
            return;
        case 1:
            g_menuMgr->push(MN_MEMORY_EDITOR_INDEX);
            return;
        case 2:
            g_menuMgr->push(MN_MEM_FILES_INDEX);
            return;
        }
    }

    cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
