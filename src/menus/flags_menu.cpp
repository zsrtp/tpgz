#include "menus/flags_menu.h"
#include "controller.h"
#include "font.h"
#include "utils/cursor.h"
#include "utils/lines.h"

#define LINES 5

static Cursor cursor = {0, 0};
bool init_once = false;

Line lines[LINES] = {{"general flags", GENERAL_FLAGS_INDEX, "general flags", false},
                     {"dungeon flags", DUNGEON_FLAGS_INDEX, "dungeon related flags", false},
                     {"portal flags", PORTAL_FLAGS_INDEX, "warp portal flags", false},
                     {"flag records", FLAG_RECORDS_INDEX, "view flag records", false},
                     {"flag log", FLAG_LOG_INDEX, "view flag log", false}};

void FlagsMenu::render() {
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
        case GENERAL_FLAGS_INDEX: {
            MenuRendering::set_menu(MN_GENERAL_FLAGS_INDEX);
            return;
        }
        case DUNGEON_FLAGS_INDEX: {
            MenuRendering::set_menu(MN_DUNGEON_FLAGS_INDEX);
            return;
        }
        case PORTAL_FLAGS_INDEX: {
            MenuRendering::set_menu(MN_PORTAL_FLAGS_INDEX);
            return;
        }
        case FLAG_RECORDS_INDEX: {
            MenuRendering::set_menu(MN_FLAG_RECORDS_INDEX);
            return;
        }
        case FLAG_LOG_INDEX: {
            MenuRendering::set_menu(MN_FLAG_LOG_INDEX);
            return;
        }
        }
    }

    Utilities::move_cursor(cursor, LINES);
    Utilities::render_lines(lines, cursor.y, LINES);
};
