#include "menus/menu_tools_rng/include/tools_rng_menu.h"
#include "menus/utils/menu_mgr.h"
#include "utils/hook.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"
#include "libtp_c/include/msl_c/math.h"

#define MAX_RNG_PRESETS 10

KEEP_VAR ToolsRngData* toolsRngData;

KEEP_FUNC ToolsRngMenu::ToolsRngMenu(Cursor& cursor)
    : Menu(cursor),
      lines{{"freeze rng values", FREEZE_RNG_INDEX, "Freeze main 3 RNG values", true,
             ACTIVE_FUNC(STNG_TOOLS_FREEZE_RNG)},
            {"randomize values", RANDOMIZE_INDEX, "Advance one iteration of the Wichmann-Hill algorithm"},
            {"load preset", LOAD_PRESET_INDEX, "Apply the RNG preset onto the current RNG values"},
            {"rng presets:", PRESET_OPTIONS_INDEX, "Scroll through various known RNG values", false, nullptr}
            } {
}

ToolsRngMenu::~ToolsRngMenu() {}

void ToolsRngMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    GZSettingEntry* stng = nullptr;

    RngPresetMember rng_opt[MAX_RNG_PRESETS] = {
        {"zant head 1st platform", 4134, 7345, 3379},
        {"zant head 3rd platform", 25170, 3588, 2141},
        {"zant head back left", 4995, 3011, 718},
        {"zant head back mid", 12361, 7069, 29087},
        {"zant head back right", 10870, 5151, 9268},
        {"horseback A (middle)", 5872, 10996, 94},
        //{"horseback B (down but goes right for 2nd node)", 5235, 12278, 15980},
        {"horseback B (down)", 2793, 21116, 3179},
        {"horseback C (up)", 29379, 13886, 25014},
        {"kb1 left after 3rd hit", 5872, 10996, 94},
        {"kb1 right after 3rd hit", 25170, 3588, 2141},
    };

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        switch (cursor.y) {
            case RANDOMIZE_INDEX:
                r0 = (r0 * 171) % 30269;
                r1 = (r1 * 172) % 30307;
                r2 = (r2 * 170) % 30323;

                store_frozen_rng_values(r0, r1, r2);
                break;
            case LOAD_PRESET_INDEX:
                stng = GZStng_get(STNG_TOOLS_FREEZE_RNG);
                if (!stng) {
                    stng = new GZSettingEntry{STNG_TOOLS_FREEZE_RNG, sizeof(bool), new bool};
                    g_settings.push_back(stng);
                }
                if (stng)
                    *(bool*)stng->data = true;

                r0 = rng_opt[toolsRngData->l_rng_preset_idx].r0;
                r1 = rng_opt[toolsRngData->l_rng_preset_idx].r1;
                r2 = rng_opt[toolsRngData->l_rng_preset_idx].r2;

                store_frozen_rng_values(r0, r1, r2);
                break;
            case FREEZE_RNG_INDEX:
                stng = GZStng_get(STNG_TOOLS_FREEZE_RNG);

                if (!stng) {
                    stng = new GZSettingEntry{STNG_TOOLS_FREEZE_RNG, sizeof(bool), new bool};
                    g_settings.push_back(stng);
                }

                if (stng)
                    *(bool*)stng->data = !*(bool*)stng->data;

                if (stng && *(bool*)stng->data) {
                    store_frozen_rng_values(r0, r1, r2);
                }
                break;
        }
    }
    
    switch (cursor.y) {
        case PRESET_OPTIONS_INDEX:
            cursor.x = toolsRngData->l_rng_preset_idx;
            cursor.move(MAX_RNG_PRESETS, MENU_LINE_NUM);

            if (cursor.y == PRESET_OPTIONS_INDEX) {
                toolsRngData->l_rng_preset_idx = cursor.x;
            }
            break;
        default:
            cursor.move(0, MENU_LINE_NUM);
            break;
        }
    
    lines[PRESET_OPTIONS_INDEX].printf(" <%s>", rng_opt[toolsRngData->l_rng_preset_idx].member);

    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
    GZ_drawRngLines(lines, cursor.y, MENU_LINE_NUM);
}

KEEP_FUNC void store_frozen_rng_values(int r0, int r1, int r2) {
    preset_r0 = r0;
    preset_r1 = r1;
    preset_r2 = r2;
}
