#include "gz_flags.h"
#include "menus/flags_menu.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/utils.h"

#define LINE_NUM 11

Cursor GeneralFlagsMenu::cursor;

bool l_bossFlag;
bool l_rupeeFlag = false;
bool l_midnaCharge;
bool l_transformWarp;
bool l_midnaZ;
bool l_eponaStolen;
bool l_eponaTamed;
bool l_mapWarping;
bool l_midnaHealed;
bool l_midnaRide;
bool l_wolfSense;

Line lines[LINE_NUM] = {
    {"boss flag", BOSS_FLAG_INDEX, "Sets the boss flag value", true, &l_bossFlag},
    {"rupee cutscenes", RUPEE_CS_FLAG_INDEX, "Toggle rupee cutscenes being enabled", true,
     &l_rupeeFlag},
    {"epona stolen", EPONA_STOLEN_INDEX, "Toggle flag for Epona being stolen", true,
     &l_eponaStolen},
    {"epona tamed", EPONA_TAMED_INDEX, "Toggle flag for Epona being tamed", true, &l_eponaTamed},
    {"map warping", MAP_WARPING_INDEX, "Toggle flag for map warping", true, &l_mapWarping},
    {"midna charge", MIDNA_CHARGE_INDEX, "Toggle flag for Midna charge", true, &l_midnaCharge},
    {"midna healed", MIDNA_HEALTHY, "Toggle flag for Midna being healed", true, &l_midnaHealed},
    {"midna on back", MIDNA_ON_BACK, "Toggle flag for Midna appearing on Wolf Link's back", true,
     &l_midnaRide},
    {"midna on Z", MIDNA_Z_INDEX, "Toggle flag for being able to call Midna", true, &l_midnaZ},
    {"transform/warp", TRANSFORM_WARP_INDEX, "Toggle flag for transforming/warping", true,
     &l_transformWarp},
    {"wolf sense", WOLF_SENSE_INDEX, "Toggle flag for wolf sense", true, &l_wolfSense},
};

void GeneralFlagsMenu::draw() {
    // update flags
    l_bossFlag = tp_bossFlags > 0;
    l_midnaCharge = dComIfGs_isEventBit(0x0501);
    l_transformWarp = dComIfGs_isEventBit(0x0D04);
    l_midnaZ = dComIfGs_isEventBit(0x0C10);
    l_eponaStolen = dComIfGs_isEventBit(0x0580);
    l_eponaTamed = dComIfGs_isEventBit(0x0601);
    l_mapWarping = dComIfGs_isEventBit(0x0604);
    l_midnaHealed = dComIfGs_isEventBit(0x1E08);
    l_midnaRide = dComIfGs_isTransformLV(3);
    l_wolfSense = dComIfGs_isEventBit(0x4308);

    for (int i = BLUE_RUPEE; i <= SILVER_RUPEE; i++) {
        if (dComIfGs_isItemFirstBit(i)) {
            l_rupeeFlag = true;
            break;
        }
    }

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        GZ_setMenu(GZ_FLAGS_MENU);
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        switch (cursor.y) {
        case BOSS_FLAG_INDEX:
            if (l_bossFlag) {
                tp_bossFlags = 0;
            } else {
                tp_bossFlags = 255;
            }
            break;
        case RUPEE_CS_FLAG_INDEX:
            if (l_rupeeFlag) {
                for (int i = BLUE_RUPEE; i <= SILVER_RUPEE; i++) {
                    dComIfGs_offItemFirstBit(i);
                }
            } else {
                for (int i = BLUE_RUPEE; i <= SILVER_RUPEE; i++) {
                    dComIfGs_onItemFirstBit(i);
                }
            }
            break;
        case EPONA_STOLEN_INDEX:
            setEventFlag(0x0580);
            break;
        case EPONA_TAMED_INDEX:
            setEventFlag(0x0601);
            break;
        case MAP_WARPING_INDEX:
            setEventFlag(0x0604);
            break;
        case MIDNA_HEALTHY:
            setEventFlag(0x1E08);
            break;
        case MIDNA_ON_BACK:
            if (dComIfGs_isTransformLV(3)) {
                dComIfGs_offTransformLV(3);
            } else {
                dComIfGs_onTransformLV(3);
            }
            break;
        case MIDNA_Z_INDEX:
            setEventFlag(0x0C10);
            break;
        case TRANSFORM_WARP_INDEX:
            setEventFlag(0x0D04);
            break;
        case WOLF_SENSE_INDEX:
            setEventFlag(0x4308);
            break;
        case MIDNA_CHARGE_INDEX:
            setEventFlag(0x0501);
            break;
        }
    }

    cursor.move(0, LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, LINE_NUM);
}
