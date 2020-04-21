#include "font.h"
#include "menu.h"
#include "controller.h"
#include "utils.h"

#define MAX_WATCHES 10
#define WATCH_COLUMNS 6

struct Cursor {
    int y = 0;
    int x = 0;
};

Cursor cursor;

bool memory_visible;
bool init_once = false;

MemoryWatch Watches[MAX_WATCHES] = {
    {0x80000000, 100.0f, 200.0f}};

void render_memory_lines(Font& font, MemoryWatch Watches[MAX_WATCHES], Cursor cursor) {
    font.renderChars("Address     X    Y    Hex   Type  Offset", 25.0f, 60.0f, 0xFFFFFFFF);
    if (g_drop_shadows) {
        font.renderChars("Address     X    Y    Hex   Type  Offset", 25.0f + 2.0f, 60.0 + 2.0f, DROP_SHADOWS_RGBA);
    };
    for (int i = 0; i < MAX_WATCHES; i++) {
        char line[43];
        char type[5];
        switch (Watches[i].type) {
            case u8: {
                sprintf(type, "u8 ");
                break;
            }
            case u16: {
                sprintf(type, "u16");
                break;
            }
            case u32: {
                sprintf(type, "u32");
                break;
            }
            case i8: {
                sprintf(type, "i8 ");
                break;
            }
            case i16: {
                sprintf(type, "i16");
                break;
            }
            case i32: {
                sprintf(type, "i32");
                break;
            }

            case f32: {
                sprintf(type, "f32");
                break;
            }
            case string: {
                sprintf(type, "str");
            }
        }
        sprintf(line, "0x%08X %.0f  %.0f  %s   %s  0x%04X  %s",
                Watches[i].address,
                Watches[i].x,
                Watches[i].y,
                Watches[i].hex ? "true " : "false",
                type,
                Watches[i].offset,
                Watches[i].visible ? "[X]" : "[] ");
        font.renderChars(line, 25.0f, (80.0f + (i * 20.0f)), (cursor.x == i ? CURSOR_RGBA : 0xFFFFFFFF));
        if (g_drop_shadows) {
            font.renderChars(line, 25.0f + 2.0f, (80.0f + (i * 20.0f)) + 2.0f, DROP_SHADOWS_RGBA);
        };
    }
}

void move_cursor(Cursor &cursor) {
    if (button_is_pressed(Controller::DPAD_UP)) {
        if (cursor.x > 0) {
        cursor.x -= 1;
        }
        else {
            cursor.x = MAX_WATCHES - 1;
        }
    }
    if (button_is_pressed(Controller::DPAD_DOWN)) {
        if (cursor.x < MAX_WATCHES - 1) {
        cursor.x += 1;
        }
        else {
            cursor.x = 0;
        }
    }
    if (button_is_pressed(Controller::DPAD_RIGHT)) {
        if (cursor.y < WATCH_COLUMNS) {
        cursor.y += 1;
        }
        else {
            cursor.y = 0;
        }
    }
    if (button_is_pressed(Controller::DPAD_LEFT)) {
        if (cursor.y > 0) {
        cursor.y -= 1;
        }
        else {
            cursor.y = WATCH_COLUMNS - 1;
        }
    }
}

void MemoryMenu::render(Font& font) {
    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

    if (button_is_pressed(Controller::B)) {
        memory_visible = false;
        mm_visible = true;
        return;
    };

    if (button_is_pressed(Controller::A)) {
        // finish
    }

    if (button_is_pressed(Controller::Z)) {
        Watches[cursor.x].visible = !Watches[cursor.x].visible;
    }

    move_cursor(cursor);
    render_memory_lines(font, Watches, cursor);
};
