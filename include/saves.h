#include "menu.h"
#include "menus/cheats_menu.h"
#include "menus/memory_menu.h"
#include "menus/position_settings_menu.h"
#include "menus/scene_menu.h"
#include "menus/settings_menu.h"
#include "menus/tools_menu.h"

#define GZ_SAVE_VERSION_NUMBER 0
#define GZ_SAVE_ENTRIES_AMNT 10

// These numbers can only change when we change the GZ_SAVE_VERSION_NUMBER,
// otherwise, only new entries can be added.
enum GZSaveIndex {
    SV_CHEATS_INDEX = 0,
    SV_TOOLS_INDEX = 1,
    SV_SCENE_INDEX = 2,
    SV_WATCHES_INDEX = 3,
    SV_SPRITES_INDEX = 4,
    SV_DROP_SHADOW_INDEX = 5,
    SV_AREA_RELOAD_INDEX = 6,
    SV_CURSOR_COLOR_INDEX = 7,
    SV_COMMANDS = 8,
    SV_FONT_INDEX = 9,
};

struct GZSaveHeader {
    uint32_t version;
    uint32_t entries;
    uint32_t offsetsLoc;
    uint32_t sizesLoc;
};

struct GZSaveLayout {
    Cheats::Cheat CheatItems[CHEAT_AMNT];
    Tools::Tool ToolItems[TOOL_AMNT];
    Scene::SceneItem SceneItems[SCENE_AMNT];
    MemoryWatch Watches[MAX_WATCHES];
    Vec2 sprite_offsets[SPRITES_AMNT];
    bool commands_states[COMMANDS_AMNT];
    bool g_drop_shadows;
    int g_area_reload_behavior;
    int g_cursor_color;
    int g_font;
};

struct GZSaveFile {
    GZSaveHeader header;
    uint32_t offsets[GZ_SAVE_ENTRIES_AMNT];
    uint32_t sizes[GZ_SAVE_ENTRIES_AMNT];
    GZSaveLayout data;
};