#include "menu.h"

#define GENERAL_FLAGS_INDEX 0
#define DUNGEON_FLAGS_INDEX 1
#define PORTAL_FLAGS_INDEX 2
#define FLAG_RECORDS_INDEX 3
#define FLAG_LOG_INDEX 4

enum GeneralFlagsIndex {
    BOSS_FLAG_INDEX,
    RUPEE_CS_FLAG_INDEX,
    EPONA_STOLEN_INDEX,
    EPONA_TAMED_INDEX,
    MAP_WARPING_INDEX,
    MIDNA_CHARGE_INDEX,
    MIDNA_HEALTHY,
    MIDNA_ON_BACK,
    MIDNA_Z_INDEX,
    TRANSFORM_WARP_INDEX,
    WOLF_SENSE_INDEX
};

enum DungeonFlagsIndex {
    SELECT_DUNGEON_INDEX,
    SMALL_KEY_FLAG_INDEX,
    MAP_FLAG_INDEX,
    COMPASS_FLAG_INDEX,
    BOSS_KEY_FLAG_INDEX,
    DEFEAT_MINIBOSS_FLAG_INDEX,
    DEFEAT_BOSS_FLAG_INDEX,
    CLEAR_DUNGEON_FLAGS_INDEX
};

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

class FlagsMenu : public Menu {
public:
    FlagsMenu();
    virtual void draw();

    Cursor cursor;
private:
    Line lines[5];
};

class GeneralFlagsMenu : public Menu {
public:
    GeneralFlagsMenu();
    virtual void draw();

    Cursor cursor;
private:
    bool l_bossFlag;
    bool l_rupeeFlag;
    bool l_midnaCharge;
    bool l_transformWarp;
    bool l_midnaZ;
    bool l_eponaStolen;
    bool l_eponaTamed;
    bool l_mapWarping;
    bool l_midnaHealed;
    bool l_midnaRide;
    bool l_wolfSense;

    Line lines[11];
};

class DungeonFlagsMenu : public Menu {
public:
    DungeonFlagsMenu();
    virtual void draw();

    Cursor cursor;
private:
    bool init_once = false;

    bool l_mapFlag;
    bool l_compassFlag;
    bool l_bosskeyFlag;
    bool l_minibossFlag;
    bool l_bossFlag;
    int l_selDun;
    uint8_t l_keyNum;

    Line lines[8];
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

class FlagLogMenu : public Menu {
public:
    FlagLogMenu();
    virtual void draw();

    Cursor cursor;
private:
    Line lines[1];
};