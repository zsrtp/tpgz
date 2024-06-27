#pragma once

#include "menus/menu.h"
#include "features/projection_view/include/projection_view.h"

class ProjectionViewMenu : public Menu {
public:
    ProjectionViewMenu(Cursor&);
    virtual ~ProjectionViewMenu();
    virtual void draw();

private:
    Line lines[PROJECTION_VIEW_MAX];
};