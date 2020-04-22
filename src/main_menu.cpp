#include "libtp_c/include/tp.h"
#include "libtp_c/include/controller.h"
#include "fifo_queue.h"
#include "menu.h"
#include "controller.h"
#include "utils.h"
#include <stdio.h>
#include "log.h"
#define LINES 7

static Cursor cursor = {0,0};
bool mm_visible;

Line lines[LINES] = {
    {"inventory", 0, "set link's items and equipment", false},
    {"cheats", 1, "turn cheats on/off", false},
    {"warping", 2, "warp to dungeons, towns, grottos, etc.", false},
    {"memory", 3, "add memory watches to the screen", false},
    {"practice", 4, "practice tools for various categories", false},
    {"tools", 5, "various tools for practice and testing", false},
    {"settings", 6, "configure settings", false}};

void transition_into() { }

void MainMenu::render(Font& font) {

    if (button_is_pressed(Controller::B)) {
        mm_visible = false;
        fifo_visible = true;
        return;
    };

    Utilities::move_cursor(cursor, LINES);
    
    if (current_input == 256 && a_held == false) {
        switch (cursor.x) {
            case MEMORY_INDEX: {
                memory_visible = true;
                mm_visible = false;
                return;
            }
            case INVENTORY_INDEX: {
                inventory_visible = true;
                mm_visible = false;
                return;
            }
            case CHEAT_INDEX: {
                mm_visible = false;
                cheats_visible = true;
                return;
            }
            case TOOLS_INDEX: {
                mm_visible = false;
                tools_visible = true;
                return;
            }
            case SETTINGS_INDEX: {
                mm_visible = false;
                settings_visible = true;
                return;
            }
            case WARPING_INDEX: {
                warping_visible = true;
                mm_visible = false;
                return;
            }
            case PRACTICE_INDEX: {
                mm_visible = false;
                prac_visible = true;
                return;
            }
        }
    }
    Utilities::render_lines(font, lines, cursor.x, LINES);
};