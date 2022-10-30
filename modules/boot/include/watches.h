#pragma once

#include <cstdint>

#define MAX_WATCHES 10

enum MemoryType { 
    mem_u8, 
    mem_i8, 
    mem_u16, 
    mem_i16, 
    mem_u32, 
    mem_i32, 
    mem_f32, 
    mem_string 
};

enum MemoryColumns { WatchAddress, WatchX, WatchY, WatchHex, WatchType, WatchOffset };

struct MemoryWatch {
    uint32_t address = 0x80000000;
    float x = 400.0f;
    float y = 100.0f;
    bool hex = false;
    uint8_t type = mem_string;
    uint16_t offset = 0x0000;
    uint32_t value;
    bool visible = false;
    bool line_selected = false;
    bool value_selected = false;
};

extern MemoryWatch g_watches[MAX_WATCHES];
