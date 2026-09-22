#include "menus/menu_tools_checkers/include/tools_checkers_menu.h"
#include "menus/utils/menu_mgr.h"

#define MAX_GORGE_VOID_OPTIONS 3

KEEP_FUNC CheckersMenu::CheckersMenu(Cursor& cursor)
    : Menu(cursor), lines{
#ifdef WII_PLATFORM
            {"bit", BIT_INDEX, "use " BACK_IN_TIME_TEXT " to warp to ordon bridge", true,
             ACTIVE_FUNC(STNG_TOOLS_BIT)},
            {"slash", SLASH_INDEX, "frame counter for slash out of item wheel", true,
            ACTIVE_FUNC(STNG_TOOLS_SLASH)},
#endif
            {"coro td", COROTD_INDEX, "show frame info when doing coro td", true,
             ACTIVE_FUNC(STNG_TOOLS_COROTD)},
            {"ebmb", EBMB_INDEX, "show frame information when doing ending blow moon boots", 
             true, ACTIVE_FUNC(STNG_TOOLS_EBMB)},
            {"elevator escape", ELEVATOR_ESCAPE_INDEX, "show frame info when doing elevator escape",
             true, ACTIVE_FUNC(STNG_TOOLS_ELEVATOR_ESCAPE)},
            {"ladder freezard cancel", LFC_INDEX, "ladder freezard cancel checker",
             true, ACTIVE_FUNC(STNG_TOOLS_LFC)},
            {"a/b mash rate", MASH_CHECKER_INDEX, "display A/B button mashing speeds", true,
             ACTIVE_FUNC(STNG_TOOLS_MASH_CHECKER)},
            {"rolling", ROLL_INDEX, "frame counter for chaining rolls", true,
             ACTIVE_FUNC(STNG_TOOLS_ROLL)},
            {"universal map delay", UMD_INDEX, "practice snowpeak universal map delay timing", true,
             ACTIVE_FUNC(STNG_TOOLS_UMD)},
            {"fast eel regrab", FAST_EEL_REGRAB_INDEX, "show frame info when fast morpheel regrab (claw before boots)", true, ACTIVE_FUNC(STNG_TOOLS_FAST_EEL_REGRAB)},
            {
                "gorge void", 
                GORGE_INDEX, 
                "use " GORGE_VOID_TEXT " to warp to kakariko gorge",
                false, 
                nullptr, 
                MAX_GORGE_VOID_OPTIONS
            },
            } {}

CheckersMenu::~CheckersMenu() {}

void CheckersMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    GZSettingEntry* stng = nullptr;

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        switch (cursor.y) {

            #ifdef WII_PLATFORM
            case BIT_INDEX:
                stng = GZStng_get(STNG_TOOLS_BIT);
                if (!stng) {
                    stng = new GZSettingEntry{STNG_TOOLS_BIT, sizeof(bool), new bool{false}};
                    g_settings.push_back(stng);
                }
                *static_cast<bool*>(stng->data) = !*static_cast<bool*>(stng->data);
                break;
            case SLASH_INDEX:
                stng = GZStng_get(STNG_TOOLS_SLASH);
                if (!stng) {
                    stng = new GZSettingEntry{STNG_TOOLS_SLASH, sizeof(bool), new bool{false}};
                    g_settings.push_back(stng);
                }
                *static_cast<bool*>(stng->data) = !*static_cast<bool*>(stng->data);
                break;
            #endif

            case COROTD_INDEX:
                stng = GZStng_get(STNG_TOOLS_COROTD);
                if (!stng) {
                    stng = new GZSettingEntry{STNG_TOOLS_COROTD, sizeof(bool), new bool{false}};
                    g_settings.push_back(stng);
                }
                *static_cast<bool*>(stng->data) = !*static_cast<bool*>(stng->data);
                break;
            case EBMB_INDEX:
                stng = GZStng_get(STNG_TOOLS_EBMB);
                if (!stng) {
                    stng = new GZSettingEntry{STNG_TOOLS_EBMB, sizeof(bool), new bool{false}};
                    g_settings.push_back(stng);
                }
                *static_cast<bool*>(stng->data) = !*static_cast<bool*>(stng->data);
                break;
            case ELEVATOR_ESCAPE_INDEX:
                stng = GZStng_get(STNG_TOOLS_ELEVATOR_ESCAPE);
                if (!stng) {
                    stng = new GZSettingEntry{STNG_TOOLS_ELEVATOR_ESCAPE, sizeof(bool), new bool{false}};
                    g_settings.push_back(stng);
                }
                *static_cast<bool*>(stng->data) = !*static_cast<bool*>(stng->data);
                break;
            case LFC_INDEX:
                stng = GZStng_get(STNG_TOOLS_LFC);
                if (!stng) {
                    stng = new GZSettingEntry{STNG_TOOLS_LFC, sizeof(bool), new bool{false}};
                    g_settings.push_back(stng);
                }
                *static_cast<bool*>(stng->data) = !*static_cast<bool*>(stng->data);
                break;
            case MASH_CHECKER_INDEX:
                stng = GZStng_get(STNG_TOOLS_MASH_CHECKER);
                if (!stng) {
                    stng = new GZSettingEntry{STNG_TOOLS_MASH_CHECKER, sizeof(bool), new bool{false}};
                    g_settings.push_back(stng);
                }
                *static_cast<bool*>(stng->data) = !*static_cast<bool*>(stng->data);
                break;
            case ROLL_INDEX:
                stng = GZStng_get(STNG_TOOLS_ROLL);
                if (!stng) {
                    stng = new GZSettingEntry{STNG_TOOLS_ROLL, sizeof(bool), new bool{false}};
                    g_settings.push_back(stng);
                }
                *static_cast<bool*>(stng->data) = !*static_cast<bool*>(stng->data);
                break;
            case UMD_INDEX:
                stng = GZStng_get(STNG_TOOLS_UMD);
                if (!stng) {
                    stng = new GZSettingEntry{STNG_TOOLS_UMD, sizeof(bool), new bool{false}};
                    g_settings.push_back(stng);
                }
                *static_cast<bool*>(stng->data) = !*static_cast<bool*>(stng->data);
                break;
            case FAST_EEL_REGRAB_INDEX:
                stng = GZStng_get(STNG_TOOLS_FAST_EEL_REGRAB);
                if (!stng) {
                    stng = new GZSettingEntry{STNG_TOOLS_FAST_EEL_REGRAB, sizeof(bool), new bool{false}};
                    g_settings.push_back(stng);
                }
                *static_cast<bool*>(stng->data) = !*static_cast<bool*>(stng->data);
                break;
        }
    }

    ListMember gorge_opt[MAX_GORGE_VOID_OPTIONS] = {"off", "wolf", "human"};

    stng = nullptr;
    auto prev_x = cursor.x;
    // handle list rendering
    switch (cursor.y) {
        case GORGE_INDEX:
            stng = GZStng_get(STNG_TOOLS_GORGE);
            cursor.x = stng ? *static_cast<uint32_t*>(stng->data) : 0;
            prev_x = cursor.x;
            cursor.move(MAX_GORGE_VOID_OPTIONS, MENU_LINE_NUM);

            if (cursor.y == GORGE_INDEX) {
                if (cursor.x != prev_x) {
                    if (!stng) {
                        stng = new GZSettingEntry{STNG_TOOLS_GORGE, sizeof(uint32_t), new uint32_t(cursor.x)};
                        g_settings.push_back(stng);
                    } else {
                        *static_cast<uint32_t*>(stng->data) = cursor.x;
                    }
                }
            }
            break;
        default:
            cursor.move(0, MENU_LINE_NUM);
            break;
    }
    
    lines[GORGE_INDEX].printf(" <%s>", gorge_opt[GZStng_getData<uint32_t>(STNG_TOOLS_GORGE, 0)].member);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
