#pragma once

#include "menu.h"
#include "tools.h"

void GZ_applyCheats();

class ToolsMenu : public Menu {
public:
    ToolsMenu(Cursor&);
    virtual ~ToolsMenu();
    virtual void draw();

    Cursor& m_cursor;

private:
    uint8_t l_tunicCol_idx;

    Line lines[TOOLS_COUNT];
};