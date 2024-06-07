#pragma once

#include <stdint.h>
#include "utils/lines.h"
#include "utils/containers/deque.h"

#define CURSOR_RGBA g_cursorColor
#define FONT_OPTIONS_COUNT (sizeof(g_font_opt) / sizeof(g_font_opt[0]))

#define LOAD_AREA 0
#define LOAD_FILE 1

extern bool g_swap_equips_flag;
extern ListMember g_font_opt[7];

// WARNING
// The order is important, DO NOT add entries in the middle of the enum.
// Add them at the end, even if it should be with an other group.
// Changes in the order is only allowed when the
// version number GZ_SAVE_VERSION_NUMBER is changed.
enum GZSettingID : uint32_t {
    // Cheats
    STNG_CHEATS_INFINITE_AIR,
    STNG_CHEATS_INFINITE_ARROWS,
    STNG_CHEATS_INFINITE_BOMBS,
    STNG_CHEATS_INFINITE_HEARTS,
    STNG_CHEATS_INFINITE_OIL,
    STNG_CHEATS_INFINITE_RUPEES,
    STNG_CHEATS_INFINITE_SLINGSHOT,
    STNG_CHEATS_INVINCIBLE,
    STNG_CHEATS_INVINCIBLE_ENEMIES,
    STNG_CHEATS_MOON_JUMP,
    STNG_CHEATS_DOOR_STORAGE,
    STNG_CHEATS_SUPER_CLAWSHOT,
    STNG_CHEATS_UNRESTRICTED_ITEMS,
    STNG_CHEATS_TRANSFORM_ANYWHERE,
    STNG_CHEATS_DISABLE_ITEM_TIMER,
    STNG_CHEATS_GALE_LJA,  // Wii only, but we reserve the id anyway
    // Tools
    STNG_TOOLS_RELOAD_AREA,
    STNG_TOOLS_FRAME_ADVANCE,
    STNG_TOOLS_FAST_BONK,
    STNG_TOOLS_FAST_MOVEMENT,
    STNG_TOOLS_GORGE,
    STNG_TOOLS_BIT,  // Wii only, but we reserve the id anyway
    STNG_TOOLS_COROTD,
    STNG_TOOLS_UMD,
    STNG_TOOLS_INPUT_VIEWER,
    STNG_TOOLS_LINK_DEBUG,
    STNG_TOOLS_HEAP_DEBUG,
    STNG_TOOLS_SAND,
    STNG_TOOLS_ROLL,
    STNG_TOOLS_MASH_CHECKER,
    STNG_TOOLS_TELEPORT,
    STNG_TOOLS_TURBO_MODE,
    STNG_TOOLS_TIMER,
    STNG_TOOLS_LOAD_TIMER,
    STNG_TOOLS_IGT_TIMER,
    STNG_TOOLS_FREE_CAM,
    STNG_TOOLS_MOVE_LINK,
    STNG_TOOLS_TRANSFORM_INDICATOR,
    // Scene
    STNG_SCENE_FREEZE_ACTOR,
    STNG_SCENE_HIDE_ACTOR,
    STNG_SCENE_DISABLE_BG,
    STNG_SCENE_DISABLE_SFX,
    STNG_SCENE_FREEZE_CAMERA,
    STNG_SCENE_HIDE_HUD,
    STNG_SCENE_FREEZE_TIME,
    // Watches
    STNG_WATCHES,
    // Sprites
    STNG_SPRITES_VIEWER,
    STNG_SPRITES_MENU,
    STNG_SPRITES_DEBUG_INFO,
    STNG_SPRITES_TIMER_SPR,
    STNG_SPRITES_LOAD_TIMER_SPR,
    STNG_SPRITES_IGT_TIMER_SPR,
    STNG_SPRITES_FIFO_SPR,
    STNG_SPRITES_HEAP_INFO,
    STNG_SPRITES_MASH_INFO,
    STNG_SPRITES_TRANSFORM_IND,
    // Commands
    STNG_COMMANDS_STORE_POSITION,
    STNG_COMMANDS_LOAD_POSITION,
    STNG_COMMANDS_MOON_JUMP,
    STNG_COMMANDS_RELOAD_AREA,
    STNG_COMMANDS_TIMER_TOGGLE,
    STNG_COMMANDS_TIMER_RESET,
    STNG_COMMANDS_FREE_CAM,
    STNG_COMMANDS_MOVE_LINK,
    STNG_COMMANDS_FRAME_PAUSE,
    // Miscellaneous
    STNG_DROP_SHADOWS,
    STNG_AREA_RELOAD_BEHAVIOUR,
    STNG_CURSOR_COLOR,
    STNG_FONT,
};

struct GZSettingEntry {
    GZSettingID id;
    size_t size;
    void* data;
};

extern tpgz::containers::deque<GZSettingEntry*> g_settings;

/**
 * If the setting is not yet in the list, adds it.
 * Otherwise, deletes the old data, and replaces it by the provided one.
 */
void GZStng_addSetting(GZSettingID id, void* data, size_t size);
/**
 * Removes a setting from the list.
 */
void GZStng_removeSetting(GZSettingID id);
/**
 * Returns a setting entry if it is in the list. nullptr otherwise.
 */
GZSettingEntry* GZStng_getSetting(GZSettingID id);
/**
 * Returns a list of all the ids of the settings in the list.
 */
tpgz::containers::deque<GZSettingID>* GZStng_getSettingsList();

enum cursor_colors {
    CURSOR_GREEN,
    CURSOR_BLUE,
    CURSOR_RED,
    CURSOR_ORANGE,
    CURSOR_YELLOW,
    CURSOR_PURPLE
};

void GZ_initFont();

inline bool GZ_checkDropShadows() {
    auto* stng = GZStng_getSetting(STNG_DROP_SHADOWS);
    return stng && *static_cast<bool*>(stng->data);
}
