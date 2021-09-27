#include "menus/practice_menu.h"
#include "controller.h"
#include "font.h"
#include "utils/cursor.h"
#include "utils/lines.h"

#define LINES 3

static Cursor cursor = {0, 0};
bool init_once = false;
char last_category[5];
int last_save_index;
int last_special_size;
special* last_special_ptr;

Line lines[LINES] = {{"any%", ANY_INDEX, "Any% practice saves", false},
                     {"100%", HUNDO_INDEX, "100% practice saves", false},
                     {"all dungeons", AD_INDEX, "All Dungeons practice saves", false}};

void PracticeMenu::render() {
    if (button_is_pressed(BACK_BUTTON)) {
        init_once = false;
        MenuRendering::set_menu(MN_MAIN_MENU_INDEX);
        return;
    };

    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

    if (current_input == SELECTION_BUTTON && a_held == false) {
        switch (cursor.y) {
        case ANY_INDEX: {
            MenuRendering::set_menu(MN_ANY_SAVES_INDEX);
            return;
        }
        case HUNDO_INDEX: {
            MenuRendering::set_menu(MN_HUNDO_SAVES_INDEX);
            return;
        }
        case AD_INDEX: {
            MenuRendering::set_menu(MN_AD_SAVES_INDEX);
            return;
        }
        }
    }

    Utilities::move_cursor(cursor, LINES);

    Utilities::render_lines(lines, cursor.y, LINES);
};
