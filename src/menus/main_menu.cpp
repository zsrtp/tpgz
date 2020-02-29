#include "libtp_c/include/tp.h"
#include "libtp_c/include/controller.h"
#include "tpgz/fifo_queue.h"
#include "menus/menu.h"
#include "tpgz/controller.h"
#include "tpgz/utils.h"
#include <stdio.h>
#include "tpgz/log.h"
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

void MainMenu::render(Font& font) {

    if (button_is_down(Controller::B) && !button_is_held(Controller::B)) {
        mm_visible = false;
        fifo_visible = true;
        return;
    };

    Utilities::move_cursor(cursor, LINES);
    
    if (button_is_down(Controller::A) && !button_is_held(Controller::A)) {
        switch (cursor) {
            case MEMORY_INDEX: {
                // go to memory menu
                return;
            }
            case INVENTORY_INDEX: {
                //transition(MenuState::InventoryMenu);
                return;
            }
            case CHEAT_INDEX: {
                mm_visible = false;
                cheats_visible = true;
                return;
            }
            case TOOLS_INDEX: {
                //transition(MenuState::Settings);
                mm_visible = false;
                tools_visible = true;
                return;
            }
            case SETTINGS_INDEX: {
                //transition(MenuState::Settings);
                mm_visible = false;
                settings_visible = true;
                return;
            }
            case WARPING_INDEX: {
                //transition(MenuState::Warp);
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