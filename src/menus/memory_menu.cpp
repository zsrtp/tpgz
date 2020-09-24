#include "libtp_c/include/tp.h"
#include "font.h"
#include "menu.h"
#include "controller.h"
#include "utils/cursor.hpp"
#include "utils/lines.hpp"

#define LINES 2

static Cursor cursor = {0, 0};
bool init_once = false;
bool memory_visible;

Line lines[LINES] = {
    {"watches", 0, "Manage memory watches", false},
    {"memory editor", 1, "View/edit memory", false}};

void MemoryMenu::render(Font& font) {
    if (button_is_pressed(Controller::B)) {
        init_once = false;
        memory_visible = false;
        mm_visible = true;
        return;
    }

    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

    if (current_input == 256 && a_held == false) {
        switch (cursor.y) {
            case 0: {
                memory_visible = false;
                watches_visible = true;
                return;
            }
            case 1: {
                memory_visible = false;
                memory_editor_visible = true;
                return;
            }
        }
    }

    Utilities::move_cursor(cursor, LINES);
    Utilities::render_lines(font, lines, cursor.y, LINES);
};
