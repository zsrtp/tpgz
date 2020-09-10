#include "libtp_c/include/flag.h"
#include "libtp_c/include/tp.h"
#include "font.h"
#include "menu.h"
#include "controller.h"
#include "utils/cursor.hpp"
#include "utils/lines.hpp"

#define LINES 3

static Cursor cursor = {0, 0};
bool init_once = false;
bool flags_menu_visible;

Line lines[LINES] = {
    {"general flags", GENERAL_FLAGS_INDEX, "general flags", false},
    {"dungeon flags", DUNGEON_FLAGS_INDEX, "dungeon related flags", false},
    {"portal flags", PORTAL_FLAGS_INDEX, "warp portal flags", false}};

void FlagsMenu::render(Font& font) {
    if (button_is_pressed(Controller::B)) {
        init_once = false;
        flags_menu_visible = false;
        mm_visible = true;
        return;
    }

    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

    if (current_input == 256 && a_held == false) {
        switch (cursor.y) {
            case GENERAL_FLAGS_INDEX: {
                flags_menu_visible = false;
                general_flags_visible = true;
                return;
            }
            case DUNGEON_FLAGS_INDEX: {
                flags_menu_visible = false;
                dungeon_flags_visible = true;
                return;
            }
            case PORTAL_FLAGS_INDEX: {
                flags_menu_visible = false;
                portal_flags_visible = true;
                return;
            }
        }
    }

    Utilities::move_cursor(cursor, LINES);
    Utilities::render_lines(font, lines, cursor.y, LINES);
};
