#pragma once

#include "menus/menu.h"
#include "tools.h"

#ifdef GCN_PLATFORM
#define STORE_POSITION_TEXT "D-PAD up + R"
#define LOAD_POSITION_TEXT "D-PAD down + R"
#define MOVE_LINK_TEXT "L+R+Y"
#endif

#ifdef WII_PLATFORM
#define STORE_POSITION_TEXT "Z+C+1"
#define LOAD_POSITION_TEXT "Z+C+2"
#define MOVE_LINK_TEXT "Z+C+B+Plus"
#endif

enum ToolsLinkIndex {
    FAST_BONK_INDEX,
    FAST_MOVEMENT_INDEX,
    LINK_DEBUG_INDEX,
    LINK_STAGE_INFO_INDEX,
    SAND_INDEX,
    TELEPORT_INDEX,
    DISPLACEMENT_INDEX,
    MOVE_LINK_INDEX,
    TUNIC_COLOR_INDEX,

    TOOLS_LINK_COUNT
};

struct ToolsLinkData {
    uint8_t l_tunicCol_idx;
};

class ToolsLinkMenu : public Menu {
public:
    ToolsLinkMenu(Cursor&, ToolsLinkData&);
    virtual ~ToolsLinkMenu();
    virtual void draw();

private:
    uint8_t& l_tunicCol_idx;

    Line lines[TOOLS_LINK_COUNT];
};