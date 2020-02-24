#include "libtp_c/include/tp.h"
#include "libtp_c/include/controller.h"
#include "menu.h"
#include "controller.h"
#include "utils.h"
#include "gorge.h"
#include "rollcheck.h"
#define LINES 4

static int cursor = 2;
// static float current_offset = 0.0f;
// static int current_index = 0;
// bool trigger_menu_anim = false;

void transition_into(){};

Line lines[LINES] = {
    {"practice", 0},
    {"", 1},
    {"roll check [ ]", 2, "see how bad u are at chaining rolls"},
    {"gorge void [ ]", 3, "gorge void practice -- use L + Z to warp to to kak gorge"}};

// void menu_anim(Font& font, int idx) {
//     if (current_offset != 60.0f + ((float)PRACTICE_INDEX * 20.0f)) {
//         current_offset = current_offset + 5.0f;
//     }

//     font.renderChars(lines[idx].line, 15.0f, current_offset, 0xFFFFFFFF);
//     if (current_offset == 60.0f + ((float)PRACTICE_INDEX * 20.0f)) {
//         prac_visible = false;
//         mm_visible = true;
//         trigger_menu_anim = false;
//     }
// }

void PracticeMenu::render(Font& font) {
    // if (trigger_menu_anim == true) {
    //     menu_anim(font, 0);
    // }

    if (button_is_down(Controller::B)) {
        prac_visible = false;
        mm_visible = true;
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
            case GORGE_INDEX: {
                if (g_gorge_active) {
                    g_gorge_active = false;
                } else {
                    g_gorge_active = true;
                }
                break;
            }
            case ROLL_INDEX: {
                if (g_roll_check_active) {
                    g_roll_check_active = false;
                } else {
                    g_roll_check_active = true;
                }
                break;
            }
        }
    }

    font.renderChars("tpgz v0.1", 13.0f, 15.0f, 0x008080FF);

    for (int i = 0; i < LINES; i++) {
        float offset = (60.0f + (float)i * 20.0f);
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

        if (g_gorge_active) {
            strcpy(lines[GORGE_INDEX].line, "gorge void [X]");
        }
        else {
            strcpy(lines[GORGE_INDEX].line, "gorge void [ ]");
        }

        if (g_roll_check_active) {
            strcpy(lines[ROLL_INDEX].line, "roll check [X]");
        }
        else {
            strcpy(lines[ROLL_INDEX].line, "roll check [ ]");
        }

        font.renderChars(lines[i].line, 15.0f, offset, cursor_color);
        font.renderChars(lines[i].description, 15.0f, 440.f, description_color);
    };

    // if (g_gorge_active) {
    //     strcat(lines[GORGE_INDEX].line, " [X]");
    // }

    // if (g_roll_check_active) {
    //     strcat(lines[ROLL_INDEX].line, " [X]");
    // }
};