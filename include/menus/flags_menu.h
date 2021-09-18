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
    FlagsMenu() : Menu() {}
    static void render();
};

class GeneralFlagsMenu : public Menu {
public:
    GeneralFlagsMenu() : Menu() {}
    static void render();
};

class DungeonFlagsMenu : public Menu {
public:
    DungeonFlagsMenu() : Menu() {}
    static void render();
};

class PortalFlagsMenu : public Menu {
public:
    PortalFlagsMenu() : Menu() {}
    static void render();
};

class FlagLogMenu : public Menu {
public:
    FlagLogMenu() : Menu() {}
    static void render();
};