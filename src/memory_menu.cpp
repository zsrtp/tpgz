#include "font.h"
#include "menu.h"
#include "controller.h"
#include "utils.h"

#define LINES 3

static int cursor = 2;
bool memory_visible;

Line lines[LINES] = {
    {"memory", 0, "", false},
    {"", 1, "", false},
    {"TBD", 2, "TBD", false}};

void MemoryMenu::render(Font& font) {

    if (button_is_pressed(Controller::B)) {
        memory_visible = false;
        mm_visible = true;
        return;
    };

    Utilities::move_cursor(cursor, LINES);
    Utilities::render_lines(font, lines, cursor, LINES);
};