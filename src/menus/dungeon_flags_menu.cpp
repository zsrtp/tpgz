#include "controller.h"
#include "font.h"
#include "libtp_c/include/msl_c/string.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
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
bool miniboss_flag;
bool boss_flag;

int select_dungeon_index = 0;
uint8_t key_num = 0;
uint8_t area_id;

Line lines[LINES] = {
    {"dungeon:", SELECT_DUNGEON_INDEX, "Selected dungeon flags", false, nullptr,
     MAX_DUNGEON_OPTIONS},
    {"small keys", SMALL_KEY_FLAG_INDEX, "Selected dungeon small keys", false, nullptr, 5},
    {"have map", MAP_FLAG_INDEX, "Give selected dungeon map", true, &map_flag},
    {"have compass", COMPASS_FLAG_INDEX, "Give selected dungeon compass", true, &compass_flag},
    {"have boss key", BOSS_KEY_FLAG_INDEX, "Give selected dungeon boss key", true, &boss_key_flag},
    {"miniboss dead", DEFEAT_MINIBOSS_FLAG_INDEX, "Selected dungeon miniboss is defeated", true,
     &miniboss_flag},
    {"boss dead", DEFEAT_BOSS_FLAG_INDEX, "Selected dungeon boss is defeated", true, &boss_flag},
    {"clear flags", CLEAR_DUNGEON_FLAGS_INDEX, "Clear all selected dungeon flags"}};

ListMember dungeon_options[MAX_DUNGEON_OPTIONS] = {
    "Forest Temple",     "Goron Mines",        "Lakebed Temple",
    "Arbiter's Grounds", "Snowpeak Ruins",     "Temple of Time",
    "City in the Sky",   "Palace of Twilight", "Hyrule Castle"};

bool getSaveDungeonItem(int32_t stage, int32_t flag) {
    return dSv_memBit_c__isDungeonItem(&dComIfGs_getSavedata().mSave[stage].mBit, flag);
}

void setSaveDungeonItem(int32_t stage, int32_t flag) {
    if (getSaveDungeonItem(stage, flag)) {
        dComIfGs_getSavedata().mSave[stage].mBit.offDungeonItem(flag);
    } else {
        dSv_memBit_c__onDungeonItem(&dComIfGs_getSavedata().mSave[stage].mBit, flag);
    }
}

uint8_t getSaveDungeonKeys(int32_t stage) {
    return dComIfGs_getSavedata().mSave[stage].mBit.getKeyNum();
}

void setSaveDungeonKeys(int32_t stage, uint8_t num) {
    dComIfGs_getSavedata().mSave[stage].mBit.setKeyNum(num);
}

void DungeonFlagsMenu::render() {
    if (button_is_pressed(BACK_BUTTON)) {
        init_once = false;
        MenuRendering::set_menu(MN_FLAGS_INDEX);
        return;
    }

    if (!init_once) {
        current_input = 0;
        init_once = true;
        key_num = getSaveDungeonKeys(area_id);
    }

    if (cursor.y == SELECT_DUNGEON_INDEX) {
        cursor.x = select_dungeon_index;
        Utilities::move_cursor(cursor, LINES, MAX_DUNGEON_OPTIONS, false, false, false, true);
        if (cursor.y == SELECT_DUNGEON_INDEX) {
            select_dungeon_index = cursor.x;
        }
        key_num = getSaveDungeonKeys(area_id);
    } else if (cursor.y == SMALL_KEY_FLAG_INDEX) {
        cursor.x = key_num;
        Utilities::move_cursor(cursor, LINES, 6, false, false, false, true);
        if (cursor.y == SMALL_KEY_FLAG_INDEX) {
            key_num = cursor.x;
            setSaveDungeonKeys(area_id, key_num);
            dComIfGs_getSave(g_dComIfG_gameInfo.info.mDan.mStageNo);
        }
    } else {
        Utilities::move_cursor(cursor, LINES, 2);
    }

    switch (select_dungeon_index) {
    case 0: {
        area_id = dSv_memory_c::FOREST_TEMPLE;
        break;
    }
    case 1: {
        area_id = dSv_memory_c::GORON_MINES;
        break;
    }
    case 2: {
        area_id = dSv_memory_c::LAKEBED;
        break;
    }
    case 3: {
        area_id = dSv_memory_c::ARBITERS;
        break;
    }
    case 4: {
        area_id = dSv_memory_c::SNOWPEAK_RUINS;
        break;
    }
    case 5: {
        area_id = dSv_memory_c::TEMPLE_OF_TIME;
        break;
    }
    case 6: {
        area_id = dSv_memory_c::CITY;
        break;
    }
    case 7: {
        area_id = dSv_memory_c::PALACE;
        break;
    }
    case 8: {
        area_id = dSv_memory_c::HYRULE_CASTLE;
        break;
    }
    }

    // update flags
    map_flag = getSaveDungeonItem(area_id, dSv_memBit_c::MAP);
    compass_flag = getSaveDungeonItem(area_id, dSv_memBit_c::COMPASS);
    boss_key_flag = getSaveDungeonItem(area_id, dSv_memBit_c::BOSS_KEY);
    miniboss_flag = getSaveDungeonItem(area_id, dSv_memBit_c::STAGE_BOSS_ENEMY_2);
    boss_flag = getSaveDungeonItem(area_id, dSv_memBit_c::STAGE_BOSS_ENEMY);

    if (current_input == SELECTION_BUTTON && a_held == false) {
        switch (cursor.y) {
        case MAP_FLAG_INDEX: {
            setSaveDungeonItem(area_id, dSv_memBit_c::MAP);
            break;
        }
        case COMPASS_FLAG_INDEX: {
            setSaveDungeonItem(area_id, dSv_memBit_c::COMPASS);
            break;
        }
        case BOSS_KEY_FLAG_INDEX: {
            setSaveDungeonItem(area_id, dSv_memBit_c::BOSS_KEY);
            break;
        }
        case DEFEAT_MINIBOSS_FLAG_INDEX: {
            setSaveDungeonItem(area_id, dSv_memBit_c::STAGE_BOSS_ENEMY_2);
            break;
        }
        case DEFEAT_BOSS_FLAG_INDEX: {
            setSaveDungeonItem(area_id, dSv_memBit_c::STAGE_BOSS_ENEMY);
            break;
        }
        case CLEAR_DUNGEON_FLAGS_INDEX: {
            tp_memset(&dComIfGs_getSavedata().mSave[area_id].mBit, 0, sizeof(dSv_memBit_c));
            key_num = 0;
            break;
        }
        }
        // copy current stage save flags over temp flags
        dComIfGs_getSave(g_dComIfG_gameInfo.info.mDan.mStageNo);
    }

    tp_sprintf(lines[SMALL_KEY_FLAG_INDEX].value, " <%d>", key_num);
    tp_sprintf(lines[SELECT_DUNGEON_INDEX].value, " <%s>",
               dungeon_options[select_dungeon_index].member);

    Utilities::render_lines(lines, cursor.y, LINES);
};
