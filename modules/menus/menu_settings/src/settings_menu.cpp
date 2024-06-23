#include "menus/menu_settings/include/settings_menu.h"
#include <cstdio>
#include "utils/card.h"
#include "gz_flags.h"
#include "fifo_queue.h"
#include "settings.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

#define MAX_RELOAD_OPTIONS 2
#define MAX_CURSOR_COLOR_OPTIONS 6

KEEP_FUNC SettingsMenu::SettingsMenu(Cursor& cursor)
    : Menu(cursor), lines{
                        {"area reload behavior:", AREA_RELOAD_BEHAVIOR_INDEX,
                         "Load area: reload last area | Load file = reload last file", false,
                         nullptr, MAX_RELOAD_OPTIONS},
                        {"cursor color:", CURSOR_COLOR_INDEX, "Change cursor color", false, nullptr,
                         MAX_CURSOR_COLOR_OPTIONS},
                        {"font:", FONT_INDEX, "Change font", false, nullptr, FONT_OPTIONS_COUNT},
                        {"drop shadows", DROP_SHADOWS_INDEX, "Adds shadows to all font letters",
                         true, GZ_checkDropShadows},
                        {"swap equips", SWAP_EQUIPS_INDEX,
                         "Swap equips when loading practice files", true, [](){return g_swap_equips_flag;}},
                        {"save card", SAVE_CARD_INDEX, "Save settings to memory card"},
                        {"load card", LOAD_CARD_INDEX, "Load settings from memory card"},
                        {"delete card", DELETE_CARD_INDEX, "Delete settings from memory card"},
                        {"combo", COMBO_INDEX, "view combo menu", false},
                        {"menu positions", POS_SETTINGS_MENU_INDEX,
                         "Change menu object positions (A to toggle selection, DPad to move)",
                         false},
                         {"credits", CREDITS_INDEX, "view credits", false},
                    } {}

SettingsMenu::~SettingsMenu() {}

void SettingsMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    GZSettingEntry* stng = nullptr;
    // static Storage storage;
    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        switch (cursor.y) {
        case DROP_SHADOWS_INDEX:
            stng = GZStng_get(STNG_DROP_SHADOWS);
            if (!stng) {
                stng = new GZSettingEntry{STNG_DROP_SHADOWS, sizeof(bool), new bool{false}};
                g_settings.push_back(stng);
            }
            *static_cast<bool*>(stng->data) = !*static_cast<bool*>(stng->data);
            break;
        case POS_SETTINGS_MENU_INDEX:
            g_menuMgr->push(MN_POS_SETTINGS_INDEX);
            return;
        case CREDITS_INDEX:
            g_menuMgr->push(MN_CREDITS_INDEX);
            return;
        case COMBO_INDEX:
            g_menuMgr->push(MN_COMBO_INDEX);
            return;
        case SAVE_CARD_INDEX: {
            static Storage storage;
            storage.file_name = "tpgz01";
            storage.sector_size = SECTOR_SIZE;
            snprintf(storage.file_name_buffer, sizeof(storage.file_name_buffer), storage.file_name);
#ifndef WII_PLATFORM
            storage.result = CARDProbeEx(0, nullptr, &storage.sector_size);
            if (storage.result == Ready) {
                GZ_storeMemCard(storage);
            }
#else
            GZ_storeMemCard(storage);
#endif  // WII_PLATFORM
            break;
        }
        case LOAD_CARD_INDEX: {
            static Storage storage;
            storage.file_name = "tpgz01";
            storage.sector_size = SECTOR_SIZE;
            snprintf(storage.file_name_buffer, sizeof(storage.file_name_buffer), storage.file_name);
#ifndef WII_PLATFORM
            storage.result = CARDProbeEx(0, NULL, &storage.sector_size);
            if (storage.result == Ready) {
                GZ_loadMemCard(storage);
            }
#else
            GZ_loadMemCard(storage);
#endif  // WII_PLATFORM
            break;
        }
        case DELETE_CARD_INDEX: {
            static Storage storage;
            storage.file_name = "tpgz01";
            storage.sector_size = SECTOR_SIZE;
            snprintf(storage.file_name_buffer, sizeof(storage.file_name_buffer), storage.file_name);
#ifndef WII_PLATFORM
            storage.result = CARDProbeEx(0, nullptr, &storage.sector_size);
            if (storage.result == Ready) {
                GZ_deleteMemCard(storage);
            }
#else
            GZ_deleteMemCard(storage);
#endif  // WII_PLATFORM
            break;
        }
        case SWAP_EQUIPS_INDEX:
            g_swap_equips_flag = !g_swap_equips_flag;
            break;
        }
    }

    ListMember reload_opt[MAX_RELOAD_OPTIONS] = {"load area", "load file"};

    ListMember cursorCol_opt[MAX_CURSOR_COLOR_OPTIONS] = {"green",  "blue",   "red",
                                                          "orange", "yellow", "purple"};

    stng = nullptr;
    auto prev_x = cursor.x;
    // handle list rendering
    switch (cursor.y) {
    case AREA_RELOAD_BEHAVIOR_INDEX:
        stng = GZStng_get(STNG_AREA_RELOAD_BEHAVIOUR);
        cursor.x = stng ? *static_cast<uint32_t*>(stng->data) : 0;
        prev_x = cursor.x;
        cursor.move(MAX_RELOAD_OPTIONS, MENU_LINE_NUM);

        if (cursor.y == AREA_RELOAD_BEHAVIOR_INDEX) {
            if (cursor.x != prev_x) {
                if (!stng) {
                    stng = new GZSettingEntry{STNG_AREA_RELOAD_BEHAVIOUR, sizeof(uint32_t), new uint32_t(cursor.x)};
                    g_settings.push_back(stng);
                } else {
                    *static_cast<uint32_t*>(stng->data) = cursor.x;
                }
            }
        }
        break;
    case CURSOR_COLOR_INDEX:
        stng = GZStng_get(STNG_CURSOR_COLOR);
        cursor.x = stng ? *static_cast<uint32_t*>(stng->data) : 0;
        prev_x = cursor.x;
        cursor.move(MAX_CURSOR_COLOR_OPTIONS, MENU_LINE_NUM);

        if (cursor.y == CURSOR_COLOR_INDEX) {
            if (cursor.x != prev_x) {
                if (!stng) {
                    stng = new GZSettingEntry{STNG_CURSOR_COLOR, sizeof(uint32_t), new uint32_t(cursor.x)};
                    g_settings.push_back(stng);
                } else {
                    *static_cast<uint32_t*>(stng->data) = cursor.x;
                }
            }
        }
        break;
    case FONT_INDEX: {
        stng = GZStng_get(STNG_FONT);
        cursor.x = stng ? *static_cast<uint32_t*>(stng->data) : 0;
        prev_x = cursor.x;
        int old_font = cursor.x;
        cursor.move(FONT_OPTIONS_COUNT, MENU_LINE_NUM);

        if (cursor.y == FONT_INDEX) {
            if (prev_x != cursor.x) {
                if (!stng) {
                    stng = new GZSettingEntry{STNG_FONT, sizeof(uint32_t), new uint32_t(cursor.x)};
                    g_settings.push_back(stng);
                } else {
                    *static_cast<uint32_t*>(stng->data) = cursor.x;
                }
            }
        }
        if (old_font != cursor.x) {
            uint32_t fontType = stng ? *static_cast<uint32_t*>(stng->data) : 0;
            if (fontType >= 0 && fontType < FONT_OPTIONS_COUNT) {
                char buf[40];
                snprintf(buf, sizeof(buf), "tpgz/fonts/%s.fnt", g_font_opt[fontType].member);
                Font::loadFont(buf);
            }
        }
        break;
    }
    default:
        cursor.move(0, MENU_LINE_NUM);
        break;
    }

    lines[AREA_RELOAD_BEHAVIOR_INDEX].printf(" <%s>", reload_opt[GZStng_getData<uint32_t>(STNG_AREA_RELOAD_BEHAVIOUR, 0)].member);
    lines[CURSOR_COLOR_INDEX].printf(" <%s>", cursorCol_opt[GZStng_getData<uint32_t>(STNG_CURSOR_COLOR, 0)].member);
    lines[FONT_INDEX].printf(" <%s>", g_font_opt[GZStng_getData<uint32_t>(STNG_FONT, 0)].member);

    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
