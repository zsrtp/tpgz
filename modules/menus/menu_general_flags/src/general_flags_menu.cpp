#include "menus/menu_general_flags/include/general_flags_menu.h"
#include "gz_flags.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/utils.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

KEEP_VAR GeneralFlagsData* generalFlagsData;

KEEP_FUNC GeneralFlagsMenu::GeneralFlagsMenu(Cursor& cursor)
    : Menu(cursor),
      lines{
          {"boss flag", BOSS_FLAG_INDEX, "Sets the boss flag value", true, [](){return generalFlagsData->l_bossFlag;}},
          {"rupee cutscenes", RUPEE_CS_FLAG_INDEX, "Toggle rupee cutscenes being enabled", true,
           [](){return generalFlagsData->l_rupeeFlag;}},
          {"epona stolen", EPONA_STOLEN_INDEX, "Toggle flag for Epona being stolen", true,
           [](){return generalFlagsData->l_eponaStolen;}},
          {"epona tamed", EPONA_TAMED_INDEX, "Toggle flag for Epona being tamed", true,
           [](){return generalFlagsData->l_eponaTamed;}},
          {"map warping", MAP_WARPING_INDEX, "Toggle flag for map warping", true, [](){return generalFlagsData->l_mapWarping;}},
          {"midna charge", MIDNA_CHARGE_INDEX, "Toggle flag for Midna charge", true,
           [](){return generalFlagsData->l_midnaCharge;}},
          {"midna healed", MIDNA_HEALTHY, "Toggle flag for Midna being healed", true,
           [](){return generalFlagsData->l_midnaHealed;}},
          {"midna on back", MIDNA_ON_BACK, "Toggle flag for Midna appearing on Wolf Link's back",
           true, [](){return generalFlagsData->l_midnaRide;}},
          {"midna available", MIDNA_Z_INDEX, "Toggle flag for being able to call Midna", true,
           [](){return generalFlagsData->l_midnaZ;}},
          {"transform/warp", TRANSFORM_WARP_INDEX, "Toggle flag for transforming/warping", true,
           [](){return generalFlagsData->l_transformWarp;}},
          {"wolf sense", WOLF_SENSE_INDEX, "Toggle flag for wolf sense", true, [](){return generalFlagsData->l_wolfSense;}},
      } {}

GeneralFlagsMenu::~GeneralFlagsMenu() {}

void GeneralFlagsMenu::draw() {
    if (!generalFlagsData) {
        return;
    }

    // update flags
    generalFlagsData->l_bossFlag = bossFlags > 0;
    generalFlagsData->l_midnaCharge = dComIfGs_isEventBit(0x0501);
    generalFlagsData->l_transformWarp = dComIfGs_isEventBit(0x0D04);
    generalFlagsData->l_midnaZ = dComIfGs_isEventBit(0x0C10);
    generalFlagsData->l_eponaStolen = dComIfGs_isEventBit(0x0580);
    generalFlagsData->l_eponaTamed = dComIfGs_isEventBit(0x0601);
    generalFlagsData->l_mapWarping = dComIfGs_isEventBit(0x0604);
    generalFlagsData->l_midnaHealed = dComIfGs_isEventBit(0x1E08);
    generalFlagsData->l_midnaRide = dComIfGs_isTransformLV(3);
    generalFlagsData->l_wolfSense = dComIfGs_isEventBit(0x4308);

    for (int i = BLUE_RUPEE; i <= SILVER_RUPEE; i++) {
        if (dComIfGs_isItemFirstBit(i)) {
            generalFlagsData->l_rupeeFlag = true;
            break;
        }
    }

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        switch (cursor.y) {
        case BOSS_FLAG_INDEX:
            if (generalFlagsData->l_bossFlag) {
                bossFlags = 0;
            } else {
                bossFlags = 255;
            }
            break;
        case RUPEE_CS_FLAG_INDEX:
            if (generalFlagsData->l_rupeeFlag) {
                for (int i = BLUE_RUPEE; i <= SILVER_RUPEE; i++) {
                    dComIfGs_offItemFirstBit(i);
                }
                generalFlagsData->l_rupeeFlag = false;
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

    cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
