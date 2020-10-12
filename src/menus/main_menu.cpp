#include "libtp_c/include/tp.h"
#include "libtp_c/include/controller.h"
#include "fifo_queue.h"
#include "menus/main_menu.h"
#include "controller.h"
#include "utils/cursor.hpp"
#include "utils/lines.hpp"
#include <stdio.h>

#define LINES 9

static Cursor cursor = {0, 0};

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
        MenuRendering::set_menu(MN_NONE_INDEX);
        fifo_visible = true;
        return;
    };

    Utilities::move_cursor(cursor, LINES);

    if (current_input == Controller::Pad::A && !a_held) {
        switch (cursor.y) {
            case MEMORY_INDEX: {
                MenuRendering::set_menu(MN_MEMORY_INDEX);
                return;
            }
            case INVENTORY_INDEX: {
                MenuRendering::set_menu(MN_INVENTORY_INDEX);
                return;
            }
            case CHEAT_INDEX: {
                MenuRendering::set_menu(MN_CHEAT_INDEX);
                return;
            }
            case TOOLS_INDEX: {
                MenuRendering::set_menu(MN_TOOLS_INDEX);
                return;
            }
            case SETTINGS_INDEX: {
                MenuRendering::set_menu(MN_SETTINGS_INDEX);
                return;
            }
            case WARPING_INDEX: {
                MenuRendering::set_menu(MN_WARPING_INDEX);
                return;
            }
            case PRACTICE_INDEX: {
                MenuRendering::set_menu(MN_PRACTICE_INDEX);
                return;
            }
            case SCENE_INDEX: {
                MenuRendering::set_menu(MN_SCENE_INDEX);
                return;
            }
            case FLAGS_INDEX: {
                MenuRendering::set_menu(MN_FLAGS_INDEX);
                return;
            }
        }
    }

    Utilities::render_lines(font, lines, cursor.y, LINES);
};
