#include "menus/menu_cheats/include/cheats_menu.h"
#include "cheats.h"
#include "commands.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "rels/include/patch.h"
#include "libtp_c/include/defines.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

KEEP_FUNC CheatsMenu::CheatsMenu(Cursor& cursor)
    : Menu(cursor),
      lines{
          {"infinite air", InfiniteAir, "Gives infinite air underwater", true,
           &g_cheats[InfiniteAir].active},
          {"infinite arrows", InfiniteArrows, "Always have 99 arrows", true,
           &g_cheats[InfiniteArrows].active},
          {"infinite bombs", InfiniteBombs, "Always have 99 bombs", true,
           &g_cheats[InfiniteBombs].active},
          {"infinite hearts", InfiniteHearts, "Always have full hearts", true,
           &g_cheats[InfiniteHearts].active},
          {"infinite oil", InfiniteOil, "Gives infinite lantern oil", true,
           &g_cheats[InfiniteOil].active},
          {"infinite rupees", InfiniteRupees, "Always have 1000 rupees", true,
           &g_cheats[InfiniteRupees].active},
          {"infinite slingshot", InfiniteSlingshot, "Always have 99 slingshot pellets", true,
           &g_cheats[InfiniteSlingshot].active},
          {"invincible", Invincible, "Disables Link's hurtbox", true, &g_cheats[Invincible].active},
          {"invincible enemies", InvincibleEnemies, "Make some enemies invincible", true,
           &g_cheats[InvincibleEnemies].active},
          {"moon jump", MoonJump, "Hold " MOON_JUMP_TEXT " to moon jump", true,
           &g_cheats[MoonJump].active},
          {"disable walls", DoorStorage, "Disables most wall collision", true,
           &g_cheats[DoorStorage].active},
          {"super clawshot", SuperClawshot, "Super fast / long Clawshot", true,
           &g_cheats[SuperClawshot].active},
          {"unrestricted items", UnrestrictedItems, "Disable item restrictions", true,
           &g_cheats[UnrestrictedItems].active},
          {"transform anywhere", TransformAnywhere, "Transform at any location", true,
           &g_cheats[TransformAnywhere].active},
#ifdef WII_PLATFORM
          {"gale LJA", GaleLJA, "Yeet everywhere", true, &g_cheats[GaleLJA].active},
#endif
      } {
}

CheatsMenu::~CheatsMenu() {}

void CheatsMenu::draw() {
    cursor.move(0, MENU_LINE_NUM);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        g_cheats[cursor.y].active = !g_cheats[cursor.y].active;
    }

    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}