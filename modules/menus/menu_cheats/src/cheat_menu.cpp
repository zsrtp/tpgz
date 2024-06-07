#include "menus/menu_cheats/include/cheats_menu.h"
#include "cheats.h"
#include "commands.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "rels/include/patch.h"
#include "libtp_c/include/defines.h"
#include "gz_flags.h"
#include "settings.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

#define ACTIVE_FUNC(id) []() { auto* stng = GZStng_getSetting(id); return stng && *(bool*)stng->data; }

KEEP_FUNC CheatsMenu::CheatsMenu(Cursor& cursor)
    : Menu(cursor), lines{
                        {"infinite air", InfiniteAir, "Gives infinite air underwater", true,
                         ACTIVE_FUNC(STNG_CHEATS_INFINITE_AIR)},
                        {"infinite arrows", InfiniteArrows, "Always have 99 arrows", true,
                         ACTIVE_FUNC(STNG_CHEATS_INFINITE_ARROWS)},
                        {"infinite bombs", InfiniteBombs, "Always have 99 bombs", true,
                         ACTIVE_FUNC(STNG_CHEATS_INFINITE_BOMBS)},
                        {"infinite hearts", InfiniteHearts, "Always have full hearts", true,
                         ACTIVE_FUNC(STNG_CHEATS_INFINITE_HEARTS)},
                        {"infinite oil", InfiniteOil, "Gives infinite lantern oil", true,
                         ACTIVE_FUNC(STNG_CHEATS_INFINITE_OIL)},
                        {"infinite rupees", InfiniteRupees, "Always have 1000 rupees", true,
                         ACTIVE_FUNC(STNG_CHEATS_INFINITE_RUPEES)},
                        {"infinite slingshot", InfiniteSlingshot,
                         "Always have 99 slingshot pellets", true,
                         ACTIVE_FUNC(STNG_CHEATS_INFINITE_SLINGSHOT)},
                        {"invincible", Invincible, "Disables Link's hurtbox", true,
                         ACTIVE_FUNC(STNG_CHEATS_INVINCIBLE)},
                        {"invincible enemies", InvincibleEnemies, "Make some enemies invincible",
                         true, ACTIVE_FUNC(STNG_CHEATS_INVINCIBLE_ENEMIES)},
                        {"moon jump", MoonJump, "Hold " MOON_JUMP_TEXT " to moon jump", true,
                         ACTIVE_FUNC(STNG_CHEATS_MOON_JUMP)},
                        {"disable walls", DoorStorage, "Disables most wall collision", true,
                         ACTIVE_FUNC(STNG_CHEATS_DOOR_STORAGE)},
                        {"super clawshot", SuperClawshot, "Super fast / long Clawshot", true,
                         ACTIVE_FUNC(STNG_CHEATS_SUPER_CLAWSHOT)},
                        {"unrestricted items", UnrestrictedItems, "Disable item restrictions", true,
                         ACTIVE_FUNC(STNG_CHEATS_UNRESTRICTED_ITEMS)},
                        {"transform anywhere", TransformAnywhere, "Transform at any location", true,
                         ACTIVE_FUNC(STNG_CHEATS_TRANSFORM_ANYWHERE)},
                        {"disable item timer", DisableItemTimer, "Disable item delete timer", true,
                         ACTIVE_FUNC(STNG_CHEATS_DISABLE_ITEM_TIMER)},
#ifdef WII_PLATFORM
                        {"gale LJA", GaleLJA, "Yeet everywhere", true, ACTIVE_FUNC(STNG_CHEATS_GALE_LJA)},
#endif
                    } {
}

CheatsMenu::~CheatsMenu() {}

GZSettingID l_mapping[] = {
    STNG_CHEATS_INFINITE_AIR,
    STNG_CHEATS_INFINITE_ARROWS,
    STNG_CHEATS_INFINITE_BOMBS,
    STNG_CHEATS_INFINITE_HEARTS,
    STNG_CHEATS_INFINITE_OIL,
    STNG_CHEATS_INFINITE_RUPEES,
    STNG_CHEATS_INFINITE_SLINGSHOT,
    STNG_CHEATS_INVINCIBLE,
    STNG_CHEATS_INVINCIBLE_ENEMIES,
    STNG_CHEATS_MOON_JUMP,
    STNG_CHEATS_DOOR_STORAGE,
    STNG_CHEATS_SUPER_CLAWSHOT,
    STNG_CHEATS_UNRESTRICTED_ITEMS,
    STNG_CHEATS_TRANSFORM_ANYWHERE,
    STNG_CHEATS_DISABLE_ITEM_TIMER,
#ifdef WII_PLATFORM
    STNG_CHEATS_GALE_LJA,
#endif
};

void CheatsMenu::draw() {
    cursor.move(0, MENU_LINE_NUM);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        auto* stng = GZStng_getSetting(l_mapping[cursor.y]);
        if (stng) {
            *(bool*)stng->data = !*(bool*)stng->data;
        } else {
            GZStng_addSetting(l_mapping[cursor.y], new bool(true), sizeof(bool));
        }
    }

    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}