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

KEEP_FUNC WarpingMenu::WarpingMenu(WarpingData& data)
    : Menu(data.cursor), l_warpInfo(data.l_warpInfo), l_warpLayer(data.l_warpLayer),
      l_typeIdx(data.l_typeIdx), l_stageIdx(data.l_stageIdx), l_roomIdx(data.l_roomIdx),
      l_spawnIdx(data.l_spawnIdx), l_dataLoaded(data.l_dataLoaded),
      lines{{"type:", WARP_TYPE_INDEX, "The type of stage", false},
            {"stage:", WARP_STAGE_INDEX, "Current stage name", false},
            {"room:", WARP_ROOM_INDEX, "Current room name", false},
            {"spawn:", WARP_SPAWN_INDEX, "Current spawn number", false},
            {"layer:", WARP_LAYER_INDEX, "Current layer number", false},
            {"warp", WARP_BUTTON_INDEX, "Trigger warp", false},
            {"save", SAVE_LOCATION_INDEX, "Set savefile location to selected location", false}} {}

WarpingMenu::~WarpingMenu() {}

enum { CAVE, DUNGEON, INTERIOR, OVERWORLD, SPECIAL };

char stage_types[5][10] = {"cave", "dungeon", "interior", "overworld", "special"};

void WarpingMenu::loadPrevInfo(void* buffer, signed long& counter, signed long length, char max_num,
                               int offset) {
    if (counter < 0) {
        counter = (max_num * offset) - offset;
    }
    loadFile(l_filePath, buffer, length, counter);
}

void WarpingMenu::loadNextInfo(void* buffer, signed long& counter, signed long length, char max_num,
                               int offset) {
    if (counter == (offset * max_num)) {
        counter = 0;
    }
    loadFile(l_filePath, buffer, length, counter);
}

char l_stageMapping[5][10] = {"cave", "dungeon", "interior", "overworld", "special"};

void WarpingMenu::setStagePath(int current_stage_type) {
    if (current_stage_type < 0 || current_stage_type > 4) {
        return;
    }
    snprintf(l_filePath, sizeof(l_filePath), "tpgz/stage_info/%s.bin", l_stageMapping[current_stage_type]);
}

void WarpingMenu::loadPrevStageInfo() {
    WarpingMenu::setStagePath(l_typeIdx);
    l_stageIdx -= STAGE_OFFSET;
    WarpingMenu::loadPrevInfo(&l_warpInfo.stage_info, l_stageIdx, STAGE_READ_LENGTH,
                              l_warpInfo.stage_info.num_stages, STAGE_OFFSET);
}

void WarpingMenu::loadPrevRoomInfo() {
    snprintf(l_filePath, sizeof(l_filePath), "tpgz/stage_info/%s/rooms.bin",
             l_warpInfo.stage_info.stage_id);
    l_roomIdx -= ROOM_OFFSET;
    WarpingMenu::loadPrevInfo(&l_warpInfo.room_info, l_roomIdx, ROOM_READ_LENGTH,
                              l_warpInfo.room_info.num_rooms, ROOM_OFFSET);
}

void WarpingMenu::loadNextStageInfo() {
    WarpingMenu::setStagePath(l_typeIdx);
    l_stageIdx += STAGE_OFFSET;
    WarpingMenu::loadNextInfo(&l_warpInfo.stage_info, l_stageIdx, STAGE_READ_LENGTH,
                              l_warpInfo.stage_info.num_stages, STAGE_OFFSET);
}

void WarpingMenu::loadNextRoomInfo() {
    snprintf(l_filePath, sizeof(l_filePath), "tpgz/stage_info/%s/rooms.bin",
             l_warpInfo.stage_info.stage_id);
    l_roomIdx += ROOM_OFFSET;
    WarpingMenu::loadNextInfo(&l_warpInfo.room_info, l_roomIdx, ROOM_READ_LENGTH,
                              l_warpInfo.room_info.num_rooms, ROOM_OFFSET);
}

void WarpingMenu::loadNextSpawnInfo() {
    snprintf(l_filePath, sizeof(l_filePath), "tpgz/stage_info/%s/%02d/sp.bin",
             l_warpInfo.stage_info.stage_id, (int)l_warpInfo.room_info.room_id[0]);
    l_spawnIdx += SPAWN_OFFSET;
    WarpingMenu::loadNextInfo(&l_warpInfo.spawn_info, l_spawnIdx, SPAWN_READ_LENGTH,
                              l_warpInfo.spawn_info.num_spawns, SPAWN_OFFSET);
}

void WarpingMenu::loadPrevSpawnInfo() {
    snprintf(l_filePath, sizeof(l_filePath), "tpgz/stage_info/%s/%02d/sp.bin",
             l_warpInfo.stage_info.stage_id, (int)l_warpInfo.room_info.room_id[0]);
    l_spawnIdx -= SPAWN_OFFSET;
    WarpingMenu::loadPrevInfo(&l_warpInfo.spawn_info, l_spawnIdx, SPAWN_READ_LENGTH,
                              l_warpInfo.spawn_info.num_spawns, SPAWN_OFFSET);
}

void WarpingMenu::loadDefaultStage() {
    l_stageIdx = -64;
    WarpingMenu::setStagePath(l_typeIdx);
    WarpingMenu::loadNextStageInfo();
}

void WarpingMenu::loadDefaultRoom() {
    l_roomIdx = -64;
    WarpingMenu::loadNextRoomInfo();
}

void WarpingMenu::loadDefaultSpawn() {
    l_spawnIdx = -4;
    WarpingMenu::loadNextSpawnInfo();
}

void WarpingMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    if (!l_dataLoaded) {
        WarpingMenu::loadDefaultStage();
        WarpingMenu::loadDefaultRoom();
        WarpingMenu::loadDefaultSpawn();
        l_dataLoaded = true;
    }

    if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
        switch (cursor.y) {
        case WARP_TYPE_INDEX:
            l_typeIdx++;
            if (l_typeIdx > 4) {
                l_typeIdx = 0;
            }
            WarpingMenu::loadDefaultStage();
            WarpingMenu::loadDefaultRoom();
            WarpingMenu::loadDefaultSpawn();
            l_warpLayer = DEFAULT_LAYER;
            break;
        case WARP_STAGE_INDEX:
            WarpingMenu::loadNextStageInfo();
            WarpingMenu::loadDefaultRoom();
            WarpingMenu::loadDefaultSpawn();
            l_warpLayer = DEFAULT_LAYER;
            break;
        case WARP_ROOM_INDEX:
            WarpingMenu::loadNextRoomInfo();
            WarpingMenu::loadDefaultSpawn();
            l_warpLayer = DEFAULT_LAYER;
            break;
        case WARP_SPAWN_INDEX:
            WarpingMenu::loadNextSpawnInfo();
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
        switch (cursor.y) {
        case WARP_TYPE_INDEX:
            l_typeIdx--;
            if (l_typeIdx < 0) {
                l_typeIdx = 4;
            }
            WarpingMenu::loadDefaultStage();
            WarpingMenu::loadDefaultRoom();
            WarpingMenu::loadDefaultSpawn();
            l_warpLayer = DEFAULT_LAYER;
            break;
        case WARP_STAGE_INDEX:
            WarpingMenu::loadPrevStageInfo();
            WarpingMenu::loadDefaultRoom();
            WarpingMenu::loadDefaultSpawn();
            l_warpLayer = DEFAULT_LAYER;
            break;
        case WARP_ROOM_INDEX:
            WarpingMenu::loadPrevRoomInfo();
            WarpingMenu::loadDefaultSpawn();
            l_warpLayer = DEFAULT_LAYER;
            break;
        case WARP_SPAWN_INDEX:
            WarpingMenu::loadPrevSpawnInfo();
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
        switch (cursor.y) {
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
    lines[WARP_TYPE_INDEX].printf(" <%s>", tmpbuf);

    strcpy(tmpbuf, l_warpInfo.stage_info.stage_name);
    lines[WARP_STAGE_INDEX].printf(" <%s>", tmpbuf);

    strcpy(tmpbuf, l_warpInfo.room_info.room_name);
    lines[WARP_ROOM_INDEX].printf(" <%s>", tmpbuf);

    lines[WARP_SPAWN_INDEX].printf(" <%d>", l_warpInfo.spawn_info.spawn_id[0]);
    if (l_warpLayer == DEFAULT_LAYER) {
        lines[WARP_LAYER_INDEX].printf(" <default>");
    } else {
        lines[WARP_LAYER_INDEX].printf(" <%d>", l_warpLayer);
    }

    cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}