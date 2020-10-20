#include "libtp_c/include/tp.h"
#include "font.h"
#include "menus/position_settings_menu.h"
#include "menus/settings_menu.h"
#include "controller.h"
#include "utils/cursor.hpp"
#include "utils/lines.hpp"
#include "fifo_queue.h"
#include "utils/draw.h"
#include <cstdio>

#define LINES SPRITES_AMNT
#define NO_SELECTION ((uint8_t)-1)

#define INITAL_SPEED 1.0f
#define INCREMENT_FACTOR 1.05f
#define MAX_SPEED 20.f

static Cursor cursor = {0, 0};
bool init_once = false;

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
    {"igt timer", SpritesIndex::IGT_TIMER_SPR_INDEX, "Change IGT timer position", false},
    {"fifo queue", SpritesIndex::FIFO_SPR_INDEX, "Change fifo queue position", false}};

void draw_cursor(Vec2 pos) {
    bool cycle = (TP::get_frame_count() / 8) % 2;
    if (g_drop_shadows) {
        Draw::draw_rect_outline(DROP_SHADOWS_RGBA, {pos.x - 10 + 1, pos.y + 1}, {20, 0}, 0xA);
        Draw::draw_rect_outline(DROP_SHADOWS_RGBA, {pos.x + 1, pos.y - 10 + 1}, {0, 20}, 0xA);
    }
    Draw::draw_rect_outline(cycle ? cursor_rgba : 0xFFFFFFFF, {pos.x - 10, pos.y}, {20, 0}, 0xA);
    Draw::draw_rect_outline(cycle ? cursor_rgba : 0xFFFFFFFF, {pos.x, pos.y - 10}, {0, 20}, 0xA);
}

void PosSettingsMenu::render() {
    if (button_is_pressed(Controller::B)) {
        if (selected_item != NO_SELECTION) {
            selected_item = NO_SELECTION;
        } else {
            init_once = false;
		    MenuRendering::set_menu(MN_SETTINGS_INDEX);
            return;
        }
    };

    if (!init_once) {
        selected_item = NO_SELECTION;
        current_input = 0;
        init_once = true;
    }

    if (current_input == Controller::Pad::A && a_held == false) {
        if (cursor.y < SPRITES_AMNT) {
            selected_item = selected_item == cursor.y ? NO_SELECTION : cursor.y;
        }
    }

    if (selected_item != NO_SELECTION && selected_item < SPRITES_AMNT) {
        if (button_is_pressed(Controller::DPAD_RIGHT, 3)) {
            sprite_offsets[selected_item].x += speed;
        }
        if (button_is_pressed(Controller::DPAD_LEFT, 3)) {
            sprite_offsets[selected_item].x -= speed;
        }
        if (button_is_pressed(Controller::DPAD_UP, 3)) {
            sprite_offsets[selected_item].y -= speed;
        }
        if (button_is_pressed(Controller::DPAD_DOWN, 3)) {
            sprite_offsets[selected_item].y += speed;
        }
        // Draw visual cursor
        draw_cursor(sprite_offsets[selected_item]);
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
    Utilities::render_lines(lines, cursor.y, LINES);
}

void PosSettingsMenu::initDefaults() {
    sprite_offsets[VIEWER_INDEX] = {220.f, 380.f};
    sprite_offsets[MENU_INDEX] = {25.f, 60.f};
    sprite_offsets[DEBUG_INFO_INDEX] = {450.0f, 200.f};
    sprite_offsets[TIMER_SPR_INDEX] = {525.0f, 420.f};
    sprite_offsets[LOAD_TIMER_SPR_INDEX] = {525.0f, 30.f};
    sprite_offsets[IGT_TIMER_SPR_INDEX] = {35.0f, 30.f};
    sprite_offsets[FIFO_SPR_INDEX] = {5.0f, 440.f};
}