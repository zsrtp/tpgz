#include "libtp_c/include/controller.h"
#include "libtp_c/include/inventory.h"
#include "libtp_c/include/items.h"
#include "libtp_c/include/tp.h"
#include "libtp_c/include/link.h"
#include "libtp_c/include/system.h"
#include "menus/cheats_menu.h"
#include "controller.h"
#include "cheats.h"
#include "commands.h"
#include "utils/cursor.hpp"
#include "utils/lines.hpp"
#include <string.h>

#define LINES CHEAT_AMNT

static Cursor cursor = {0, 0};
bool init_once = false;
bool chest_collision = false;
using namespace Cheats;

Cheat CheatItems[CHEAT_AMNT] = {
    {InfiniteAir, false},
    {InfiniteArrows, false},
    {InfiniteBombs, false},
    {InfiniteHearts, false},
    {InfiniteOil, false},
    {InfiniteRupees, false},
    {InfiniteSlingshot, false},
    {Invincible, false},
    {InvincibleEnemies, false},
    {MoonJump, false},
    {DoorStorage, false},
    {SuperClawshot, false},
    {UnrestrictedItems, false},
    {TransformAnywhere, false}};

Line lines[LINES] = {
    {"infinite air", InfiniteAir, "Gives Link infinite air underwater", true, &CheatItems[InfiniteAir].active},
    {"infinite arrows", InfiniteArrows, "Gives Link 99 arrows", true, &CheatItems[InfiniteArrows].active},
    {"infinite bombs", InfiniteBombs, "Gives Link 99 bombs in all bags", true, &CheatItems[InfiniteBombs].active},
    {"infinite hearts", InfiniteHearts, "Link will always have full hearts", true, &CheatItems[InfiniteHearts].active},
    {"infinite oil", InfiniteOil, "Gives Link infinite lantern oil", true, &CheatItems[InfiniteOil].active},
    {"infinite rupees", InfiniteRupees, "Link will always have 1000 rupees", true, &CheatItems[InfiniteRupees].active},
    {"infinite slingshot", InfiniteSlingshot, "Gives Link 99 slingshot pellets", true, &CheatItems[InfiniteSlingshot].active},
    {"invincible", Invincible, "Makes Link invincible", true, &CheatItems[Invincible].active},
    {"invincible enemies", InvincibleEnemies, "Makes some enemies invincible", true, &CheatItems[InvincibleEnemies].active},
    {"moon jump", MoonJump, "Hold R+A to moon jump", true, &CheatItems[MoonJump].active},
    {"door storage", DoorStorage, "Disable most collision", true, &CheatItems[DoorStorage].active},
    {"super clawshot", SuperClawshot, "Super Clawshot", true, &CheatItems[SuperClawshot].active},
    {"unrestricted items", UnrestrictedItems, "Disable item restrictions", true, &CheatItems[UnrestrictedItems].active},
    {"transform anywhere", TransformAnywhere, "Transform at any location", true, &CheatItems[TransformAnywhere].active}};

namespace Cheats {
    using namespace Controller;

    void apply_cheats() {
        Link::Link *link = Link::get_link();
        Inventory::Inventory *inventory = Inventory::get_inventory();
        for (auto cheat : CheatItems) {
            if (cheat.active) {
                switch (cheat.id) {
                    case MoonJump: {
                        Commands::enable_command(Commands::CMD_MOON_JUMP);
                        break;
                    }
                    case Invincible: {
                        if (tp_gameInfo.link_collision_ptr != nullptr) {
                            tp_gameInfo.link_collision_ptr->invincibility_timer = 5;
                        }
                        break;
                    }
                    case InfiniteHearts: {
                        link->heart_quarters = (link->heart_pieces / 5) * 4;
                        break;
                    }
                    case InfiniteAir: {
                        *(Link::get_air()) = 600;
                        break;
                    }
                    case InfiniteOil: {
                        link->current_lantern_oil = 0x5460;
                        break;
                    }
                    case InfiniteBombs: {
                        inventory->bomb_bag_1_amnt = 99;
                        inventory->bomb_bag_2_amnt = 99;
                        inventory->bomb_bag_3_amnt = 99;
                        break;
                    }
                    case InfiniteRupees: {
                        link->rupees = 1000;
                        break;
                    }
                    case InfiniteArrows: {
                        inventory->arrow_count = 99;
                        break;
                    }
                    case InfiniteSlingshot: {
                        inventory->slingshot_count = 99;
                    }
                    case SuperClawshot: {
                        tp_clawshot.speed = 2870.0f;
                        tp_clawshot.extension_rate = 69120.0f;
                        tp_clawshot.retraction_rate = 2870.0f;
                        tp_clawshot.pull_rate = 500.0f;
                        break;
                    }
                    case DoorStorage: {
                        if (tp_gameInfo.link_collision_ptr != nullptr) {
                            tp_gameInfo.link_collision_ptr->chest_collision = 0xE4;
                            tp_gameInfo.link_collision_ptr->door_collision = 0x40;
                            chest_collision = true;
                        }
                        break;
                    }
                    default: {}
                }
            } else {
                switch (cheat.id) {
                    case MoonJump: {
                        Commands::disable_command(Commands::CMD_MOON_JUMP);
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
                        if (tp_gameInfo.link_collision_ptr != nullptr && chest_collision == true) {
                            tp_gameInfo.link_collision_ptr->chest_collision = 0xE0;
                            tp_gameInfo.link_collision_ptr->door_collision = 0x20;
                            chest_collision = false;
                        }
                        break;
                    }
                    default: {}
                }
            }
        }
    };
}  // namespace Cheats

void CheatsMenu::render() {
    if (button_is_pressed(Controller::B)) {
        init_once = false;
		MenuRendering::set_menu(MN_MAIN_MENU_INDEX);
        return;
    };

    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

    Utilities::move_cursor(cursor, LINES);

    if (current_input == Controller::Pad::A && a_held == false) {
        CheatItems[cursor.y].active = !(CheatItems[cursor.y].active);
    }

    Utilities::render_lines(lines, cursor.y, LINES, 180.0f);
};