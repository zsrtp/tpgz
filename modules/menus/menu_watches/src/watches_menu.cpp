#include "menus/menu_watches/include/watches_menu.h"
#include <cstdio>
#include "settings.h"
#include "utils/lines.h"
#include "utils/memory.h"
#include "memory_editor.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

#define WATCH_COLUMNS 6
#define WATCH_ADDRESS_X_OFFSET 25.0f
#define WHITE_RGBA 0xFFFFFFFF
#define SPEED_THRESHOLD 30

#ifdef GCN_PLATFORM
#define MEMORY_BUTTON (GZPad::Y)
#define MEMORY_TEXT "Y"
#define ADD_WATCH_BUTTON (GZPad::R)
#define ADD_WATCH_TEXT "R"
#define REMOVE_WATCH_BUTTON (GZPad::L)
#define REMOVE_WATCH_TEXT "L"
#endif
#ifdef WII_PLATFORM
#define MEMORY_BUTTON (GZPad::ONE)
#define MEMORY_TEXT "1"
#define ADD_WATCH_BUTTON (GZPad::PLUS)
#define ADD_WATCH_TEXT "(+)"
#define REMOVE_WATCH_BUTTON (GZPad::MINUS)
#define REMOVE_WATCH_TEXT "(-)"
#endif

#ifdef WII_PLATFORM
extern bool isWidescreen;
#else
#define isWidescreen (false)
#endif

WatchesMenu::WatchesMenu(Cursor& cursor, WatchesData& data)
    : Menu(cursor), button_held_counter(data.button_held_counter),
      l_scrollSpeed(data.l_scrollSpeed), l_addrIdx(data.l_addrIdx), l_offsetIdx(data.l_offsetIdx) {}

WatchesMenu::~WatchesMenu() {}

void WatchesMenu::drawMemoryLines(MemoryWatch* watches, size_t n_watches) {
    static size_t l_firstLine = 0;

    const float scale = isWidescreen ? 0.75f : 1.0f;

    const float watch_x_pos_x_offset =
        WATCH_ADDRESS_X_OFFSET * scale +
        maxF(GZ_getTextWidth("Address"), GZ_getTextWidth("0x80000000")) + 5.0f * scale;
    const float watch_y_pos_x_offset =
        watch_x_pos_x_offset + maxF(GZ_getTextWidth("X"), GZ_getTextWidth("<000>")) + 5.0f;
    const float watch_hex_x_offset =
        watch_y_pos_x_offset + maxF(GZ_getTextWidth("Y"), GZ_getTextWidth("<000>")) + 5.0f;
    const float watch_type_x_offset =
        watch_hex_x_offset + maxF(GZ_getTextWidth("Hex"), GZ_getTextWidth("<false>")) + 5.0f;
    const float watch_offset_x_offset =
        watch_type_x_offset + maxF(GZ_getTextWidth("Type"), GZ_getTextWidth("<u32>")) + 5.0f;
    const float watch_visible_x_offset =
        watch_offset_x_offset + maxF(GZ_getTextWidth("Offset"), GZ_getTextWidth("0x0000")) + 5.0f;

    GZ_drawText("Address", WATCH_ADDRESS_X_OFFSET * scale, 60.0f, WHITE_RGBA,
                GZ_checkDropShadows());
    GZ_drawText("X", watch_x_pos_x_offset, 60.0f, WHITE_RGBA, GZ_checkDropShadows());
    GZ_drawText("Y", watch_y_pos_x_offset, 60.0f, WHITE_RGBA, GZ_checkDropShadows());
    GZ_drawText("Hex", watch_hex_x_offset, 60.0f, WHITE_RGBA, GZ_checkDropShadows());
    GZ_drawText("Type", watch_type_x_offset, 60.0f, WHITE_RGBA, GZ_checkDropShadows());
    GZ_drawText("Offset", watch_offset_x_offset, 60.0f, WHITE_RGBA, GZ_checkDropShadows());
    GZ_drawText("Visible", watch_visible_x_offset, 60.0f, WHITE_RGBA, GZ_checkDropShadows());

    if (cursor.y < (int)l_firstLine) {
        l_firstLine = cursor.y;
    }
    if (cursor.y > (int)l_firstLine + MAX_RENDER_LINES - 1) {
        l_firstLine = cursor.y - MAX_RENDER_LINES + 1;
    }

    if (l_firstLine > 0) {
        Font::GZ_drawStr("^", WATCH_ADDRESS_X_OFFSET * scale, 80.0f - 8.0f, 0xFFFFFFFF,
                         GZ_checkDropShadows());
    }

    if (l_firstLine + MAX_RENDER_LINES - 1 < n_watches - 1) {
        Font::GZ_drawStr("v", WATCH_ADDRESS_X_OFFSET * scale,
                         80.0f + 20.0f * MAX_RENDER_LINES - 10.f, 0xFFFFFFFF,
                         GZ_checkDropShadows());
    }

    for (int i = MAX(0, l_firstLine); i < (int)MIN(l_firstLine + MAX_RENDER_LINES, n_watches);
         i++) {
        const float line_y_offset = (80.0f + ((i - l_firstLine) * 20.0f));
        char watch_address[11];
        char watch_x[8];
        char watch_y[8];
        char watch_hex[8];
        char watch_type[6];
        char watch_offset[7];
        char watch_visible[4];

        snprintf(watch_address, sizeof(watch_address), "0x%08X", watches[i].address);
        snprintf(watch_x, sizeof(watch_x), "%.0f", watches[i].x);
        snprintf(watch_y, sizeof(watch_y), "%.0f", watches[i].y);
        snprintf(watch_hex, sizeof(watch_hex), "%s", watches[i].hex ? "true" : "false");

        switch (watches[i].type) {
        case MEM_TYPE_U8:
            snprintf(watch_type, sizeof(watch_type), "u8");
            break;
        case MEM_TYPE_U16:
            snprintf(watch_type, sizeof(watch_type), "u16");
            break;
        case MEM_TYPE_U32:
            snprintf(watch_type, sizeof(watch_type), "u32");
            break;
        case MEM_TYPE_S8:
            snprintf(watch_type, sizeof(watch_type), "s8");
            break;
        case MEM_TYPE_S16:
            snprintf(watch_type, sizeof(watch_type), "s16");
            break;
        case MEM_TYPE_S32:
            snprintf(watch_type, sizeof(watch_type), "s32");
            break;
        case MEM_TYPE_F32:
            snprintf(watch_type, sizeof(watch_type), "f32");
            break;
        case MEM_TYPE_STR:
            snprintf(watch_type, sizeof(watch_type), "str");
            break;
        }
        snprintf(watch_offset, sizeof(watch_offset), "0x%04X", watches[i].offset);
        snprintf(watch_visible, sizeof(watch_visible), "%s", watches[i].visible ? "[X]" : "[ ]");

        if (watches[i].line_selected) {
            switch (cursor.x) {
            case WatchAddress:
                if (watches[i].value_selected) {
                    if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
                        if (l_addrIdx == 9) {
                            l_addrIdx = 3;
                        } else if (l_addrIdx >= 3 && l_addrIdx < 9) {
                            l_addrIdx++;
                        }
                    }
                    if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
                        if (l_addrIdx == 3) {
                            l_addrIdx = 9;
                        } else if (l_addrIdx > 3 && l_addrIdx <= 9) {
                            l_addrIdx--;
                        }
                    }
                    if (GZ_getButtonRepeat(GZPad::DPAD_UP)) {
                        if (l_addrIdx == 3 && watches[i].address >= 0x81000000) {
                            watches[i].address = 0x817FFFFF;
                        } else if (l_addrIdx <= 9 && l_addrIdx >= 3) {
                            watches[i].address += 1 << ((9 - l_addrIdx) * 4);
                        }
                        if (watches[i].address > 0x817FFFFF) {
                            watches[i].address = 0x817FFFFF;
                        }
                    }
                    if (GZ_getButtonRepeat(GZPad::DPAD_DOWN)) {
                        if (l_addrIdx <= 9 && l_addrIdx >= 3) {
                            watches[i].address -= 1 << ((9 - l_addrIdx) * 4);
                        }
                        if (watches[i].address < 0x80000000) {
                            watches[i].address = 0x80000000;
                        }
                    }

                    GZ_drawSelectChar(watch_address, WATCH_ADDRESS_X_OFFSET * scale, line_y_offset,
                                      l_addrIdx, 9, WHITE_RGBA);
                } else {
                    GZ_drawText(watch_address, WATCH_ADDRESS_X_OFFSET * scale, line_y_offset,
                                CURSOR_RGBA, GZ_checkDropShadows());
                }
                GZ_drawText(watch_x, watch_x_pos_x_offset, line_y_offset, WHITE_RGBA,
                            GZ_checkDropShadows());
                GZ_drawText(watch_y, watch_y_pos_x_offset, line_y_offset, WHITE_RGBA,
                            GZ_checkDropShadows());
                GZ_drawText(watch_hex, watch_hex_x_offset, line_y_offset, WHITE_RGBA,
                            GZ_checkDropShadows());
                GZ_drawText(watch_type, watch_type_x_offset, line_y_offset, WHITE_RGBA,
                            GZ_checkDropShadows());
                GZ_drawText(watch_offset, watch_offset_x_offset, line_y_offset, WHITE_RGBA,
                            GZ_checkDropShadows());
                GZ_drawText(watch_visible, watch_visible_x_offset, line_y_offset, WHITE_RGBA,
                            GZ_checkDropShadows());
                break;
            case WatchX:
                if (watches[i].value_selected) {
                    if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
                        if (watches[i].x >= 0.0f && watches[i].x < 600.0f) {
                            watches[i].x += l_scrollSpeed * scale;
                        }
                    }
                    if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
                        if (watches[i].x > 0.0f && watches[i].x <= 600.0f) {
                            watches[i].x -= l_scrollSpeed * scale;
                        }
                    }
                    if (watches[i].x < 0) {
                        watches[i].x = 0;
                    }
                    if (watches[i].x > 600) {
                        watches[i].x = 600;
                    }
                    snprintf(watch_x, sizeof(watch_x), "<%.0f>", watches[i].x);
                    GZ_drawText(watch_x, watch_x_pos_x_offset - 8.0f * scale, line_y_offset,
                                CURSOR_RGBA, GZ_checkDropShadows());
                } else {
                    GZ_drawText(watch_x, watch_x_pos_x_offset, line_y_offset, CURSOR_RGBA,
                                GZ_checkDropShadows());
                }
                GZ_drawText(watch_address, WATCH_ADDRESS_X_OFFSET * scale, line_y_offset,
                            WHITE_RGBA, GZ_checkDropShadows());
                GZ_drawText(watch_y, watch_y_pos_x_offset, line_y_offset, WHITE_RGBA,
                            GZ_checkDropShadows());
                GZ_drawText(watch_hex, watch_hex_x_offset, line_y_offset, WHITE_RGBA,
                            GZ_checkDropShadows());
                GZ_drawText(watch_type, watch_type_x_offset, line_y_offset, WHITE_RGBA,
                            GZ_checkDropShadows());
                GZ_drawText(watch_offset, watch_offset_x_offset, line_y_offset, WHITE_RGBA,
                            GZ_checkDropShadows());
                GZ_drawText(watch_visible, watch_visible_x_offset, line_y_offset, WHITE_RGBA,
                            GZ_checkDropShadows());
                break;
            case WatchY:
                if (watches[i].value_selected) {
                    if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
                        if (watches[i].y >= 0.0f && watches[i].y < 500.0f) {
                            watches[i].y += l_scrollSpeed;
                        }
                    }
                    if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
                        if (watches[i].y > 0.0f && watches[i].y <= 500.0f) {
                            watches[i].y -= l_scrollSpeed;
                        }
                    }
                    if (watches[i].y < 0) {
                        watches[i].y = 0;
                    }
                    if (watches[i].y > 500) {
                        watches[i].y = 500;
                    }
                    snprintf(watch_y, sizeof(watch_y), "<%.0f>", watches[i].y);
                    GZ_drawText(watch_y, watch_y_pos_x_offset - 8.0f * scale, line_y_offset,
                                CURSOR_RGBA, GZ_checkDropShadows());
                } else {
                    GZ_drawText(watch_y, watch_y_pos_x_offset, line_y_offset, CURSOR_RGBA,
                                GZ_checkDropShadows());
                }
                GZ_drawText(watch_address, WATCH_ADDRESS_X_OFFSET * scale, line_y_offset,
                            WHITE_RGBA, GZ_checkDropShadows());
                GZ_drawText(watch_x, watch_x_pos_x_offset, line_y_offset, WHITE_RGBA,
                            GZ_checkDropShadows());
                GZ_drawText(watch_hex, watch_hex_x_offset, line_y_offset, WHITE_RGBA,
                            GZ_checkDropShadows());
                GZ_drawText(watch_type, watch_type_x_offset, line_y_offset, WHITE_RGBA,
                            GZ_checkDropShadows());
                GZ_drawText(watch_offset, watch_offset_x_offset, line_y_offset, WHITE_RGBA,
                            GZ_checkDropShadows());
                GZ_drawText(watch_visible, watch_visible_x_offset, line_y_offset, WHITE_RGBA,
                            GZ_checkDropShadows());

                break;
            case WatchHex:
                if (watches[i].value_selected) {
                    if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
                        watches[i].hex = !watches[i].hex;
                    }
                    if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
                        watches[i].hex = !watches[i].hex;
                    }
                    snprintf(watch_hex, sizeof(watch_hex), "<%s>",
                             watches[i].hex ? "true" : "false");
                    GZ_drawText(watch_hex, watch_hex_x_offset - 8.0f * scale, line_y_offset,
                                CURSOR_RGBA, GZ_checkDropShadows());
                } else {
                    GZ_drawText(watch_hex, watch_hex_x_offset, line_y_offset, CURSOR_RGBA,
                                GZ_checkDropShadows());
                }
                GZ_drawText(watch_address, WATCH_ADDRESS_X_OFFSET * scale, line_y_offset,
                            WHITE_RGBA, GZ_checkDropShadows());
                GZ_drawText(watch_x, watch_x_pos_x_offset, line_y_offset, WHITE_RGBA,
                            GZ_checkDropShadows());
                GZ_drawText(watch_y, watch_y_pos_x_offset, line_y_offset, WHITE_RGBA,
                            GZ_checkDropShadows());
                GZ_drawText(watch_type, watch_type_x_offset, line_y_offset, WHITE_RGBA,
                            GZ_checkDropShadows());
                GZ_drawText(watch_offset, watch_offset_x_offset, line_y_offset, WHITE_RGBA,
                            GZ_checkDropShadows());
                GZ_drawText(watch_visible, watch_visible_x_offset, line_y_offset, WHITE_RGBA,
                            GZ_checkDropShadows());
                break;
            case WatchType:
                if (watches[i].value_selected) {
                    if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
                        if (watches[i].type == MEM_TYPE_STR) {
                            watches[i].type = MEM_TYPE_U8;
                        } else if (watches[i].type >= MEM_TYPE_U8 &&
                                   watches[i].type < MEM_TYPE_STR) {
                            watches[i].type++;
                        }
                    }
                    if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
                        if (watches[i].type == MEM_TYPE_U8) {
                            watches[i].type = MEM_TYPE_STR;
                        } else if (watches[i].type > MEM_TYPE_U8 &&
                                   watches[i].type <= MEM_TYPE_STR) {
                            watches[i].type--;
                        }
                    }
                    switch (watches[i].type) {
                    case MEM_TYPE_U8:
                        snprintf(watch_type, sizeof(watch_type), "<u8>");
                        break;
                    case MEM_TYPE_U16:
                        snprintf(watch_type, sizeof(watch_type), "<u16>");
                        break;
                    case MEM_TYPE_U32:
                        snprintf(watch_type, sizeof(watch_type), "<u32>");
                        break;
                    case MEM_TYPE_S8:
                        snprintf(watch_type, sizeof(watch_type), "<s8>");
                        break;
                    case MEM_TYPE_S16:
                        snprintf(watch_type, sizeof(watch_type), "<s16>");
                        break;
                    case MEM_TYPE_S32:
                        snprintf(watch_type, sizeof(watch_type), "<s32>");
                        break;
                    case MEM_TYPE_F32:
                        snprintf(watch_type, sizeof(watch_type), "<f32>");
                        break;
                    case MEM_TYPE_STR:
                        snprintf(watch_type, sizeof(watch_type), "<str>");
                    }
                    GZ_drawText(watch_type, watch_type_x_offset - 8.0f * scale, line_y_offset,
                                CURSOR_RGBA, GZ_checkDropShadows());
                } else {
                    GZ_drawText(watch_type, watch_type_x_offset, line_y_offset, CURSOR_RGBA,
                                GZ_checkDropShadows());
                }
                GZ_drawText(watch_address, WATCH_ADDRESS_X_OFFSET * scale, line_y_offset,
                            WHITE_RGBA, GZ_checkDropShadows());
                GZ_drawText(watch_x, watch_x_pos_x_offset, line_y_offset, WHITE_RGBA,
                            GZ_checkDropShadows());
                GZ_drawText(watch_y, watch_y_pos_x_offset, line_y_offset, WHITE_RGBA,
                            GZ_checkDropShadows());
                GZ_drawText(watch_hex, watch_hex_x_offset, line_y_offset, WHITE_RGBA,
                            GZ_checkDropShadows());
                GZ_drawText(watch_offset, watch_offset_x_offset, line_y_offset, WHITE_RGBA,
                            GZ_checkDropShadows());
                GZ_drawText(watch_visible, watch_visible_x_offset, line_y_offset, WHITE_RGBA,
                            GZ_checkDropShadows());
                break;
            case WatchOffset:
                if (watches[i].value_selected) {
                    if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
                        if (l_offsetIdx == 5) {
                            l_offsetIdx = 2;
                        } else if (l_offsetIdx >= 2 && l_offsetIdx < 5) {
                            l_offsetIdx++;
                        }
                    }
                    if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
                        if (l_offsetIdx == 2) {
                            l_offsetIdx = 5;
                        } else if (l_offsetIdx > 2 && l_offsetIdx <= 5) {
                            l_offsetIdx--;
                        }
                    }
                    if (GZ_getButtonRepeat(GZPad::DPAD_UP)) {
                        watches[i].offset += (0x100000 >> (l_offsetIdx * 4));
                        if (watches[i].offset > 0xFFFF) {
                            watches[i].offset = 0xFFFF;
                        }
                    }
                    if (GZ_getButtonRepeat(GZPad::DPAD_DOWN)) {
                        watches[i].offset -= (0x100000 >> (l_offsetIdx * 4));
                        if (watches[i].offset < 0x0000) {
                            watches[i].offset = 0x0000;
                        }
                    }
                    GZ_drawSelectChar(watch_offset, watch_offset_x_offset, line_y_offset,
                                      l_offsetIdx, 5, WHITE_RGBA);
                } else {
                    GZ_drawText(watch_offset, watch_offset_x_offset, line_y_offset, CURSOR_RGBA,
                                GZ_checkDropShadows());
                }
                GZ_drawText(watch_address, WATCH_ADDRESS_X_OFFSET * scale, line_y_offset,
                            WHITE_RGBA, GZ_checkDropShadows());
                GZ_drawText(watch_x, watch_x_pos_x_offset, line_y_offset, WHITE_RGBA,
                            GZ_checkDropShadows());
                GZ_drawText(watch_y, watch_y_pos_x_offset, line_y_offset, WHITE_RGBA,
                            GZ_checkDropShadows());
                GZ_drawText(watch_hex, watch_hex_x_offset, line_y_offset, WHITE_RGBA,
                            GZ_checkDropShadows());
                GZ_drawText(watch_type, watch_type_x_offset, line_y_offset, WHITE_RGBA,
                            GZ_checkDropShadows());
                GZ_drawText(watch_visible, watch_visible_x_offset, line_y_offset, WHITE_RGBA,
                            GZ_checkDropShadows());
                break;
            }
        } else {
            int y = cursor.y;
            GZ_drawText(watch_address, WATCH_ADDRESS_X_OFFSET * scale, line_y_offset,
                        (y == i ? CURSOR_RGBA : WHITE_RGBA), GZ_checkDropShadows());
            GZ_drawText(watch_x, watch_x_pos_x_offset, line_y_offset,
                        (y == i ? CURSOR_RGBA : WHITE_RGBA), GZ_checkDropShadows());
            GZ_drawText(watch_y, watch_y_pos_x_offset, line_y_offset,
                        (y == i ? CURSOR_RGBA : WHITE_RGBA), GZ_checkDropShadows());
            GZ_drawText(watch_hex, watch_hex_x_offset, line_y_offset,
                        (y == i ? CURSOR_RGBA : WHITE_RGBA), GZ_checkDropShadows());
            GZ_drawText(watch_type, watch_type_x_offset, line_y_offset,
                        (y == i ? CURSOR_RGBA : WHITE_RGBA), GZ_checkDropShadows());
            GZ_drawText(watch_offset, watch_offset_x_offset, line_y_offset,
                        (y == i ? CURSOR_RGBA : WHITE_RGBA), GZ_checkDropShadows());
            GZ_drawText(watch_visible, watch_visible_x_offset, line_y_offset,
                        (y == i ? CURSOR_RGBA : WHITE_RGBA), GZ_checkDropShadows());
        }
    }
}

bool checkMemLineSelected(MemoryWatch* watches, size_t n_watches) {
    bool return_value = false;
    for (int i = 0; i < (int)n_watches; i++) {
        if (watches[i].line_selected) {
            return_value = true;
        }
    }
    return return_value;
}

bool checkLineValSelected(MemoryWatch* watches, size_t n_watches) {
    bool return_value = false;
    for (int i = 0; i < (int)n_watches; i++) {
        if (watches[i].value_selected) {
            return_value = true;
        }
    }

    return return_value;
}

void WatchesMenu::draw() {
    cursor.setMode(Cursor::MODE_UNRESTRICTED);

    const float scale = isWidescreen ? 0.75f : 1.0f;

    auto* stng = GZStng_getSetting(STNG_WATCHES);
    if (!stng) {
        stng = new GZSettingEntry{STNG_WATCHES, 0, nullptr};
        g_settings.push_back(stng);
    }

    MemoryWatch* watches = static_cast<MemoryWatch*>(stng->data);
    size_t n_watches = stng->size / sizeof(MemoryWatch);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        if (checkLineValSelected(watches, n_watches)) {
            for (int i = 0; i < (int)n_watches; i++) {
                watches[i].value_selected = false;
            }
            watches[cursor.y].value_selected = false;
            cursor.lock_x = false;
        } else if (checkMemLineSelected(watches, n_watches)) {
            for (int i = 0; i < (int)n_watches; i++) {
                watches[i].line_selected = false;
            }
            watches[cursor.y].line_selected = false;
            cursor.lock_y = false;
        } else {
            g_menuMgr->pop();
            return;
        }
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON) && watches) {
        if (watches[cursor.y].value_selected) {
            watches[cursor.y].value_selected = false;
            cursor.lock_x = false;
        } else if (watches[cursor.y].line_selected) {
            watches[cursor.y].value_selected = true;
            cursor.lock_x = true;
        } else {
            watches[cursor.y].line_selected = true;
            cursor.lock_y = true;
        }
    }

    if (GZ_getButtonTrig(GZPad::Z) && watches) {
        watches[cursor.y].visible = !watches[cursor.y].visible;
    }

    if (GZ_getButtonTrig(MEMORY_BUTTON) && watches) {
        if (watches[cursor.y].offset > 0 && *(uint32_t*)watches[cursor.y].address != 0) {
            g_memoryEditor_addressIndex =
                *(uint32_t*)watches[cursor.y].address + watches[cursor.y].offset;
        } else {
            g_memoryEditor_addressIndex = watches[cursor.y].address;
        }
        g_menuMgr->push(MN_MEMORY_EDITOR_INDEX);
    }

    if (GZ_getButtonRepeat(ADD_WATCH_BUTTON) && !checkMemLineSelected(watches, n_watches)) {
        if (n_watches < MAX_WATCHES) {
            MemoryWatch* new_watches = new MemoryWatch[n_watches + 1];
            if (watches) {
                if (n_watches > 0) {
                    for (int i = 0; i < (int)cursor.y + 1; ++i) {
                        new_watches[i] = watches[i];
                    }
                    for (int i = n_watches - 1; i >= cursor.y; --i) {
                        new_watches[i + 1] = watches[i];
                    }
                }
                delete[] watches;
            }
            stng->data = new_watches;
            stng->size = (n_watches + 1) * sizeof(MemoryWatch);
            watches = new_watches;
            ++n_watches;
        }
    }

    if (GZ_getButtonRepeat(REMOVE_WATCH_BUTTON) && !checkMemLineSelected(watches, n_watches)) {
        if (watches && n_watches > 0) {
            MemoryWatch* new_watches = nullptr;
            if (n_watches > 1) {
                new_watches = new MemoryWatch[n_watches - 1];
                for (int i = 0; i < (int)cursor.y; i++) {
                    new_watches[i] = watches[i];
                }
                for (int i = cursor.y; i < (int)n_watches - 1; i++) {
                    new_watches[i] = watches[i + 1];
                }
            }
            if (cursor.y > 0 && cursor.y == (int)n_watches - 1) {
                cursor.y -= 1;
            }
            delete[] watches;
            stng->data = new_watches;
            stng->size = (n_watches - 1) * sizeof(MemoryWatch);
            --n_watches;
            watches = new_watches;
        }
    }

    if (GZ_getButtonPressed(GZPad::DPAD_RIGHT) || GZ_getButtonPressed(GZPad::DPAD_LEFT)) {
        if (l_scrollSpeed < 20.0f) {
            l_scrollSpeed += 1.0f;
        }
        if (l_scrollSpeed > 20.0f) {
            l_scrollSpeed = 20.0f;
        }
    } else {
        l_scrollSpeed = 1.0f;
    }

    if (checkMemLineSelected(watches, n_watches) && watches) {
        cursor.setMode(Cursor::MODE_UNRESTRICTED);
        cursor.move(WATCH_COLUMNS, n_watches);
        GZ_drawText("Z: enable/disable watch; " MEMORY_TEXT ": go to address in editor",
                    20.0f * scale, 440.f, WHITE_RGBA, GZ_checkDropShadows());
    } else {
        cursor.setMode(Cursor::MODE_SINGLE_COLUMN);
        cursor.move(0, n_watches);
        GZ_drawText("Z: enable/disable watch; " MEMORY_TEXT ": go to address; " ADD_WATCH_TEXT
                    "/" REMOVE_WATCH_TEXT ": add/remove watch",
                    20.0f * scale, 440.f, WHITE_RGBA, GZ_checkDropShadows());
    }
    if (watches) {
        drawMemoryLines(watches, n_watches);
    } else {
        GZ_drawText("No watches", 25.0f * scale, 60.0f, WHITE_RGBA, GZ_checkDropShadows());
    }
}