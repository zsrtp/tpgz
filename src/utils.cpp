#include "utils.h"
#include "libtp_c/include/tp.h"
#include "libtp_c/include/system.h"
#include "controller.h"
#include "save_injector.h"
#include "commands.h"
#include "gorge.h"
#include "log.h"
#include "fs.h"
#include "menu.h"

bool loading_initiated = false;
int apply_after_counter = 0;

namespace Utilities {
    static Log log;

    void move_cursor(int& cursor, int LINES) {
        if (button_is_pressed(Controller::DPAD_DOWN)) {
            if (cursor < LINES - 1) {
                cursor++;
            } else if (cursor == LINES - 1) {
                cursor = 2;
            }
        };

        if (button_is_pressed(Controller::DPAD_UP)) {
            if (cursor > 2) {
                cursor--;
            } else if (cursor == 2) {
                cursor = LINES - 1;
            }
        };
    }

    void render_lines(Font& font, Line input_lines[], int cursor, int LINES) {
        font.renderChars("tpgz v0.1a", 13.0f, 15.0f, 0x00CC00FF);

        for (int i = 0; i < LINES; i++) {
            float offset = (60.0f + ((float)i * 20.0f));
            int cursor_color = 0xFFFFFF00;
            int description_color = 0xFFFFFF00;
            int cursor_alpha = 0xFF;
            int description_alpha = 0xFF;
            int drop_shadows_color = 0x00000080;

            if (input_lines[i].idx != cursor) {
                cursor_alpha = 0x80;
            }
            if (input_lines[i].idx != cursor) {
                description_alpha = 0x00;
            }
            cursor_color |= cursor_alpha;
            description_color |= description_alpha;

            if (input_lines[i].toggleable) {
                char toggleline[54];
                for (int j = 0; j < 50; j++) {
                    toggleline[j] = input_lines[i].line[j];
                }
                if (*input_lines[i].activation_flag) {
                    strcat(toggleline, " [X]");
                } else {
                    strcat(toggleline, " [ ]");
                }

                font.renderChars(toggleline, 15.0f, offset, cursor_color);
                if (g_drop_shadows) {
                    font.renderChars(toggleline, 15.0f + 2.0f, offset + 2.0f, drop_shadows_color);
                };
            } else {
                font.renderChars(input_lines[i].line, 15.0f, offset, cursor_color);
                if (g_drop_shadows) {
                    font.renderChars(input_lines[i].line, 15.0f + 2.0f, offset + 2.0f, drop_shadows_color);
                };
            }

            font.renderChars(input_lines[i].description, 200.0f, 440.f, description_color);
            if (g_drop_shadows && input_lines[i].idx == cursor) {
                font.renderChars(input_lines[i].description, 200.0f + 2.0f, 440.0f + 2.0f, drop_shadows_color);
            };
        };
    }  // namespace Utilities

    void trigger_load() {
        // trigger loading
        if (tp_fopScnRq.isLoading == 0 && !loading_initiated) {
            log.PrintLog("Initiating warp", INFO);
            practice_file.inject_options_before_load();
            tp_gameInfo.warp.enabled = true;
        }

        if (tp_fopScnRq.isLoading == 1) {
            practice_file.inject_options_during_load();
            loading_initiated = true;
        }

        if (loading_initiated == true) {
            if (tp_fopScnRq.isLoading == 0) {
                practice_file.inject_options_after_load();
                tp_osReport("%d", apply_after_counter);
                if (practice_file.inject_options_after_counter == apply_after_counter) {
                    apply_after_counter = 0;
                    practice_file.inject_options_after_counter = 0;
                    loading_initiated = false;
                    inject_save_flag = false;
                } else {
                    apply_after_counter++;
                }
            }
        }
    }
}  // namespace Utilities