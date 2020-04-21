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
#include "utils.h"
#include <string.h>
#define LINES CHEAT_AMNT

static int cursor = 2;
bool init_once = false;
bool cheats_visible;
using namespace Cheats;

Cheat CheatItems[CHEAT_AMNT] = {
        {Blank, false},
        {Blank2, false},
        {Invincible, false},
        {InvincibleEnemies, false},
        {InfiniteHearts, false},
        {InfiniteAir, false},
        {InfiniteOil, false},
        {InfiniteBombs, false},
        {InfiniteRupees, false},
        {InfiniteArrows, false},
        {InfiniteSlingshot, false},
        {MoonJump, false},
        {Teleport, false},
        {SandHeightLoss, false},
        {ReloadArea, false},
        {FastMovement, false},
        {FastBonk, false},
        {SuperClawshot, false}};
    

Line lines[LINES] = {
    {"cheats", 0, "", false},
    {"", 1, "", false},
    {"invincible", Invincible, "makes link invincible", true, &CheatItems[Invincible].active},
    {"invincible enemies", InvincibleEnemies, "makes some enemies invicible", true,&CheatItems[InvincibleEnemies].active},
    {"infinite hearts", InfiniteHearts, "link will always have full hearts", true,&CheatItems[InfiniteHearts].active},
    {"infinite air", InfiniteAir, "gives link infinite air underwater", true,&CheatItems[InfiniteAir].active},
    {"infinite oil", InfiniteOil, "gives link infinite lantern oil", true,&CheatItems[InfiniteOil].active},
    {"infinite bombs", InfiniteBombs, "gives link 99 bombs in all bags", true,&CheatItems[InfiniteBombs].active},
    {"infinite rupees", InfiniteRupees, "link will always have 1000 rupees", true,&CheatItems[InfiniteRupees].active},
    {"infinite arrows", InfiniteArrows, "gives link 99 arrows", true,&CheatItems[InfiniteArrows].active},
    {"infinite slingshot pellets", InfiniteSlingshot, "gives link 99 slingshot pellets", true,&CheatItems[InfiniteSlingshot].active},
    {"moon jump", MoonJump, "hold R+A to moon jump", true,&CheatItems[MoonJump].active},
    {"teleport", Teleport, "dpad+up to set, dpad+down to load ", true,&CheatItems[Teleport].active},
    {"no sinking in sand",SandHeightLoss, "link won't sink in sand", true,&CheatItems[SandHeightLoss].active},
    {"area reload", ReloadArea, "use L+R+Start+A to reload current area", true,&CheatItems[ReloadArea].active},
    {"fast movement", FastMovement, "link's movement is much faster", true,&CheatItems[FastMovement].active},
    {"fast bonk recovery", FastBonk, "reduces bonk animation significantly", true,&CheatItems[FastBonk].active},
    {"super clawshot", SuperClawshot, "clawshot is long and can grab most things", true,&CheatItems[SuperClawshot].active},
};

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
                    case Teleport: {
                        Commands::enable_command(Commands::STORE_POSITION);
                        Commands::enable_command(Commands::LOAD_POSITION);
                        break;
                    }
                    case ReloadArea: {
                        Commands::enable_command(Commands::RELOAD_AREA);
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
                        link->lamp_fuel = 0x5460;
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
                    case FastMovement: {
                        tp_link_human_frontroll.roll_factor = 3.0f;
                        tp_link_human_swim.swim_up_speed = 50;
                        tp_link_human_swim.back_swim_speed = 50;
                        tp_link_human_swim.side_swim_speed = 50;
                        tp_link_human_swim.dash_swim_max_speed = 50;
                        tp_link_human_swim.forward_swim_speed = 50;
                        tp_link_human_swim.ib_swim_speed = 50;
                        tp_link_human_swim.sinking_speed = -50;
                        tp_link_human_swim.initial_sinking_speed = -50;
                        tp_link_wolf_general.dash_initial_speed_large_area = 100;
                        tp_link_wolf_general.dash_speed_large_area = 100;
                        tp_link_wolf_general.dash_initial_speed_small_area = 70;
                        tp_link_wolf_general.dash_speed_small_area = 70;
                        tp_link_wolf_swim.dash_swim_speed = 50;
                        tp_link_wolf_swim.swim_speed = 50;
                        break;
                    }
                    case FastBonk: {
                        tp_link_human_frontroll.bonk_recoil_anim_speed = 50.0f;
                        tp_link_human_frontroll.bonk_recovery_anim_factor = 0.0f;
                        break;
                    }
                    case SandHeightLoss: {
                        tp_zelAudio.link_debug_ptr->sand_height_lost = 0;
                        break;
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
                    case Teleport: {
                        Commands::disable_command(Commands::STORE_POSITION);
                        Commands::disable_command(Commands::LOAD_POSITION);
                        break;
                    }
                    case ReloadArea: {
                        Commands::disable_command(Commands::RELOAD_AREA);
                        break;
                    }
                    case InvincibleEnemies: {
                        uint32_t unpatch = 0x7C030050;
                        memcpy((void *)0x80087F2C, (void *)&unpatch, 4);
                        break;
                    }
                    case FastMovement: {
                        tp_link_human_frontroll.roll_factor = 1.3;
                        tp_link_human_swim.swim_up_speed = 12;
                        tp_link_human_swim.forward_swim_speed = 8;
                        tp_link_human_swim.back_swim_speed = 6;
                        tp_link_human_swim.side_swim_speed = 8;
                        tp_link_human_swim.dash_swim_max_speed = 13;
                        tp_link_human_swim.ib_swim_speed = 8;
                        tp_link_human_swim.sinking_speed = -20;
                        tp_link_human_swim.initial_sinking_speed = -0.699999988;
                        tp_link_wolf_general.dash_initial_speed_large_area = 65;
                        tp_link_wolf_general.dash_speed_large_area = 45;
                        tp_link_wolf_general.dash_initial_speed_small_area = 35;
                        tp_link_wolf_general.dash_speed_small_area = 33;
                        tp_link_wolf_swim.dash_swim_speed = 20;
                        tp_link_wolf_swim.swim_speed = 9;
                        break;
                    }
                    case FastBonk: {
                        tp_link_human_frontroll.bonk_recoil_anim_speed = 3.0f;
                        tp_link_human_frontroll.bonk_recovery_anim_factor = 0.800000012f;
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
        CheatItems[cursor].active = !(CheatItems[cursor].active);
    }

    Utilities::render_lines(font, lines, cursor, LINES);
};