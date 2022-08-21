#pragma once
#include "menu.h"

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

class DungeonFlagsMenu : public Menu {
public:
    DungeonFlagsMenu();
    virtual void draw();

    Cursor cursor;

private:
    bool init_once = false;

    bool l_mapFlag;
    bool l_compassFlag;
    bool l_bosskeyFlag;
    bool l_minibossFlag;
    bool l_bossFlag;
    int l_selDun;
    uint8_t l_keyNum;

    Line lines[8];
};
