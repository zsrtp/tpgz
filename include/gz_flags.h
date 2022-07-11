#pragma once

#include "font.h"
#include "cheats.h"
#include "save_manager.h"
#include "menus/settings_menu.h"
#include "fifo_queue.h"

#ifdef WII_PLATFORM
#define MAX_GZ_FLAGS 16
#define FRAME_ADVANCE_BTN Controller::Z
#endif
#ifdef GCN_PLATFORM
#define MAX_GZ_FLAGS 15
#define FRAME_ADVANCE_BTN GZPad::R
#endif

struct GZFlag {
    bool* mpFlag;
    int mPhase;
    void (*mpActiveFunc)();
    void (*mpDeactiveFunc)();
};

enum {
/* Main Menus */
    GZ_NO_MENU = -1,
    GZ_MAIN_MENU,
    GZ_CHEAT_MENU,
    GZ_FLAGS_MENU,
    GZ_INVENTORY_MENU,
    GZ_MEMORY_MENU,
    GZ_PRACTICE_MENU,
    GZ_SCENE_MENU,
    GZ_SETTINGS_MENU,
    GZ_TOOLS_MENU,
    GZ_WARP_MENU,

/* Flags Sub-Menus */
    GZ_GEN_FLAGS_MENU,
    GZ_DUN_FLAGS_MENU,
    GZ_PORTAL_FLAGS_MENU,
    GZ_FLAG_RECORD_MENU,
    GZ_FLAG_LOG_MENU,

/* Inventory Sub-Menus */
    GZ_WHEEL_MENU,
    GZ_PAUSE_MENU,
    GZ_AMOUNTS_MENU,

/* Memory Sub-Menus */
    GZ_WATCHES_MENU,
    GZ_MEM_EDITOR_MENU,
    GZ_MEMFILES_MENU,

/* Practice Sub-Menus */
    GZ_ANY_SAVES_MENU,
    GZ_HUNDO_SAVES_MENU,
    GZ_AD_SAVES_MENU,

/* Scene Sub-Menus */
    GZ_SPAWN_MENU,
    GZ_ACLIST_MENU,

/* Settings Sub-Menus */
    GZ_POS_SETTINGS_MENU,
};

extern bool g_framePaused;

enum LoopPhase { GAME_LOOP, POST_GAME_LOOP };

inline bool GZ_checkCheat(int cheatIdx) {
    return g_cheats[cheatIdx].active;
}

inline bool GZ_checkDropShadows() {
    return g_dropShadows;
}

inline void GZ_setFifoVisible(bool visible) {
    g_fifoVisible = visible;
}

void GZ_execute(int phase);
void GZ_drawFrameTex(Texture* pauseTex, Texture* playTex);

#define sPauseTimer (*(uint8_t *)(sPauseTimer_addr))