#pragma once

#include "menu.h"
#include "tools.h"

struct ToolsData {
    uint8_t l_tunicCol_idx;
};

void GZ_applyCheats();

class ToolsMenu : public Menu {
public:
    ToolsMenu(Cursor&, ToolsData&);
    virtual ~ToolsMenu();
    virtual void draw();

private:
    uint8_t& l_tunicCol_idx;

    Line lines[TOOLS_COUNT];
};