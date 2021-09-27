#include "menus/amounts_menu.h"
#include "controller.h"
#include "font.h"
#include "libtp_c/include/msl_c/math.h"
#include "libtp_c/include/msl_c/string.h"
#include "utils/cursor.h"
#include "utils/lines.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"

#define LINES 8

static Cursor cursor = {0, 0};
bool init_once = false;

static uint8_t arrow_ammo;
static uint8_t bomb_bag_1_ammo = 0;
static uint8_t bomb_bag_2_ammo = 0;
static uint8_t bomb_bag_3_ammo = 0;
static uint8_t slingshot_ammo = 0;
static uint8_t poe_count = 0;
static uint16_t hp_count = 0;
static uint16_t rupee_count = 0;

Line lines[LINES] = {{"arrow ammo:", ARROW_AMMO_INDEX, "Amount of arrows held"},
                     {"bomb bag 1 ammo:", BOMB_BAG_1_AMMO_INDEX, "Amount of bombs in bag 1"},
                     {"bomb bag 2 ammo:", BOMB_BAG_2_AMMO_INDEX, "Amount of bombs in bag 2"},
                     {"bomb bag 3 ammo:", BOMB_BAG_3_AMMO_INDEX, "Amount of bombs in bag 3"},
                     {"slingshot ammo:", SLINGSHOT_AMMO_INDEX, "Amount of slingshot pellets held"},
                     {"heart pieces:", HEART_PIECE_COUNT_INDEX, "Amount of heart pieces collected"},
                     {"poes:", POE_COUNT_INDEX, "Amount of poes collected"},
                     {"rupees:", RUPEE_COUNT_INDEX, "Current rupee count"}};

void AmountsMenu::render() {
    // update amounts
    arrow_ammo = dComIfGs_getArrowNum();
    bomb_bag_1_ammo = dComIfGs_getBombNum(BOMB_BAG_1);
    bomb_bag_2_ammo = dComIfGs_getBombNum(BOMB_BAG_2);
    bomb_bag_3_ammo = dComIfGs_getBombNum(BOMB_BAG_3);
    slingshot_ammo = dComIfGs_getPachinkoNum();
    poe_count = dComIfGs_getPohSpiritNum();
    hp_count = dComIfGs_getMaxLife();
    rupee_count = dComIfGs_getRupee();

    if (button_is_pressed(BACK_BUTTON)) {
        init_once = false;
        MenuRendering::set_menu(MN_INVENTORY_INDEX);
        return;
    };

    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

    switch (cursor.y) {
    case ARROW_AMMO_INDEX: {
        if (button_is_pressed(Controller::DPAD_LEFT)) {
            arrow_ammo--;
        } else if (button_is_pressed(Controller::DPAD_RIGHT)) {
            arrow_ammo++;
        }
        dComIfGs_setArrowNum(arrow_ammo);
        break;
    }
    case BOMB_BAG_1_AMMO_INDEX: {
        if (button_is_pressed(Controller::DPAD_LEFT)) {
            bomb_bag_1_ammo--;
        } else if (button_is_pressed(Controller::DPAD_RIGHT)) {
            bomb_bag_1_ammo++;
        }
        dComIfGs_setBombNum(BOMB_BAG_1, bomb_bag_1_ammo);
        break;
    }
    case BOMB_BAG_2_AMMO_INDEX: {
        if (button_is_pressed(Controller::DPAD_LEFT)) {
            bomb_bag_2_ammo--;
        } else if (button_is_pressed(Controller::DPAD_RIGHT)) {
            bomb_bag_2_ammo++;
        }
        dComIfGs_setBombNum(BOMB_BAG_2, bomb_bag_2_ammo);
        break;
    }
    case BOMB_BAG_3_AMMO_INDEX: {
        if (button_is_pressed(Controller::DPAD_LEFT)) {
            bomb_bag_3_ammo--;
        } else if (button_is_pressed(Controller::DPAD_RIGHT)) {
            bomb_bag_3_ammo++;
        }
        dComIfGs_setBombNum(BOMB_BAG_3, bomb_bag_3_ammo);
        break;
    }
    case SLINGSHOT_AMMO_INDEX: {
        if (button_is_pressed(Controller::DPAD_LEFT)) {
            slingshot_ammo--;
        } else if (button_is_pressed(Controller::DPAD_RIGHT)) {
            slingshot_ammo++;
        }
        dComIfGs_setPachinkoNum(slingshot_ammo);
        break;
    }
    case HEART_PIECE_COUNT_INDEX: {
        if (button_is_pressed(Controller::DPAD_LEFT)) {
            hp_count--;
        } else if (button_is_pressed(Controller::DPAD_RIGHT)) {
            hp_count++;
        }
        dComIfGs_setMaxLife(hp_count);
        break;
    }
    case POE_COUNT_INDEX: {
        if (button_is_pressed(Controller::DPAD_LEFT)) {
            poe_count--;
        } else if (button_is_pressed(Controller::DPAD_RIGHT)) {
            poe_count++;
        }
        dComIfGs_setPohSpiritNum(poe_count);
        break;
    }
    case RUPEE_COUNT_INDEX: {
        if (button_is_pressed(Controller::DPAD_LEFT)) {
            rupee_count--;
        } else if (button_is_pressed(Controller::DPAD_RIGHT)) {
            rupee_count++;
        }
        dComIfGs_setRupee(rupee_count);
        break;
    }
    }

    tp_sprintf(lines[ARROW_AMMO_INDEX].value, " <%d>", arrow_ammo);
    tp_sprintf(lines[BOMB_BAG_1_AMMO_INDEX].value, " <%d>", bomb_bag_1_ammo);
    tp_sprintf(lines[BOMB_BAG_2_AMMO_INDEX].value, " <%d>", bomb_bag_2_ammo);
    tp_sprintf(lines[BOMB_BAG_3_AMMO_INDEX].value, " <%d>", bomb_bag_3_ammo);
    tp_sprintf(lines[SLINGSHOT_AMMO_INDEX].value, " <%d>", slingshot_ammo);
    tp_sprintf(lines[HEART_PIECE_COUNT_INDEX].value, " <%d>", hp_count);
    tp_sprintf(lines[POE_COUNT_INDEX].value, " <%d>", poe_count);
    tp_sprintf(lines[RUPEE_COUNT_INDEX].value, " <%d>", rupee_count);

    Utilities::move_cursor(cursor, LINES, 0, false, false, false, true);
    Utilities::render_lines(lines, cursor.y, LINES);
};
