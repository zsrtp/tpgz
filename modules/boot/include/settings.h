#pragma once

#include <stdint.h>
#include "utils/lines.h"
#include "utils/containers/deque.h"

#define CURSOR_RGBA g_cursorColor
#define FONT_OPTIONS_COUNT ARRAY_COUNT(g_font_opt)

#define LOAD_AREA 0
#define LOAD_FILE 1

#define ACTIVE_FUNC(id) []() { return GZStng_getData(id, false); }

extern bool g_swap_equips_flag;
extern ListMember g_font_opt[7];

// WARNING
// The order is important, DO NOT add entries in the middle of the enum.
// Add them at the end, even if it should be with an other group.
// Changes in the order is only allowed when the
// version number GZ_SAVE_VERSION_NUMBER is changed.
enum GZSettingID : uint32_t {
    // Miscellaneous
    STNG_DROP_SHADOWS,
    STNG_AREA_RELOAD_BEHAVIOUR,
    STNG_CURSOR_COLOR,
    STNG_FONT,
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
    STNG_SPRITES_INPUT_VIEWER,
    STNG_SPRITES_MENU,
    STNG_SPRITES_DEBUG_INFO,
    STNG_SPRITES_TIMER_SPR,
    STNG_SPRITES_LOAD_TIMER_SPR,
    STNG_SPRITES_IGT_TIMER_SPR,
    STNG_SPRITES_FIFO_SPR,
    STNG_SPRITES_HEAP_INFO,
    STNG_SPRITES_MASH_INFO,
    STNG_SPRITES_TRANSFORM_IND,
    // New Adds
    STNG_SCENE_LJA_PROJECTION,
    STNG_SCENE_MIDNA_CHARGE_PROJECTION,
    // Combos
    STNG_CMD_FRAME_PAUSE,
    STNG_CMD_FRAME_ADVANCE,
    STNG_CMD_TIMER_TOGGLE,
    STNG_CMD_TIMER_RESET,
    STNG_CMD_STORE_POSITION,
    STNG_CMD_LOAD_POSITION,
    STNG_CMD_RELOAD_AREA,
    STNG_CMD_FREE_CAM,
    STNG_CMD_MOVE_LINK,
    STNG_CMD_BIT, // Wii only, but we reserve the id anyway
    STNG_CMD_GORGE_VOID,
    STNG_CMD_MOON_JUMP,
    // New Adds
    STNG_TOOLS_LFC,
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
void GZStng_add(GZSettingID id, void* data, size_t size);
/**
 * Removes a setting from the list.
 */
void GZStng_remove(GZSettingID id);
/**
 * Returns a setting entry if it is in the list. nullptr otherwise.
 */
GZSettingEntry* GZStng_get(GZSettingID id);
/**
 * Returns a list of all the ids of the settings in the list.
 */
tpgz::containers::deque<GZSettingID>* GZStng_getList();

template <typename T>
T GZStng_getData(GZSettingID id, T defaultValue) {
    auto* stng = GZStng_get(id);
    return stng ? *static_cast<T*>(stng->data) : defaultValue;
}

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
    auto* stng = GZStng_get(STNG_DROP_SHADOWS);
    return stng && *static_cast<bool*>(stng->data);
}
