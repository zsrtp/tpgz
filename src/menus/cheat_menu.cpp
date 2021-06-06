#include "cheats.h"
#include "commands.h"
#include "controller.h"
#include "libtp_c/include/addrs.h"
#include "libtp_c/include/JSystem/JUtility/JUTGamePad.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/patch.h"
#include "libtp_c/include/msl_c/string.h"
#include "menus/cheats_menu.h"
#include "utils/cursor.h"
#include "utils/lines.h"

#define LINES CHEAT_AMNT

#ifdef GCN_PLATFORM
#define INVINCIBLE_ENEMIES_OFFSET (0x328)
#endif
#ifdef WII_PLATFORM
#define INVINCIBLE_ENEMIES_OFFSET (0x244)
#endif

static Cursor cursor = {0, 0};
bool init_once = false;
bool door_collision = false;
using namespace Cheats;

Cheat CheatItems[CHEAT_AMNT] = {
    {InfiniteAir, false},       {InfiniteArrows, false},    {InfiniteBombs, false},
    {InfiniteHearts, false},    {InfiniteOil, false},       {InfiniteRupees, false},
    {InfiniteSlingshot, false}, {Invincible, false},        {InvincibleEnemies, false},
    {MoonJump, false},          {DoorStorage, false},       {SuperClawshot, false},
    {UnrestrictedItems, false}, {TransformAnywhere, false},
#ifdef WII_PLATFORM
    {GaleLJA, false},
#endif
};

Line lines[LINES] = {
    {"infinite air", InfiniteAir, "Gives Link infinite air underwater", true,
     &CheatItems[InfiniteAir].active},
    {"infinite arrows", InfiniteArrows, "Gives Link 99 arrows", true,
     &CheatItems[InfiniteArrows].active},
    {"infinite bombs", InfiniteBombs, "Gives Link 99 bombs in all bags", true,
     &CheatItems[InfiniteBombs].active},
    {"infinite hearts", InfiniteHearts, "Link will always have full hearts", true,
     &CheatItems[InfiniteHearts].active},
    {"infinite oil", InfiniteOil, "Gives Link infinite lantern oil", true,
     &CheatItems[InfiniteOil].active},
    {"infinite rupees", InfiniteRupees, "Link will always have 1000 rupees", true,
     &CheatItems[InfiniteRupees].active},
    {"infinite slingshot", InfiniteSlingshot, "Gives Link 99 slingshot pellets", true,
     &CheatItems[InfiniteSlingshot].active},
    {"invincible", Invincible, "Makes Link invincible", true, &CheatItems[Invincible].active},
    {"invincible enemies", InvincibleEnemies, "Makes some enemies invincible", true,
     &CheatItems[InvincibleEnemies].active},
    {"moon jump", MoonJump, "Hold " MOON_JUMP_TEXT " to moon jump", true,
     &CheatItems[MoonJump].active},
    {"disable walls", DoorStorage, "Disables most wall collision", true,
     &CheatItems[DoorStorage].active},
    {"super clawshot", SuperClawshot, "Super Clawshot", true, &CheatItems[SuperClawshot].active},
    {"unrestricted items", UnrestrictedItems, "Disable item restrictions", true,
     &CheatItems[UnrestrictedItems].active},
    {"transform anywhere", TransformAnywhere, "Transform at any location", true,
     &CheatItems[TransformAnywhere].active},
#ifdef WII_PLATFORM
    {"gale LJA", GaleLJA, "Yeet everywhere", true, &CheatItems[GaleLJA].active},
#endif
};

namespace Cheats {
using namespace Controller;

void apply_cheats() {
    for (auto cheat : CheatItems) {
        if (cheat.active) {
            switch (cheat.id) {
            case MoonJump: {
                Commands::enable_command(Commands::CMD_MOON_JUMP);
                break;
            }
            case InvincibleEnemies: {
                *reinterpret_cast<uint32_t*>(tp_cc_at_check_addr + INVINCIBLE_ENEMIES_OFFSET) =
                    0x60000000;  // nop
                DCFlushRange((void*)(tp_cc_at_check_addr + INVINCIBLE_ENEMIES_OFFSET),
                             sizeof(uint32_t));
                ICInvalidateRange((void*)(tp_cc_at_check_addr + INVINCIBLE_ENEMIES_OFFSET),
                                  sizeof(uint32_t));
                break;
            }
            case Invincible: {
                if (dComIfGp_getPlayer()) {
                    dComIfGp_getPlayer()->field_0x56b[2] = 5;
                }
                break;
            }
            case InfiniteHearts: {
                uint16_t max_life = dComIfGs_getMaxLife();
                dComIfGs_setLife((max_life / 5) * 4);
                break;
            }
            case InfiniteAir: {
                dComIfGs_setOxygen(600);
                break;
            }
            case InfiniteOil: {
                dComIfGs_setOil(21600);
                break;
            }
            case InfiniteBombs: {
                dComIfGs_setBombNum(BOMB_BAG_1, 99);
                dComIfGs_setBombNum(BOMB_BAG_2, 99);
                dComIfGs_setBombNum(BOMB_BAG_3, 99);
                break;
            }
            case InfiniteRupees: {
                dComIfGs_setRupee(1000);
                break;
            }
            case InfiniteArrows: {
                dComIfGs_setArrowNum(99);
                break;
            }
            case InfiniteSlingshot: {
                dComIfGs_setPachinkoNum(99);
                break;
            }
            case SuperClawshot: {
                tp_clawshot.speed = 2870.0f;
                tp_clawshot.extension_rate = 69120.0f;
                tp_clawshot.retraction_rate = 2870.0f;
                tp_clawshot.pull_rate = 500.0f;
                break;
            }
            case DoorStorage: {
                if (dComIfGp_getPlayer()) {
                    dComIfGp_getPlayer()->mLinkAcch.SetWallNone();
                    dComIfGp_getPlayer()->mLinkAcch.OnLineCheckNone();
                    door_collision = true;
                }
                break;
            }
#ifdef WII_PLATFORM
            case GaleLJA: {
                if (dComIfGp_getPlayer() && dComIfGp_getPlayer()->mActionID == 0x60 &&
                    dComIfGp_getPlayer()->field_0x2fdc == 0xFF) {
                    dComIfGp_getPlayer()->field_0x2fdc = 0x0103;
                }
            }
#endif
            default: {
            }
            }
        } else {
            switch (cheat.id) {
            case MoonJump: {
                Commands::disable_command(Commands::CMD_MOON_JUMP);
                break;
            }
            case InvincibleEnemies: {
                *reinterpret_cast<uint32_t*>(tp_cc_at_check_addr + INVINCIBLE_ENEMIES_OFFSET) =
                    0x7C030050;  // sub r0, r0, r3
                DCFlushRange((void*)(tp_cc_at_check_addr + INVINCIBLE_ENEMIES_OFFSET),
                             sizeof(uint32_t));
                ICInvalidateRange((void*)(tp_cc_at_check_addr + INVINCIBLE_ENEMIES_OFFSET),
                                  sizeof(uint32_t));
                break;
            }
            case SuperClawshot: {
                tp_clawshot.speed = 100.0f;
                tp_clawshot.extension_rate = 2000.0f;
                tp_clawshot.retraction_rate = 150.0f;
                tp_clawshot.pull_rate = 60.0f;
                break;
            }
            case DoorStorage: {
                if (dComIfGp_getPlayer() && door_collision == true) {
                    dComIfGp_getPlayer()->mLinkAcch.OffWallNone();
                    dComIfGp_getPlayer()->mLinkAcch.OffLineCheckNone();
                    door_collision = false;
                }
                break;
            }
            default: {
            }
            }
        }
    }
};
}  // namespace Cheats

void CheatsMenu::render() {
    if (button_is_pressed(BACK_BUTTON)) {
        init_once = false;
        MenuRendering::set_menu(MN_MAIN_MENU_INDEX);
        return;
    };

    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

    Utilities::move_cursor(cursor, LINES);

    if (current_input == SELECTION_BUTTON && a_held == false) {
        CheatItems[cursor.y].active = !(CheatItems[cursor.y].active);
    }

    Utilities::render_lines(lines, cursor.y, LINES);
};