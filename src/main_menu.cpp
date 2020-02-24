#include "libtp_c/include/tp.h"
#include "libtp_c/include/controller.h"
#include "menu.h"
#include "controller.h"
#include "utils.h"
#include <stdio.h>
#include "log.h"
#define LINES 9

static int cursor = 2;
static float current_offset = 0.0f;
static int current_index = 0;
bool trigger_menu_anim = false;
static char log_level_line[25];

Line lines[LINES] = {
    {"main menu", 0},
    {"", 1},
    {"inventory", 2, "set link's items and equipment"},
    {"cheats", 3, "turn cheats on/off"},
    {"warping", 4, "warp to dungeons, towns, grottos, etc."},
    {"memory", 5, "add memory watches to the screen"},
    {"practice", 6, "practice tools for various categories"},
    {"settings", 7, "configure settings"},
    {"log level: ", 8, "set the debug logging level"}};

void transition_into(){};

// void menu_anim(Font& font, int idx) {
//     if (current_offset != 60.0f) {
//         current_offset = current_offset - 5.0f;
//     }

//     font.renderChars(lines[idx].line, 15.0f, current_offset, 0xFFFFFFFF);
//     if (current_offset == 60.0f) {
//         trigger_menu_anim = false;
//         switch (idx) {
//             case PRACTICE_INDEX: {
//                 prac_visible = true;
//                 break;
//             }
//             case SETTINGS_INDEX: {
//                 settings_visible = true;
//                 break;
//             }
//         }
//     }
// }

void MainMenu::render(Font& font) {
    // if (trigger_menu_anim == true) {
    //     menu_anim(font, current_index);
    // }

    if (button_is_down(Controller::B) && !button_is_held(Controller::B)) {
        mm_visible = false;
        return;
    };

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

    if (button_is_down(Controller::A) && !button_is_held(Controller::A)) {
        switch (cursor) {
            case MEMORY_INDEX: {
                // go to memory menu
                return;
            }
            case INVENTORY_INDEX: {
                //transition(MenuState::InventoryMenu);
                return;
            }
            case CHEAT_INDEX: {
                mm_visible = false;
                cheats_visible = true;
                return;
            }
            case SETTINGS_INDEX: {
                //transition(MenuState::Settings);
                return;
            }
            case WARPING_INDEX: {
                //transition(MenuState::Warp);
                return;
            }
            case PRACTICE_INDEX: {
                mm_visible = false;
                // current_offset = 60.0f + ((float)PRACTICE_INDEX * 20.0f);
                // current_index = PRACTICE_INDEX;
                prac_visible = true;
                return;
            }
            case LOG_LEVEL_INDEX: {
                if (g_log_level < 2) {
                    g_log_level++;
                } else {
                    g_log_level = 0;
                }
            }
        }
    }
    font.renderChars("tpgz v0.1", 13.0f, 15.0f, 0x008080FF);

    if (mm_visible == true) {
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
            if (lines[i].idx == LOG_LEVEL_INDEX) {
                char buf[1];
                sprintf(buf, "%d", g_log_level);
                font.renderChars(buf, 105.0f, offset, cursor_color);
            }
        };
    };
};