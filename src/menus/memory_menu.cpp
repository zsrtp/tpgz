#include "menus/memory_menu.h"
#include "controller.h"
#include "font.h"
#include "utils/cursor.h"
#include "utils/lines.h"

#define LINES 3

static Cursor cursor = {0, 0};
bool init_once = false;

Line lines[LINES] = {{"watches", 0, "Manage memory watches", false},
                     {"memory editor", 1, "View/edit memory", false},
                     {"mem files", 2, "Save/Load memory files", false}};

void MemoryMenu::render() {
    if (button_is_pressed(BACK_BUTTON)) {
        init_once = false;
        MenuRendering::set_menu(MN_MAIN_MENU_INDEX);
        return;
    }

    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

    if (current_input == SELECTION_BUTTON && a_held == false) {
        switch (cursor.y) {
        case 0: {
            MenuRendering::set_menu(MN_WATCHES_INDEX);
            return;
        }
        case 1: {
            MenuRendering::set_menu(MN_MEMORY_EDITOR_INDEX);
            return;
        }
        case 2: {
            MenuRendering::set_menu(MN_MEM_FILES_INDEX);
            return;
        }
        }
    }

    Utilities::move_cursor(cursor, LINES);
    Utilities::render_lines(lines, cursor.y, LINES);
};
