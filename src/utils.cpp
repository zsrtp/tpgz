#include "controller.h"
#include "utils.h"
#include "menu.h"

void move_cursor(int& cursor, int LINES) {
    if (button_is_down(Controller::DPAD_DOWN) && !button_is_held(Controller::DPAD_DOWN)) {
        if (cursor < LINES - 1) {
            cursor++;
        } else if (cursor == LINES - 1) {
            cursor = 2;
        }
    };

    if (button_is_down(Controller::DPAD_UP) && !button_is_held(Controller::DPAD_UP)) {
        if (cursor > 2) {
            cursor--;
        } else if (cursor == 2) {
            cursor = LINES - 1;
        }
    };
}

void menu_anim(Font& font, int idx) {
    if (current_offset != 60.0f) {
        current_offset = current_offset - 5.0f;
    }

    font.renderChars(lines[idx].line, 15.0f, current_offset, 0xFFFFFFFF);
    if (current_offset == 60.0f) {
        trigger_menu_anim = false;
        switch (idx) {
            case PRACTICE_INDEX: {
                prac_visible = true;
                break;
            }
            case SETTINGS_INDEX: {
                settings_visible = true;
                break;
            }
        }
    }
}

void render_lines(Font& font, int LINES) {
    font.renderChars("tpgz v0.1", 13.0f, 15.0f, 0x008080FF);
    
    for (int i = 0; i < LINES; i++) {
        float offset = (60.0f + ((float)i * 20.0f));
        int cursor_color = 0xFFFFFF00;
        int description_color = 0xFFFFFF00;
        int cursor_alpha = 0xFF;
        int description_alpha = 0xFF;
        if (lines[i].idx != cursor) {
            cursor_alpha = 0x80;
        }
        if (lines[i].idx != cursor) {
            description_alpha = 0x00;
        }
        cursor_color |= cursor_alpha;
        description_color |= description_alpha;
        font.renderChars(lines[i].line, 15.0f, offset, cursor_color);
        font.renderChars(lines[i].description, 15.0f, 440.f, description_color);
    };
}