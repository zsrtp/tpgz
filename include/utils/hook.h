
#define HOOK_AMNT 5
enum HookIndex {
    HK_SUPER_CLAWSHOT_INDEX = 0,
    HK_DISABLE_GRAV_INDEX = 1,
	HK_UNRESTRICTED_ITEMS_INDEX = 2,
	HK_TRANSFORM_ANYWHERE_INDEX = 3,
	HK_INVINCIBLE_ENEMIES_INDEX = 4
};

namespace Hook {
    void apply_hooks();
} // namespace Hook
