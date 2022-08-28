#pragma once
#include "menu.h"

enum FlagsIndex {
    GENERAL_FLAGS_INDEX,
    DUNGEON_FLAGS_INDEX,
    PORTAL_FLAGS_INDEX,
    FLAG_RECORDS_INDEX,
    FLAG_LOG_INDEX
};

class FlagsMenu : public Menu {
public:
    FlagsMenu(Cursor&);
    virtual ~FlagsMenu();
    virtual void draw();

private:
    Line lines[5];
};
