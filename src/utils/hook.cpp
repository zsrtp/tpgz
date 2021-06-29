#include "utils/hook.h"
#include "cheats.h"
#include "controller.h"
#include "lib.h"
#include "libtp_c/include/addrs.h"
#include "libtp_c/include/patch.h"
#include "flaglog.h"
#include "fifo_queue.h"
#include "libtp_c/include/msl_c/string.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "utils/card.h"
#include "movelink.h"

#define HOOK_DEF(rettype, name, params)                                                            \
    typedef rettype(*tp_##name##_t) params;                                                        \
    tp_##name##_t name##Trampoline;

HOOK_DEF(void, cDyl_InitAsync, (void*, void*, void*));
HOOK_DEF(void, fapGm_Execute, (void));
HOOK_DEF(void, ExceptionCallback, (void));
HOOK_DEF(void, draw, (void*));

struct PadStatus {
    uint8_t ok[12];
};

#ifdef GCN_PLATFORM
#define PAD_READ_RETURN_OFFSET (0x2FC)
#endif
#ifdef WII_PLATFORM
#define PAD_READ_RETURN_OFFSET (0x2DC)
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

struct {
    uint32_t a[2];
} trampolines[HOOK_AMNT];

namespace Hook {
using namespace mod::patch;

void initHook(void* p1, void* p2, void* p3) {
    cDyl_InitAsyncTrampoline(p1, p2, p3);
    init();
}

void gameLoopHook(void) {
    game_loop();
    fapGm_ExecuteTrampoline();
}

void drawHook(void* p1) {
    drawTrampoline(p1);
    draw();
}

void myExceptionCallbackHook(void) {
    ExceptionCallbackTrampoline();
    *reinterpret_cast<uint32_t*>(0x80450580) = 1;
    DCFlushRange((void*)(0x80450580), sizeof(uint32_t));
    ICInvalidateRange((void*)(0x80450580), sizeof(uint32_t));
}

uint32_t readControllerHook(uint16_t* p1) {
    auto returnValue = PADReadTrampoline(p1);
    Controller::read_controller();
    return returnValue;
}

uint32_t superClawshotHook(void* p1, void* p2) {
    if (CheatItems[Cheats::SuperClawshot].active) {
        return 1;
    } else {
        return checkHookshotStickBGTrampoline(p1, p2);
    }
}

void disableGravityHook(float p1, float p2, int p3) {
    if (move_link_active) {
        return setSpecialGravityTrampoline(0.0f, p2, p3);
    } else {
        return setSpecialGravityTrampoline(p1, p2, p3);
    }
}

uint32_t unrestrictedItemsHook(uint16_t p1) {
    if (CheatItems[Cheats::UnrestrictedItems].active) {
        return 1;
    } else {
        return checkCastleTownUseItemTrampoline(p1);
    }
}

uint32_t transformAnywhereHook(void* p1, void* p2, int p3) {
    if (CheatItems[Cheats::TransformAnywhere].active) {
        return 0;
    } else {
        return query042Trampoline(p1, p2, p3);
    }
}

static char buf[40];
void onEventBitHook(void* addr, uint16_t pFlag) {
    if (g_flag_log_active) {
        if (addr == &g_dComIfG_gameInfo.mInfo.mTmp) {
            tp_sprintf(buf, "%s[0x%X] : %X | ON", "Event Tmp", pFlag >> 8, pFlag & 0xFF);
        } else {
            tp_sprintf(buf, "%s[0x%X] : %X | ON", "Event", pFlag >> 8, pFlag & 0xFF);
        }
        FIFOQueue::push(buf, Queue, 0xFFFFFF00);
    }

    return onEventBitTrampoline(addr, pFlag);
}

void offEventBitHook(void* addr, uint16_t pFlag) {
    if (g_flag_log_active) {
        if (addr == &g_dComIfG_gameInfo.mInfo.mTmp) {
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
    if (g_flag_log_active) {
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
    if (inject_memfile_flag) {
        return;
    } else {
        return putSaveTrampoline(addr, stageNo);
    }
}

void apply_hooks() {
#define APPLY_HOOK(name, addr, idx, func)                                                          \
    name##Trampoline = hookFunction((tp_##name##_t)addr, trampolines[idx].a, func)
    APPLY_HOOK(cDyl_InitAsync, tp_cDyl_InitAsync_addr, HK_LIB_INIT_INDEX, initHook);
    APPLY_HOOK(fapGm_Execute, tp_fapGm_Execute_addr, HK_LIB_GAME_LOOP_INDEX, gameLoopHook);
    APPLY_HOOK(draw, tp_draw_console_addr, HK_LIB_DRAW_INDEX, drawHook);
    APPLY_HOOK(PADRead, (tp_PADRead_addr + 0), HK_LIB_READ_CONTROLLER_INDEX, readControllerHook);
    APPLY_HOOK(checkHookshotStickBG, tp_clawshot_checkbg_addr, HK_SUPER_CLAWSHOT_INDEX,
               superClawshotHook);
    APPLY_HOOK(setSpecialGravity, tp_setSpecialGravity_addr, HK_DISABLE_GRAV_INDEX,
               disableGravityHook);
    APPLY_HOOK(checkCastleTownUseItem, tp_checkCastleTownUseItem_addr, HK_UNRESTRICTED_ITEMS_INDEX,
               unrestrictedItemsHook);
    APPLY_HOOK(query042, tp_query042_addr, HK_TRANSFORM_ANYWHERE_INDEX, transformAnywhereHook);

    APPLY_HOOK(onSwitch, dSv_info_c__onSwitch_addr, HK_ONSWITCH_INDEX, onSwitchHook);
    APPLY_HOOK(onEventBit, dSv_event_c__onEventBit_addr, HK_ONEVENTBIT_INDEX, onEventBitHook);
    APPLY_HOOK(offEventBit, dSv_event_c__offEventBit_addr, HK_OFFEVENTBIT_INDEX, offEventBitHook);
    APPLY_HOOK(putSave, tp_putSave_addr, HK_PUTSAVE_INDEX, putSaveHook);
    #if PR_TEST
    APPLY_HOOK(ExceptionCallback, tp_myExceptionCallback_addr, HK_MYEXCEPTIONCALLBACK_INDEX, myExceptionCallbackHook);
    #endif

#undef APPLY_HOOK
}
}  // namespace Hook