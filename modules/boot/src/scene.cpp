#include "scene.h"
#include "settings.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/d/meter/d_meter_HIO.h"

KEEP_FUNC void GZ_freezeTime() {
    if (GZStng_getData(STNG_SCENE_FREEZE_TIME, false)) {
        dStage_roomControl_c__setTimePass(TIME_STOP);
    }
}

bool l_initCamLock;
KEEP_FUNC void GZ_freezeCamera() {
    l_initCamLock = true;
    dComIfGp_getEventManager().mCameraPlay = 1;
}

KEEP_FUNC void GZ_unfreezeCamera() {
    if (l_initCamLock) {
        dComIfGp_getEventManager().mCameraPlay = 0;
        l_initCamLock = false;
    }
}

bool l_initHide;
KEEP_FUNC void GZ_hideHUD() {
    g_drawHIO.mHUDAlpha = 0.0f;
    l_initHide = true;
}

KEEP_FUNC void GZ_showHUD() {
    if (l_initHide) {
        g_drawHIO.mHUDAlpha = 1.0f;
        l_initHide = false;
    }
}

bool l_initActorFreeze;
KEEP_FUNC void GZ_freezeActors() {
    l_initActorFreeze = true;
    g_dComIfAc_gameInfo.freeze = true;
}

KEEP_FUNC void GZ_unfreezeActors() {
    if (l_initActorFreeze) {
        g_dComIfAc_gameInfo.freeze = false;
        l_initActorFreeze = false;
    }
}

bool l_initActorHide;
KEEP_FUNC void GZ_hideActors() {
    l_initActorHide = true;
    fopAc_ac_c__stopStatus |= 0x100;
}

KEEP_FUNC void GZ_showActors() {
    if (l_initActorHide) {
        fopAc_ac_c__stopStatus &= ~0x100;
        l_initActorHide = false;
    }
}
