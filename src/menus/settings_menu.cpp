#include "libtp_c/include/tp.h"
#include "libtp_c/include/controller.h"
#include "menus/menu.h"
#include "tpgz/controller.h"
#include "tpgz/utils.h"
#include <stdio.h>
#include "tpgz/log.h"
#define LINES 5

static int cursor = 2;
bool g_reload_temp_flags;
bool g_drop_shadows = true;

Line lines[LINES] = {
    {"settings", 0, "", false},
    {"", 1, "", false},
    {"log level:", 2, "changes log level for debugging", false},
    {"reload temp flags", 3, "resets temp flags when using area reload cheat", true, &g_reload_temp_flags},
    {"drop shadows", 4, "adds shadows to all font letters", true, &g_drop_shadows}};

void SettingsMenu::render(Font& font) {
    if (button_is_down(Controller::B) && !button_is_held(Controller::B)) {
        settings_visible = false;
        mm_visible = true;
        return;
    };

    Utilities::move_cursor(cursor, LINES);

    if (button_is_down(Controller::A) && !button_is_held(Controller::A)) {
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
            case RELOAD_TEMP_FLAGS_INDEX: {
                g_reload_temp_flags = !g_reload_temp_flags;
                break;
            }
            case DROP_SHADOWS_INDEX: {
                g_drop_shadows = !g_drop_shadows;
                break;
            }
        }
    }
    Utilities::render_lines(font, lines, cursor, LINES);

    int cursor_alpha = 0xFF;
    int cursor_color = 0xFFFFFF00;
    float offset = (60.0f + ((float)LOG_LEVEL_INDEX * 20.0f));

    if (lines[LOG_LEVEL_INDEX].idx != cursor) {
        cursor_alpha = 0x80;
    }

    cursor_color |= cursor_alpha;
    char buf[5];
    switch (g_log_level) {
        case 0: {
            sprintf(buf, "NONE");
            break;
        }
        case 1: {
            sprintf(buf, "INFO");
            break;
        }
        case 2: {
            sprintf(buf, "DEBUG");
            break;
        }
    }
    font.renderChars(buf, 105.0f, offset, cursor_color);
    if (g_drop_shadows) {
        font.renderChars(buf, 105.0f+2.0f, offset+2.0f, 0x00000080);
    }
};