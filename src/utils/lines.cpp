#include "utils/lines.h"
#include "libtp_c/include/math.h"
#include "libtp_c/include/system.h"
#include "menus/position_settings_menu.h"
#include "menus/settings_menu.h"
#include "utils/draw.h"
#include "utils/texture.h"

int cursor_rgba;
int min_line = 0;
int max_line = 15;

float max_value_f(float a, float b) {
    return MAX(a, b);
}

namespace Utilities {
void render_lines(Line input_lines[], int cursor, int LINES) {
    float x_offset = sprite_offsets[MENU_INDEX].x;
    float y_offset = 0.0f;

    float max_line_width = 0.0f;
    for (int i = 0; i < LINES; ++i) {
        max_line_width = max_value_f(max_line_width, Font::get_chars_width(input_lines[i].line));
    }

    if (LINES <= MAX_RENDER_LINES) {
        min_line = 0;
        max_line = MAX_RENDER_LINES;
    }

    for (int i = 0; i < LINES; i++) {
        if (cursor > max_line) {
            max_line = cursor;
            min_line = max_line - MAX_RENDER_LINES;
        }
        if (cursor < min_line) {
            min_line = cursor;
            max_line = min_line + MAX_RENDER_LINES;
        }

        if (i > max_line || i < min_line) {
            continue;
        }
        y_offset = (sprite_offsets[MENU_INDEX].y + (i - min_line) * 20.0f);

        int cursor_color = cursor_rgba;
        int description_color = 0xFFFFFF00;
        int description_alpha = 0xFF;

        // fade line/hide descriptions for lines the cursor isn't on
        if (input_lines[i].idx != cursor) {
            cursor_color = 0xFFFFFFFF;
            description_alpha = 0x00;
        }
        description_color |= description_alpha;

        // logic for lines that are toggleable
        if (input_lines[i].toggleable) {
            if (*input_lines[i].activation_flag) {
                Font::gz_renderChars(" [X]", x_offset + max_line_width, y_offset, cursor_color,
                                     g_drop_shadows);
            } else {
                Font::gz_renderChars(" [ ]", x_offset + max_line_width, y_offset, cursor_color,
                                     g_drop_shadows);
            }

            Font::gz_renderChars(input_lines[i].line, x_offset, y_offset, cursor_color,
                                 g_drop_shadows);
        } else {
            Font::gz_renderChars(input_lines[i].line, x_offset, y_offset, cursor_color,
                                 g_drop_shadows);
            Font::gz_renderChars(input_lines[i].value, x_offset + max_line_width, y_offset,
                                 cursor_color, g_drop_shadows);
        }

        // render line descriptions
        if (input_lines[i].idx == cursor) {
            Font::gz_renderChars(input_lines[i].description, x_offset, 440.f, 0x00000000, true);
        }
        Font::gz_renderChars(input_lines[i].description, x_offset, 440.f, description_color, false);
    };
}

void change_cursor_color() {
    switch (g_cursor_color) {
    case CURSOR_GREEN: {
        cursor_rgba = 0x00CC00FF;
        break;
    }
    case CURSOR_BLUE: {
        cursor_rgba = 0x0080FFFF;
        break;
    }
    case CURSOR_RED: {
        cursor_rgba = 0xCC0000FF;
        break;
    }
    case CURSOR_ORANGE: {
        cursor_rgba = 0xEE8000FF;
        break;
    }
    case CURSOR_YELLOW: {
        cursor_rgba = 0xFFCC00FF;
        break;
    }
    case CURSOR_PURPLE: {
        cursor_rgba = 0x6600CCFF;
        break;
    }
    }
}

}  // namespace Utilities
