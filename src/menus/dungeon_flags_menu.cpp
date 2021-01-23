#include "controller.h"
#include "font.h"
#include "libtp_c/include/flag.h"
#include "libtp_c/include/system.h"
#include "libtp_c/include/tp.h"
#include "menus/flags_menu.h"
#include "utils/cursor.h"
#include "utils/lines.h"

#include <stdint.h>

#define LINES 8
#define MAX_DUNGEON_OPTIONS 9

static Cursor cursor = {0, 0};
bool init_once = false;

bool map_flag;
bool compass_flag;
bool boss_key_flag;
bool small_keys_flag;
bool miniboss_flag;
bool boss_flag;

int select_dungeon_index = 0;
uint8_t area_id;
Flags::GlobalFlags* dungeon_node;

Line lines[LINES] = {
    {"dungeon:", SELECT_DUNGEON_INDEX, "Selected dungeon flags", false, nullptr,
     MAX_DUNGEON_OPTIONS},
    {"have map", MAP_FLAG_INDEX, "Give selected dungeon map", true, &map_flag},
    {"have compass", COMPASS_FLAG_INDEX, "Give selected dungeon compass", true, &compass_flag},
    {"have boss key", BOSS_KEY_FLAG_INDEX, "Give selected dungeon boss key", true, &boss_key_flag},
    {"have small keys", SMALL_KEY_FLAG_INDEX, "Give selected dungeon small keys", true,
     &small_keys_flag},
    {"miniboss dead", DEFEAT_MINIBOSS_FLAG_INDEX, "Selected dungeon miniboss is defeated", true,
     &miniboss_flag},
    {"boss dead", DEFEAT_BOSS_FLAG_INDEX, "Selected dungeon boss is defeated", true, &boss_flag},
    {"clear flags", CLEAR_DUNGEON_FLAGS_INDEX, "Clear all selected dungeon flags"}};

void copyGlobalFlags(uint8_t id) {
    if (tp_gameInfo.area_id == id) {
        for (uint8_t j = 0; j < 0x20; j++) {
            tp_gameInfo.temp_flags.flags[j] = dungeon_node->flags[j];
        }
    }
}

void DungeonFlagsMenu::render() {
    if (button_is_pressed(Controller::B)) {
        init_once = false;
        MenuRendering::set_menu(MN_FLAGS_INDEX);
        return;
    }

    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

    ListMember dungeon_options[MAX_DUNGEON_OPTIONS] = {
        "Forest Temple",     "Goron Mines",        "Lakebed Temple",
        "Arbiter's Grounds", "Snowpeak Ruins",     "Temple of Time",
        "City in the Sky",   "Palace of Twilight", "Hyrule Castle"};

    if (cursor.y == SELECT_DUNGEON_INDEX) {
        cursor.x = select_dungeon_index;
        Utilities::move_cursor(cursor, LINES, MAX_DUNGEON_OPTIONS, false, false, false, true);
        if (cursor.y == SELECT_DUNGEON_INDEX) {
            select_dungeon_index = cursor.x;
        }
    } else {
        Utilities::move_cursor(cursor, LINES);
    }

    switch (select_dungeon_index) {
    case 0: {
        dungeon_node = &tp_gameInfo.dungeon_flags.forest_temple_flags;
        area_id = 0x10;
        break;
    }
    case 1: {
        dungeon_node = &tp_gameInfo.dungeon_flags.goron_mines_flags;
        area_id = 0x11;
        break;
    }
    case 2: {
        dungeon_node = &tp_gameInfo.dungeon_flags.lakebed_flags;
        area_id = 0x12;
        break;
    }
    case 3: {
        dungeon_node = &tp_gameInfo.dungeon_flags.arbiters_flags;
        area_id = 0x13;
        break;
    }
    case 4: {
        dungeon_node = &tp_gameInfo.dungeon_flags.snowpeak_ruins_flags;
        area_id = 0x14;
        break;
    }
    case 5: {
        dungeon_node = &tp_gameInfo.dungeon_flags.temple_of_time_flags;
        area_id = 0x15;
        break;
    }
    case 6: {
        dungeon_node = &tp_gameInfo.dungeon_flags.cits_flags;
        area_id = 0x16;
        break;
    }
    case 7: {
        dungeon_node = &tp_gameInfo.dungeon_flags.palace_flags;
        area_id = 0x17;
        break;
    }
    case 8: {
        dungeon_node = &tp_gameInfo.dungeon_flags.hyrule_castle_flags;
        area_id = 0x18;
        break;
    }
    }

    // update flags
    map_flag = (dungeon_node->flags[29] & (1 << 0));
    compass_flag = (dungeon_node->flags[29] & (1 << 1));
    boss_key_flag = (dungeon_node->flags[29] & (1 << 2));
    small_keys_flag = dungeon_node->flags[28];
    miniboss_flag = (dungeon_node->flags[29] & (1 << 7));
    boss_flag = (dungeon_node->flags[29] & (1 << 3));

    if (current_input == Controller::Pad::A && a_held == false) {
        switch (cursor.y) {
        case MAP_FLAG_INDEX: {
            dungeon_node->flags[29] ^= 1 << 0;
            copyGlobalFlags(area_id);
            break;
        }
        case COMPASS_FLAG_INDEX: {
            dungeon_node->flags[29] ^= 1 << 1;
            copyGlobalFlags(area_id);
            break;
        }
        case BOSS_KEY_FLAG_INDEX: {
            dungeon_node->flags[29] ^= 1 << 2;
            copyGlobalFlags(area_id);
            break;
        }
        case SMALL_KEY_FLAG_INDEX: {
            if (small_keys_flag) {
                dungeon_node->flags[28] = 0x00;
            } else {
                dungeon_node->flags[28] = 0x05;
            }
            copyGlobalFlags(area_id);
            break;
        }
        case DEFEAT_MINIBOSS_FLAG_INDEX: {
            dungeon_node->flags[29] ^= 1 << 7;
            copyGlobalFlags(area_id);
            break;
        }
        case DEFEAT_BOSS_FLAG_INDEX: {
            dungeon_node->flags[29] ^= 1 << 3;
            copyGlobalFlags(area_id);
            break;
        }
        case CLEAR_DUNGEON_FLAGS_INDEX: {
            for (int i = 0; i < 0x20; i++) {
                dungeon_node->flags[i] = 0;
            }
            copyGlobalFlags(area_id);
            break;
        }
        }
    }

    tp_sprintf(lines[SELECT_DUNGEON_INDEX].value, " <%s>",
               dungeon_options[select_dungeon_index].member);

    Utilities::render_lines(lines, cursor.y, LINES);
};
