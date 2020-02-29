#include "tpgz/font.h"
#include "menus/menu.h"
#include "tpgz/controller.h"
#include "tpgz/utils.h"

#define LINES 3

static int cursor = 2;

Line lines[LINES] = {
    {"warping", 0, "", false},
    {"", 1, "", false},
    {"TBD", 2, "TBD", false}};

void WarpingMenu::render(Font& font) {
    if (button_is_down(Controller::B) && !button_is_held(Controller::B)) {
        warping_visible = false;
        mm_visible = true;
        return;
    };

    Utilities::move_cursor(cursor, LINES);
    Utilities::render_lines(font, lines, cursor, LINES);
}