#include "utils/lines.hpp"

int cursor_rgba;

namespace Utilities {
    void render_lines(Font &font, Line input_lines[], int cursor, int LINES, float menu_toggle_switch_x_offset) {
        float x_offset = 25.0f + sprite_offsets[MENU_INDEX].x;
        float y_offset = 0.0f;
		font.gz_renderChars("tpgz v0.1a", x_offset, 25.0f, cursor_rgba, g_drop_shadows);

        for (int i = 0; i < LINES; i++) {
            // don't draw past line 15/cursor
            if (LINES > 15 && i > 15 && cursor < i) {
                if (i == LINES - 1 && cursor < LINES) {
                    font.gz_renderChars("______", x_offset, 380.0f, 0xFFFFFF80, g_drop_shadows);
                }
                continue;
            };

            // initiate scroll
            if (cursor > 15) {
                if (i < (cursor - 15)) {
                    continue;
                } else {
                    y_offset = ((60.0f + (sprite_offsets[MENU_INDEX].y)) + (i - (cursor - 15)) * 20.0f);
                }
            }
            // normal line rendering offset
            else {
                y_offset = ((60.0f + (sprite_offsets[MENU_INDEX].y)) + (i * 20.0f));
            }

            //int cursor_color = 0x00CC00FF;
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
                    font.gz_renderChars(" [X]", x_offset + menu_toggle_switch_x_offset, y_offset, cursor_color, g_drop_shadows);
                } else {
                    font.gz_renderChars(" [ ]", x_offset + menu_toggle_switch_x_offset, y_offset, cursor_color, g_drop_shadows);
                }

                font.gz_renderChars(input_lines[i].line, x_offset, y_offset, cursor_color, g_drop_shadows);
            } else {
                font.gz_renderChars(input_lines[i].line, x_offset, y_offset, cursor_color, g_drop_shadows);
            }

            // render line descriptions
            font.gz_renderChars(input_lines[i].description, x_offset, 440.f, description_color, false);
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
