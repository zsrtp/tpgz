#pragma once
#include "menu.h"

#define MAX_WATCHES 10

enum MemoryType { u8, i8, u16, i16, u32, i32, f32, string };

enum MemoryColumns { WatchAddress, WatchX, WatchY, WatchHex, WatchType, WatchOffset };

struct MemoryWatch {
    uint32_t address = 0x80000000;
    float x = 400.0f;
    float y = 100.0f;
    bool hex = false;
    uint8_t type = string;
    uint16_t offset = 0x0000;
    uint32_t value;
    bool visible = false;
    bool line_selected = false;
    bool value_selected = false;
};

extern MemoryWatch g_watches[MAX_WATCHES];

class MemoryMenu : public Menu {
public:
    MemoryMenu() : Menu() {}
    static void draw();

    static Cursor cursor;
};

class WatchesMenu : public Menu {
public:
    WatchesMenu() : Menu() {}
    static void draw();
    static void drawMemoryLines();

    static Cursor cursor;
};