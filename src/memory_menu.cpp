#include "font.h"
#include "menu.h"
#include "controller.h"
#include "utils.h"

#define MAX_WATCHES 10
#define WATCH_COLUMNS 6

Cursor cursor;

bool memory_visible;
bool init_once = false;

MemoryWatch Watches[MAX_WATCHES] = {
    {0x80000000, 100.0f, 200.0f}};

void render_memory_lines(Font& font, MemoryWatch Watches[MAX_WATCHES], Cursor cursor) {
    font.renderChars("Address     X   Y   Hex Type Offset", 25.0f, 60.0f, 0xFFFFFFFF);
    if (g_drop_shadows) {
        font.renderChars("Address     X   Y   Hex Type Offset", 25.0f + 2.0f, 60.0 + 2.0f, DROP_SHADOWS_RGBA);
    };
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
        sprintf(watch_visible, "%s", Watches[i].visible ? "[X]" : "[] ");

        if (Watches[i].line_selected) {
            switch (cursor.y) {
                case WatchAddress: {
                    font.renderChars(watch_address, WATCH_ADDRESS_X_OFFSET, LINE_Y_OFFSET, CURSOR_RGBA);
                    font.renderChars(watch_x, WATCH_X_POS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA);
                    font.renderChars(watch_y, WATCH_Y_POS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA);
                    font.renderChars(watch_hex, WATCH_HEX_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA);
                    font.renderChars(watch_type, WATCH_TYPE_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA);
                    font.renderChars(watch_offset, WATCH_OFFSET_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA);
                    font.renderChars(watch_visible, WATCH_VISIBLE_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA);
                    break;
                }
                case WatchX: {
                    font.renderChars(watch_address, WATCH_ADDRESS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA);
                    font.renderChars(watch_x, WATCH_X_POS_X_OFFSET, LINE_Y_OFFSET, CURSOR_RGBA);
                    font.renderChars(watch_y, WATCH_Y_POS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA);
                    font.renderChars(watch_hex, WATCH_HEX_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA);
                    font.renderChars(watch_type, WATCH_TYPE_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA);
                    font.renderChars(watch_offset, WATCH_OFFSET_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA);
                    font.renderChars(watch_visible, WATCH_VISIBLE_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA);
                    break;
                }
                case WatchY: {
                    font.renderChars(watch_address, WATCH_ADDRESS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA);
                    font.renderChars(watch_x, WATCH_X_POS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA);
                    font.renderChars(watch_y, WATCH_Y_POS_X_OFFSET, LINE_Y_OFFSET, CURSOR_RGBA);
                    font.renderChars(watch_hex, WATCH_HEX_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA);
                    font.renderChars(watch_type, WATCH_TYPE_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA);
                    font.renderChars(watch_offset, WATCH_OFFSET_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA);
                    font.renderChars(watch_visible, WATCH_VISIBLE_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA);
                    break;
                }
                case WatchHex: {
                    font.renderChars(watch_address, WATCH_ADDRESS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA);
                    font.renderChars(watch_x, WATCH_X_POS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA);
                    font.renderChars(watch_y, WATCH_Y_POS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA);
                    font.renderChars(watch_hex, WATCH_HEX_X_OFFSET, LINE_Y_OFFSET, CURSOR_RGBA);
                    font.renderChars(watch_type, WATCH_TYPE_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA);
                    font.renderChars(watch_offset, WATCH_OFFSET_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA);
                    font.renderChars(watch_visible, WATCH_VISIBLE_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA);
                    break;
                }
                case WatchType: {
                    font.renderChars(watch_address, WATCH_ADDRESS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA);
                    font.renderChars(watch_x, WATCH_X_POS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA);
                    font.renderChars(watch_y, WATCH_Y_POS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA);
                    font.renderChars(watch_hex, WATCH_HEX_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA);
                    font.renderChars(watch_type, WATCH_TYPE_X_OFFSET, LINE_Y_OFFSET, CURSOR_RGBA);
                    font.renderChars(watch_offset, WATCH_OFFSET_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA);
                    font.renderChars(watch_visible, WATCH_VISIBLE_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA);
                    break;
                }
                case WatchOffset: {
                    font.renderChars(watch_address, WATCH_ADDRESS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA);
                    font.renderChars(watch_x, WATCH_X_POS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA);
                    font.renderChars(watch_y, WATCH_Y_POS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA);
                    font.renderChars(watch_hex, WATCH_HEX_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA);
                    font.renderChars(watch_type, WATCH_TYPE_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA);
                    font.renderChars(watch_offset, WATCH_OFFSET_X_OFFSET, LINE_Y_OFFSET, CURSOR_RGBA);
                    font.renderChars(watch_visible, WATCH_VISIBLE_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA);
                    break;
                }
            }
            if (g_drop_shadows) {
                font.renderChars(watch_address, WATCH_ADDRESS_X_OFFSET + 2.0f, LINE_Y_OFFSET + 2.0f, DROP_SHADOWS_RGBA);
                font.renderChars(watch_x, WATCH_X_POS_X_OFFSET + 2.0f, LINE_Y_OFFSET + 2.0f, DROP_SHADOWS_RGBA);
                font.renderChars(watch_y, WATCH_Y_POS_X_OFFSET + 2.0f, LINE_Y_OFFSET + 2.0f, DROP_SHADOWS_RGBA);
                font.renderChars(watch_hex, WATCH_HEX_X_OFFSET + 2.0f, LINE_Y_OFFSET + 2.0f, DROP_SHADOWS_RGBA);
                font.renderChars(watch_type, WATCH_TYPE_X_OFFSET + 2.0f, LINE_Y_OFFSET + 2.0f, DROP_SHADOWS_RGBA);
                font.renderChars(watch_offset, WATCH_OFFSET_X_OFFSET + 2.0f, LINE_Y_OFFSET + 2.0f, DROP_SHADOWS_RGBA);
                font.renderChars(watch_visible, WATCH_VISIBLE_X_OFFSET + 2.0f, LINE_Y_OFFSET + 2.0f, DROP_SHADOWS_RGBA);
            };
        } else {
            sprintf(watch_line, "%s %s %s %s %s %s %s",
                    watch_address,
                    watch_x,
                    watch_y,
                    watch_hex,
                    watch_type,
                    watch_offset,
                    watch_visible);
            font.renderChars(watch_line, 25.0f, (80.0f + (i * 20.0f)), (cursor.x == i ? CURSOR_RGBA : 0xFFFFFFFF));
            if (g_drop_shadows) {
                font.renderChars(watch_line, 25.0f + 2.0f, (80.0f + (i * 20.0f)) + 2.0f, DROP_SHADOWS_RGBA);
            };
        }
    }
}

void MemoryMenu::render(Font& font) {
    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

    if (button_is_pressed(Controller::B)) {
        if (Watches[cursor.x].line_selected) {
            Watches[cursor.x].line_selected = false;
        } else {
            memory_visible = false;
            mm_visible = true;
            return;
        }
    };

    if (button_is_pressed(Controller::A)) {
        // finish
        Watches[cursor.x].line_selected = true;
    }

    if (button_is_pressed(Controller::Z)) {
        Watches[cursor.x].visible = !Watches[cursor.x].visible;
    }

    Utilities::move_cursor(cursor, MAX_WATCHES, WATCH_COLUMNS);
    render_memory_lines(font, Watches, cursor);
};
