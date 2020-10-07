#include "font.h"
#include "menus/warping_menu.h"
#include "controller.h"
#include "utils/cursor.hpp"
#include "utils/lines.hpp"
#include "libtp_c/include/tp.h"
#include "commands.h"
#include "fs.h"
#include <stdio.h>
#include "libtp_c/include/system.h"

#define LINES 6
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
bool file;
int stage_type_counter = 0;
signed long stage_counter = 0;
signed long room_counter = 0;
signed long spawn_counter = 0;
char file_path[89];
WarpInfo warp_info;

enum {
    DUNGEON,
    OVERWORLD,
    INTERIOR,
    CAVE,
    SPECIAL
};

char stage_types[5][10] = {
    "dungeon",
    "overworld",
    "interior",
    "cave",
    "special"};

Line lines[LINES] = {
    {"type:", WARP_TYPE_INDEX, "The type of stage", false},
    {"stage:", WARP_STAGE_INDEX, "Current stage name", false},
    {"room:", WARP_ROOM_INDEX, "Current room name", false},
    {"spawn:", WARP_SPAWN_INDEX, "Current spawn number", false},
    {"layer:", WARP_LAYER_INDEX, "Current layer number", false},
    {"warp", WARP_BUTTON_INDEX, "Trigger warp", false},
};

void load_previous_info(void* buffer, signed long& counter, signed long length, char max_num, int offset) {
    if (counter < 0) {
        counter = (max_num * offset) - offset;
    }
    loadFile(file_path, buffer, length, counter);
}

void load_next_info(void* buffer, signed long& counter, signed long length, char max_num, int offset) {
    if (counter == (offset * max_num)) {
        counter = 0;
    }
    loadFile(file_path, buffer, length, counter);
}

void set_stage_path(int current_stage_type) {
    switch (current_stage_type) {
        case DUNGEON: {
            strcpy(file_path, "tpgz/stage_info/dungeon.bin");
            break;
        }
        case OVERWORLD: {
            strcpy(file_path, "tpgz/stage_info/overworld.bin");
            break;
        }
        case INTERIOR: {
            strcpy(file_path, "tpgz/stage_info/interior.bin");
            break;
        }
        case CAVE: {
            strcpy(file_path, "tpgz/stage_info/cave.bin");
            break;
        }
        case SPECIAL: {
            strcpy(file_path, "tpgz/stage_info/special.bin");
            break;
        }
    }
}

void load_previous_stage_info() {
    set_stage_path(stage_type_counter);
    stage_counter -= STAGE_OFFSET;
    load_previous_info(&warp_info.stage_info, stage_counter, STAGE_READ_LENGTH, warp_info.stage_info.num_stages, STAGE_OFFSET);
}

void load_previous_room_info() {
    sprintf(file_path, "tpgz/stage_info/%s/rooms.bin", warp_info.stage_info.stage_id);
    room_counter -= ROOM_OFFSET;
    load_previous_info(&warp_info.room_info, room_counter, ROOM_READ_LENGTH, warp_info.room_info.num_rooms, ROOM_OFFSET);
}

void load_next_stage_info() {
    set_stage_path(stage_type_counter);
    stage_counter += STAGE_OFFSET;
    load_next_info(&warp_info.stage_info, stage_counter, STAGE_READ_LENGTH, warp_info.stage_info.num_stages, STAGE_OFFSET);
}

void load_next_room_info() {
    sprintf(file_path, "tpgz/stage_info/%s/rooms.bin", warp_info.stage_info.stage_id);
    room_counter += ROOM_OFFSET;
    load_next_info(&warp_info.room_info, room_counter, ROOM_READ_LENGTH, warp_info.room_info.num_rooms, ROOM_OFFSET);
}

void load_next_spawn_info() {
    sprintf(file_path, "tpgz/stage_info/%s/%02d/spawns.bin", warp_info.stage_info.stage_id, (int)warp_info.room_info.room_id[0]);
    spawn_counter += SPAWN_OFFSET;
    load_next_info(&warp_info.spawn_info, spawn_counter, SPAWN_READ_LENGTH, warp_info.spawn_info.num_spawns, SPAWN_OFFSET);
}

void load_previous_spawn_info() {
    sprintf(file_path, "tpgz/stage_info/%s/%02d/spawns.bin", warp_info.stage_info.stage_id, (int)warp_info.room_info.room_id[0]);
    spawn_counter -= SPAWN_OFFSET;
    load_previous_info(&warp_info.spawn_info, spawn_counter, SPAWN_READ_LENGTH, warp_info.spawn_info.num_spawns, SPAWN_OFFSET);
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

void WarpingMenu::render(Font& font) {
    if (button_is_pressed(Controller::B)) {
        init_once = false;
		MenuRendering::set_menu(MN_MAIN_MENU_INDEX);
        return;
    };

    if (!init_once) {
        current_input = 0;
        load_default_stage();
        load_default_room();
        load_default_spawn();
        init_once = true;
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

    if (current_input == 256 && a_held == false) {
        switch (cursor.y) {
            case WARP_BUTTON_INDEX: {
                memcpy(&tp_gameInfo.warp.entrance.stage, &warp_info.stage_info.stage_id, 8);
                tp_gameInfo.warp.entrance.room = warp_info.room_info.room_id[0];
                tp_gameInfo.warp.entrance.spawn = warp_info.spawn_info.spawn_id[0];
                tp_gameInfo.warp.entrance.state = layer;
                init_once = false;
		        MenuRendering::set_menu(MN_NONE_INDEX);
                tp_gameInfo.loading_animation = 13;  // instant load
                tp_gameInfo.warp.enabled = true;
                break;
            }
        }
    }

    // temp fix for sprintf warning
    char tmpbuf[32];

    strcpy(tmpbuf, stage_types[stage_type_counter]);
    sprintf(lines[WARP_TYPE_INDEX].line, "type: <%s>", tmpbuf);

    strcpy(tmpbuf, warp_info.stage_info.stage_name);
    sprintf(lines[WARP_STAGE_INDEX].line, "stage: <%s>", tmpbuf);

    strcpy(tmpbuf, warp_info.room_info.room_name);
    sprintf(lines[WARP_ROOM_INDEX].line, "room: <%s>", tmpbuf);

    sprintf(lines[WARP_SPAWN_INDEX].line, "spawn: <%d>", warp_info.spawn_info.spawn_id[0]);
    if (layer == DEFAULT_LAYER) {
        sprintf(lines[WARP_LAYER_INDEX].line, "layer: <default>");
    } else {
        sprintf(lines[WARP_LAYER_INDEX].line, "layer: <%d>", layer);
    }

    Utilities::move_cursor(cursor, LINES);
    Utilities::render_lines(font, lines, cursor.y, LINES);
}