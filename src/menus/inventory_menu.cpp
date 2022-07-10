#include "menus/inventory_menu.h"
#include "font.h"
#include "gz_flags.h"

#define LINE_NUM 3

Cursor InventoryMenu::cursor;

Line lines[LINE_NUM] = {
    {"item wheel", ITEM_WHEEL_INDEX, "Modify the item wheel", false},
    {"pause menu", PAUSE_MENU_INDEX, "Modify the pause menu collection", false},
    {"amounts", AMOUNTS_MENU_INDEX, "Modify ammo / collectible amounts", false},
};

void InventoryMenu::draw() {
    cursor.move(0, LINE_NUM);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        GZ_setMenu(GZ_MAIN_MENU);
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        switch (cursor.y) {
        case ITEM_WHEEL_INDEX:
            GZ_setMenu(GZ_WHEEL_MENU);
            return;
        case PAUSE_MENU_INDEX:
            GZ_setMenu(GZ_PAUSE_MENU);
            return;
        case AMOUNTS_MENU_INDEX:
            GZ_setMenu(GZ_AMOUNTS_MENU);
            return;
        }
    }

    GZ_drawMenuLines(lines, cursor.y, LINE_NUM);
}