#include "menus/inventory_menu.h"
#include "font.h"
#include "gz_flags.h"
#include "rels/include/defines.h"

KEEP_FUNC InventoryMenu::InventoryMenu()
    : Menu(), lines{
                  {"item wheel", ITEM_WHEEL_INDEX, "Modify the item wheel", false},
                  {"pause menu", PAUSE_MENU_INDEX, "Modify the pause menu collection", false},
                  {"amounts", AMOUNTS_MENU_INDEX, "Modify ammo / collectible amounts", false},
              } {}

void InventoryMenu::draw() {
    cursor.move(0, MENU_LINE_NUM);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        GZ_setMenu(MN_MAIN_MENU_INDEX);
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        switch (cursor.y) {
        case ITEM_WHEEL_INDEX:
            GZ_setMenu(MN_ITEM_WHELL_INDEX);
            return;
        case PAUSE_MENU_INDEX:
            GZ_setMenu(MN_PAUSE_INDEX);
            return;
        case AMOUNTS_MENU_INDEX:
            GZ_setMenu(MN_AMOUNTS_INDEX);
            return;
        }
    }

    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}