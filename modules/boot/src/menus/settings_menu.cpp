#include "menus/settings_menu.h"
#include "libtp_c/include/msl_c/string.h"
#include "utils/card.h"
#include "gz_flags.h"
#include "fifo_queue.h"
#include "rels/include/defines.h"

#define MAX_RELOAD_OPTIONS 2
#define MAX_CURSOR_COLOR_OPTIONS 6
#define FONT_OPTIONS_COUNT (sizeof(font_opt) / sizeof(font_opt[0]))

ListMember font_opt[] = {"consola",   "calamity-bold",  "lib-sans",      "lib-sans-bold",
                         "lib-serif", "lib-serif-bold", "press-start-2p"};

KEEP_FUNC SettingsMenu::SettingsMenu()
    : Menu(), lines{
                  {"area reload behavior:", AREA_RELOAD_BEHAVIOR_INDEX,
                   "Load area: reload last area | Load file = reload last file", false, nullptr,
                   MAX_RELOAD_OPTIONS},
                  {"cursor color:", CURSOR_COLOR_INDEX, "Change cursor color", false, nullptr,
                   MAX_CURSOR_COLOR_OPTIONS},
                  {"font:", FONT_INDEX, "Change font", false, nullptr, FONT_OPTIONS_COUNT},
                  {"drop shadows", DROP_SHADOWS_INDEX, "Adds shadows to all font letters", true,
                   &g_dropShadows},
                  {"swap equips", SWAP_EQUIPS_INDEX, "Swap equips when loading practice files",
                   true, &g_swap_equips_flag},
                  {"save card", SAVE_CARD_INDEX, "Save settings to memory card"},
                  {"load card", LOAD_CARD_INDEX, "Load settings from memory card"},
                  {"delete card", DELETE_CARD_INDEX, "Delete settings from memory card"},
                  {"menu positions", POS_SETTINGS_MENU_INDEX,
                   "Change menu object positions (A to toggle selection, DPad to move)", false},
              } {}

bool g_dropShadows;
bool g_swap_equips_flag;
uint32_t g_reloadType;
uint32_t g_fontType = 0;
uint32_t g_cursorColorType;

void SettingsMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        GZ_setMenu(MN_MAIN_MENU_INDEX);
        return;
    }

    // static Storage storage;
    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        switch (cursor.y) {
        case DROP_SHADOWS_INDEX:
            g_dropShadows = !g_dropShadows;
            break;
        case POS_SETTINGS_MENU_INDEX:
            GZ_setMenu(MN_POS_SETTINGS_INDEX);
            return;
        case SAVE_CARD_INDEX: {
            static Storage storage;
            storage.file_name = "tpgz01";
            storage.sector_size = SECTOR_SIZE;
            sprintf(storage.file_name_buffer, storage.file_name);
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
            sprintf(storage.file_name_buffer, storage.file_name);
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
            sprintf(storage.file_name_buffer, storage.file_name);
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

    // handle list rendering
    switch (cursor.y) {
    case AREA_RELOAD_BEHAVIOR_INDEX:
        cursor.x = g_reloadType;
        cursor.move(MAX_RELOAD_OPTIONS, MENU_LINE_NUM);

        if (cursor.y == AREA_RELOAD_BEHAVIOR_INDEX) {
            g_reloadType = cursor.x;
        }
        break;
    case CURSOR_COLOR_INDEX:
        cursor.x = g_cursorColorType;
        cursor.move(MAX_CURSOR_COLOR_OPTIONS, MENU_LINE_NUM);

        if (cursor.y == CURSOR_COLOR_INDEX) {
            g_cursorColorType = cursor.x;
        }
        break;
    case FONT_INDEX: {
        cursor.x = g_fontType;
        uint32_t old_font = g_fontType;
        cursor.move(FONT_OPTIONS_COUNT, MENU_LINE_NUM);

        if (cursor.y == FONT_INDEX) {
            g_fontType = cursor.x;
        }
        if (old_font != g_fontType) {
            if (g_fontType >= 0 && g_fontType < FONT_OPTIONS_COUNT) {
                char buf[40];
                sprintf(buf, "tpgz/fonts/%s.fnt", font_opt[g_fontType].member);
                Font::loadFont(buf);
            }
        }
        break;
    }
    default:
        cursor.move(0, MENU_LINE_NUM);
        break;
    }

    sprintf(lines[AREA_RELOAD_BEHAVIOR_INDEX].value, " <%s>", reload_opt[g_reloadType].member);
    sprintf(lines[CURSOR_COLOR_INDEX].value, " <%s>", cursorCol_opt[g_cursorColorType].member);
    sprintf(lines[FONT_INDEX].value, " <%s>", font_opt[g_fontType].member);

    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}

void SettingsMenu::initFont() {
    if (g_fontType >= 0 && g_fontType < FONT_OPTIONS_COUNT) {
        char buf[40] = {0};
        sprintf(buf, "tpgz/fonts/%s.fnt", font_opt[g_fontType].member);
        Font::loadFont(buf);
    }
}