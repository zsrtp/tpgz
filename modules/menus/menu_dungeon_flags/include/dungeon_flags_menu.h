#pragma once
#include "menu.h"

struct DungeonFlagsData {
    bool init_once = false;
    bool l_mapFlag;
    bool l_compassFlag;
    bool l_bosskeyFlag;
    bool l_minibossFlag;
    bool l_bossFlag;
    int l_selDun;
    uint8_t l_keyNum;
};

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
    DungeonFlagsMenu(Cursor&, DungeonFlagsData&);
    virtual ~DungeonFlagsMenu();
    virtual void draw();

private:
    bool& init_once;

    bool& l_mapFlag;
    bool& l_compassFlag;
    bool& l_bosskeyFlag;
    bool& l_minibossFlag;
    bool& l_bossFlag;
    int& l_selDun;
    uint8_t& l_keyNum;

    Line lines[8];
};
