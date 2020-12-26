#include "menus/inventory_menu.h"
#include "controller.h"
#include "font.h"
#include "utils/cursor.h"
#include "utils/lines.h"

#define LINES 3

static Cursor cursor = {0, 0};
bool init_once = false;

Line lines[LINES] = {{"item wheel", ITEM_WHEEL_INDEX, "Modify the item wheel", false},
                     {"pause menu", PAUSE_MENU_INDEX, "Modify the pause menu collection", false},
                     {"amounts", AMOUNTS_MENU_INDEX, "Modify ammo / collectible amounts", false}};

void InventoryMenu::render() {
    if (button_is_pressed(Controller::B)) {
        init_once = false;
        MenuRendering::set_menu(MN_MAIN_MENU_INDEX);
        return;
    };

    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

    if (current_input == Controller::Pad::A && a_held == false) {
        switch (cursor.y) {
        case ITEM_WHEEL_INDEX: {
            MenuRendering::set_menu(MN_ITEM_WHELL_INDEX);
            return;
        }
        case PAUSE_MENU_INDEX: {
            MenuRendering::set_menu(MN_PAUSE_INDEX);
            return;
        }
        case AMOUNTS_MENU_INDEX: {
            MenuRendering::set_menu(MN_AMOUNTS_INDEX);
            return;
        }
        }
    }

    Utilities::move_cursor(cursor, LINES);

    Utilities::render_lines(lines, cursor.y, LINES);
};