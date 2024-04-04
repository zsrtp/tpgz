#pragma once

#include "menu.h"
#include "trigger_view.h"

class TriggerViewMenu : public Menu {
public:
    TriggerViewMenu(Cursor&);
    virtual ~TriggerViewMenu();
    virtual void draw();

private:
    Line lines[TRIGGER_VIEW_MAX];
};
