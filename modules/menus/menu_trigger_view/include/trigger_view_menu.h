#pragma once

#include "menu.h"

class TriggerViewMenu : public Menu {
public:
    TriggerViewMenu(Cursor&);
    virtual ~TriggerViewMenu();
    virtual void draw();

private:
    Line lines[4];
};
