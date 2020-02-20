#include "libtp_c/include/tp.h"
#include "libtp_c/include/controller.h"
#include "menu.h"
#include "controller.h"
#include "utils.h"
#include "gorge.h"
#include "rollcheck.h"
#define LINES 2

static int cursor = 0;
static bool ddown_held_last_frame;
static bool dup_held_last_frame;

void transition_into(){};

void PracticeMenu::render(Font& font) {
    Line lines[LINES] = {
        {"rolling", 0, false, "see how bad u are at chaining rolls"},
        {"gorge void", 1, false, "gorge void practice -- use L + R to warp to to kak gorge"}};

    if (button_is_down(Controller::B)) {
        prac_visible = false;
        mm_visible = true;
        return;
    };

    if (!button_is_down(Controller::DPAD_DOWN)) {
        ddown_held_last_frame = false;
    };

    if (!button_is_down(Controller::DPAD_UP)) {
        dup_held_last_frame = false;
    };

    if (button_is_down(Controller::DPAD_DOWN) && ddown_held_last_frame == false) {
        if (cursor < LINES - 1) {
            cursor++;
        }
        ddown_held_last_frame = true;
    };

    if (button_is_down(Controller::DPAD_UP) && dup_held_last_frame == false) {
        if (cursor > 0) {
            cursor--;
        }
        dup_held_last_frame = true;
    };

    if (button_is_down(Controller::A)) {
        switch (cursor) {
            case GORGE_INDEX: {

            }
            case ROLL_INDEX: {

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

        if (i == GORGE_INDEX && (GorgeVoidIndicator::active == true)) {
            strcat(lines[i].line, " [X]");
        }

        if (i == ROLL_INDEX && (RollIndicator::active == true)) {
            strcat(lines[i].line, " [X]");
        }

        font.renderChars(lines[i].line, 15.0f, offset, cursor_color);
        font.renderChars(lines[i].description, 15.0f, 440.f, description_color);
    };
};