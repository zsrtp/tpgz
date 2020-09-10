#include "libtp_c/include/tp.h"
#include "libtp_c/include/inventory.h"
#include "libtp_c/include/flag.h"
#include "font.h"
#include "menu.h"
#include "controller.h"
#include "utils/cursor.hpp"
#include "utils/lines.hpp"
#include <stdio.h>

#define LINES 8

static Cursor cursor = { 0, 0 };
bool init_once = false;
bool amounts_visible;

static uint8_t arrow_ammo;
static uint8_t bomb_bag_1_ammo = 0;
static uint8_t bomb_bag_2_ammo = 0;
static uint8_t bomb_bag_3_ammo = 0;
static uint8_t slingshot_ammo = 0;
static uint8_t poe_count = 0;
static uint16_t hp_count = 0;
static uint16_t rupee_count = 0;

Line lines[LINES] = {
    {"arrow ammo:", ARROW_AMMO_INDEX, "Amount of arrows held"},
    {"bomb bag 1 ammo:", BOMB_BAG_1_AMMO_INDEX, "Amount of bombs in bag 1"},
    {"bomb bag 2 ammo:", BOMB_BAG_2_AMMO_INDEX, "Amount of bombs in bag 2"},
    {"bomb bag 3 ammo:", BOMB_BAG_3_AMMO_INDEX, "Amount of bombs in bag 3"},
    {"slingshot ammo:", SLINGSHOT_AMMO_INDEX, "Amount of slingshot pellets held"},
    {"heart pieces:", HEART_PIECE_COUNT_INDEX, "Amount of heart pieces collected"},
    {"poes:", POE_COUNT_INDEX, "Amount of poes collected"},
    {"rupees:", RUPEE_COUNT_INDEX, "Current rupee count"}};

void AmountsMenu::render(Font & font) {
	// update amounts
	arrow_ammo = tp_gameInfo.inventory.arrow_count;
	bomb_bag_1_ammo = tp_gameInfo.inventory.bomb_bag_1_amnt;
	bomb_bag_2_ammo = tp_gameInfo.inventory.bomb_bag_2_amnt;
	bomb_bag_3_ammo = tp_gameInfo.inventory.bomb_bag_3_amnt;
	slingshot_ammo = tp_gameInfo.inventory.slingshot_count;
	poe_count = tp_gameInfo.inventory.poe_count;
	hp_count = tp_gameInfo.link.heart_pieces;
	rupee_count = tp_gameInfo.link.rupees;

	if (button_is_pressed(Controller::B)) {
		init_once = false;
		amounts_visible = false;
		inventory_visible = true;
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
            tp_gameInfo.inventory.arrow_count = arrow_ammo;
            break;
        }
        case BOMB_BAG_1_AMMO_INDEX: {
            if (button_is_pressed(Controller::DPAD_LEFT)) {
                bomb_bag_1_ammo--;
            } else if (button_is_pressed(Controller::DPAD_RIGHT)) {
                bomb_bag_1_ammo++;
            }
            tp_gameInfo.inventory.bomb_bag_1_amnt = bomb_bag_1_ammo;
            break;
        }
        case BOMB_BAG_2_AMMO_INDEX: {
            if (button_is_pressed(Controller::DPAD_LEFT)) {
                bomb_bag_2_ammo--;
            } else if (button_is_pressed(Controller::DPAD_RIGHT)) {
                bomb_bag_2_ammo++;
            }
            tp_gameInfo.inventory.bomb_bag_2_amnt = bomb_bag_2_ammo;
            break;
        }
        case BOMB_BAG_3_AMMO_INDEX: {
            if (button_is_pressed(Controller::DPAD_LEFT)) {
                bomb_bag_3_ammo--;
            } else if (button_is_pressed(Controller::DPAD_RIGHT)) {
                bomb_bag_3_ammo++;
            }
            tp_gameInfo.inventory.bomb_bag_3_amnt = bomb_bag_3_ammo;
            break;
        }
        case SLINGSHOT_AMMO_INDEX: {
            if (button_is_pressed(Controller::DPAD_LEFT)) {
                slingshot_ammo--;
            } else if (button_is_pressed(Controller::DPAD_RIGHT)) {
                slingshot_ammo++;
            }
            tp_gameInfo.inventory.slingshot_count = slingshot_ammo;
            break;
        }
        case HEART_PIECE_COUNT_INDEX: {
            if (button_is_pressed(Controller::DPAD_LEFT)) {
                hp_count--;
            } else if (button_is_pressed(Controller::DPAD_RIGHT)) {
                hp_count++;
            }
            tp_gameInfo.link.heart_pieces = hp_count;
            break;
            }
        case POE_COUNT_INDEX: {
            if (button_is_pressed(Controller::DPAD_LEFT)) {
                poe_count--;
            } else if (button_is_pressed(Controller::DPAD_RIGHT)) {
                poe_count++;
            }
            tp_gameInfo.inventory.poe_count = poe_count;
            break;
        }
        case RUPEE_COUNT_INDEX: {
            if (button_is_pressed(Controller::DPAD_LEFT)) {
                rupee_count--;
            } else if (button_is_pressed(Controller::DPAD_RIGHT)) {
                rupee_count++;
            }
            tp_gameInfo.link.rupees = rupee_count;
            break;
        }
    }

	sprintf(lines[ARROW_AMMO_INDEX].line, "arrow ammo: <%d>", arrow_ammo);
	sprintf(lines[BOMB_BAG_1_AMMO_INDEX].line, "bomb bag 1 ammo: <%d>", bomb_bag_1_ammo);
	sprintf(lines[BOMB_BAG_2_AMMO_INDEX].line, "bomb bag 2 ammo: <%d>", bomb_bag_2_ammo);
	sprintf(lines[BOMB_BAG_3_AMMO_INDEX].line, "bomb bag 3 ammo: <%d>", bomb_bag_3_ammo);
	sprintf(lines[SLINGSHOT_AMMO_INDEX].line, "slingshot ammo: <%d>", slingshot_ammo);
	sprintf(lines[HEART_PIECE_COUNT_INDEX].line, "heart pieces: <%d>", hp_count);
	sprintf(lines[POE_COUNT_INDEX].line, "poes: <%d>", poe_count);
	sprintf(lines[RUPEE_COUNT_INDEX].line, "rupees: <%d>", rupee_count);

	Utilities::move_cursor(cursor, LINES);
	Utilities::render_lines(font, lines, cursor.y, LINES);
};
