#pragma once

#include "menus/cheats_menu.h"
#include "menus/memory_menu.h"
#include "menus/position_settings_menu.h"
#include "menus/scene_menu.h"
#include "menus/settings_menu.h"
#include "menus/tools_menu.h"
#include "menus/hundo_saves_menu.h"
#include "libtp_c/include/msl_c/string.h"
#include "libtp_c/include/dolphin/mtx/vec.h"

#define GZ_SAVE_VERSION_NUMBER 0
#define GZ_SAVE_ENTRIES_AMNT 10

#ifdef GCN_NTSCU
#define sTmpBuf 0x803ecf40
#endif
#ifdef GCN_PAL
#define sTmpBuf 0x803eeee0
#endif
#ifdef GCN_NTSCJ
#define sTmpBuf 0x803e7080
#endif
#ifdef WII_NTSCU_10
#define sTmpBuf 0x8046a3e0
#endif
#ifdef WII_PAL
#define sTmpBuf 0x804522e0
#endif

// index into qlog where these exist
#define SPAWN_INDEX 96
#define ROOM_INDEX 97
#define STAGE_INDEX 88

struct AreaReload {
    uint8_t temp_flags[0x20];
    uint8_t tears[4];
};

typedef void (*LoadingCallback)(void);

class special {
public:
    special(int i_idx, LoadingCallback cb_during, LoadingCallback cb_after) {
        idx = i_idx;
        CallbackDuring = cb_during;
        CallbackAfter = cb_after;
    }

    uint32_t idx;
    LoadingCallback CallbackDuring;
    LoadingCallback CallbackAfter;

private:
};

struct PracticeFileOpts {
    void (*inject_options_before_load)();
    void (*inject_options_during_load)();
    void (*inject_options_after_load)();
    int inject_options_after_counter = 0;
};

struct PracticeSaveInfo {
    uint8_t requirements;
    uint8_t _p0[1];
    uint16_t angle;
    Vec position;
    Vec cam_pos;
    Vec cam_target;
    uint32_t counter;
    char filename[32];
    uint8_t _p1[4];
} __attribute__((packed));

class SaveManager {
public:
    PracticeFileOpts mPracticeFileOpts;
    PracticeSaveInfo mPracticeSaveInfo __attribute__((aligned(32)));
    AreaReload mAreaReloadOpts;
    special* mSpecials;
    bool loading_initiated = false;

public:
    static void inject_save(void* buffer);
    static void inject_memfile(void* buffer);
    static void inject_default_before();
    static void inject_default_during();
    static void inject_memfile_during();
    static void inject_default_after();
    static void load_save(uint32_t id, char* category, special* i_specials = nullptr, int size = 0);
    static void load_save_file(const char* fileName);
    static void trigger_load();
    static void default_load();
};

extern SaveManager gSaveManager;

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