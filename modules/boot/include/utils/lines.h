#pragma once
#include "font.h"
#include <cstdio>

#define MAX_RENDER_LINES 15

#define MAX_LIST_MEMBER_LENGTH 40
#define MAX_LIST_ITEMS 20
#define MAX_LINE_LENGTH 50
#define MAX_DESCRIPTION_LENGTH 100

extern uint32_t g_cursorColor;

struct ListMember {
    char member[MAX_LIST_MEMBER_LENGTH];
};

struct Line {
    char line[50];
    const uint32_t idx;
    char description[MAX_DESCRIPTION_LENGTH];
    bool toggleable = false;
    bool* activation_flag;
    uint8_t max_y_cursor_options;
    char value[sizeof(Line::line)] = {0};

    template <typename... Args>
    void printf(const char* fmt, Args... args) {
        snprintf(value, sizeof(value), fmt, args...);
    }
};

float maxF(float a, float b);
void menu_anim(int idx);
void GZ_drawMenuLines(Line input_lines[], uint32_t cursor, uint32_t LINES);