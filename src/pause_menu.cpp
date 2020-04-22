#include "font.h"
#include "menu.h"
#include "controller.h"
#include "utils.h"

#define LINES 1

static Cursor cursor = {0,0};
bool pause_visible;

Line lines[LINES] = {
    {"TBD", 0, "TBD", false}};

void PauseMenu::render(Font& font) {

    if (button_is_pressed(Controller::B)) {
        pause_visible = false;
        inventory_visible = true;
        return;
    };

    Utilities::move_cursor(cursor, LINES);
    Utilities::render_lines(font, lines, cursor.x, LINES);
};