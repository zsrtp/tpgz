#pragma once

#include "menu.h"
#include "tools.h"

struct ToolsData {
    Cursor cursor;
    uint8_t l_tunicCol_idx;
};

void GZ_applyCheats();

class ToolsMenu : public Menu {
public:
    ToolsMenu(ToolsData&);
    virtual ~ToolsMenu();
    virtual void draw();

    Cursor& m_cursor;

private:
    uint8_t& l_tunicCol_idx;

    Line lines[TOOLS_COUNT];
};