#include "font.h"
#include "menu.h"

#define LINES 3

static int cursor = 2;

Line lines[LINES] = {
    {"memory", 0, "", false},
    {"", 1, "", false},
    {"TBD", 2, "TBD", false}};

void transition_into(){};

void MemoryMenu::render(Font& font) {

    if (button_is_down(Controller::B) && !button_is_held(Controller::B)) {
        memory_visible = false;
        mm_visible = true;
        return;
    };

    Utilities::move_cursor(cursor, LINES);
    Utilities::render_lines(font, lines, cursor, LINES);
};