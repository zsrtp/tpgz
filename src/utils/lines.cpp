#include "utils/lines.hpp"

namespace Utilities {
    void render_lines(Font &font, Line input_lines[], int cursor, int LINES, float menu_toggle_switch_x_offset) {
        font.gz_renderChars("tpgz v0.1a", 25.0f, 25.0f, 0x00CC00FF, g_drop_shadows);
        float offset = 0.0f;
        for (int i = 0; i < LINES; i++) {
            // don't draw past line 15/cursor
            if (LINES > 15 && i > 15 && cursor < i) {
                if (i == LINES - 1 && cursor < LINES) {
                    font.gz_renderChars("______", 25.0f, 380.0f, 0xFFFFFF80, g_drop_shadows);
                }
                continue;
            };

            // initiate scroll
            if (cursor > 15) {
                if (i < (cursor - 15)) {
                    continue;
                } else {
                    offset = (60.0f + (i - (cursor - 15)) * 20.0f);
                }
            }
            // normal line rendering offset
            else {
                offset = (60.0f + (i * 20.0f));
            }

            int cursor_color = 0x00CC00FF;
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
                    font.gz_renderChars(" [X]", menu_toggle_switch_x_offset, offset, cursor_color, g_drop_shadows);
                } else {
                    font.gz_renderChars(" [ ]", menu_toggle_switch_x_offset, offset, cursor_color, g_drop_shadows);
                }

                font.gz_renderChars(input_lines[i].line, 25.0f, offset, cursor_color, g_drop_shadows);
            } else {
                font.gz_renderChars(input_lines[i].line, 25.0f, offset, cursor_color, g_drop_shadows);
            }

            // render line descriptions
            font.gz_renderChars(input_lines[i].description, 25.0f, 440.f, description_color, false);
        };
    }

}  // namespace Utilities
