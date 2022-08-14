#include "menu.h"

enum WarpingIndex {
    WARP_TYPE_INDEX,
    WARP_STAGE_INDEX,
    WARP_ROOM_INDEX,
    WARP_SPAWN_INDEX,
    WARP_LAYER_INDEX,
    WARP_BUTTON_INDEX,
    SAVE_LOCATION_INDEX
};

struct StageInfo {
    char num_stages;
    char stage_id[31];
    char stage_name[32];
};

struct RoomInfo {
    char num_rooms;
    char room_id[31];
    char room_name[32];
};

struct SpawnInfo {
    char num_spawns;
    char spawn_id[3];
};

struct WarpInfo {
    StageInfo stage_info;
    RoomInfo room_info;
    SpawnInfo spawn_info;
} __attribute__((aligned(32)));

class WarpingMenu : public Menu {
public:
    WarpingMenu();
    virtual void draw();

    Cursor cursor;

private:
    Line lines[7];
};