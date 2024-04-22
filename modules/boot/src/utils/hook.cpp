#include "utils/hook.h"
#include <cstdio>
#include "cheats.h"
#include "controller.h"
#include "boot.h"
#include "libtp_c/include/addrs.h"
#include "rels/include/patch.h"
#include "flaglog.h"
#include "fifo_queue.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "utils/card.h"
#include "global_data.h"
#include "memfiles.h"
#include "rels/include/cxx.h"
#include "rels/include/defines.h"
#include "save_manager.h"
#include "collision_view.h"

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

#ifdef GCN_NTSCU
#define CRASH_ADDRESS (0x80450580)
#endif
#ifdef GCN_PAL
#define CRASH_ADDRESS (0x80452540)
#endif
#ifdef GCN_NTSCJ
#define CRASH_ADDRESS (0x8044A6C0)
#endif
#ifdef WII_NTSCU_10
#define CRASH_ADDRESS (0x80537560)
#endif
#ifdef WII_NTSCU_12
#define CRASH_ADDRESS (0x8051d5e0)
#endif
#ifdef WII_NTSCJ
#define CRASH_ADDRESS (0x8051b460)
#endif
#ifdef WII_PAL
#define CRASH_ADDRESS (0x8051DEE0)
#endif

HOOK_DEF(uint32_t, PADRead, (uint16_t*));
HOOK_DEF(uint32_t, checkHookshotStickBG, (void*, void*));
HOOK_DEF(void, setSpecialGravity, (float, float, int));
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
    *reinterpret_cast<uint32_t*>(CRASH_ADDRESS) = 1;
    DCFlushRange((void*)(CRASH_ADDRESS), sizeof(uint32_t));
    ICInvalidateRange((void*)(CRASH_ADDRESS), sizeof(uint32_t));
}
#endif  // PR_TEST

uint32_t readControllerHook(uint16_t* p1) {
    auto returnValue = PADReadTrampoline(p1);
    GZ_readController();
    return returnValue;
}

uint32_t superClawshotHook(void* p1, void* p2) {
    if (g_cheats[SuperClawshot].active) {
        return 1;
    } else {
        return checkHookshotStickBGTrampoline(p1, p2);
    }
}

void disableGravityHook(float p1, float p2, int p3) {
    if (g_moveLinkEnabled || g_actorViewEnabled) {
        return setSpecialGravityTrampoline(0.0f, p2, p3);
    } else {
        return setSpecialGravityTrampoline(p1, p2, p3);
    }
}

uint32_t unrestrictedItemsHook(uint16_t p1) {
    if (g_cheats[UnrestrictedItems].active) {
        return 1;
    } else {
        return checkCastleTownUseItemTrampoline(p1);
    }
}

uint32_t transformAnywhereHook(void* p1, void* p2, int p3) {
    if (g_cheats[TransformAnywhere].active) {
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
    if (g_actorViewEnabled || g_moveLinkEnabled) {
        // i_this->SetRoofNone();
        // i_this->SetWallNone();
        // i_this->mSpeed = 0;
        i_this->mHitParam = (1 << 5);
        // i_this->SetGrndNone();
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
#define f_dCcS__Draw dCcS__Draw_void_
#define f_dScnPly_BeforeOfPaint mDoGph_BeforeOfDraw_void_
#define f_dCcS__MoveAfterCheck dCcS__MoveAfterCheck_void_
#define f_dBgS_Acch__CrrPos dBgS_Acch__CrrPos_dBgS___
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
#define f_dCcS__Draw Draw__4dCcSFv
#define f_dScnPly_BeforeOfPaint dScnPly_BeforeOfPaint__Fv
#define f_dCcS__MoveAfterCheck MoveAfterCheck__4dCcSFv
#define f_dBgS_Acch__CrrPos CrrPos__9dBgS_AcchFR4dBgS
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
#ifdef PR_TEST
    APPLY_HOOK(ExceptionCallback, &f_myExceptionCallback, myExceptionCallbackHook);
#endif

#undef APPLY_HOOK
}
}  // namespace Hook