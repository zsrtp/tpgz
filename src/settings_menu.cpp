#include "libtp_c/include/system.h"
#include "libtp_c/include/tp.h"
#include "controller.h"
#include "menu.h"
#include "utils.h"
#include <stdio.h>
#include "log.h"
#define LINES 4

static int cursor = 2;
bool g_reset_temp_flags;
bool g_drop_shadows = true;
bool init_once = false;


Line lines[LINES] = {
    {"settings", 0, "", false},
    {"", 1, "", false},
    {"log level:", 2, "changes log level for debugging", false, nullptr, true, {"NONE","INFO","DEBUG"}, &g_log_level},
    {"drop shadows", 3, "adds shadows to all font letters", true, &g_drop_shadows}};

void SettingsMenu::render(Font& font) {
    if (button_is_pressed(Controller::B)) {
        init_once = false;
        settings_visible = false;
        mm_visible = true;
        return;
    };

    if (!init_once) {current_input = 0;init_once = true;}

    Utilities::move_cursor(cursor, LINES);

    if (current_input == 256 && a_held == false) {
        switch (cursor) {
            case LOG_LEVEL_INDEX: {
                if (g_log_level < 2) {
                    g_log_level++;
                    break;
                } else {
                    g_log_level = 0;
                    break;
                }
            }
            case DROP_SHADOWS_INDEX: {
                g_drop_shadows = !g_drop_shadows;
                break;
            }
        }
    }
    Utilities::render_lines(font, lines, cursor, LINES);

    // int cursor_alpha = 0xFF;
    // int cursor_color = 0xFFFFFF00;
    // float offset = (60.0f + ((float)LOG_LEVEL_INDEX * 20.0f));

    // if (lines[LOG_LEVEL_INDEX].idx != cursor) {
    //     cursor_alpha = 0x80;
    // }

    // cursor_color |= cursor_alpha;
    // char buf[5];
    // switch (g_log_level) {
    //     case 0: {
    //         sprintf(buf, "NONE");
    //         break;
    //     }
    //     case 1: {
    //         sprintf(buf, "INFO");
    //         break;
    //     }
    //     case 2: {
    //         sprintf(buf, "DEBUG");
    //         break;
    //     }
    // }
    // font.renderChars(buf, 105.0f, offset, cursor_color);
    // if (g_drop_shadows) {
    //     font.renderChars(buf, 105.0f+2.0f, offset+2.0f, 0x00000080);
    // }
};