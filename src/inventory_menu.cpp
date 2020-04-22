#include "font.h"
#include "menu.h"
#include "controller.h"
#include "utils.h"

#define LINES 2

static Cursor cursor = {0,0};
bool init_once = false;
bool inventory_visible;

Line lines[LINES] = {
    {"item wheel", ITEM_WHEEL_INDEX, "modify the item wheel items", false},
    {"pause menu", PAUSE_MENU_INDEX, "modify the pause menu items", false}};

void InventoryMenu::render(Font& font) {

    if (button_is_pressed(Controller::B)) {
        init_once = false;
        inventory_visible = false;
        mm_visible = true;
        return;
    };

    if (!init_once) {current_input = 0;init_once = true;}
    
    if (current_input == 256 && a_held == false) {
        switch (cursor.x) {
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
    
    Utilities::render_lines(font, lines, cursor.x, LINES);
};