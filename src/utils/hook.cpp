#include "utils/hook.h"
#include "libtp_c/include/patch.h"
#include "cheats.h"
#include "movelink.h"

typedef uint32_t (*tp_checkHookshotStickBG_t)(void*,void*);
#define tp_checkHookshotStickBG ((tp_checkHookshotStickBG_t)0x801087b0)
tp_checkHookshotStickBG_t superClawshotTrampoline;

typedef void (*tp_setSpecialGravity_t)(float, float, int);
#define tp_setSpecialGravity ((tp_setSpecialGravity_t)0x800bb770)
tp_setSpecialGravity_t disableGravityTrampoline;

typedef uint32_t (*tp_checkCastleTownUseItem_t)(uint16_t);
#define tp_checkCastleTownUseItem ((tp_checkCastleTownUseItem_t)0x800c0678)
tp_checkCastleTownUseItem_t unrestrictedItemsTrampoline;

typedef uint32_t (*tp_query042_t)(void*, void*, int);
#define tp_query042 ((tp_query042_t)0x8024bfec)
tp_query042_t transformAnywhereTrampoline;

typedef void* (*tp_cc_at_check_t)(void*, int*);
#define tp_cc_at_check ((tp_cc_at_check_t)0x80087c04)
tp_cc_at_check_t invincibleEnemiesTrampoline;

struct {
    uint32_t a[2];
} trampolines[HOOK_AMNT];

namespace Hook {
    using namespace mod::patch;

    uint32_t superClawshotHook(void* p1, void* p2) {
        if (CheatItems[Cheats::SuperClawshot].active) {
            return 1;
        } else {
            return superClawshotTrampoline(p1, p2);
        }
    }

	void disableGravityHook(float p1, float p2, int p3) {
        if (move_link_active) {
            return disableGravityTrampoline(0.0f, p2, p3);
        } else {
            return disableGravityTrampoline(p1, p2, p3);
        }
    }

	uint32_t unrestrictedItemsHook(uint16_t p1) {
        if (CheatItems[Cheats::UnrestrictedItems].active) {
            return 1;
        } else {
            return unrestrictedItemsTrampoline(p1);
        }
    }

	uint32_t transformAnywhereHook(void* p1, void* p2, int p3) {
        if (CheatItems[Cheats::TransformAnywhere].active) {
            return 0;
        } else {
            return transformAnywhereTrampoline(p1, p2, p3);
        }
    }

	void* invincibleEnemiesHook(void* p1, int* p2) {
        if (CheatItems[Cheats::InvincibleEnemies].active) {
            return invincibleEnemiesTrampoline(p1, p2 + 0x8000);
		} else {
            return invincibleEnemiesTrampoline(p1, p2);
		}
	}



    void apply_hooks() {
        superClawshotTrampoline = hookFunction(tp_checkHookshotStickBG, trampolines[HK_SUPER_CLAWSHOT_INDEX].a, superClawshotHook);
        disableGravityTrampoline = hookFunction(tp_setSpecialGravity, trampolines[HK_DISABLE_GRAV_INDEX].a, disableGravityHook);
        unrestrictedItemsTrampoline = hookFunction(tp_checkCastleTownUseItem, trampolines[HK_UNRESTRICTED_ITEMS_INDEX].a, unrestrictedItemsHook);
        transformAnywhereTrampoline = hookFunction(tp_query042, trampolines[HK_TRANSFORM_ANYWHERE_INDEX].a, transformAnywhereHook);
        invincibleEnemiesTrampoline = hookFunction(tp_cc_at_check, trampolines[HK_INVINCIBLE_ENEMIES_INDEX].a, invincibleEnemiesHook);
    }
} // namespace Hook
