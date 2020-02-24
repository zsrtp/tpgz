#include "libtp_c/include/tp.h"
#include "libtp_c/include/controller.h"
#include "menu.h"
#include "controller.h"
#include "utils.h"
#include <stdio.h>
#include "log.h"
#define LINES 3

static int cursor = 2;

Line lines[LINES] = {
    {"main menu", 0},
    {"", 1},
    {"log level", 2, "changes log level for debugging"},
    {""}

void SettingsMenu::render(Font& font) {
    if (button_is_down(Controller::B) && !button_is_held(Controller::B)) {
        settings_visible = false;
        mm_visible = true;
        return;
    };

    move_cursor(cursor, LINES);

    if (button_is_down(Controller::A) && !button_is_held(Controller::A)) {
        switch (cursor) {
            case LOG_LEVEL_INDEX: {
                if (g_log_level < 2) {
                    g_log_level++;
                } else {
                    g_log_level = 0;
                }
            }
        }
    }

    if (settings_visible == true) {
        render_lines(font, LINES);

        int cursor_alpha = 0xFF;
        int cursor_color = 0xFFFFFF00;
        float offset = (60.0f + ((float)LOG_LEVEL_INDEX * 20.0f));

        if (lines[LOG_LEVEL_INDEX].idx != cursor) {
            cursor_alpha = 0x00;
        }

        cursor_color |= cursor_alpha;
        char buf[5];
        case (g_log_level) {
            case 0: { buf = "NONE"}
            case 1: { buf = "INFO"}
            case 2: { buf = "DEBUG"}
        }
        font.renderChars(buf, 105.0f, offset, cursor_color);
    };
};