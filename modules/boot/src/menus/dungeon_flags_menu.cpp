#include "libtp_c/include/msl_c/string.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "menus/flags_menu.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

#define MAX_DUNGEON_OPTIONS 9

KEEP_FUNC DungeonFlagsMenu::DungeonFlagsMenu()
    : Menu(), lines{
                  {"dungeon:", SELECT_DUNGEON_INDEX, "Selected dungeon flags", false, nullptr,
                   MAX_DUNGEON_OPTIONS},
                  {"small keys", SMALL_KEY_FLAG_INDEX, "Selected dungeon small keys", false,
                   nullptr, 5},
                  {"have map", MAP_FLAG_INDEX, "Give selected dungeon map", true, &l_mapFlag},
                  {"have compass", COMPASS_FLAG_INDEX, "Give selected dungeon compass", true,
                   &l_compassFlag},
                  {"have boss key", BOSS_KEY_FLAG_INDEX, "Give selected dungeon boss key", true,
                   &l_bosskeyFlag},
                  {"miniboss dead", DEFEAT_MINIBOSS_FLAG_INDEX,
                   "Selected dungeon miniboss is defeated", true, &l_minibossFlag},
                  {"boss dead", DEFEAT_BOSS_FLAG_INDEX, "Selected dungeon boss is defeated", true,
                   &l_bossFlag},
                  {"clear flags", CLEAR_DUNGEON_FLAGS_INDEX, "Clear all selected dungeon flags"},
              } {}

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

void DungeonFlagsMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        init_once = false;
        g_menuMgr->pop();
        return;
    }

    uint8_t area_id = 0;
    switch (l_selDun) {
    case 0:
        area_id = dSv_memory_c::FOREST_TEMPLE;
        break;
    case 1:
        area_id = dSv_memory_c::GORON_MINES;
        break;
    case 2:
        area_id = dSv_memory_c::LAKEBED;
        break;
    case 3:
        area_id = dSv_memory_c::ARBITERS;
        break;
    case 4:
        area_id = dSv_memory_c::SNOWPEAK_RUINS;
        break;
    case 5:
        area_id = dSv_memory_c::TEMPLE_OF_TIME;
        break;
    case 6:
        area_id = dSv_memory_c::CITY;
        break;
    case 7:
        area_id = dSv_memory_c::PALACE;
        break;
    case 8:
        area_id = dSv_memory_c::HYRULE_CASTLE;
        break;
    }

    if (!init_once) {
        l_keyNum = getSaveDungeonKeys(area_id);
        init_once = true;
    }

    switch (cursor.y) {
    case SELECT_DUNGEON_INDEX:
        cursor.x = l_selDun;
        cursor.move(MAX_DUNGEON_OPTIONS, MENU_LINE_NUM);

        if (cursor.y == SELECT_DUNGEON_INDEX) {
            l_selDun = cursor.x;
        }
        l_keyNum = getSaveDungeonKeys(area_id);
        break;
    case SMALL_KEY_FLAG_INDEX:
        cursor.x = l_keyNum;
        cursor.move(6, MENU_LINE_NUM);

        if (cursor.y == SMALL_KEY_FLAG_INDEX) {
            l_keyNum = cursor.x;
            setSaveDungeonKeys(area_id, l_keyNum);
            dComIfGs_getSave(g_dComIfG_gameInfo.info.mDan.mStageNo);
        }
        break;
    default:
        cursor.move(0, MENU_LINE_NUM);
        break;
    }

    // update flags
    l_mapFlag = getSaveDungeonItem(area_id, dSv_memBit_c::MAP);
    l_compassFlag = getSaveDungeonItem(area_id, dSv_memBit_c::COMPASS);
    l_bosskeyFlag = getSaveDungeonItem(area_id, dSv_memBit_c::BOSS_KEY);
    l_minibossFlag = getSaveDungeonItem(area_id, dSv_memBit_c::STAGE_BOSS_ENEMY_2);
    l_bossFlag = getSaveDungeonItem(area_id, dSv_memBit_c::STAGE_BOSS_ENEMY);

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        switch (cursor.y) {
        case MAP_FLAG_INDEX:
            setSaveDungeonItem(area_id, dSv_memBit_c::MAP);
            break;
        case COMPASS_FLAG_INDEX:
            setSaveDungeonItem(area_id, dSv_memBit_c::COMPASS);
            break;
        case BOSS_KEY_FLAG_INDEX:
            setSaveDungeonItem(area_id, dSv_memBit_c::BOSS_KEY);
            break;
        case DEFEAT_MINIBOSS_FLAG_INDEX:
            setSaveDungeonItem(area_id, dSv_memBit_c::STAGE_BOSS_ENEMY_2);
            break;
        case DEFEAT_BOSS_FLAG_INDEX:
            setSaveDungeonItem(area_id, dSv_memBit_c::STAGE_BOSS_ENEMY);
            break;
        case CLEAR_DUNGEON_FLAGS_INDEX:
            memset(&dComIfGs_getSavedata().mSave[area_id].mBit, 0, sizeof(dSv_memBit_c));
            l_keyNum = 0;
            break;
        }
        // copy current stage save flags over temp flags
        dComIfGs_getSave(g_dComIfG_gameInfo.info.mDan.mStageNo);
    }

    ListMember dun_opt[MAX_DUNGEON_OPTIONS] = {
        "Forest Temple",     "Goron Mines",        "Lakebed Temple",
        "Arbiter's Grounds", "Snowpeak Ruins",     "Temple of Time",
        "City in the Sky",   "Palace of Twilight", "Hyrule Castle",
    };

    sprintf(lines[SMALL_KEY_FLAG_INDEX].value, " <%d>", l_keyNum);
    sprintf(lines[SELECT_DUNGEON_INDEX].value, " <%s>", dun_opt[l_selDun].member);

    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
