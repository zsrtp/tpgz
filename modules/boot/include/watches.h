#pragma once

#include <cstdint>

#define MAX_WATCHES 10

enum MemoryType { MEM_TYPE_U8, MEM_TYPE_S8, MEM_TYPE_U16, MEM_TYPE_S16, MEM_TYPE_U32, MEM_TYPE_S32, MEM_TYPE_F32, MEM_TYPE_STR };

enum MemoryColumns { WatchAddress, WatchX, WatchY, WatchHex, WatchType, WatchOffset };

struct MemoryWatch {
    uint32_t address = 0x80000000;
    float x = 400.0f;
    float y = 100.0f;
    bool hex = false;
    uint8_t type = MEM_TYPE_STR;
    uint16_t offset = 0x0000;
    uint32_t value;
    bool visible = false;
    bool line_selected = false;
    bool value_selected = false;
};

extern MemoryWatch g_watches[MAX_WATCHES];
