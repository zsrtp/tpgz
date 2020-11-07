#include "font.h"
#include "menus/practice_menu.h"
#include "controller.h"
#include "save_injector.h"
#include "utils/cursor.h"
#include "utils/lines.h"
#include "libtp_c/include/tp.h"

#define LINES 2

static Cursor cursor = {0,0};
bool init_once = false;
PracticeFile practice_file;

Line lines[LINES] = {
    {"any%", ANY_INDEX, "Any% practice saves", false},
    {"100%", HUNDO_INDEX, "100% practice saves", false}};

void PracticeMenu::render() {

    if (button_is_pressed(Controller::B)) {
        init_once = false;
        MenuRendering::set_menu(MN_MAIN_MENU_INDEX);
        return;
    };

    if (!init_once) {current_input = 0;init_once = true;}

    if (current_input == Controller::Pad::A && a_held == false) {
        switch (cursor.y) {
            case ANY_INDEX: {
                MenuRendering::set_menu(MN_ANY_SAVES_INDEX);
                return;
            }
            case HUNDO_INDEX: {
                MenuRendering::set_menu(MN_HUNDO_SAVES_INDEX);
                return;
            }
        }
    }

    Utilities::move_cursor(cursor, LINES);

    Utilities::render_lines(lines, cursor.y, LINES);
};
