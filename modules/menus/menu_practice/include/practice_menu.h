#pragma once
#include "menu.h"
#include "practice.h"
#include "gz_flags.h"

#define PRACTICE_MENU_NUM 5

class PracticeMenu : public Menu {
public:
    PracticeMenu(Cursor&);
    virtual ~PracticeMenu();
    virtual void draw();

private:
    Line lines[PRACTICE_MENU_NUM];
};