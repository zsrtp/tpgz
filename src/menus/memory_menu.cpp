#include "font.h"
#include "menu.h"
#include "controller.h"
#include "utils/cursor.hpp"
#include "utils/lines.hpp"
#include <stdio.h>

#define MAX_WATCHES 10
#define WATCH_COLUMNS 6

Cursor cursor;

bool memory_visible;
bool init_once = false;

MemoryWatch Watches[MAX_WATCHES] = {
    {0x80000000, 100.0f, 200.0f}};

void render_memory_lines(Font& font, MemoryWatch Watches[MAX_WATCHES], Cursor cursor) {
    font.gz_renderChars("Address     X   Y   Hex Type Offset Visible", 25.0f, 60.0f, 0xFFFFFFFF, g_drop_shadows);
    for (int i = 0; i < MAX_WATCHES; i++) {
        char watch_line[40];
        char watch_address[11];
        char watch_x[4];
        char watch_y[4];
        char watch_hex[6];
        char watch_type[4];
        char watch_offset[7];
        char watch_visible[4];

#define WATCH_ADDRESS_X_OFFSET 25.0f
#define WATCH_X_POS_X_OFFSET 133.0f
#define WATCH_Y_POS_X_OFFSET 171.0f
#define WATCH_HEX_X_OFFSET 208.5f
#define WATCH_TYPE_X_OFFSET 260.5f
#define WATCH_OFFSET_X_OFFSET 294.5f
#define WATCH_VISIBLE_X_OFFSET 364.0f
#define LINE_Y_OFFSET (80.0f + (i * 20.0f))
#define WHITE_RGBA 0xFFFFFFFF

        sprintf(watch_address, "0x%08X", Watches[i].address);
        sprintf(watch_x, "%.0f", Watches[i].x);
        sprintf(watch_y, "%.0f", Watches[i].y);
        sprintf(watch_hex, "%s", Watches[i].hex ? "true " : "false");
        switch (Watches[i].type) {
            case u8: {
                sprintf(watch_type, "u8 ");
                break;
            }
            case u16: {
                sprintf(watch_type, "u16");
                break;
            }
            case u32: {
                sprintf(watch_type, "u32");
                break;
            }
            case i8: {
                sprintf(watch_type, "i8 ");
                break;
            }
            case i16: {
                sprintf(watch_type, "i16");
                break;
            }
            case i32: {
                sprintf(watch_type, "i32");
                break;
            }

            case f32: {
                sprintf(watch_type, "f32");
                break;
            }
            case string: {
                sprintf(watch_type, "str");
            }
        }
        sprintf(watch_offset, "0x%04X", Watches[i].offset);
        sprintf(watch_visible, "%s", Watches[i].visible ? "[X]" : "[ ]");

        if (Watches[i].line_selected) {
            switch (cursor.x) {
                case WatchAddress: {
                    font.gz_renderChars(watch_address, WATCH_ADDRESS_X_OFFSET, LINE_Y_OFFSET, CURSOR_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_x, WATCH_X_POS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_y, WATCH_Y_POS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_hex, WATCH_HEX_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_type, WATCH_TYPE_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_offset, WATCH_OFFSET_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_visible, WATCH_VISIBLE_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    break;
                }
                case WatchX: {
                    font.gz_renderChars(watch_address, WATCH_ADDRESS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_x, WATCH_X_POS_X_OFFSET, LINE_Y_OFFSET, CURSOR_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_y, WATCH_Y_POS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_hex, WATCH_HEX_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_type, WATCH_TYPE_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_offset, WATCH_OFFSET_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_visible, WATCH_VISIBLE_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    break;
                }
                case WatchY: {
                    font.gz_renderChars(watch_address, WATCH_ADDRESS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_x, WATCH_X_POS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_y, WATCH_Y_POS_X_OFFSET, LINE_Y_OFFSET, CURSOR_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_hex, WATCH_HEX_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_type, WATCH_TYPE_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_offset, WATCH_OFFSET_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_visible, WATCH_VISIBLE_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    break;
                }
                case WatchHex: {
                    font.gz_renderChars(watch_address, WATCH_ADDRESS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_x, WATCH_X_POS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_y, WATCH_Y_POS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_hex, WATCH_HEX_X_OFFSET, LINE_Y_OFFSET, CURSOR_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_type, WATCH_TYPE_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_offset, WATCH_OFFSET_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_visible, WATCH_VISIBLE_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    break;
                }
                case WatchType: {
                    font.gz_renderChars(watch_address, WATCH_ADDRESS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_x, WATCH_X_POS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_y, WATCH_Y_POS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_hex, WATCH_HEX_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_type, WATCH_TYPE_X_OFFSET, LINE_Y_OFFSET, CURSOR_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_offset, WATCH_OFFSET_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_visible, WATCH_VISIBLE_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    break;
                }
                case WatchOffset: {
                    font.gz_renderChars(watch_address, WATCH_ADDRESS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_x, WATCH_X_POS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_y, WATCH_Y_POS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_hex, WATCH_HEX_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_type, WATCH_TYPE_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_offset, WATCH_OFFSET_X_OFFSET, LINE_Y_OFFSET, CURSOR_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_visible, WATCH_VISIBLE_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    break;
                }
            }
        } else {
            sprintf(watch_line, "%s %s %s %s %s %s %s",
                    watch_address,
                    watch_x,
                    watch_y,
                    watch_hex,
                    watch_type,
                    watch_offset,
                    watch_visible);
            font.gz_renderChars(watch_line, 25.0f, (80.0f + (i * 20.0f)), (cursor.y == i ? CURSOR_RGBA : 0xFFFFFFFF), g_drop_shadows);
        }
    }
}

bool check_if_any_memory_line_is_selected(MemoryWatch Watches[]) {
    bool return_value = false;
    for (int i = 0; i < MAX_WATCHES; i++) {
        if (Watches[i].line_selected) {
            return_value = true;
        }
    }

    return return_value;
}

void MemoryMenu::render(Font& font) {
    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

    if (button_is_pressed(Controller::B)) {
        if (check_if_any_memory_line_is_selected(Watches)) {
            for (int i = 0; i < MAX_WATCHES; i++) {
                Watches[i].line_selected = false;
            }
            Watches[cursor.y].line_selected = false;
        } else {
            init_once = false;
            memory_visible = false;
            mm_visible = true;
            return;
        }
    };

    if (!init_once) {current_input = 0;init_once = true;}

    if (current_input == 256 && a_held == false) {
        // finish
        Watches[cursor.y].line_selected = true;
    }

    if (button_is_pressed(Controller::Z)) {
        Watches[cursor.y].visible = !Watches[cursor.y].visible;
    }


    Utilities::move_cursor(cursor, MAX_WATCHES, WATCH_COLUMNS);
    render_memory_lines(font, Watches, cursor);
};