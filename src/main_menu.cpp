#include "libtp_c/include/tp.h"
#include "libtp_c/include/controller.h"
#include "menu.h"
#include "controller.h"
#include "utils.h"
#define LINES 6

static int cursor = 0;
static bool ddown_held_last_frame;
static bool dup_held_last_frame;

void transition_into(){};

void MainMenu::render(Font& font) {
    Line lines[LINES] = {
        {"inventory", 0},
        {"cheats", 1},
        {"warping", 2},
        {"memory", 3},
        {"practice", 4},
        {"settings", 5},
    };
    // const int INVENTORY_INDEX = 0;
    // const int CHEAT_INDEX = 1;
    // const int WARPING_INDEX = 2;
    // const int MEMORY_INDEX = 3;
    // const int SETTINGS_INDEX = 4;

    //let state = get_state();
    //Inventory::Inventory inventory = *Inventory::get_inventory();
    //uint8_t boss_flags = TP::get_boss_flags();

    if (button_is_down(Controller::B)) {
        visible = false;
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

    // if (button_is_down(Controller::A)) {
    //     switch (cursor) {
    //         case MEMORY_INDEX: {
    //             // go to memory menu
    //             return;
    //         }
    //         case INVENTORY_INDEX: {
    //             //transition(MenuState::InventoryMenu);
    //             return;
    //         }
    //         case CHEAT_INDEX: {
    //             //transition(MenuState::CheatMenu);
    //             return;
    //         }
    //         case SETTINGS_INDEX: {
    //             //transition(MenuState::Settings);
    //             return;
    //         }
    //         case WARPING_INDEX: {
    //             //transition(MenuState::Warp);
    //             return;
    //         }
    //     }
    // }
    if (visible) {
        for (int i = 0; i < LINES; i++) {
            float offset = (120.0f + (float)i * 20.0f);
            int color = 0xFFFFFF00;
            int alpha = 0xFF;
            if (lines[i].idx != cursor) {
                alpha = 0x80;
            }
            color |= alpha;
            font.renderChars(lines[i].line, 120.f, offset, color);
        };
    };
};