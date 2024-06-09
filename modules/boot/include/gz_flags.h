#pragma once

#include "font.h"
#include "cheats.h"
#include "save_manager.h"
#include "settings.h"
#include "fifo_queue.h"
#include "utils/containers/deque.h"
#include "libtp_c/include/m_Do/m_Re_controller_pad.h"

#ifdef WII_PLATFORM
#define FRAME_ADVANCE_BTN GZPad::TWO
#define FRAME_ADVANCE_PAD CButton::TWO
#endif
#ifdef GCN_PLATFORM
#define FRAME_ADVANCE_BTN GZPad::R
#define FRAME_ADVANCE_PAD CButton::R
#endif

enum GZFlags {
    GZFLG_GORGE_VOID,
#ifdef WII_PLATFORM
    GZFLG_BIT,
#endif
    GZFLG_ROLL,
    GZFLG_COROTD,
    GZFLG_UMD,
    GZFLG_FREEZE_ACTOR,
    GZFLG_HIDE_ACTOR,
    GZFLG_FREEZE_CAMERA,
    GZFLG_HIDE_HUD,
    GZFLG_FREEZE_TIME,
    GZFLG_DISABLE_BGM,
    GZFLG_DISABLE_SFX,
};

struct GZFlag {
    GZFlags id;
    bool (*mpFlag)();
    int mPhase;
    void (*mpActiveFunc)();
    void (*mpDeactiveFunc)();
};

extern bool g_framePaused;

extern tpgz::containers::deque<GZFlag*> g_gzFlags;

void GZFlg_addFlag(GZFlag* flag);
GZFlag* GZFlg_removeFlag(GZFlags flag_id);

enum LoopPhase { GAME_LOOP, POST_GAME_LOOP };

inline void GZ_setFifoVisible(bool visible) {
    g_fifoVisible = visible;
}

void GZ_frameAdvance();
void GZ_execute(int phase);
void GZ_drawFrameTex(Texture* pauseTex, Texture* playTex);

extern volatile uint8_t sPauseTimer;

bool GZ_freezeActors_active();
bool GZ_hideActors_active();
bool GZ_freezeCamera_active();
bool GZ_hideHUD_active();
bool GZ_freezeTime_active();
bool GZ_disableBgm_active();
bool GZ_disableSFX_active();