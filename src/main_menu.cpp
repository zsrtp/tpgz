#include "libtp_c/include/tp.h"
#include "libtp_c/include/controller.h"
#include "controller.h"
#include "utils.h"

static int cursor = 0;

void transition_into() {};

void render() {
    const int INVENTORY_INDEX = 0;
    const int CHEAT_INDEX = 1;
    const int WARPING_INDEX = 2;
    const int MEMORY_INDEX = 3;
    const int SETTINGS_INDEX = 4;

    //let state = get_state();
    Inventory::Inventory inventory = *Inventory::get_inventory();
    uint8_t boss_flags = TP::get_boss_flags();

    if (button_is_down(Controller::B)) {
        //visible = false
        return;
    };

    char contents[5][20] = {
        "Inventory",
        "Cheats",
        "Warping",
        "Memory",
        "Settings",
    };
    move_cursor(sizeof(contents) / sizeof(*contents), cursor);

    if (button_is_down(Controller::A)) {
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
                //transition(MenuState::CheatMenu);
                return;
            }
            case SETTINGS_INDEX: {
                //transition(MenuState::Settings);
                return;
            }
            case WARPING_INDEX: {
                //transition(MenuState::Warp);
                return;
            }
        }
    }
}