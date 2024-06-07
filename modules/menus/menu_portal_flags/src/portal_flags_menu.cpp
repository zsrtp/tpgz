#include "menus/menu_portal_flags/include/portal_flags_menu.h"
#include <cstdio>
#include "gz_flags.h"
#include "libtp_c/include/m_Do/m_Do_printf.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

#define MAX_REGION_OPTIONS 6

KEEP_VAR PortalFlagsData* portalFlagsData;

KEEP_FUNC PortalFlagsMenu::PortalFlagsMenu(Cursor& cursor)
    : Menu(cursor),
      lines{
          {"region:", SELECT_REGION_INDEX, "Select region flag", false, nullptr,
           MAX_REGION_OPTIONS},
          {"region unlocked", REGION_FLAG_INDEX, "Unlock selected map region", true, [](){return portalFlagsData->l_mapRegion;}},
          {"ordon spring", SPRING_WARP_INDEX, "Ordon Spring warp portal", true, [](){return portalFlagsData->l_springWarp;}},
          {"south faron", S_FARON_WARP_INDEX, "South Faron warp portal", true, [](){return portalFlagsData->l_sfaronWarp;}},
          {"north faron", N_FARON_WARP_INDEX, "North Faron warp portal", true, [](){return portalFlagsData->l_nfaronWarp;}},
          {"sacred grove", GROVE_WARP_INDEX, "Sacred Grove warp portal", true, [](){return portalFlagsData->l_groveWarp;}},
          {"eldin gorge", GORGE_WARP_INDEX, "Eldin Gorge warp portal", true, [](){return portalFlagsData->l_gorgeWarp;}},
          {"kak village", KAKARIKO_WARP_INDEX, "Kakariko Village warp portal", true, [](){return portalFlagsData->l_kakWarp;}},
          {"death mountain", MOUNTAIN_WARP_INDEX, "Death Mountain warp portal", true,
           [](){return portalFlagsData->l_mountainWarp;}},
          {"eldin bridge", BRIDGE_WARP_INDEX, "Bridge of Eldin warp portal", true, [](){return portalFlagsData->l_bridgeWarp;}},
          {"castle town", TOWN_WARP_INDEX, "Castle Town warp portal", true, [](){return portalFlagsData->l_ctWarp;}},
          {"lake hylia", LAKE_WARP_INDEX, "Lake Hylia warp portal", true, [](){return portalFlagsData->l_lakeWarp;}},
          {"zora's domain", DOMAIN_WARP_INDEX, "Zora's Domain warp portal", true, [](){return portalFlagsData->l_domainWarp;}},
          {"upper river", UZR_WARP_INDEX, "Upper Zora's River warp portal", true, [](){return portalFlagsData->l_uzrWarp;}},
          {"snowpeak", SNOWPEAK_WARP_INDEX, "Snowpeak warp portal", true, [](){return portalFlagsData->l_snowpeakWarp;}},
          {"gerudo mesa", MESA_WARP_INDEX, "Gerudo Mesa warp portal", true, [](){return portalFlagsData->l_mesaWarp;}},
          {"mirror chamber", MIRROR_WARP_INDEX, "Mirror Chamber warp portal", true, [](){return portalFlagsData->l_mirrorWarp;}},
      } {}

PortalFlagsMenu::~PortalFlagsMenu() {}

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

inline void setRegionFlag(int regionBit) {
    g_dComIfG_gameInfo.info.getPlayer().mPlayerFieldLastStayInfo.mRegion ^= (1 << regionBit);
}

inline bool getRegionFlag(int regionBit) {
    return g_dComIfG_gameInfo.info.getPlayer().mPlayerFieldLastStayInfo.mRegion & (1 << regionBit);
}

void PortalFlagsMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    portalFlagsData->l_mapRegion = getRegionFlag(portalFlagsData->l_selRegion + 1);
    portalFlagsData->l_springWarp = getSaveSwitch(dSv_memory_c::ORDON, 52);
    portalFlagsData->l_sfaronWarp = getSaveSwitch(dSv_memory_c::FARON, 71);
    portalFlagsData->l_nfaronWarp = getSaveSwitch(dSv_memory_c::FARON, 2);
    portalFlagsData->l_groveWarp = getSaveSwitch(dSv_memory_c::GROVE, 100);
    portalFlagsData->l_gorgeWarp = getSaveSwitch(dSv_memory_c::FIELD, 21);
    portalFlagsData->l_kakWarp = getSaveSwitch(dSv_memory_c::ELDIN, 31);
    portalFlagsData->l_mountainWarp = getSaveSwitch(dSv_memory_c::ELDIN, 21);
    portalFlagsData->l_bridgeWarp = getSaveSwitch(dSv_memory_c::FIELD, 99);
    portalFlagsData->l_ctWarp = getSaveSwitch(dSv_memory_c::FIELD, 3);
    portalFlagsData->l_lakeWarp = getSaveSwitch(dSv_memory_c::LANAYRU, 10);
    portalFlagsData->l_domainWarp = getSaveSwitch(dSv_memory_c::LANAYRU, 2);
    portalFlagsData->l_uzrWarp = getSaveSwitch(dSv_memory_c::LANAYRU, 21);
    portalFlagsData->l_snowpeakWarp = getSaveSwitch(dSv_memory_c::SNOWPEAK, 21);
    portalFlagsData->l_mesaWarp = getSaveSwitch(dSv_memory_c::DESERT, 21);
    portalFlagsData->l_mirrorWarp = getSaveSwitch(dSv_memory_c::DESERT, 40);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        switch (cursor.y) {
        case REGION_FLAG_INDEX:
            setRegionFlag(portalFlagsData->l_selRegion + 1);
            break;
        case SPRING_WARP_INDEX:
            setSaveSwitch(dSv_memory_c::ORDON, 52);
            break;
        case S_FARON_WARP_INDEX:
            setSaveSwitch(dSv_memory_c::FARON, 71);
            break;
        case N_FARON_WARP_INDEX:
            setSaveSwitch(dSv_memory_c::FARON, 2);
            break;
        case GROVE_WARP_INDEX:
            setSaveSwitch(dSv_memory_c::GROVE, 100);
            break;
        case GORGE_WARP_INDEX:
            setSaveSwitch(dSv_memory_c::FIELD, 21);
            break;
        case KAKARIKO_WARP_INDEX:
            setSaveSwitch(dSv_memory_c::ELDIN, 31);
            break;
        case MOUNTAIN_WARP_INDEX:
            setSaveSwitch(dSv_memory_c::ELDIN, 21);
            break;
        case BRIDGE_WARP_INDEX:
            setSaveSwitch(dSv_memory_c::FIELD, 99);
            break;
        case TOWN_WARP_INDEX:
            setSaveSwitch(dSv_memory_c::FIELD, 3);
            break;
        case LAKE_WARP_INDEX:
            setSaveSwitch(dSv_memory_c::LANAYRU, 10);
            break;
        case DOMAIN_WARP_INDEX:
            setSaveSwitch(dSv_memory_c::LANAYRU, 2);
            break;
        case UZR_WARP_INDEX:
            setSaveSwitch(dSv_memory_c::LANAYRU, 21);
            break;
        case SNOWPEAK_WARP_INDEX:
            setSaveSwitch(dSv_memory_c::SNOWPEAK, 21);
            break;
        case MESA_WARP_INDEX:
            setSaveSwitch(dSv_memory_c::DESERT, 21);
            break;
        case MIRROR_WARP_INDEX:
            setSaveSwitch(dSv_memory_c::DESERT, 40);
            break;
        }
        // copy stage save flags to temp flags
        dComIfGs_getSave(g_dComIfG_gameInfo.info.mDan.mStageNo);
    }

    switch (cursor.y) {
    case SELECT_REGION_INDEX:
        cursor.x = portalFlagsData->l_selRegion;
        cursor.move(MAX_REGION_OPTIONS, MENU_LINE_NUM);

        if (cursor.y == SELECT_REGION_INDEX) {
            portalFlagsData->l_selRegion = cursor.x;
        }
        break;
    default:
        cursor.move(0, MENU_LINE_NUM);
        break;
    }

    ListMember region_opt[MAX_REGION_OPTIONS] = {
        "ordon", "faron", "eldin", "lanayru", "desert", "snowpeak",
    };

    lines[SELECT_REGION_INDEX].printf(" <%s>", region_opt[portalFlagsData->l_selRegion].member);

    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
