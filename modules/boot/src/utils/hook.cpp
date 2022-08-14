#include "utils/hook.h"
#include "cheats.h"
#include "controller.h"
#include "boot.h"
#include "libtp_c/include/addrs.h"
#include "rels/include/patch.h"
#include "flaglog.h"
#include "fifo_queue.h"
#include "libtp_c/include/msl_c/string.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "utils/card.h"
#include "movelink.h"
#include "menus/memfiles_menu.h"
#include "rels/include/cxx.h"

#define HOOK_DEF(rettype, name, params)                                                            \
    typedef rettype(*tp_##name##_t) params;                                                        \
    tp_##name##_t name##Trampoline;

HOOK_DEF(void, cDyl_InitAsync, (void*, void*, void*));
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
#ifdef WII_PAL
#define CRASH_ADDRESS (0x8051DEE0)
#endif

HOOK_DEF(uint32_t, PADRead, (uint16_t*));
HOOK_DEF(uint32_t, checkHookshotStickBG, (void*, void*));
HOOK_DEF(void, setSpecialGravity, (float, float, int));
HOOK_DEF(uint32_t, checkCastleTownUseItem, (uint16_t));
HOOK_DEF(uint32_t, query042, (void*, void*, int));
HOOK_DEF(void*, cc_at_check, (void*, int*));

HOOK_DEF(void, onEventBit, (void*, uint16_t));
HOOK_DEF(void, offEventBit, (void*, uint16_t));
HOOK_DEF(void, onSwitch, (void*, int, int));
HOOK_DEF(void, putSave, (void*, int));

HOOK_DEF(void, dCcS__draw, (void));
HOOK_DEF(void, BeforeOfPaint, (void));

// struct {
//     uint32_t* a;
// } trampolines[HOOK_AMNT];

namespace Hook {
void initHook(void* p1, void* p2, void* p3) {
    cDyl_InitAsyncTrampoline(p1, p2, p3);
    init();
}

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
    if (g_moveLinkEnabled) {
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
            tp_sprintf(buf, "%s[0x%X] : %X | ON", "Event Tmp", pFlag >> 8, pFlag & 0xFF);
        } else {
            tp_sprintf(buf, "%s[0x%X] : %X | ON", "Event", pFlag >> 8, pFlag & 0xFF);
        }
        FIFOQueue::push(buf, Queue, 0xFFFFFF00);
    }

    return onEventBitTrampoline(addr, pFlag);
}

void offEventBitHook(void* addr, uint16_t pFlag) {
    if (g_flagLogEnabled) {
        if (addr == &g_dComIfG_gameInfo.info.mTmp) {
            tp_sprintf(buf, "%s[0x%X] : %X | OFF", "Event Tmp", pFlag >> 8, pFlag & 0xFF);
        } else {
            tp_sprintf(buf, "%s[0x%X] : %X | OFF", "Event", pFlag >> 8, pFlag & 0xFF);
        }
        FIFOQueue::push(buf, Queue, 0xFFFFFF00);
    }

    return offEventBitTrampoline(addr, pFlag);
}

void onSwitchHook(void* addr, int pFlag, int i_roomNo) {
    int tmp = pFlag;
    if (g_flagLogEnabled) {
        if (pFlag < 0x80) {
            tp_sprintf(buf, "%s[%d] : %d | ON", "Memory Switch", tmp >> 5, tmp & 0x1F);
        } else if (pFlag < 0xC0) {
            tmp -= 0x80;
            tp_sprintf(buf, "%s[%d] : %d | ON", "Dan Switch", tmp >> 5, tmp & 0x1F);
        } else if (pFlag < 0xE0) {
            tmp -= 0xC0;
            tp_sprintf(buf, "%s[%d] : %d | ON", "Zone Switch", tmp >> 5, tmp & 0x1F);
        } else {
            tmp -= 0xE0;
            tp_sprintf(buf, "%s[%d] : %d | ON", "Zone OneSwitch", tmp >> 5, tmp & 0x1F);
        }
        FIFOQueue::push(buf, Queue, 0xFFFFFF00);
    }
    return onSwitchTrampoline(addr, pFlag, i_roomNo);
}

// Stops temp flags from being stored to save when loading memfile
void putSaveHook(void* addr, int stageNo) {
    if (g_injectMemfile) {
        return;
    } else {
        return putSaveTrampoline(addr, stageNo);
    }
}

extern "C" {
uint32_t PADRead(uint16_t*);
}

#ifdef WII_PLATFORM
#define CODE_HEAP HEAP_ZELDA
#else
#define CODE_HEAP HEAP_ARCHIVE
#endif

void applyHooks() {
#define APPLY_HOOK(name, addr, func) name##Trampoline = hookFunction((tp_##name##_t)addr, func)
    // APPLY_HOOK(cDyl_InitAsync, tp_cDyl_InitAsync_addr, HK_LIB_INIT_INDEX, initHook);
    APPLY_HOOK(fapGm_Execute, tp_fapGm_Execute_addr, gameLoopHook);
    APPLY_HOOK(draw, tp_draw_console_addr, drawHook);
    APPLY_HOOK(PADRead, (&PADRead), readControllerHook);
    APPLY_HOOK(checkHookshotStickBG, tp_clawshot_checkbg_addr, superClawshotHook);
    APPLY_HOOK(setSpecialGravity, tp_setSpecialGravity_addr, disableGravityHook);
    APPLY_HOOK(checkCastleTownUseItem, tp_checkCastleTownUseItem_addr, unrestrictedItemsHook);
    APPLY_HOOK(query042, tp_query042_addr, transformAnywhereHook);

    APPLY_HOOK(onSwitch, dSv_info_c__onSwitch_addr, onSwitchHook);
    APPLY_HOOK(onEventBit, dSv_event_c__onEventBit_addr, onEventBitHook);
    APPLY_HOOK(offEventBit, dSv_event_c__offEventBit_addr, offEventBitHook);
    APPLY_HOOK(putSave, tp_putSave_addr, putSaveHook);
#ifdef PR_TEST
    APPLY_HOOK(ExceptionCallback, tp_myExceptionCallback_addr, myExceptionCallbackHook);
#endif

#undef APPLY_HOOK
}
}  // namespace Hook