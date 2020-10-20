#include "libtp_c/include/flag.h"
#include "libtp_c/include/tp.h"
#include "font.h"
#include "menus/flags_menu.h"
#include "controller.h"
#include "utils/cursor.hpp"
#include "utils/lines.hpp"

#define LINES 4

static Cursor cursor = {0, 0};
bool init_once = false;

Line lines[LINES] = {
    {"general flags", GENERAL_FLAGS_INDEX, "general flags", false},
    {"dungeon flags", DUNGEON_FLAGS_INDEX, "dungeon related flags", false},
    {"portal flags", PORTAL_FLAGS_INDEX, "warp portal flags", false},
    {"temp flags", TEMP_FLAGS_INDEX, "local area temp flags", false}};

void FlagsMenu::render() {
    if (button_is_pressed(Controller::B)) {
        init_once = false;
		MenuRendering::set_menu(MN_MAIN_MENU_INDEX);
        return;
    }

    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

    if (current_input == Controller::Pad::A && a_held == false) {
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
            case TEMP_FLAGS_INDEX: {
		        MenuRendering::set_menu(MN_TEMP_FLAGS_INDEX);
                return;
            }
        }
    }

    Utilities::move_cursor(cursor, LINES);
    Utilities::render_lines(lines, cursor.y, LINES);
};
