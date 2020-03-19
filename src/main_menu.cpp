#include "libtp_c/include/tp.h"
#include "libtp_c/include/controller.h"
#include "fifo_queue.h"
#include "menu.h"
#include "controller.h"
#include "utils.h"
#include <stdio.h>
#include "log.h"
#define LINES 9

static int cursor = 2;

Line lines[LINES] = {
    {"main menu", 0, "", false},
    {"", 1, "", false},
    {"inventory", 2, "set link's items and equipment", false},
    {"cheats", 3, "turn cheats on/off", false},
    {"warping", 4, "warp to dungeons, towns, grottos, etc.", false},
    {"memory", 5, "add memory watches to the screen", false},
    {"practice", 6, "practice tools for various categories", false},
    {"tools", 7, "various tools for practice and testing", false},
    {"settings", 8, "configure settings", false}};

void transition_into() { }

void MainMenu::render(Font& font) {

    if (button_is_pressed(Controller::B)) {
        mm_visible = false;
        fifo_visible = true;
        return;
    };

    Utilities::move_cursor(cursor, LINES);
    
    if (button_is_pressed(Controller::A)) {
        switch (cursor) {
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
    Utilities::render_lines(font, lines, cursor, LINES);
};