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
#define LINES 18

static int cursor = 2;
bool init_once = false;
using namespace Cheats;

static Cheats::Cheat CheatItems[LINES] = {
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
        {MoonJump, false},
        {Teleport, false},
        {SandHeightLoss, false},
        {ReloadArea, false},
        {FastMovement, false},
        {FastBonk, false},
        {SuperClawshot, false},
        {SuperSpinner, false}};


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
    {"moon jump", MoonJump, "hold R+A to moon jump", true,&CheatItems[MoonJump].active},
    {"teleport", Teleport, "dpad+up to set, dpad+down to load ", true,&CheatItems[Teleport].active},
    {"no sinking in sand",SandHeightLoss, "link won't sink in sand", true,&CheatItems[SandHeightLoss].active},
    {"area reload", ReloadArea, "use L+R+Start+A to reload current area", true,&CheatItems[ReloadArea].active},
    {"fast movement", FastMovement, "link's movement is much faster", true,&CheatItems[FastMovement].active},
    {"fast bonk recovery", FastBonk, "reduces bonk animation significantly", true,&CheatItems[FastBonk].active},
    {"super clawshot", SuperClawshot, "clawshot is long and can grab most things", true,&CheatItems[SuperClawshot].active},
    {"super spinner", SuperSpinner, "spinner is very fast and can hover", true,&CheatItems[SuperSpinner].active}
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
                        tp_gameInfo.link_collision_ptr->invincibility_timer = 5;
                        break;
                    }
                    case InvincibleEnemies: {
                        break;
                        // libtp::system::memory::write::<u32>(0x8008_7F28, 0x4BF7_D158);
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
                    case FastMovement: {
                        tp_link_frontroll.roll_factor = 3.0f;
                        //tp_link_swim.swim_up_max_speed = 50;
                        tp_link_swim.swim_up_speed = 50;
                        tp_link_swim.back_swim_speed = 50;
                        tp_link_swim.side_swim_speed = 50;
                        tp_link_swim.dash_swim_max_speed = 50;
                        tp_link_swim.forward_swim_speed = 50;
                        tp_link_swim.ib_swim_speed = 50;
                        tp_link_swim.sinking_speed = -50;
                        tp_link_swim.initial_sinking_speed = -50;
                        break;
                    }
                    case FastBonk: {
                        tp_link_frontroll.bonk_recoil_anim_speed = 50.0f;
                        tp_link_frontroll.bonk_recovery_anim_factor = 0.0f;
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
                    case SuperSpinner: {
                        
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
                        break;
                        //libtp::system::memory::write::<u32>(0x8008_7F28, 0xA81B_0562);
                    }
                    case FastMovement: {
                        tp_link_frontroll.roll_factor = 1.3;
                        tp_link_swim.swim_up_speed = 12;
                        tp_link_swim.forward_swim_speed = 8;
                        tp_link_swim.back_swim_speed = 6;
                        tp_link_swim.side_swim_speed = 8;
                        tp_link_swim.dash_swim_max_speed = 13;
                        tp_link_swim.ib_swim_speed = 8;
                        tp_link_swim.sinking_speed = -20;
                        tp_link_swim.initial_sinking_speed = -0.699999988;
                        break;
                    }
                    case FastBonk: {
                        tp_link_frontroll.bonk_recoil_anim_speed = 3.0f;
                        tp_link_frontroll.bonk_recovery_anim_factor = 0.800000012f;
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
        switch (cursor) {
            case Invincible: {
                CheatItems[Invincible].active = !(CheatItems[Invincible].active);
                break;
            }
            case InvincibleEnemies: {
                CheatItems[InvincibleEnemies].active = !CheatItems[InvincibleEnemies].active;
                break;
            }
            case InfiniteAir: {
                CheatItems[InfiniteAir].active = !CheatItems[InfiniteAir].active;
                break;
            }
            case InfiniteOil: {
                CheatItems[InfiniteOil].active = !CheatItems[InfiniteOil].active;
                break;
            }
            case InfiniteBombs: {
                CheatItems[InfiniteBombs].active = !CheatItems[InfiniteBombs].active;
                break;
            }
            case InfiniteRupees: {
                CheatItems[InfiniteRupees].active = !CheatItems[InfiniteRupees].active;
                break;
            }
            case InfiniteArrows: {
                CheatItems[InfiniteArrows].active = !CheatItems[InfiniteArrows].active;
                break;
            }
            case MoonJump: {
                CheatItems[MoonJump].active = !CheatItems[MoonJump].active;
                break;
            }
            case Teleport: {
                CheatItems[Teleport].active = !CheatItems[Teleport].active;
                break;
            }
            case ReloadArea: {
                CheatItems[ReloadArea].active = !CheatItems[ReloadArea].active;
                break;
            }
            case FastMovement: {
                CheatItems[FastMovement].active = !CheatItems[FastMovement].active;
                break;
            }
            case SandHeightLoss: {
                CheatItems[SandHeightLoss].active = !CheatItems[SandHeightLoss].active;
                break;
            }
            case FastBonk: {
                CheatItems[FastBonk].active = !CheatItems[FastBonk].active;
                break;
            }
            case SuperSpinner: {
                CheatItems[SuperSpinner].active = !CheatItems[SuperSpinner].active;
                break;
            }
            case SuperClawshot: {
                CheatItems[SuperClawshot].active = !CheatItems[SuperClawshot].active;
                break;
            }
        }
    }

    Utilities::render_lines(font, lines, cursor, LINES);
};