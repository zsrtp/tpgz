#include "utils/hook.h"
#include <cstdio>
#include "cheats.h"
#include "controller.h"
#include "boot.h"
#include "rels/include/patch.h"
#include "flaglog.h"
#include "fifo_queue.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/SSystem/SComponent/c_lib.h"
#include "utils/card.h"
#include "global_data.h"
#include "memfiles.h"
#include "rels/include/cxx.h"
#include "rels/include/defines.h"
#include "save_manager.h"
#include "settings.h"
#include "collision_view.h"
#include "features/projection_view/include/projection_view.h"
#include "libtp_c/include/m_Do/m_Do_printf.h"
#include "libtp_c/include/d/s/d_s_logo.h"

#define HOOK_DEF(rettype, name, params)                                                            \
    typedef rettype(*tp_##name##_t) params;                                                        \
    tp_##name##_t name##Trampoline;

HOOK_DEF(void, fapGm_Execute, (void));
HOOK_DEF(void, ExceptionCallback, (void));
HOOK_DEF(void, draw, (void*));

#ifdef GCN_PLATFORM
#define PAD_READ_RETURN_OFFSET (0x2FC)
#endif
#ifdef WII_PLATFORM
#define PAD_READ_RETURN_OFFSET (0x2DC)
#endif

extern volatile uint32_t gzCrashReport;

HOOK_DEF(uint32_t, PADRead, (uint16_t*));
HOOK_DEF(uint32_t, checkHookshotStickBG, (void*, void*));
HOOK_DEF(void, setSpecialGravity, (daAlink_c*, float, float, int));
HOOK_DEF(uint32_t, checkCastleTownUseItem, (uint16_t));
HOOK_DEF(uint32_t, query042, (void*, void*, int));

HOOK_DEF(void, onEventBit, (void*, uint16_t));
HOOK_DEF(void, offEventBit, (void*, uint16_t));
HOOK_DEF(void, onSwitch, (void*, int, int));
HOOK_DEF(void, putSave, (void*, int));

HOOK_DEF(void, dCcS__draw, (dCcS*));
HOOK_DEF(void, BeforeOfPaint, (void));
HOOK_DEF(void, dCcS__MoveAfterCheck, (dCcS*));

HOOK_DEF(int, dScnPly__phase_1, (void*));
HOOK_DEF(int, dScnPly__phase_4, (void*));

HOOK_DEF(void, dBgS_Acch__CrrPos, (dBgS_Acch*, dBgS&));
HOOK_DEF(void, daAlink_c__setCutJumpSpeed, (daAlink_c*, int));
HOOK_DEF(void, daAlink_c__posMove, (daAlink_c*));

#ifdef WII_PLATFORM
HOOK_DEF(void, dScnLogo_c__create, (dScnLogo_c_wii*));
HOOK_DEF(void, dScnLogo_c__dvdWaitDraw, (dScnLogo_c_wii*));
HOOK_DEF(int, mDoGph_gInf_c__startFadeOut, (int));
#else
HOOK_DEF(void, dScnLogo_c__warningInDraw, (dScnLogo_c*));
#endif

namespace Hook {
void gameLoopHook(void) {
    game_loop();
    fapGm_ExecuteTrampoline();
    post_game_loop();
}

void drawHook(void* p1) {
    drawTrampoline(p1);
    draw();
}

#ifdef PR_TEST
void myExceptionCallbackHook(void) {
    ExceptionCallbackTrampoline();
    gzCrashReport = 1;
    DCFlushRange((void*)(&gzCrashReport), sizeof(gzCrashReport));
    ICInvalidateRange((void*)(&gzCrashReport), sizeof(gzCrashReport));
}
#endif  // PR_TEST

uint32_t readControllerHook(uint16_t* p1) {
    auto returnValue = PADReadTrampoline(p1);
    GZ_readController();
    return returnValue;
}

uint32_t superClawshotHook(void* p1, void* p2) {
    if (GZ_checkCheat(STNG_CHEATS_SUPER_CLAWSHOT)) {
        return 1;
    } else {
        return checkHookshotStickBGTrampoline(p1, p2);
    }
}

void disableGravityHook(daAlink_c* i_this, float p1, float p2, int p3) {
    if (g_moveLinkEnabled || g_actorViewEnabled) {
        return setSpecialGravityTrampoline(i_this, 0.0f, p2, p3);
    } else {
        return setSpecialGravityTrampoline(i_this, p1, p2, p3);
    }
}

uint32_t unrestrictedItemsHook(uint16_t p1) {
    if (GZ_checkCheat(STNG_CHEATS_UNRESTRICTED_ITEMS)) {
        return 1;
    } else {
        return checkCastleTownUseItemTrampoline(p1);
    }
}

uint32_t transformAnywhereHook(void* p1, void* p2, int p3) {
    if (GZ_checkCheat(STNG_CHEATS_TRANSFORM_ANYWHERE)) {
        return 0;
    } else {
        return query042Trampoline(p1, p2, p3);
    }
}

static char buf[40];
void onEventBitHook(void* addr, uint16_t pFlag) {
    if (g_flagLogEnabled) {
        if (addr == &g_dComIfG_gameInfo.info.mTmp) {
            snprintf(buf, sizeof(buf), "%s[0x%X] : %X | ON", "Event Tmp", pFlag >> 8, pFlag & 0xFF);
        } else {
            snprintf(buf, sizeof(buf), "%s[0x%X] : %X | ON", "Event", pFlag >> 8, pFlag & 0xFF);
        }
        FIFOQueue::push(buf, Queue, 0xFFFFFF00);
    }

    return onEventBitTrampoline(addr, pFlag);
}

void offEventBitHook(void* addr, uint16_t pFlag) {
    if (g_flagLogEnabled) {
        if (addr == &g_dComIfG_gameInfo.info.mTmp) {
            snprintf(buf, sizeof(buf), "%s[0x%X] : %X | OFF", "Event Tmp", pFlag >> 8,
                     pFlag & 0xFF);
        } else {
            snprintf(buf, sizeof(buf), "%s[0x%X] : %X | OFF", "Event", pFlag >> 8, pFlag & 0xFF);
        }
        FIFOQueue::push(buf, Queue, 0xFFFFFF00);
    }

    return offEventBitTrampoline(addr, pFlag);
}

void onSwitchHook(void* addr, int pFlag, int i_roomNo) {
    int tmp = pFlag;
    if (g_flagLogEnabled) {
        if (pFlag < 0x80) {
            snprintf(buf, sizeof(buf), "%s[%d] : %d | ON", "Memory Switch", tmp >> 5, tmp & 0x1F);
        } else if (pFlag < 0xC0) {
            tmp -= 0x80;
            snprintf(buf, sizeof(buf), "%s[%d] : %d | ON", "Dan Switch", tmp >> 5, tmp & 0x1F);
        } else if (pFlag < 0xE0) {
            tmp -= 0xC0;
            snprintf(buf, sizeof(buf), "%s[%d] : %d | ON", "Zone Switch", tmp >> 5, tmp & 0x1F);
        } else {
            tmp -= 0xE0;
            snprintf(buf, sizeof(buf), "%s[%d] : %d | ON", "Zone OneSwitch", tmp >> 5, tmp & 0x1F);
        }
        FIFOQueue::push(buf, Queue, 0xFFFFFF00);
    }
    return onSwitchTrampoline(addr, pFlag, i_roomNo);
}

// Stops temp flags from being stored to save when loading memfile
void putSaveHook(void* addr, int stageNo) {
    if (SaveManager::s_injectMemfile) {
        return;
    } else {
        return putSaveTrampoline(addr, stageNo);
    }
}

// Hook to inject save data before dScnPly phase_1 is run
int saveInjectHook(void* i_scene) {
    if (SaveManager::s_injectSave || SaveManager::s_injectMemfile) {
        SaveManager::loadData();
    }
    
    return dScnPly__phase_1Trampoline(i_scene);
}

// Hook to disable save inject flags after dScnPly phase_4 is run
int endSaveInjectHook(void* i_scene) {
    int rt = dScnPly__phase_4Trampoline(i_scene);

    if (SaveManager::s_injectSave || SaveManager::s_injectMemfile) {
        if (gSaveManager.mPracticeFileOpts.inject_options_after_load) {
            SaveManager::s_applyAfterTimer = 5;
        }

        SaveManager::s_injectSave = false;
        SaveManager::s_injectMemfile = false;
    }
    
    return rt;
}

void dCcSDrawHook(dCcS* i_this) {
    GZ_drawCc(i_this);
    return dCcS__drawTrampoline(i_this);
}

void beforeOfPaintHook() {
    BeforeOfPaintTrampoline();
    dDbVw_deleteDrawPacketList();
}

void dCcSMoveAfterCheckHook(dCcS* i_this) {
    dCcS_Data::at_obj_count = i_this->mObjAtCount;
    dCcS_Data::tg_obj_count = i_this->mObjTgCount;
    dCcS_Data::co_obj_count = i_this->mObjCoCount;
    return dCcS__MoveAfterCheckTrampoline(i_this);
}

void dBgS_AcchCrrPosHook(dBgS_Acch* i_this, dBgS& i_bgs) {
    dBgS_Acch__CrrPosTrampoline(i_this, i_bgs);
    if (g_actorViewEnabled/*  || g_moveLinkEnabled */) {
        i_this->m_flags = dBgS_Acch::GROUND_HIT; // sets actor to always be in "coliding with ground" state
    }
}

void daAlink_c__setCutJumpSpeedHook(daAlink_c* i_this, int i_air) {
    daAlink_c__setCutJumpSpeedTrampoline(i_this, i_air);
}

#ifdef WII_PLATFORM
// Skip intro logos (Wii)
void dScnLogo_c__create(dScnLogo_c_wii* i_this) {
    dScnLogo_c__createTrampoline(i_this);
    i_this->mExecCommand = 14; // dScnLogo_c::EXEC_DVD_WAIT
}

int mDoGph_gInf_c__startFadeOut(int i) {
    return mDoGph_gInf_c__startFadeOutTrampoline(i);
}

void dScnLogo_c__dvdWaitDraw(dScnLogo_c_wii* i_this) {
    // fade out
    mDoGph_gInf_c__startFadeOutTrampoline(0);
    dScnLogo_c__dvdWaitDrawTrampoline(i_this);
}

#else
// Skip intro logos (GCN)
void dScnLogo_c__warningInDraw(dScnLogo_c* i_this) {
    i_this->mExecCommand = dScnLogo_c::EXEC_DVD_WAIT;
}
#endif

void setupLJAProjectionLine(daAlink_c* i_this) {
    bool got_it = false;

    // if we haven't done the jump attack yet
    if (i_this->mActionID == daAlink_c::PROC_ATN_ACTOR_WAIT) {
        // lifted from procCutJumpInit
        i_this->mNormalSpeed = 25.0f;
        i_this->speed.y = 27.0f;
        daAlink_c__setCutJumpSpeedTrampoline(i_this, 0); // Calculate jump speed (LJA set here)
        i_this->current.angle.y = i_this->shape_angle.y;
    }

    // store next 20 future projected positions
    for (int i = 0; i < 40; i++) {
        if (i_this->mNormalSpeed > 70.0f) {
            got_it = true;
        }
        daAlink_c__posMoveTrampoline(i_this);
        g_ljaProjectionLine.pos[i] = i_this->current.pos;
        g_ljaProjectionLine.got_it = got_it;
    }
}

void setupMidnaChargeProjectionLine(daAlink_c* i_this) {
    if (i_this->mActionID == daAlink_c::PROC_WOLF_ROLL_ATTACK_MOVE) {
        // this is logic from procWolfLockAttackInit
        fopAc_ac_c* lock_actor = i_this->mWolfLockAcKeep[0].getActor();
        if (lock_actor != NULL) {
            i_this->field_0x37c8 = lock_actor->mEyePos;
        }
        i_this->shape_angle.y = cLib_targetAngleY(&i_this->current.pos,&i_this->field_0x37c8);
        i_this->current.angle.y = i_this->shape_angle.y;
        cXyz l_eyePosDelta = i_this->field_0x37c8 - i_this->mEyePos;

        if (l_eyePosDelta.y < 10.0f) {
            l_eyePosDelta.y = 10.0f;
        } else {
            if (l_eyePosDelta.y > 700.0f)
                l_eyePosDelta.y = 700.0f;
        }

        f32 tmp_f = l_eyePosDelta.absXZ();

        if (tmp_f > 1000.0f) {
            f32 tmp = 1000.0f / tmp_f;
            l_eyePosDelta.x *= tmp;
            l_eyePosDelta.z *= tmp;
        }

        f32 abs = l_eyePosDelta.abs() / 85.0f;

        if (abs < 1.0f)
            abs = 1.0f;

        f32 check_frame = 85.0f / l_eyePosDelta.abs();
        i_this->mNormalSpeed = check_frame * l_eyePosDelta.absXZ();
        setSpecialGravityTrampoline(i_this,(l_eyePosDelta.y * -2.0f) / (abs * abs), i_this->mMaxFallSpeed, 0);
        i_this->speed.y = -i_this->mGravity * abs;

        for (int i = 0; i < 40; i++) {
            daAlink_c__posMoveTrampoline(i_this);
            g_midnaChargeProjectionLine.pos[i] = i_this->current.pos;

            // this is logic from procWolfLockAttack (is this actually required?)
            // if (i_this->field_0x3008 != 0) {
            //     i_this->field_0x3008--;

            //     if (i_this->field_0x3008 == 0) {
            //         setSpecialGravityTrampoline(i_this,-9.0f, i_this->mMaxFallSpeed, 0);
            //     }
            // } else if (i_this->mNormalSpeed > 30.0f) {
            //     cLib_addCalc(&i_this->mNormalSpeed, 30.0f, 0.3f, 5.0f, 1.0f);
            // }
        }
    } else {
        for (int i = 0; i < 40; i++) {
            daAlink_c__posMoveTrampoline(i_this);
            g_midnaChargeProjectionLine.pos[i] = i_this->current.pos;
        }
    }
}

void daAlink_c__posMoveHook(daAlink_c* i_this) {
    if (GZStng_getData(STNG_SCENE_LJA_PROJECTION, false) || GZStng_getData(STNG_SCENE_MIDNA_CHARGE_PROJECTION, false)) {
        // store any variables that may be modified
        f32 speed_y = i_this->speed.y;
        cXyz link_pos = i_this->current.pos;
        s16 shape_angle_y = i_this->shape_angle.y;
        f32 m_normal_speed = i_this->mNormalSpeed;
        s16 current_angle_y = i_this->current.angle.y;
        cXyz eye_pos = i_this->mEyePos;
        s16 field_3008 = i_this->field_0x3008;
        f32 max_fall_speed = i_this->mMaxFallSpeed;
        f32 gravity = i_this->mGravity;
        cXyz field_0x37c8 = i_this->field_0x37c8;
        int reset_flag_3 = i_this->mNoResetFlg3;
        dCcD_Cyl mAtCyl = i_this->field_0x10F0;
        f32 field_0x342c = i_this->field_0x342c;
        f32 field_0x3430 = i_this->field_0x3430;
        dBgS_LinkAcch m_link_acch = i_this->mLinkAcch;

        dCcD_Cyl field_0x850[3];
        dCcD_Cyl field_0xC04[3];

        for (int i = 0; i < 3; i++) {
            field_0x850[i] = i_this->field_0x850[i];
            field_0xC04[i] = i_this->field_0xC04[i];
        }

        if (i_this->mActionID == daAlink_c::PROC_ATN_ACTOR_WAIT || i_this->mActionID == daAlink_c::PROC_CUT_JUMP) {
            if (GZStng_getData(STNG_SCENE_LJA_PROJECTION, false)) {
                setupLJAProjectionLine(i_this);
            }
        }

        if (i_this->mActionID == daAlink_c::PROC_WOLF_ROLL_ATTACK_MOVE || i_this->mActionID == daAlink_c::PROC_WOLF_LOCK_ATTACK || i_this->mActionID == daAlink_c::PROC_WOLF_LOCK_ATTACK_TURN) {
            if (GZStng_getData(STNG_SCENE_MIDNA_CHARGE_PROJECTION, false)) {
                setupMidnaChargeProjectionLine(i_this);
            }
        }

        // restore variables
        i_this->speed.y = speed_y;
        i_this->current.pos = link_pos;
        i_this->shape_angle.y = shape_angle_y;
        i_this->mNormalSpeed = m_normal_speed;
        i_this->current.angle.y = current_angle_y;
        i_this->mEyePos = eye_pos;
        i_this->field_0x3008 = field_3008;
        i_this->mMaxFallSpeed = max_fall_speed;
        i_this->mGravity = gravity;
        i_this->field_0x37c8 = field_0x37c8;
        i_this->mNoResetFlg3 = reset_flag_3;
        i_this->field_0x10F0 = mAtCyl;
        i_this->field_0x342c = field_0x342c;
        i_this->field_0x3430 = field_0x3430;
        i_this->mLinkAcch = m_link_acch;

        for (int i = 0; i < 3; i++) {
            i_this->field_0x850[i] = field_0x850[i];
            i_this->field_0xC04[i] = field_0xC04[i];
        }
    }

    // run the original posMove method if actor view is not enabled
    if (!g_actorViewEnabled) {
        return daAlink_c__posMoveTrampoline(i_this);
    }
}

#ifdef WII_PLATFORM
#define draw_console JUTConsoleManager__draw_void__const
#define f_fapGm_Execute fapGm_Execute_void_
#define clawshot_checkbg daAlink_c__checkHookshotStickBG_cBgS_PolyInfo___
#define set_special_gravity daAlink_c__setSpecialGravity_float__float__int_
#define checkCastleTownUseItem daAlink_c__checkCastleTownUseItem_unsigned_short_
#define query042 dMsgFlow_c__query042_mesg_flow_node_branch____fopAc_ac_c____int_
#define f_onSwitch dSv_info_c__onSwitch_int__int_
#define f_onEventBit dSv_event_c__onEventBit_unsigned_short_
#define f_offEventBit dSv_event_c__offEventBit_unsigned_short_
#define f_putSave dSv_info_c__putSave_int_
#define f_myExceptionCallback myExceptionCallback_unsigned
#define f_dScnPly__phase_1 phase_1_dScnPly_c___
#define f_dScnPly__phase_4 phase_4_dScnPly_c___
#define f_dScnLogo_c__warningInDraw dScnLogo_c__warningInDraw_void_
#define f_dCcS__Draw dCcS__Draw_void_
#define f_dScnPly_BeforeOfPaint mDoGph_BeforeOfDraw_void_
#define f_dCcS__MoveAfterCheck dCcS__MoveAfterCheck_void_
#define f_dBgS_Acch__CrrPos dBgS_Acch__CrrPos_dBgS___
#define f_daAlink_c__setCutJumpSpeed daAlink_c__setCutJumpSpeed_int_
#define f_daAlink_c__posMove daAlink_c__posMove_void_
#define f_dScnLogo_c__create dScnLogo_c__create_void_
#define f_dScnLogo_c__dvdWaitDraw dScnLogo_c__dvdWaitDraw_void_
#define f_mDoGph_gInf_c__startFadeOut mDoGph_gInf_c__startFadeOut_int_
#else
#define draw_console draw__17JUTConsoleManagerCFv
#define f_fapGm_Execute fapGm_Execute__Fv
#define clawshot_checkbg checkHookshotStickBG__9daAlink_cFR13cBgS_PolyInfo
#define set_special_gravity setSpecialGravity__9daAlink_cFffi
#define checkCastleTownUseItem checkCastleTownUseItem__9daAlink_cFUs
#define query042 query042__10dMsgFlow_cFP21mesg_flow_node_branchP10fopAc_ac_ci
#define f_onSwitch onSwitch__10dSv_info_cFii
#define f_onEventBit onEventBit__11dSv_event_cFUs
#define f_offEventBit offEventBit__11dSv_event_cFUs
#define f_putSave putSave__10dSv_info_cFi
#define f_myExceptionCallback myExceptionCallback__FUsP9OSContextUlUl
#define f_dScnPly__phase_1 phase_1__FP9dScnPly_c
#define f_dScnPly__phase_4 phase_4__FP9dScnPly_c
#define f_dScnLogo_c__warningInDraw warningInDraw__10dScnLogo_cFv
#define f_dCcS__Draw Draw__4dCcSFv
#define f_dScnPly_BeforeOfPaint dScnPly_BeforeOfPaint__Fv
#define f_dCcS__MoveAfterCheck MoveAfterCheck__4dCcSFv
#define f_dBgS_Acch__CrrPos CrrPos__9dBgS_AcchFR4dBgS
#define f_daAlink_c__setCutJumpSpeed setCutJumpSpeed__9daAlink_cFi
#define f_daAlink_c__posMove posMove__9daAlink_cFv
#endif

extern "C" {
uint32_t PADRead(uint16_t*);
void draw_console(void*);
void f_fapGm_Execute();
uint32_t clawshot_checkbg(void*, void*);
void set_special_gravity(float, float, int);
uint32_t checkCastleTownUseItem(uint16_t);
uint32_t query042(void*, void*, int);
void f_onSwitch(void*, int, int);
void f_onEventBit(void*, uint16_t);
void f_offEventBit(void*, uint16_t);
void f_putSave(void*, int);
void f_myExceptionCallback();
int f_dScnPly__phase_1(void*);
int f_dScnPly__phase_4(void*);
void f_dCcS__Draw(dCcS*);
void f_dScnPly_BeforeOfPaint();
void f_dCcS__MoveAfterCheck(dCcS*);
void f_dBgS_Acch__CrrPos(dBgS_Acch*, dBgS&);
void f_daAlink_c__setCutJumpSpeed(daAlink_c*, int);
void f_daAlink_c__posMove(daAlink_c*);
#ifdef WII_PLATFORM
void f_dScnLogo_c__create(dScnLogo_c_wii*);
void f_dScnLogo_c__dvdWaitDraw(dScnLogo_c_wii*);
void f_mDoGph_gInf_c__startFadeOut(int);
#else
void f_dScnLogo_c__warningInDraw(dScnLogo_c*);
#endif
}

KEEP_FUNC void applyHooks() {
#define APPLY_HOOK(name, addr, func) name##Trampoline = hookFunction((tp_##name##_t)(addr), func)
    APPLY_HOOK(fapGm_Execute, &f_fapGm_Execute, gameLoopHook);
    APPLY_HOOK(draw, &draw_console, drawHook);
    APPLY_HOOK(PADRead, &PADRead, readControllerHook);
    APPLY_HOOK(checkHookshotStickBG, &clawshot_checkbg, superClawshotHook);
    APPLY_HOOK(setSpecialGravity, &set_special_gravity, disableGravityHook);
    APPLY_HOOK(checkCastleTownUseItem, &checkCastleTownUseItem, unrestrictedItemsHook);
    APPLY_HOOK(query042, &query042, transformAnywhereHook);

    APPLY_HOOK(onSwitch, &f_onSwitch, onSwitchHook);
    APPLY_HOOK(onEventBit, &f_onEventBit, onEventBitHook);
    APPLY_HOOK(offEventBit, &f_offEventBit, offEventBitHook);
    APPLY_HOOK(putSave, &f_putSave, putSaveHook);
    APPLY_HOOK(dScnPly__phase_1, &f_dScnPly__phase_1, saveInjectHook);
    APPLY_HOOK(dScnPly__phase_4, &f_dScnPly__phase_4, endSaveInjectHook);

    APPLY_HOOK(dCcS__draw, &f_dCcS__Draw, dCcSDrawHook);
    APPLY_HOOK(BeforeOfPaint, &f_dScnPly_BeforeOfPaint, beforeOfPaintHook);
    APPLY_HOOK(dCcS__MoveAfterCheck, &f_dCcS__MoveAfterCheck, dCcSMoveAfterCheckHook);

    APPLY_HOOK(dBgS_Acch__CrrPos, &f_dBgS_Acch__CrrPos, dBgS_AcchCrrPosHook);

    APPLY_HOOK(daAlink_c__setCutJumpSpeed, &f_daAlink_c__setCutJumpSpeed, daAlink_c__setCutJumpSpeedHook);
    APPLY_HOOK(daAlink_c__posMove, &f_daAlink_c__posMove, daAlink_c__posMoveHook);
#ifdef WII_PLATFORM
    APPLY_HOOK(dScnLogo_c__create, &f_dScnLogo_c__create, dScnLogo_c__create);
    APPLY_HOOK(dScnLogo_c__dvdWaitDraw, &f_dScnLogo_c__dvdWaitDraw, dScnLogo_c__dvdWaitDraw);
    APPLY_HOOK(mDoGph_gInf_c__startFadeOut, &f_mDoGph_gInf_c__startFadeOut, mDoGph_gInf_c__startFadeOut);
#else
APPLY_HOOK(dScnLogo_c__warningInDraw, &f_dScnLogo_c__warningInDraw, dScnLogo_c__warningInDraw);
#endif

#ifdef PR_TEST
    APPLY_HOOK(ExceptionCallback, &f_myExceptionCallback, myExceptionCallbackHook);
#endif

#undef APPLY_HOOK
}
}  // namespace Hook