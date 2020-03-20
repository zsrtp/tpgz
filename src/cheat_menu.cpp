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
#define LINES 15

static int cursor = 2;
using namespace Cheats;

static Cheats::Cheat CheatItems[CHEAT_AMNT] = {
        {Blank, false},
        {Blank2, false},
        {Invincible, false},
        {InvincibleEnemies, false},
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
        {FastBonk, false}};


Line lines[LINES] = {
    {"cheats", 0, "", false},
    {"", 1, "", false},
    {"invincible", Invincible, "makes link invincible", true, &CheatItems[Invincible].active},
    {"invincible enemies", InvincibleEnemies, "makes some enemies invicible (area reload required)", true,&CheatItems[InvincibleEnemies].active},
    {"infinite air", InfiniteAir, "gives link infinite air underwater", true,&CheatItems[InfiniteAir].active},
    {"infinite oil", InfiniteOil, "gives link infinite lantern oil", true,&CheatItems[InfiniteOil].active},
    {"infinite bombs", InfiniteBombs, "gives link 99 bombs in all bags", true,&CheatItems[InfiniteBombs].active},
    {"infinite rupees", InfiniteRupees, "link will always have 1000 rupees", true,&CheatItems[InfiniteRupees].active},
    {"infinite arrows", InfiniteArrows, "gives link 99 arrows", true,&CheatItems[InfiniteArrows].active},
    {"moon jump", MoonJump, "hold R+A to moon jump", true,&CheatItems[MoonJump].active},
    {"teleport", Teleport, "use dpad+up to set position, use dpad+down to load position", true,&CheatItems[Teleport].active},
    {"no sinking in sand",SandHeightLoss, "link won't sink in sand", true,&CheatItems[SandHeightLoss].active},
    {"area reload", ReloadArea, "use L+R+Start+A to reload current area", true,&CheatItems[ReloadArea].active},
    {"fast movement", FastMovement, "link's movement is much faster", true,&CheatItems[FastMovement].active},
    {"fast bonk recovery", FastBonk, "reduces bonk animation significantly", true,&CheatItems[FastBonk].active}};

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
                        link->heart_quarters = (link->heart_pieces / 5) * 4;
                        break;
                    }
                    case InvincibleEnemies: {
                        break;
                        // libtp::system::memory::write::<u32>(0x8008_7F28, 0x4BF7_D158);
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
                    }
                    case SandHeightLoss: {
                        tp_zelAudio.link_debug_ptr->sand_height_lost = 0;
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
                    default: {}
                }
            }
        }
    };
}  // namespace Cheats

void CheatsMenu::render(Font& font) {
    if (button_is_pressed(Controller::B)) {
        cheats_visible = false;
        mm_visible = true;
        return;
    };

    Utilities::move_cursor(cursor, LINES);

    if (button_is_pressed(Controller::A)) {
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
        }
    }

    Utilities::render_lines(font, lines, cursor, LINES);
};