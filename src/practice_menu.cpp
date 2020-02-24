#include "libtp_c/include/tp.h"
#include "libtp_c/include/controller.h"
#include "menu.h"
#include "controller.h"
#include "utils.h"
#include "gorge.h"
#include "rollcheck.h"
#define LINES 4

static int cursor = 2;

void transition_into(){};

Line lines[LINES] = {
    {"practice", 0},
    {"", 1},
    {"roll check [ ]", 2, "see how bad u are at chaining rolls"},
    {"gorge void [ ]", 3, "gorge void practice -- use L + Z to warp to to kak gorge"}};

void PracticeMenu::render(Font& font) {
    if (button_is_down(Controller::B)) {
        prac_visible = false;
        mm_visible = true;
        return;
    };

    move_cursor(cursor, LINES);

    if (button_is_down(Controller::A) && !button_is_held(Controller::A)) {
        switch (cursor) {
            case GORGE_INDEX: {
                g_gorge_active = !g_gorge_active;
                break;
            }
            case ROLL_INDEX: {
                g_roll_check_active = !g_roll_check_active;
                break;
            }
        }
    }

    render_lines(font, LINES);
    float gorge_offset = (60.0f + (float)GORGE_INDEX * 20.0f);
    float roll_offset = (60.0f + (float)GORGE_INDEX * 20.0f);
    int cursor_color = 0xFFFFFF00;
    int cursor_alpha = 0xFF;
    if (lines[i].idx != cursor) {
        cursor_alpha = 0x80;
    }
    cursor_color |= cursor_alpha;

    if (g_gorge_active) {
        strcpy(lines[GORGE_INDEX].line, "gorge void [X]");
    } else {
        strcpy(lines[GORGE_INDEX].line, "gorge void [ ]");
    }

    if (g_roll_check_active) {
        strcpy(lines[ROLL_INDEX].line, "roll check [X]");
    } else {
        strcpy(lines[ROLL_INDEX].line, "roll check [ ]");
    }

    font.renderChars(lines[GORGE_INDEX].line, 15.0f, gorge_offset, cursor_color);
    font.renderChars(lines[ROLL_INDEX].line, 15.0f, roll_offset, cursor_color);
};