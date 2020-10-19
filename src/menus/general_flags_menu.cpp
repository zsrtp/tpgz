#include "libtp_c/include/flag.h"
#include "libtp_c/include/tp.h"
#include "font.h"
#include "menus/flags_menu.h"
#include "controller.h"
#include "utils/cursor.hpp"
#include "utils/lines.hpp"

#define LINES 11

static Cursor cursor = { 0, 0 };
bool init_once = false;

bool boss_flag;
bool rupee_flag;
bool midna_charge;
bool transform_warp;
bool midna_on_z;
bool epona_stolen;
bool epona_tamed;
bool map_warping;
bool midna_healthy;
bool midna_on_back;
bool wolf_sense;

Line lines[LINES] = {
	{"boss flag", BOSS_FLAG_INDEX, "Set the boss flag value. Press A to lock the value", true, &boss_flag},
	{"rupee cutscenes", RUPEE_CS_FLAG_INDEX, "Toggle flag for rupee cutscenes being enabled", true, &rupee_flag},
	{"epona stolen", EPONA_STOLEN_INDEX, "Toggle flag for Epona being stolen", true, &epona_stolen},
	{"epona tamed", EPONA_TAMED_INDEX, "Toggle flag for Epona being tamed", true, &epona_tamed},
	{"map warping", MAP_WARPING_INDEX, "Toggle flag for having map warping", true, &map_warping},
	{"midna charge", MIDNA_CHARGE_INDEX, "Toggle flag for Midna charge", true, &midna_charge},
	{"midna healthy", MIDNA_HEALTHY, "Toggle flag for Midna being healthy/sick", true, &midna_healthy},
	{"midna on back", MIDNA_ON_BACK, "Toggle flag for Midna appearing on Wolf Link's back", true, &midna_on_back},
	{"midna on z", MIDNA_Z_INDEX, "Toggle flag for being able to use Midna", true, &midna_on_z},
	{"transform/warp", TRANSFORM_WARP_INDEX, "Toggle flag for transforming/warping", true, &transform_warp},
	{"wolf sense", WOLF_SENSE_INDEX, "Toggle flag for having wolf sense", true, &wolf_sense} };

void GeneralFlagsMenu::render() {
    // update flags
    boss_flag = (TP::get_boss_flags() > 0x00);
    rupee_flag = tp_gameInfo.inventory.rupee_cs_flags;
    midna_charge = (tp_gameInfo.event_flags.flags[0x05] & (1 << 0));
    transform_warp = (tp_gameInfo.event_flags.flags[0x0D] & (1 << 2));
    midna_on_z = (tp_gameInfo.event_flags.flags[0x0C] & (1 << 4));
    epona_stolen = (tp_gameInfo.event_flags.flags[0x05] & (1 << 7));
    epona_tamed = (tp_gameInfo.event_flags.flags[0x06] & (1 << 0));
    map_warping = (tp_gameInfo.event_flags.flags[0x06] & (1 << 2));
    midna_healthy = (tp_gameInfo.event_flags.flags[0x1E] & (1 << 3));
    midna_on_back = (tp_gameInfo.midna_on_back_flag & (1 << 3));
    wolf_sense = (tp_gameInfo.event_flags.flags[0x43] & (1 << 3));

    if (button_is_pressed(Controller::B)) {
        init_once = false;
		MenuRendering::set_menu(MN_FLAGS_INDEX);
        return;
    }

    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

    if (current_input == 256 && a_held == false) {
        switch (cursor.y) {
            case BOSS_FLAG_INDEX: {
                if (boss_flag) {
                    tp_bossFlags = 0x00;
                } else {
                    tp_bossFlags = 0xFF;
                }
                break;
            }
            case RUPEE_CS_FLAG_INDEX: {
                if (rupee_flag) {
                    tp_gameInfo.inventory.rupee_cs_flags = 0x00;
                } else {
                    tp_gameInfo.inventory.rupee_cs_flags = 0xFF;
                }
                break;
            }
            case EPONA_STOLEN_INDEX: {
                tp_gameInfo.event_flags.flags[0x05] ^= 0x80;
                break;
            }
            case EPONA_TAMED_INDEX: {
                tp_gameInfo.event_flags.flags[0x06] ^= 0x01;
                break;
            }
            case MAP_WARPING_INDEX: {
                tp_gameInfo.event_flags.flags[0x06] ^= 0x04;
                break;
            }
            case MIDNA_HEALTHY: {
                tp_gameInfo.event_flags.flags[0x1E] ^= 0x08;
                break;
            }
            case MIDNA_ON_BACK: {
                tp_gameInfo.midna_on_back_flag ^= 0x08;
                break;
            }
            case MIDNA_Z_INDEX: {
                tp_gameInfo.event_flags.flags[0x0C] ^= 0x10;
                break;
            }
            case TRANSFORM_WARP_INDEX: {
                tp_gameInfo.event_flags.flags[0x0D] ^= 0x04;
                break;
            }
            case WOLF_SENSE_INDEX: {
                tp_gameInfo.event_flags.flags[0x43] ^= 0x08;
                break;
            }

            case MIDNA_CHARGE_INDEX: {
                tp_gameInfo.event_flags.flags[0x05] ^= 0x01;
                break;
            }
        }
    }

    Utilities::move_cursor(cursor, LINES);
    Utilities::render_lines(lines, cursor.y, LINES, 150.0f);
};
