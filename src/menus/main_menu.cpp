#include "libtp_c/include/tp.h"
#include "libtp_c/include/controller.h"
#include "fifo_queue.h"
#include "menu.h"
#include "controller.h"
#include "utils/cursor.hpp"
#include "utils/lines.hpp"
#include <stdio.h>
#include "log.h"
#define LINES 9

static Cursor cursor = {0, 0};
bool mm_visible;

Line lines[LINES] = {
    {"cheats", CHEAT_INDEX, "Turn cheats on/off", false},
    {"flags", FLAGS_INDEX, "Turn in-game flags on/off", false},
    {"inventory", INVENTORY_INDEX, "Set Link's items and equipment", false},
    {"memory", MEMORY_INDEX, "View/edit memory and add watches", false},
    {"practice", PRACTICE_INDEX, "Load practice files", false},
    {"scene", SCENE_INDEX, "Adjust the scene's state", false},
    {"settings", SETTINGS_INDEX, "Configure settings", false},
    {"tools", TOOLS_INDEX, "Use various tools for practice and testing", false},
    {"warping", WARPING_INDEX, "Warp to dungeons, towns, grottos, etc.", false}};

void MainMenu::render(Font& font) {
    if (button_is_pressed(Controller::B)) {
        mm_visible = false;
        fifo_visible = true;
        return;
    };

    Utilities::move_cursor(cursor, LINES);

    if (current_input == 256 && !a_held) {
        switch (cursor.y) {
            case MEMORY_INDEX: {
                mm_visible = false;
                memory_visible = true;
                return;
            }
            case INVENTORY_INDEX: {
                mm_visible = false;
                inventory_visible = true;
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
                mm_visible = false;
                warping_visible = true;
                return;
            }
            case PRACTICE_INDEX: {
                mm_visible = false;
                prac_visible = true;
                return;
            }
            case SCENE_INDEX: {
                mm_visible = false;
                scene_menu_visible = true;
                return;
            }
            case FLAGS_INDEX: {
                mm_visible = false;
                flags_menu_visible = true;
            }
        }
    }

    Utilities::render_lines(font, lines, cursor.y, LINES);
};
