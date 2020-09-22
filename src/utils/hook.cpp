#include "utils/hook.h"
#include "libtp_c/include/patch.h"
#include "cheats.h"

typedef uint32_t (*tp_checkHookshotStickBG_t)(void*,void*);
#define tp_checkHookshotStickBG ((tp_checkHookshotStickBG_t)0x801087b0)
tp_checkHookshotStickBG_t superClawshotTrampoline;

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

    void apply_hooks() {
        superClawshotTrampoline = hookFunction(tp_checkHookshotStickBG, trampolines[HK_SUPER_CLAWSHOT_INDEX].a, superClawshotHook);
    }
} // namespace Hook
