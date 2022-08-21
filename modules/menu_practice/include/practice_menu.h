#pragma once
#include "menu.h"
#include "practice.h"
#include "gz_flags.h"

class PracticeMenu : public Menu {
public:
    PracticeMenu(Cursor&);
    virtual ~PracticeMenu();
    virtual void draw();

    Cursor& m_cursor;

private:
    Line lines[3];
};