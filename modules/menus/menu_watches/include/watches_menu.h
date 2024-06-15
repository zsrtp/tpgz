#pragma once
#include "menus/menu.h"
#include "utils/memory.h"

#define MAX_WATCHES 50

struct WatchesData {
    uint8_t button_held_counter = 0;
    float l_scrollSpeed = 1.0f;
    uint8_t l_addrIdx = 3;
    uint8_t l_offsetIdx = 2;
};

class WatchesMenu : public Menu {
public:
    WatchesMenu(Cursor&, WatchesData&);
    virtual ~WatchesMenu();
    virtual void draw();
    void drawMemoryLines(MemoryWatch*, size_t);

private:
    uint8_t& button_held_counter;
    float& l_scrollSpeed;
    uint8_t& l_addrIdx;
    uint8_t& l_offsetIdx;
};
