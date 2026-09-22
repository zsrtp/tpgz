#pragma once

#include "menus/menu.h"
#include "tools.h"

struct ToolsRngData {
    uint8_t l_rng_preset_idx;
};

enum ToolsRngIndex {
    FREEZE_RNG_INDEX,
    RANDOMIZE_INDEX,
    LOAD_PRESET_INDEX,
    PRESET_OPTIONS_INDEX,

    TOOLS_RNG_COUNT
};

extern ToolsRngData* toolsRngData;

class ToolsRngMenu : public Menu {
public:
    ToolsRngMenu(Cursor&);
    virtual ~ToolsRngMenu();
    virtual void draw();

private:
    Line lines[TOOLS_RNG_COUNT];
};

void store_frozen_rng_values(int r0, int r1, int r2);