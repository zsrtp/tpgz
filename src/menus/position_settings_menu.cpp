#include "font.h"
#include "menu.h"
#include "controller.h"
#include "utils/cursor.hpp"
#include "utils/lines.hpp"
#include <cstdio>

#define LINES 6

static Cursor cursor = {0, 0};
bool init_once = false;
bool pos_settings_visible;
bool lock_cursor_y = false;
bool lock_cursor_x = false;

bool menu_selected = false;
bool viewer_selected = false;
bool debug_info_selected = false;
bool timer_selected = false;
bool load_timer_selected = false;
bool igt_timer_selected = false;

// main menu offsets
float menu_x_offset;
float menu_y_offset;

// input viewer offsets
float viewer_x_offset;
float viewer_y_offset;

// debug info offsets
float debug_info_x_offset;
float debug_info_y_offset;

// timer offsets
float timer_x_offset;
float timer_y_offset;

// load timer offsets
float load_timer_x_offset;
float load_timer_y_offset;

// igt timer offsets
float igt_timer_x_offset;
float igt_timer_y_offset;

Line lines[LINES] = {
    {"main menu", 0, "Change main menu position", false},
    {"input viewer", 1, "Change input viewer position", false},
    {"link debug info", 2, "Change link debug info position", false},
    {"timer", 3, "Change timer position", false},
    {"load timer", 4, "Change load timer position", false},
    {"igt timer", 5, "Change IGT timer position", false}};

void PosSettingsMenu::render(Font& font) {
    if (button_is_pressed(Controller::B)) {
        init_once = false;
        pos_settings_visible = false;
        settings_visible = true;
        mm_visible = false;

        menu_selected = false;
        viewer_selected = false;
        debug_info_selected = false;
        timer_selected = false;
        load_timer_selected = false;
        igt_timer_selected = false;
        lock_cursor_x = false;
        lock_cursor_y = false;
        return;
    };

    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

    if (current_input == 256 && a_held == false) {
        switch (cursor.y) {
            case 0: {
                menu_selected = !menu_selected;
                break;
            }
            case 1: {
                viewer_selected = !viewer_selected;
                break;
            }
            case 2: {
                debug_info_selected = !debug_info_selected;
                break;
            }
            case 3: {
                timer_selected = !timer_selected;
                break;
            }
            case 4: {
                load_timer_selected = !load_timer_selected;
                break;
            }
            case 5: {
                igt_timer_selected = !igt_timer_selected;
                break;
            }
        }
        lock_cursor_y = !lock_cursor_y;
        lock_cursor_x = !lock_cursor_x;
    }

    if (lock_cursor_x && lock_cursor_y) {
        switch (cursor.y) {
            case 0: {
                if (menu_selected) {
                    if (button_is_pressed(Controller::DPAD_RIGHT)) {
                        menu_x_offset++;
                    }
                    if (button_is_pressed(Controller::DPAD_LEFT)) {
                        menu_x_offset--;
                    }
                    if (button_is_pressed(Controller::DPAD_UP)) {
                        menu_y_offset--;
                    }
                    if (button_is_pressed(Controller::DPAD_DOWN)) {
                        menu_y_offset++;
                    }
                }
                break;
            }
            case 1: {
                if (viewer_selected) {
                    if (button_is_pressed(Controller::DPAD_RIGHT)) {
                        viewer_x_offset++;
                    }
                    if (button_is_pressed(Controller::DPAD_LEFT)) {
                        viewer_x_offset--;
                    }
                    if (button_is_pressed(Controller::DPAD_UP)) {
                        viewer_y_offset--;
                    }
                    if (button_is_pressed(Controller::DPAD_DOWN)) {
                        viewer_y_offset++;
                    }
                }
                break;
            }
            case 2: {
                if (debug_info_selected) {
                    if (button_is_pressed(Controller::DPAD_RIGHT)) {
                        debug_info_x_offset++;
                    }
                    if (button_is_pressed(Controller::DPAD_LEFT)) {
                        debug_info_x_offset--;
                    }
                    if (button_is_pressed(Controller::DPAD_UP)) {
                        debug_info_y_offset--;
                    }
                    if (button_is_pressed(Controller::DPAD_DOWN)) {
                        debug_info_y_offset++;
                    }
                }
                break;
            }
            case 3: {
                if (timer_selected) {
                    if (button_is_pressed(Controller::DPAD_RIGHT)) {
                        timer_x_offset++;
                    }
                    if (button_is_pressed(Controller::DPAD_LEFT)) {
                        timer_x_offset--;
                    }
                    if (button_is_pressed(Controller::DPAD_UP)) {
                        timer_y_offset--;
                    }
                    if (button_is_pressed(Controller::DPAD_DOWN)) {
                        timer_y_offset++;
                    }
                }
                break;
            }
            case 4: {
                if (load_timer_selected) {
                    if (button_is_pressed(Controller::DPAD_RIGHT)) {
                        load_timer_x_offset++;
                    }
                    if (button_is_pressed(Controller::DPAD_LEFT)) {
                        load_timer_x_offset--;
                    }
                    if (button_is_pressed(Controller::DPAD_UP)) {
                        load_timer_y_offset--;
                    }
                    if (button_is_pressed(Controller::DPAD_DOWN)) {
                        load_timer_y_offset++;
                    }
                }
                break;
            }
            case 5: {
                if (igt_timer_selected) {
                    if (button_is_pressed(Controller::DPAD_RIGHT)) {
                        igt_timer_x_offset++;
                    }
                    if (button_is_pressed(Controller::DPAD_LEFT)) {
                        igt_timer_x_offset--;
                    }
                    if (button_is_pressed(Controller::DPAD_UP)) {
                        igt_timer_y_offset--;
                    }
                    if (button_is_pressed(Controller::DPAD_DOWN)) {
                        igt_timer_y_offset++;
                    }
                }
                break;
            }
        }
    }

    /*char temp_bool[15];
	char temp_bool2[15];
	char temp_bool3[15];
    sprintf(temp_bool, "menu: %d", menu_selected);
    sprintf(temp_bool2, "cursor x: %d", lock_cursor_x);
    sprintf(temp_bool3, "cursor y: %d", lock_cursor_y);
	font.gz_renderChars(temp_bool, 60.0f, 380.0f, 0xFFFFFFFF, g_drop_shadows);
    font.gz_renderChars(temp_bool2, 60.0f, 360.0f, 0xFFFFFFFF, g_drop_shadows);
	font.gz_renderChars(temp_bool3, 60.0f, 340.0f, 0xFFFFFFFF, g_drop_shadows);*/

    Utilities::move_cursor(cursor, LINES, 1, lock_cursor_x, lock_cursor_y);
    Utilities::render_lines(font, lines, cursor.y, LINES);
};