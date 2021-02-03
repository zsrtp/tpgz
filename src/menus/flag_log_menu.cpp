#include "menus/flags_menu.h"
#include "controller.h"
#include "font.h"
#include "libtp_c/include/flag.h"
#include "libtp_c/include/tp.h"
#include "utils/cursor.h"
#include "utils/lines.h"
#include "flaglog.h"

#define LINES 2

static Cursor cursor = {0, 0};
bool init_once = false;
bool g_flag_log_active = false;

Line lines[LINES] = {{"log activated", 0, "start logging flag changes", true, &g_flag_log_active},
                     {"clear log", 1, "clear flag log", false}};

void FlagLogMenu::render() {
    if (button_is_pressed(BACK_BUTTON)) {
        init_once = false;
        MenuRendering::set_menu(MN_FLAGS_INDEX);
        return;
    }

    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

    if (current_input == SELECTION_BUTTON && a_held == false) {
        switch (cursor.y) {
        case 0: {
            g_flag_log_active = !g_flag_log_active; // needs to be extern so it stays active outside of menu
            return;
        }
        case 1: {
            // clear log
            return;
        }
        }
    }

    Utilities::move_cursor(cursor, LINES);
    Utilities::render_lines(lines, cursor.y, LINES);
};