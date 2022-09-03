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

struct WarpingData {
    Cursor cursor;
    WarpInfo l_warpInfo;
    uint8_t l_warpLayer = 0xFF;
    int l_typeIdx;
    signed long l_stageIdx;
    signed long l_roomIdx;
    signed long l_spawnIdx;
    bool l_dataLoaded;
};

class WarpingMenu : public Menu {
public:
    WarpingMenu(WarpingData&);
    virtual ~WarpingMenu();
    virtual void draw();

private:
    void loadPrevInfo(void* buffer, signed long& counter, signed long length, char max_num,
                      int offset);
    void loadNextInfo(void* buffer, signed long& counter, signed long length, char max_num,
                      int offset);
    void setStagePath(int current_stage_type);
    void loadPrevStageInfo();
    void loadPrevRoomInfo();
    void loadNextStageInfo();
    void loadNextRoomInfo();
    void loadNextSpawnInfo();
    void loadPrevSpawnInfo();
    void loadDefaultStage();
    void loadDefaultRoom();
    void loadDefaultSpawn();

    WarpInfo& l_warpInfo;
    uint8_t& l_warpLayer;
    int& l_typeIdx;
    signed long& l_stageIdx;
    signed long& l_roomIdx;
    signed long& l_spawnIdx;
    bool& l_dataLoaded;
    char l_filePath[89];

    Line lines[7];
};