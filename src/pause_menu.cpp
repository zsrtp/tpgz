#include "font.h"
#include "menu.h"
#include "controller.h"
#include "utils.h"

#define LINES 3

static int cursor = 2;
bool pause_visible;

Line lines[LINES] = {
    {"pause menu", 0, "", false},
    {"", 1, "", false},
    {"TBD", 2, "TBD", false}};

void PauseMenu::render(Font& font) {

    if (button_is_pressed(Controller::B)) {
        pause_visible = false;
        inventory_visible = true;
        return;
    };

    Utilities::move_cursor(cursor, LINES);
    Utilities::render_lines(font, lines, cursor, LINES);
};