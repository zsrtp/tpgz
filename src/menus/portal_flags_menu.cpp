#include "controller.h"
#include "font.h"
#include "menus/flags_menu.h"
#include "utils/cursor.h"
#include "utils/lines.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"

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

bool getSaveSwitch(int32_t stage, int32_t flag) {
    return dSv_memBit_c__isSwitch(&dComIfGs_getSavedata().mSave[stage].mBit, flag);
}

void setSaveSwitch(int32_t stage, int32_t flag) {
    if (getSaveSwitch(stage, flag)) {
        dSv_memBit_c__offSwitch(&dComIfGs_getSavedata().mSave[stage].mBit, flag);
    } else {
        dSv_memBit_c__onSwitch(&dComIfGs_getSavedata().mSave[stage].mBit, flag);
    }
}

void PortalFlagsMenu::render() {
    spring_warp = getSaveSwitch(dSv_memory_c::ORDON, 52);
    south_faron_warp = getSaveSwitch(dSv_memory_c::FARON, 71);
    north_faron_warp = getSaveSwitch(dSv_memory_c::FARON, 2);
    grove_warp = getSaveSwitch(dSv_memory_c::GROVE, 100);
    gorge_warp = getSaveSwitch(dSv_memory_c::FIELD, 21);
    kakariko_warp = getSaveSwitch(dSv_memory_c::ELDIN, 31);
    mountain_warp = getSaveSwitch(dSv_memory_c::ELDIN, 21);
    bridge_warp = getSaveSwitch(dSv_memory_c::FIELD, 99);
    castle_town_warp = getSaveSwitch(dSv_memory_c::FIELD, 3);
    lake_hylia_warp = getSaveSwitch(dSv_memory_c::LANAYRU, 10);
    domain_warp = getSaveSwitch(dSv_memory_c::LANAYRU, 2);
    uzr_warp = getSaveSwitch(dSv_memory_c::LANAYRU, 21);
    snowpeak_warp = getSaveSwitch(dSv_memory_c::SNOWPEAK, 21);
    mesa_warp = getSaveSwitch(dSv_memory_c::DESERT, 21);
    mirror_warp = getSaveSwitch(dSv_memory_c::DESERT, 40);

    if (button_is_pressed(BACK_BUTTON)) {
        init_once = false;
        MenuRendering::set_menu(MN_FLAGS_INDEX);
        return;
    }

    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

    if (current_input == SELECTION_BUTTON && a_held == false) {
        switch (cursor.y) {
        case SPRING_WARP_INDEX: {
            setSaveSwitch(dSv_memory_c::ORDON, 52);
            break;
        }
        case S_FARON_WARP_INDEX: {
            setSaveSwitch(dSv_memory_c::FARON, 71);
            break;
        }
        case N_FARON_WARP_INDEX: {
            setSaveSwitch(dSv_memory_c::FARON, 2);
            break;
        }
        case GROVE_WARP_INDEX: {
            setSaveSwitch(dSv_memory_c::GROVE, 100);
            break;
        }
        case GORGE_WARP_INDEX: {
            setSaveSwitch(dSv_memory_c::FIELD, 21);
            break;
        }
        case KAKARIKO_WARP_INDEX: {
            setSaveSwitch(dSv_memory_c::ELDIN, 31);
            break;
        }
        case MOUNTAIN_WARP_INDEX: {
            setSaveSwitch(dSv_memory_c::ELDIN, 21);
            break;
        }
        case BRIDGE_WARP_INDEX: {
            setSaveSwitch(dSv_memory_c::FIELD, 99);
            break;
        }
        case TOWN_WARP_INDEX: {
            setSaveSwitch(dSv_memory_c::FIELD, 3);
            break;
        }
        case LAKE_WARP_INDEX: {
            setSaveSwitch(dSv_memory_c::LANAYRU, 10);
            break;
        }
        case DOMAIN_WARP_INDEX: {
            setSaveSwitch(dSv_memory_c::LANAYRU, 2);
            break;
        }
        case UZR_WARP_INDEX: {
            setSaveSwitch(dSv_memory_c::LANAYRU, 21);
            break;
        }
        case SNOWPEAK_WARP_INDEX: {
            setSaveSwitch(dSv_memory_c::SNOWPEAK, 21);
            break;
        }
        case MESA_WARP_INDEX: {
            setSaveSwitch(dSv_memory_c::DESERT, 21);
            break;
        }
        case MIRROR_WARP_INDEX: {
            setSaveSwitch(dSv_memory_c::DESERT, 40);
            break;
        }
        }
        // copy stage save flags to temp flags
        dComIfGs_getSave(g_dComIfG_gameInfo.info.mDan.mStageNo);
    }

    Utilities::move_cursor(cursor, LINES);
    Utilities::render_lines(lines, cursor.y, LINES);
};
