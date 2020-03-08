#pragma once
#include <cstdint>

struct LineWriter {
    Line line;  // referenced before defined? might be a problem?
    int position;

    // this struct has an Impl at the very bottom but i have no clue how to convert it
};

struct Line {
    char text[128];
    bool selected;

    void New();
    void clear(Line line);
    LineWriter begin(Line line);
    LineWriter write_at(Line line, int pos);
    int len(Line line);
    bool is_empty(Line line);
    void push_str(Line line, const char* string);
};

struct Lines {
    Line line[32];
};

class Menu {
   public:
    float x;
    float y;
    float offset;
    uint32_t selected_color;
    uint32_t color;
    int selected_word;
    int selected_char;
    Lines lines;

    Menu New(float x, float y);
    Lines lines(Menu menu);
    Line line(Menu menu, int idx);
    void clear(Menu menu);
    void draw(Menu menu);
    Menu Default();
};