#include "menus/warping_menu.h"
#include "commands.h"
#include "fifo_queue.h"
#include "controller.h"
#include "font.h"
#include "fs.h"
#include "utils/cursor.h"
#include "utils/lines.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/msl_c/string.h"

#define LINES 7
#define SPAWN_OFFSET 4
#define SPAWN_READ_LENGTH 32
#define ROOM_READ_LENGTH 64
#define STAGE_READ_LENGTH 64
#define STAGE_OFFSET 64
#define ROOM_OFFSET 64
#define DEFAULT_LAYER 0xFF

static Cursor cursor = {0, 0};
uint8_t layer = 0xFF;
bool init_once = false;
bool data_loaded = false;
bool file;
int stage_type_counter = 0;
signed long stage_counter = 0;
signed long room_counter = 0;
signed long spawn_counter = 0;
char file_path[89];
WarpInfo warp_info;

enum { DUNGEON, OVERWORLD, INTERIOR, CAVE, SPECIAL };

char stage_types[5][10] = {"dungeon", "overworld", "interior", "cave", "special"};

Line lines[LINES] = {
    {"type:", WARP_TYPE_INDEX, "The type of stage", false},
    {"stage:", WARP_STAGE_INDEX, "Current stage name", false},
    {"room:", WARP_ROOM_INDEX, "Current room name", false},
    {"spawn:", WARP_SPAWN_INDEX, "Current spawn number", false},
    {"layer:", WARP_LAYER_INDEX, "Current layer number", false},
    {"warp", WARP_BUTTON_INDEX, "Trigger warp", false},
    {"save", SAVE_LOCATION_INDEX, "Set savefile location to selected location", false}};

void load_previous_info(void* buffer, signed long& counter, signed long length, char max_num,
                        int offset) {
    if (counter < 0) {
        counter = (max_num * offset) - offset;
    }
    loadFile(file_path, buffer, length, counter);
}

void load_next_info(void* buffer, signed long& counter, signed long length, char max_num,
                    int offset) {
    if (counter == (offset * max_num)) {
        counter = 0;
    }
    loadFile(file_path, buffer, length, counter);
}

void set_stage_path(int current_stage_type) {
    switch (current_stage_type) {
    case DUNGEON: {
        tp_strcpy(file_path, "tpgz/stage_info/dungeon.bin");
        break;
    }
    case OVERWORLD: {
        tp_strcpy(file_path, "tpgz/stage_info/overworld.bin");
        break;
    }
    case INTERIOR: {
        tp_strcpy(file_path, "tpgz/stage_info/interior.bin");
        break;
    }
    case CAVE: {
        tp_strcpy(file_path, "tpgz/stage_info/cave.bin");
        break;
    }
    case SPECIAL: {
        tp_strcpy(file_path, "tpgz/stage_info/special.bin");
        break;
    }
    }
}

void load_previous_stage_info() {
    set_stage_path(stage_type_counter);
    stage_counter -= STAGE_OFFSET;
    load_previous_info(&warp_info.stage_info, stage_counter, STAGE_READ_LENGTH,
                       warp_info.stage_info.num_stages, STAGE_OFFSET);
}

void load_previous_room_info() {
    tp_sprintf(file_path, "tpgz/stage_info/%s/rooms.bin", warp_info.stage_info.stage_id);
    room_counter -= ROOM_OFFSET;
    load_previous_info(&warp_info.room_info, room_counter, ROOM_READ_LENGTH,
                       warp_info.room_info.num_rooms, ROOM_OFFSET);
}

void load_next_stage_info() {
    set_stage_path(stage_type_counter);
    stage_counter += STAGE_OFFSET;
    load_next_info(&warp_info.stage_info, stage_counter, STAGE_READ_LENGTH,
                   warp_info.stage_info.num_stages, STAGE_OFFSET);
}

void load_next_room_info() {
    tp_sprintf(file_path, "tpgz/stage_info/%s/rooms.bin", warp_info.stage_info.stage_id);
    room_counter += ROOM_OFFSET;
    load_next_info(&warp_info.room_info, room_counter, ROOM_READ_LENGTH,
                   warp_info.room_info.num_rooms, ROOM_OFFSET);
}

void load_next_spawn_info() {
    tp_sprintf(file_path, "tpgz/stage_info/%s/%02d/spawns.bin", warp_info.stage_info.stage_id,
               (int)warp_info.room_info.room_id[0]);
    spawn_counter += SPAWN_OFFSET;
    load_next_info(&warp_info.spawn_info, spawn_counter, SPAWN_READ_LENGTH,
                   warp_info.spawn_info.num_spawns, SPAWN_OFFSET);
}

void load_previous_spawn_info() {
    tp_sprintf(file_path, "tpgz/stage_info/%s/%02d/spawns.bin", warp_info.stage_info.stage_id,
               (int)warp_info.room_info.room_id[0]);
    spawn_counter -= SPAWN_OFFSET;
    load_previous_info(&warp_info.spawn_info, spawn_counter, SPAWN_READ_LENGTH,
                       warp_info.spawn_info.num_spawns, SPAWN_OFFSET);
}

void load_default_stage() {
    stage_counter = -64;
    set_stage_path(stage_type_counter);
    load_next_stage_info();
}

void load_default_room() {
    room_counter = -64;
    load_next_room_info();
}

void load_default_spawn() {
    spawn_counter = -4;
    load_next_spawn_info();
}

void WarpingMenu::render() {
    if (button_is_pressed(BACK_BUTTON)) {
        init_once = false;
        MenuRendering::set_menu(MN_MAIN_MENU_INDEX);
        return;
    };

    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

    if (!data_loaded) {
        load_default_stage();
        load_default_room();
        load_default_spawn();
        data_loaded = true;
    }

    if (button_is_pressed(Controller::DPAD_RIGHT)) {
        switch (cursor.y) {
        case WARP_TYPE_INDEX: {
            stage_type_counter++;
            if (stage_type_counter > 4) {
                stage_type_counter = 0;
            }
            load_default_stage();
            load_default_room();
            load_default_spawn();
            layer = DEFAULT_LAYER;
            break;
        }
        case WARP_STAGE_INDEX: {
            load_next_stage_info();
            load_default_room();
            load_default_spawn();
            layer = DEFAULT_LAYER;
            break;
        }
        case WARP_ROOM_INDEX: {
            load_next_room_info();
            load_default_spawn();
            layer = DEFAULT_LAYER;
            break;
        }
        case WARP_SPAWN_INDEX: {
            load_next_spawn_info();
            layer = DEFAULT_LAYER;
            break;
        }
        case WARP_LAYER_INDEX: {
            layer++;
            if (layer == 0x10) {
                layer = DEFAULT_LAYER;
            }
            break;
        }
        }
    }

    if (button_is_pressed(Controller::DPAD_LEFT)) {
        switch (cursor.y) {
        case WARP_TYPE_INDEX: {
            stage_type_counter--;
            if (stage_type_counter < 0) {
                stage_type_counter = 4;
            }
            load_default_stage();
            load_default_room();
            load_default_spawn();
            layer = DEFAULT_LAYER;
            break;
        }
        case WARP_STAGE_INDEX: {
            load_previous_stage_info();
            load_default_room();
            load_default_spawn();
            layer = DEFAULT_LAYER;
            break;
        }
        case WARP_ROOM_INDEX: {
            load_previous_room_info();
            load_default_spawn();
            layer = DEFAULT_LAYER;
            break;
        }
        case WARP_SPAWN_INDEX: {
            load_previous_spawn_info();
            layer = DEFAULT_LAYER;
            break;
        }
        case WARP_LAYER_INDEX: {
            layer--;
            if (layer == 0xFE) {
                layer = 0xF;
            }
            break;
        }
        }
    }

    if (current_input == SELECTION_BUTTON && a_held == false) {
        switch (cursor.y) {
        case WARP_BUTTON_INDEX: {
            tp_memcpy(&g_dComIfG_gameInfo.play.mNextStage.mStage, &warp_info.stage_info.stage_id, 8);
            g_dComIfG_gameInfo.play.mNextStage.mRoomNo = warp_info.room_info.room_id[0];
            g_dComIfG_gameInfo.play.mNextStage.mPoint = warp_info.spawn_info.spawn_id[0];
            g_dComIfG_gameInfo.play.mNextStage.mLayer = layer;
            init_once = false;
            fifo_visible = true;
            MenuRendering::set_menu(MN_NONE_INDEX);
            g_dComIfG_gameInfo.play.mNextStage.wipe = 13;  // instant load
            g_dComIfG_gameInfo.mInfo.mRestart.mLastMode = 0;
            g_dComIfG_gameInfo.play.mNextStage.enabled = true;
            break;
        }
        case SAVE_LOCATION_INDEX: {
            tp_memcpy(&g_dComIfG_gameInfo.mInfo.getPlayer().player_return.mCurrentStage, &warp_info.stage_info.stage_id, 8);
            g_dComIfG_gameInfo.mInfo.getPlayer().player_return.mRoomId = warp_info.room_info.room_id[0];
            g_dComIfG_gameInfo.mInfo.getPlayer().player_return.mSpawnId = warp_info.spawn_info.spawn_id[0];
            break;
        }
        }
    }

    // temp fix for tp_sprintf warning
    char tmpbuf[32];

    tp_strcpy(tmpbuf, stage_types[stage_type_counter]);
    tp_sprintf(lines[WARP_TYPE_INDEX].value, " <%s>", tmpbuf);

    tp_strcpy(tmpbuf, warp_info.stage_info.stage_name);
    tp_sprintf(lines[WARP_STAGE_INDEX].value, " <%s>", tmpbuf);

    tp_strcpy(tmpbuf, warp_info.room_info.room_name);
    tp_sprintf(lines[WARP_ROOM_INDEX].value, " <%s>", tmpbuf);

    tp_sprintf(lines[WARP_SPAWN_INDEX].value, " <%d>", warp_info.spawn_info.spawn_id[0]);
    if (layer == DEFAULT_LAYER) {
        tp_sprintf(lines[WARP_LAYER_INDEX].value, " <default>");
    } else {
        tp_sprintf(lines[WARP_LAYER_INDEX].value, " <%d>", layer);
    }

    Utilities::move_cursor(cursor, LINES, 0, false, false, false, true);
    Utilities::render_lines(lines, cursor.y, LINES);
}