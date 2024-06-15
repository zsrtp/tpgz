#include "utils/lines.h"
#include "libtp_c/include/msl_c/math.h"
#include "pos_settings.h"
#include "settings.h"
#include "utils/draw.h"
#include "utils/texture.h"
#include "rels/include/defines.h"

KEEP_VAR uint32_t g_cursorColor;
uint32_t min_line = 0;
uint32_t max_line = 15;

KEEP_FUNC float maxF(float a, float b) {
    return MAX(a, b);
}

KEEP_FUNC float minF(float a, float b) {
    return MIN(a, b);
}

KEEP_FUNC void GZ_drawMenuLines(Line input_lines[], uint32_t cursor, uint32_t LINES) {
    Vec2 offset = GZ_getSpriteOffset(STNG_SPRITES_MENU);
    float x_offset = offset.x;
    float y_offset = 0.0f;

    float max_line_width = 0.0f;
    for (uint32_t i = 0; i < LINES; ++i) {
        max_line_width = maxF(max_line_width, Font::getStrWidth(input_lines[i].line));
    }

    if (LINES <= MAX_RENDER_LINES) {
        min_line = 0;
        max_line = (MAX_RENDER_LINES - 1);
    }

    if (cursor > max_line) {
        max_line = cursor;
        min_line = max_line - (MAX_RENDER_LINES - 1);
    }
    if (cursor < min_line) {
        min_line = cursor;
        max_line = min_line + (MAX_RENDER_LINES - 1);
    }

    if (min_line > 0) {
        Font::GZ_drawStr("^", offset.x, offset.y - 8.0f, 0xFFFFFFFF, GZ_checkDropShadows());
    }

    if (max_line < LINES - 1) {
        Font::GZ_drawStr("v", offset.x, offset.y + 20.0f * MAX_RENDER_LINES - 10.f, 0xFFFFFFFF, GZ_checkDropShadows());
    }

    for (uint32_t i = min_line; i < MIN(max_line + 1, LINES); i++) {
        y_offset = (offset.y + (i - min_line) * 20.0f);

        uint32_t cursor_color = g_cursorColor;
        uint32_t description_color = 0xFFFFFF00;
        uint32_t description_alpha = 0xFF;

        // fade line/hide descriptions for lines the cursor isn't on
        if (input_lines[i].idx != cursor) {
            cursor_color = 0xFFFFFFFF;
            description_alpha = 0x00;
        }
        description_color |= description_alpha;

        // logic for lines that are toggleable
        if (input_lines[i].toggleable) {
            if (input_lines[i].active()) {
                Font::GZ_drawStr(" [X]", x_offset + max_line_width, y_offset, cursor_color,
                                 GZ_checkDropShadows());
            } else {
                Font::GZ_drawStr(" [", x_offset + max_line_width, y_offset, cursor_color,
                                 GZ_checkDropShadows());
                Font::GZ_drawStr(" ]", x_offset + max_line_width + Font::getStrWidth("[X"), y_offset, cursor_color,
                                 GZ_checkDropShadows());
            }

            Font::GZ_drawStr(input_lines[i].line, x_offset, y_offset, cursor_color, GZ_checkDropShadows());
        } else {
            Font::GZ_drawStr(input_lines[i].line, x_offset, y_offset, cursor_color, GZ_checkDropShadows());
            Font::GZ_drawStr(input_lines[i].value, x_offset + max_line_width, y_offset,
                             cursor_color, GZ_checkDropShadows());
        }

        // render line descriptions
        if (input_lines[i].idx == cursor) {
            Font::GZ_drawStr(input_lines[i].description, x_offset, 440.f, 0x00000000, true);
        }
        Font::GZ_drawStr(input_lines[i].description, x_offset, 440.f, description_color, false);
    }
}
