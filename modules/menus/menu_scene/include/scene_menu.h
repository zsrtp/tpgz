#pragma once

#include "menu.h"
#include "scene.h"

class SceneMenu : public Menu {
public:
    SceneMenu(Cursor&);
    virtual ~SceneMenu();
    virtual void draw();

    Cursor& m_cursor;

private:
    Line lines[11];
};