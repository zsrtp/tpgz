#include "font.h"
#include "menu.h"
#include "controller.h"
#include "utils.h"

#define LINES 4

static int cursor = 2;

Line lines[LINES] = {
    {"inventory", 0, "", false},
    {"", 1, "", false},
    {"item wheel", 2, "modify the item wheel items", false},
    {"pause menu", 3, "modify the pause menu items", false}};

void InventoryMenu::render(Font& font) {

    if (button_is_pressed(Controller::B)) {
        inventory_visible = false;
        mm_visible = true;
        return;
    };
    
    if (button_is_pressed(Controller::A)) {
        switch (cursor) {
            case ITEM_WHEEL_INDEX: {
                inventory_visible = false;
                item_wheel_visible = true;
                return;
            }
            case PAUSE_MENU_INDEX: {
                inventory_visible = false;
                pause_visible = true;
                return;
            }
        }
    }

    Utilities::move_cursor(cursor, LINES);
    
    
    
    Utilities::render_lines(font, lines, cursor, LINES);
};