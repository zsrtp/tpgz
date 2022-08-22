#include "menus/menu_warp/include/warping_menu.h"
#include <cstdio>
#include "commands.h"
#include "fifo_queue.h"
#include "fs.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/utils.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

#define SPAWN_OFFSET 4
#define SPAWN_READ_LENGTH 32
#define ROOM_READ_LENGTH 64
#define STAGE_READ_LENGTH 64
#define STAGE_OFFSET 64
#define ROOM_OFFSET 64
#define DEFAULT_LAYER 0xFF

KEEP_FUNC WarpingMenu::WarpingMenu(Cursor& cursor)
    : Menu(), m_cursor(cursor), lines{{"type:", WARP_TYPE_INDEX, "The type of stage", false},
                    {"stage:", WARP_STAGE_INDEX, "Current stage name", false},
                    {"room:", WARP_ROOM_INDEX, "Current room name", false},
                    {"spawn:", WARP_SPAWN_INDEX, "Current spawn number", false},
                    {"layer:", WARP_LAYER_INDEX, "Current layer number", false},
                    {"warp", WARP_BUTTON_INDEX, "Trigger warp", false},
                    {"save", SAVE_LOCATION_INDEX, "Set savefile location to selected location",
                     false}} {}

WarpingMenu::~WarpingMenu() {}

uint8_t l_warpLayer = 0xFF;
bool l_dataLoaded = false;
int l_typeIdx = 0;
signed long l_stageIdx = 0;
signed long l_roomIdx = 0;
signed long l_spawnIdx = 0;

char l_filePath[89];
WarpInfo l_warpInfo;

enum { DUNGEON, OVERWORLD, INTERIOR, CAVE, SPECIAL };

char stage_types[5][10] = {"dungeon", "overworld", "interior", "cave", "special"};

void GZWarp_loadPrevInfo(void* buffer, signed long& counter, signed long length, char max_num,
                         int offset) {
    if (counter < 0) {
        counter = (max_num * offset) - offset;
    }
    loadFile(l_filePath, buffer, length, counter);
}

void GZWarp_loadNextInfo(void* buffer, signed long& counter, signed long length, char max_num,
                         int offset) {
    if (counter == (offset * max_num)) {
        counter = 0;
    }
    loadFile(l_filePath, buffer, length, counter);
}

void GZWarp_setStagePath(int current_stage_type) {
    switch (current_stage_type) {
    case DUNGEON:
        strcpy(l_filePath, "tpgz/stage_info/dungeon.bin");
        break;
    case OVERWORLD:
        strcpy(l_filePath, "tpgz/stage_info/overworld.bin");
        break;
    case INTERIOR:
        strcpy(l_filePath, "tpgz/stage_info/interior.bin");
        break;
    case CAVE:
        strcpy(l_filePath, "tpgz/stage_info/cave.bin");
        break;
    case SPECIAL:
        strcpy(l_filePath, "tpgz/stage_info/special.bin");
        break;
    }
}

void GZWarp_loadPrevStageInfo() {
    GZWarp_setStagePath(l_typeIdx);
    l_stageIdx -= STAGE_OFFSET;
    GZWarp_loadPrevInfo(&l_warpInfo.stage_info, l_stageIdx, STAGE_READ_LENGTH,
                        l_warpInfo.stage_info.num_stages, STAGE_OFFSET);
}

void GZWarp_loadPrevRoomInfo() {
    snprintf(l_filePath, sizeof(l_filePath), "tpgz/stage_info/%s/rooms.bin", l_warpInfo.stage_info.stage_id);
    l_roomIdx -= ROOM_OFFSET;
    GZWarp_loadPrevInfo(&l_warpInfo.room_info, l_roomIdx, ROOM_READ_LENGTH,
                        l_warpInfo.room_info.num_rooms, ROOM_OFFSET);
}

void GZWarp_loadNextStageInfo() {
    GZWarp_setStagePath(l_typeIdx);
    l_stageIdx += STAGE_OFFSET;
    GZWarp_loadNextInfo(&l_warpInfo.stage_info, l_stageIdx, STAGE_READ_LENGTH,
                        l_warpInfo.stage_info.num_stages, STAGE_OFFSET);
}

void GZWarp_loadNextRoomInfo() {
    snprintf(l_filePath, sizeof(l_filePath), "tpgz/stage_info/%s/rooms.bin", l_warpInfo.stage_info.stage_id);
    l_roomIdx += ROOM_OFFSET;
    GZWarp_loadNextInfo(&l_warpInfo.room_info, l_roomIdx, ROOM_READ_LENGTH,
                        l_warpInfo.room_info.num_rooms, ROOM_OFFSET);
}

void GZWarp_loadNextSpawnInfo() {
    snprintf(l_filePath, sizeof(l_filePath), "tpgz/stage_info/%s/%02d/spawns.bin", l_warpInfo.stage_info.stage_id,
            (int)l_warpInfo.room_info.room_id[0]);
    l_spawnIdx += SPAWN_OFFSET;
    GZWarp_loadNextInfo(&l_warpInfo.spawn_info, l_spawnIdx, SPAWN_READ_LENGTH,
                        l_warpInfo.spawn_info.num_spawns, SPAWN_OFFSET);
}

void GZWarp_loadPrevSpawnInfo() {
    snprintf(l_filePath, sizeof(l_filePath), "tpgz/stage_info/%s/%02d/spawns.bin", l_warpInfo.stage_info.stage_id,
            (int)l_warpInfo.room_info.room_id[0]);
    l_spawnIdx -= SPAWN_OFFSET;
    GZWarp_loadPrevInfo(&l_warpInfo.spawn_info, l_spawnIdx, SPAWN_READ_LENGTH,
                        l_warpInfo.spawn_info.num_spawns, SPAWN_OFFSET);
}

void GZWarp_loadDefaultStage() {
    l_stageIdx = -64;
    GZWarp_setStagePath(l_typeIdx);
    GZWarp_loadNextStageInfo();
}

void GZWarp_loadDefaultRoom() {
    l_roomIdx = -64;
    GZWarp_loadNextRoomInfo();
}

void GZWarp_loadDefaultSpawn() {
    l_spawnIdx = -4;
    GZWarp_loadNextSpawnInfo();
}

void WarpingMenu::draw() {
    m_cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    if (!l_dataLoaded) {
        GZWarp_loadDefaultStage();
        GZWarp_loadDefaultRoom();
        GZWarp_loadDefaultSpawn();
        l_dataLoaded = true;
    }

    if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
        switch (m_cursor.y) {
        case WARP_TYPE_INDEX:
            l_typeIdx++;
            if (l_typeIdx > 4) {
                l_typeIdx = 0;
            }
            GZWarp_loadDefaultStage();
            GZWarp_loadDefaultRoom();
            GZWarp_loadDefaultSpawn();
            l_warpLayer = DEFAULT_LAYER;
            break;
        case WARP_STAGE_INDEX:
            GZWarp_loadNextStageInfo();
            GZWarp_loadDefaultRoom();
            GZWarp_loadDefaultSpawn();
            l_warpLayer = DEFAULT_LAYER;
            break;
        case WARP_ROOM_INDEX:
            GZWarp_loadNextRoomInfo();
            GZWarp_loadDefaultSpawn();
            l_warpLayer = DEFAULT_LAYER;
            break;
        case WARP_SPAWN_INDEX:
            GZWarp_loadNextSpawnInfo();
            l_warpLayer = DEFAULT_LAYER;
            break;
        case WARP_LAYER_INDEX:
            l_warpLayer++;
            if (l_warpLayer == 0x10) {
                l_warpLayer = DEFAULT_LAYER;
            }
            break;
        }
    }

    if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
        switch (m_cursor.y) {
        case WARP_TYPE_INDEX:
            l_typeIdx--;
            if (l_typeIdx < 0) {
                l_typeIdx = 4;
            }
            GZWarp_loadDefaultStage();
            GZWarp_loadDefaultRoom();
            GZWarp_loadDefaultSpawn();
            l_warpLayer = DEFAULT_LAYER;
            break;
        case WARP_STAGE_INDEX:
            GZWarp_loadPrevStageInfo();
            GZWarp_loadDefaultRoom();
            GZWarp_loadDefaultSpawn();
            l_warpLayer = DEFAULT_LAYER;
            break;
        case WARP_ROOM_INDEX:
            GZWarp_loadPrevRoomInfo();
            GZWarp_loadDefaultSpawn();
            l_warpLayer = DEFAULT_LAYER;
            break;
        case WARP_SPAWN_INDEX:
            GZWarp_loadPrevSpawnInfo();
            l_warpLayer = DEFAULT_LAYER;
            break;
        case WARP_LAYER_INDEX:
            l_warpLayer--;
            if (l_warpLayer == 0xFE) {
                l_warpLayer = 0xF;
            }
            break;
        }
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        switch (m_cursor.y) {
        case WARP_BUTTON_INDEX:
            setNextStageName(l_warpInfo.stage_info.stage_id);
            setNextStageRoom(l_warpInfo.room_info.room_id[0]);
            setNextStagePoint(l_warpInfo.spawn_info.spawn_id[0]);
            setNextStageLayer(l_warpLayer);
            GZ_setFifoVisible(true);
            g_menuMgr->hide();
            g_dComIfG_gameInfo.play.mNextStage.wipe = 13;  // instant load
            g_dComIfG_gameInfo.info.mRestart.mLastMode = 0;
            g_dComIfG_gameInfo.play.mNextStage.enabled = true;
            break;
        case SAVE_LOCATION_INDEX:
            setReturnPlace(l_warpInfo.stage_info.stage_id, l_warpInfo.room_info.room_id[0],
                           l_warpInfo.spawn_info.spawn_id[0]);
            break;
        }
    }

    // temp fix for sprintf warning
    char tmpbuf[32];

    strcpy(tmpbuf, stage_types[l_typeIdx]);
    snprintf(lines[WARP_TYPE_INDEX].value, sizeof(lines[WARP_TYPE_INDEX].value), " <%s>", tmpbuf);

    strcpy(tmpbuf, l_warpInfo.stage_info.stage_name);
    snprintf(lines[WARP_STAGE_INDEX].value, sizeof(lines[WARP_STAGE_INDEX].value), " <%s>", tmpbuf);

    strcpy(tmpbuf, l_warpInfo.room_info.room_name);
    snprintf(lines[WARP_ROOM_INDEX].value, sizeof(lines[WARP_ROOM_INDEX].value), " <%s>", tmpbuf);

    snprintf(lines[WARP_SPAWN_INDEX].value, sizeof(lines[WARP_SPAWN_INDEX].value), " <%d>", l_warpInfo.spawn_info.spawn_id[0]);
    if (l_warpLayer == DEFAULT_LAYER) {
        snprintf(lines[WARP_LAYER_INDEX].value, sizeof(lines[WARP_LAYER_INDEX].value), " <default>");
    } else {
        snprintf(lines[WARP_LAYER_INDEX].value, sizeof(lines[WARP_LAYER_INDEX].value), " <%d>", l_warpLayer);
    }

    m_cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, m_cursor.y, MENU_LINE_NUM);
}