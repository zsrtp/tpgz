#include "controller.h"
#include "font.h"
#include "menus/flags_menu.h"
#include "utils/cursor.h"
#include "utils/lines.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/utils.h"

#define LINES 11

static Cursor cursor = {0, 0};
bool init_once = false;

bool boss_flag;
bool rupee_flag = false;
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
    {"boss flag", BOSS_FLAG_INDEX, "Set the boss flag value. Press A to lock the value", true,
     &boss_flag},
    {"rupee cutscenes", RUPEE_CS_FLAG_INDEX, "Toggle flag for rupee cutscenes being enabled", true,
     &rupee_flag},
    {"epona stolen", EPONA_STOLEN_INDEX, "Toggle flag for Epona being stolen", true, &epona_stolen},
    {"epona tamed", EPONA_TAMED_INDEX, "Toggle flag for Epona being tamed", true, &epona_tamed},
    {"map warping", MAP_WARPING_INDEX, "Toggle flag for having map warping", true, &map_warping},
    {"midna charge", MIDNA_CHARGE_INDEX, "Toggle flag for Midna charge", true, &midna_charge},
    {"midna healthy", MIDNA_HEALTHY, "Toggle flag for Midna being healthy/sick", true,
     &midna_healthy},
    {"midna on back", MIDNA_ON_BACK, "Toggle flag for Midna appearing on Wolf Link's back", true,
     &midna_on_back},
    {"midna on z", MIDNA_Z_INDEX, "Toggle flag for being able to use Midna", true, &midna_on_z},
    {"transform/warp", TRANSFORM_WARP_INDEX, "Toggle flag for transforming/warping", true,
     &transform_warp},
    {"wolf sense", WOLF_SENSE_INDEX, "Toggle flag for having wolf sense", true, &wolf_sense}};

void GeneralFlagsMenu::render() {
    // update flags
    boss_flag = tp_bossFlags > 0;
    midna_charge = dComIfGs_isEventBit(0x0501);
    transform_warp = dComIfGs_isEventBit(0x0D04);
    midna_on_z = dComIfGs_isEventBit(0x0C10);
    epona_stolen = dComIfGs_isEventBit(0x0580);
    epona_tamed = dComIfGs_isEventBit(0x0601);
    map_warping = dComIfGs_isEventBit(0x0604);
    midna_healthy = dComIfGs_isEventBit(0x1E08);
    midna_on_back = dComIfGs_isTransformLV(3);
    wolf_sense = dComIfGs_isEventBit(0x4308);

    for (int i = BLUE_RUPEE; i <= SILVER_RUPEE; i++) {
        if (dComIfGs_isItemFirstBit(i)) {
            rupee_flag = true;
            break;
        }
    }

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
        case BOSS_FLAG_INDEX: {
            if (boss_flag) {
                tp_bossFlags = 0;
            } else {
                tp_bossFlags = 255;
            }
            break;
        }
        case RUPEE_CS_FLAG_INDEX: {
            if (rupee_flag) {
                for (int i = BLUE_RUPEE; i <= SILVER_RUPEE; i++) {
                    dComIfGs_offItemFirstBit(i);
                }
            } else {
                for (int i = BLUE_RUPEE; i <= SILVER_RUPEE; i++) {
                    dComIfGs_onItemFirstBit(i);
                }
            }
            break;
        }
        case EPONA_STOLEN_INDEX: {
            setEventFlag(0x0580);
            break;
        }
        case EPONA_TAMED_INDEX: {
            setEventFlag(0x0601);
            break;
        }
        case MAP_WARPING_INDEX: {
            setEventFlag(0x0604);
            break;
        }
        case MIDNA_HEALTHY: {
            setEventFlag(0x1E08);
            break;
        }
        case MIDNA_ON_BACK: {
            if (dComIfGs_isTransformLV(3)) {
                dComIfGs_offTransformLV(3);
            } else {
                dComIfGs_onTransformLV(3);
            }
            break;
        }
        case MIDNA_Z_INDEX: {
            setEventFlag(0x0C10);
            break;
        }
        case TRANSFORM_WARP_INDEX: {
            setEventFlag(0x0D04);
            break;
        }
        case WOLF_SENSE_INDEX: {
            setEventFlag(0x4308);
            break;
        }
        case MIDNA_CHARGE_INDEX: {
            setEventFlag(0x0501);
            break;
        }
        }
    }

    Utilities::move_cursor(cursor, LINES);
    Utilities::render_lines(lines, cursor.y, LINES);
};
