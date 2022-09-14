#pragma once

#include "font.h"
#include "cheats.h"
#include "save_manager.h"
#include "settings.h"
#include "fifo_queue.h"

#ifdef WII_PLATFORM
#define MAX_GZ_FLAGS 16
#define FRAME_ADVANCE_BTN GZPad::TWO
#define FRAME_ADVANCE_PAD CButton::TWO
#endif
#ifdef GCN_PLATFORM
#define MAX_GZ_FLAGS 15
#define FRAME_ADVANCE_BTN GZPad::R
#define FRAME_ADVANCE_PAD CButton::R
#endif

struct GZFlag {
    bool* mpFlag;
    int mPhase;
    void (*mpActiveFunc)();
    void (*mpDeactiveFunc)();
};

extern bool g_injectSave;
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

void GZ_frameAdvance();
void GZ_execute(int phase);
void GZ_drawFrameTex(Texture* pauseTex, Texture* playTex);

extern volatile uint8_t sPauseTimer;