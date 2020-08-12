#include "libtp_c/include/controller.h"
#include "libtp_c/include/inventory.h"
#include "libtp_c/include/items.h"
#include "libtp_c/include/tp.h"
#include "libtp_c/include/link.h"
#include "libtp_c/include/system.h"
#include "menu.h"
#include "controller.h"
#include "cheats.h"
#include "commands.h"
#include "utils/cursor.hpp"
#include "utils/lines.hpp"
#include <string.h>
#define LINES CHEAT_AMNT

static Cursor cursor = {0,0};
bool init_once = false;
bool cheats_visible;
using namespace Cheats;

Cheat CheatItems[CHEAT_AMNT] = {
        {InfiniteAir,false},
        {InfiniteArrows,false},
        {InfiniteBombs,false},
        {InfiniteHearts,false},
        {InfiniteOil,false},
        {InfiniteRupees,false},
        {InfiniteSlingshot,false},
        {Invincible,false},
        {InvincibleEnemies,false},
        {MoonJump,false}};
    

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
    {"moon jump", MoonJump, "Hold R+A to moon jump", true, &CheatItems[MoonJump].active}};

namespace Cheats {
    using namespace Controller;

    void apply_cheats() {
        Link::Link *link = Link::get_link();
        Inventory::Inventory *inventory = Inventory::get_inventory();
        for (auto cheat : CheatItems) {
            if (cheat.active) {
                switch (cheat.id) {
                    case MoonJump: {
                        Commands::enable_command(Commands::MOON_JUMP);
                        break;
                    }
                    case Invincible: {
                        if (tp_gameInfo.link_collision_ptr != nullptr) {
                            tp_gameInfo.link_collision_ptr->invincibility_timer = 5;
                        }
                        break;
                    }
                    case InvincibleEnemies: {
                        uint32_t patch = 0x20038000;
                        memcpy((void *)0x80087F2C, (void *)&patch, 4);
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
                    default: {}
                }
            } else {
                switch (cheat.id) {
                    case MoonJump: {
                        Commands::disable_command(Commands::MOON_JUMP);
                        break;
                    }
                    case InvincibleEnemies: {
                        uint32_t unpatch = 0x7C030050;
                        memcpy((void *)0x80087F2C, (void *)&unpatch, 4);
                        break;
                    }
                    case SuperClawshot: {
                        tp_clawshot.speed = 100.0f;
                        tp_clawshot.extension_rate = 2000.0f;
                        tp_clawshot.retraction_rate = 150.0f;
                        tp_clawshot.pull_rate = 60.0f;
                        break;
                    }
                    default: {}
                }
            }
        }
    };
}  // namespace Cheats

void CheatsMenu::render(Font& font) {
    if (button_is_pressed(Controller::B)) {
        init_once = false;
        cheats_visible = false;
        mm_visible = true;
        return;
    };

    if (!init_once) {current_input = 0;init_once = true;}

    Utilities::move_cursor(cursor, LINES);

    if (current_input == 256 && a_held == false) {
        CheatItems[cursor.y].active = !(CheatItems[cursor.y].active);
    }

    Utilities::render_lines(font, lines, cursor.y, LINES, 180.0f);
};