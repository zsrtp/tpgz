#include "font.h"
#include "menus/flags_menu.h"
#include "controller.h"
#include "utils/cursor.hpp"
#include "utils/lines.hpp"
#include "libtp_c/include/flag.h"
#include "libtp_c/include/tp.h"

#define LINES 15

static Cursor cursor = {0, 0};
bool init_once = false;

bool spring_warp;
bool south_faron_warp;
bool north_faron_warp;
bool grove_warp;
bool gorge_warp;
bool kakariko_warp;
bool mountain_warp;
bool bridge_warp;
bool castle_town_warp;
bool lake_hylia_warp;
bool domain_warp;
bool uzr_warp;
bool snowpeak_warp;
bool mesa_warp;
bool mirror_warp;

Line lines[LINES] = {
    {"ordon spring", SPRING_WARP_INDEX, "Ordon Spring warp portal", true, &spring_warp},
    {"south faron", S_FARON_WARP_INDEX, "South Faron warp portal", true, &south_faron_warp},
    {"north faron", N_FARON_WARP_INDEX, "North Faron warp portal", true, &north_faron_warp},
    {"sacred grove", GROVE_WARP_INDEX, "Sacred Grove warp portal", true, &grove_warp},
    {"eldin gorge", GORGE_WARP_INDEX, "Eldin Gorge warp portal", true, &gorge_warp},
    {"kak village", KAKARIKO_WARP_INDEX, "Kakariko Village warp portal", true, &kakariko_warp},
    {"death mountain", MOUNTAIN_WARP_INDEX, "Death Mountain warp portal", true, &mountain_warp},
    {"eldin bridge", BRIDGE_WARP_INDEX, "Bridge of Eldin warp portal", true, &bridge_warp},
    {"castle town", TOWN_WARP_INDEX, "Castle Town warp portal", true, &castle_town_warp},
    {"lake hylia", LAKE_WARP_INDEX, "Lake Hylia warp portal", true, &lake_hylia_warp},
    {"zora's domain", DOMAIN_WARP_INDEX, "Zora's Domain warp portal", true, &domain_warp},
    {"upper river", UZR_WARP_INDEX, "Upper Zora's River warp portal", true, &uzr_warp},
    {"snowpeak", SNOWPEAK_WARP_INDEX, "Snowpeak warp portal", true, &snowpeak_warp},
    {"gerudo mesa", MESA_WARP_INDEX, "Gerudo Mesa warp portal", true, &mesa_warp},
    {"mirror chamber", MIRROR_WARP_INDEX, "Mirror Chamber warp portal", true, &mirror_warp},
};

void PortalFlagsMenu::render(Font& font) {
    // update flags
    spring_warp = (tp_gameInfo.overworld_flags.ordon_flags.flags[13] & (1 << 4));
    south_faron_warp = (tp_gameInfo.overworld_flags.faron_flags.flags[19] & (1 << 7));
    north_faron_warp = (tp_gameInfo.overworld_flags.faron_flags.flags[11] & (1 << 2));
    grove_warp = (tp_gameInfo.overworld_flags.grove_flags.flags[23] & (1 << 4));
    gorge_warp = (tp_gameInfo.overworld_flags.hyrule_field_flags.flags[9] & (1 << 5));
    kakariko_warp = (tp_gameInfo.overworld_flags.eldin_flags.flags[8] & (1 << 7));
    mountain_warp = (tp_gameInfo.overworld_flags.eldin_flags.flags[9] & (1 << 5));
    bridge_warp = (tp_gameInfo.overworld_flags.hyrule_field_flags.flags[23] & (1 << 3));
    castle_town_warp = (tp_gameInfo.overworld_flags.hyrule_field_flags.flags[11] & (1 << 3));
    lake_hylia_warp = (tp_gameInfo.overworld_flags.lanayru_flags.flags[10] & (1 << 2));
    domain_warp = (tp_gameInfo.overworld_flags.lanayru_flags.flags[11] & (1 << 2));
    uzr_warp = (tp_gameInfo.overworld_flags.lanayru_flags.flags[9] & (1 << 5));
    snowpeak_warp = (tp_gameInfo.overworld_flags.snowpeak_flags.flags[9] & (1 << 5));
    mesa_warp = (tp_gameInfo.overworld_flags.desert_flags.flags[9] & (1 << 5));
    mirror_warp = (tp_gameInfo.overworld_flags.desert_flags.flags[14] & (1 << 0));

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
            case SPRING_WARP_INDEX: {
                tp_gameInfo.overworld_flags.ordon_flags.flags[13] ^= 1 << 4;
                break;
            }
            case S_FARON_WARP_INDEX: {
                tp_gameInfo.overworld_flags.faron_flags.flags[19] ^= 1 << 7;
                break;
            }
            case N_FARON_WARP_INDEX: {
                tp_gameInfo.overworld_flags.faron_flags.flags[11] ^= 1 << 2;
                break;
            }
            case GROVE_WARP_INDEX: {
                tp_gameInfo.overworld_flags.grove_flags.flags[23] ^= 1 << 4;
                break;
            }
            case GORGE_WARP_INDEX: {
                tp_gameInfo.overworld_flags.hyrule_field_flags.flags[9] ^= 1 << 5;
                break;
            }
            case KAKARIKO_WARP_INDEX: {
                tp_gameInfo.overworld_flags.eldin_flags.flags[8] ^= 1 << 7;
                break;
            }
            case MOUNTAIN_WARP_INDEX: {
                tp_gameInfo.overworld_flags.eldin_flags.flags[9] ^= 1 << 5;
                break;
            }
            case BRIDGE_WARP_INDEX: {
                tp_gameInfo.overworld_flags.hyrule_field_flags.flags[23] ^= 1 << 3;
                break;
            }
            case TOWN_WARP_INDEX: {
                tp_gameInfo.overworld_flags.hyrule_field_flags.flags[11] ^= 1 << 3;
                break;
            }
            case LAKE_WARP_INDEX: {
                tp_gameInfo.overworld_flags.lanayru_flags.flags[10] ^= 1 << 2;
                break;
            }
            case DOMAIN_WARP_INDEX: {
                tp_gameInfo.overworld_flags.lanayru_flags.flags[11] ^= 1 << 2;
                break;
            }
            case UZR_WARP_INDEX: {
                tp_gameInfo.overworld_flags.lanayru_flags.flags[9] ^= 1 << 5;
                break;
            }
            case SNOWPEAK_WARP_INDEX: {
                tp_gameInfo.overworld_flags.snowpeak_flags.flags[9] ^= 1 << 5;
                break;
            }
            case MESA_WARP_INDEX: {
                tp_gameInfo.overworld_flags.desert_flags.flags[9] ^= 1 << 5;
                break;
            }
            case MIRROR_WARP_INDEX: {
                tp_gameInfo.overworld_flags.desert_flags.flags[14] ^= 1 << 0;
                break;
            }
        }
    }

    Utilities::move_cursor(cursor, LINES);
    Utilities::render_lines(font, lines, cursor.y, LINES, 150.0f);
};
