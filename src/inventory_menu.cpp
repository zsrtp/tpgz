#include "font.h"
#include "menu.h"
#include "controller.h"
#include "utils.h"

#define LINES 4

static int cursor = 2;
bool init_once = false;
bool inventory_visible;

Line lines[LINES] = {
    {"inventory", 0, "", false},
    {"", 1, "", false},
    {"item wheel", 2, "modify the item wheel items", false},
    {"pause menu", 3, "modify the pause menu items", false}};

void InventoryMenu::render(Font& font) {

    if (button_is_pressed(Controller::B)) {
        init_once = false;
        inventory_visible = false;
        mm_visible = true;
        return;
    };

    if (!init_once) {current_input = 0;init_once = true;}
    
    if (current_input == 256 && a_held == false) {
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