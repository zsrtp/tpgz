#pragma once
#include "menu.h"

enum PortalFlagsIndex {
    SELECT_REGION_INDEX,
    REGION_FLAG_INDEX,
    SPRING_WARP_INDEX,
    S_FARON_WARP_INDEX,
    N_FARON_WARP_INDEX,
    GROVE_WARP_INDEX,
    GORGE_WARP_INDEX,
    KAKARIKO_WARP_INDEX,
    MOUNTAIN_WARP_INDEX,
    BRIDGE_WARP_INDEX,
    TOWN_WARP_INDEX,
    LAKE_WARP_INDEX,
    DOMAIN_WARP_INDEX,
    UZR_WARP_INDEX,
    SNOWPEAK_WARP_INDEX,
    MESA_WARP_INDEX,
    MIRROR_WARP_INDEX
};

class PortalFlagsMenu : public Menu {
public:
    PortalFlagsMenu();
    virtual void draw();

    Cursor cursor;

private:
    bool l_mapRegion;
    uint8_t l_selRegion;

    bool l_springWarp;
    bool l_sfaronWarp;
    bool l_nfaronWarp;
    bool l_groveWarp;
    bool l_gorgeWarp;
    bool l_kakWarp;
    bool l_mountainWarp;
    bool l_bridgeWarp;
    bool l_ctWarp;
    bool l_lakeWarp;
    bool l_domainWarp;
    bool l_uzrWarp;
    bool l_snowpeakWarp;
    bool l_mesaWarp;
    bool l_mirrorWarp;

    Line lines[17];
};
