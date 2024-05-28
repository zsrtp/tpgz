#pragma once

#include "menu.h"
#include "scene.h"

class SceneMenu : public Menu {
public:
    SceneMenu(Cursor&);
    virtual ~SceneMenu();
    virtual void draw();

private:
    Line lines[SCENE_MENU_MAX];
};