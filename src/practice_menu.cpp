#include "libtp_c/include/tp.h"
#include "libtp_c/include/system.h"
#include "libtp_c/include/controller.h"
#include "menu.h"
#include "controller.h"
#include "fifo_queue.h"
#include "utils.h"
#include "gorge.h"
#include "rollcheck.h"
#include "save_injector.h"
#include "save_files/norgor.h"
#include "log.h"
#define LINES 5


static int cursor = 2;

void transition_into(){};

Line lines[LINES] = {
    {"practice", 0, "", false},
    {"", 1, "", false},
    {"roll check", 2, "see how bad u are at chaining rolls", true},
    {"gorge void", 3, "gorge void practice -- use L + Z to warp to to kak gorge", true},
    {"norgor", 4, "for otti :^)", false}};

void PracticeMenu::render(Font& font) {
    
    if (button_is_down(Controller::B)) {
        prac_visible = false;
        mm_visible = true;
        return;
    };

    tp_osReport("%d", tp_mPadStatus.sval == Controller::Pad::A);
    tp_osReport("%d", button_is_held(Controller::A));
    if (tp_mPadStatus.sval == Controller::Pad::A && !button_is_held(Controller::A)) {
        switch (cursor-2) {
            case GORGE_INDEX: {
                g_gorge_active = !g_gorge_active;
                break;
            }
            case ROLL_INDEX: {
                g_roll_check_active = !g_roll_check_active;
                break;
            }
            case NORGOR_INDEX: {
                inject_save_flag = true;
                prac_visible = false;
                fifo_visible = true;
                break;
            }
        }
    }

    Utilities::move_cursor(cursor, LINES);

    Utilities::render_lines(font, lines, cursor, LINES);
    float gorge_offset = (60.0f + (float)GORGE_INDEX * 20.0f);
    float roll_offset = (60.0f + (float)ROLL_INDEX * 20.0f);
    int cursor_color = 0xFFFFFF00;
    int cursor_alpha = 0xFF;
    if (lines[GORGE_INDEX].idx != cursor) {
        cursor_alpha = 0x80;
    }
    cursor_color |= cursor_alpha;

    font.renderChars(lines[GORGE_INDEX].line, 15.0f, gorge_offset, cursor_color);
    font.renderChars(lines[ROLL_INDEX].line, 15.0f, roll_offset, cursor_color);
};