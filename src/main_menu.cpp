#include "libtp_c/include/tp.h"
#include "libtp_c/include/controller.h"
#include "menu.h"
#include "controller.h"
#include "utils.h"
#include <stdio.h>
#include "log.h"
#define LINES 8

static int cursor = 2;

Line lines[LINES] = {
    {"main menu", 0},
    {"", 1},
    {"inventory", 2, "set link's items and equipment"},
    {"cheats", 3, "turn cheats on/off"},
    {"warping", 4, "warp to dungeons, towns, grottos, etc."},
    {"memory", 5, "add memory watches to the screen"},
    {"practice", 6, "practice tools for various categories"},
    {"settings", 7, "configure settings"}};

void transition_into(){};

void MainMenu::render(Font& font) {

    if (button_is_down(Controller::B) && !button_is_held(Controller::B)) {
        mm_visible = false;
        return;
    };

    move_cursor(cursor, LINES);

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

    if (mm_visible == true) {
        render_lines(font, LINES);
    };
};