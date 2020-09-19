#include "font.h"
#include "menu.h"
#include "controller.h"
#include "utils/cursor.hpp"
#include "utils/lines.hpp"
#include <cstdio>

#define LINES SPRITES_AMNT
#define NO_SELECTION ((uint8_t)-1)

#define INITAL_SPEED 1.0f
#define INCREMENT_FACTOR 1.05f
#define MAX_SPEED 20.f

static Cursor cursor = {0, 0};
bool init_once = false;
bool pos_settings_visible;

float speed;
bool was_pressed;

uint8_t selected_item = NO_SELECTION;

Vec2 sprite_offsets[SPRITES_AMNT];

Line lines[LINES] = {
    {"main menu", SpritesIndex::MENU_INDEX, "Change main menu position", false},
    {"input viewer", SpritesIndex::VIEWER_INDEX, "Change input viewer position", false},
    {"link debug info", SpritesIndex::DEBUG_INFO_INDEX, "Change link debug info position", false},
    {"timer", SpritesIndex::TIMER_SPR_INDEX, "Change timer position", false},
    {"load timer", SpritesIndex::LOAD_TIMER_SPR_INDEX, "Change load timer position", false},
    {"igt timer", SpritesIndex::IGT_TIMER_SPR_INDEX, "Change IGT timer position", false}};

void PosSettingsMenu::render(Font& font) {
    if (button_is_pressed(Controller::B)) {
        init_once = false;
        pos_settings_visible = false;
        settings_visible = true;
        mm_visible = false;

        selected_item = NO_SELECTION;
        return;
    };

    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

    if (current_input == 256 && a_held == false) {
        if (cursor.y < SPRITES_AMNT) {
            selected_item = selected_item == cursor.y ? NO_SELECTION : cursor.y;
        }
    }

    if (selected_item != NO_SELECTION && selected_item < SPRITES_AMNT) {
        if (button_is_pressed_time(Controller::DPAD_RIGHT, 3)) {
            sprite_offsets[selected_item].x += speed;
        }
        if (button_is_pressed_time(Controller::DPAD_LEFT, 3)) {
            sprite_offsets[selected_item].x -= speed;
        }
        if (button_is_pressed_time(Controller::DPAD_UP, 3)) {
            sprite_offsets[selected_item].y -= speed;
        }
        if (button_is_pressed_time(Controller::DPAD_DOWN, 3)) {
            sprite_offsets[selected_item].y += speed;
        }
    }

    if (button_is_down(Controller::DPAD_RIGHT) ||
        button_is_down(Controller::DPAD_LEFT) ||
        button_is_down(Controller::DPAD_UP) ||
        button_is_down(Controller::DPAD_DOWN))
    {
        if (speed < MAX_SPEED) {
            speed *= INCREMENT_FACTOR;
        }
        if (speed > MAX_SPEED) {
            speed = MAX_SPEED;
        }
    } else {
        speed = INITAL_SPEED;
    }

    Utilities::move_cursor(cursor, LINES, 1, selected_item != NO_SELECTION, selected_item != NO_SELECTION);
    Utilities::render_lines(font, lines, cursor.y, LINES);
};