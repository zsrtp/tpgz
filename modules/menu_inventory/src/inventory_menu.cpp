#include "menu_inventory/include/inventory_menu.h"
#include "font.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

KEEP_FUNC InventoryMenu::InventoryMenu(Cursor& cursor)
    : Menu(), m_cursor(cursor), lines{
                  {"item wheel", ITEM_WHEEL_INDEX, "Modify the item wheel", false},
                  {"pause menu", PAUSE_MENU_INDEX, "Modify the pause menu collection", false},
                  {"amounts", AMOUNTS_MENU_INDEX, "Modify ammo / collectible amounts", false},
              } {}

InventoryMenu::~InventoryMenu() {}

void InventoryMenu::draw() {
    m_cursor.move(0, MENU_LINE_NUM);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        switch (m_cursor.y) {
        case ITEM_WHEEL_INDEX:
            g_menuMgr->push(MN_ITEM_WHELL_INDEX);
            return;
        case PAUSE_MENU_INDEX:
            g_menuMgr->push(MN_PAUSE_INDEX);
            return;
        case AMOUNTS_MENU_INDEX:
            g_menuMgr->push(MN_AMOUNTS_INDEX);
            return;
        }
    }

    GZ_drawMenuLines(lines, m_cursor.y, MENU_LINE_NUM);
}