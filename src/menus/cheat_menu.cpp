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
#define LINES 13

static int cursor = 2;

Line lines[LINES] = {
    {"cheats", 0, "", false},
    {"", 1, "", false},
    {"invincible", 2, "makes link invincible", true},
    {"invincible enemies", 3, "makes some enemies invicible (area reload required)", true},
    {"infinite air", 4, "gives link infinite air underwater", true},
    {"infinite oil", 5, "gives link infinite lantern oil", true},
    {"infinite bombs", 6, "gives link 99 bombs in all bags", true},
    {"infinite rupees", 7, "link will always have 1000 rupees", true},
    {"infinite arrows", 8, "gives link 99 arrows", true},
    {"moon jump", 9, "hold R+A to moon jump", true},
    {"teleport", 10, "use dpad+up to set position, use dpad+down to load position", true},
    {"area reload", 11, "use L+R+Start+A to reload current area", true},
    {"fast movement", 12, "move much faster (human rolling only for now)", true}};

namespace Cheats {
    using namespace Controller;

    static Cheat Items[CHEAT_AMNT] = {
        {Invincible, false},
        {InvincibleEnemies, false},
        {InfiniteAir, false},
        {InfiniteOil, false},
        {InfiniteBombs, false},
        {InfiniteRupees, false},
        {InfiniteArrows, false},
        {MoonJump, false},
        {Teleport, false},
        {ReloadArea, false},
        {FastRolling, false}};

    void apply_cheats() {
        Link::Link *link = Link::get_link();
        Inventory::Inventory *inventory = Inventory::get_inventory();
        for (auto cheat : Items) {
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
                    case FastRolling: {
                        tp_linkRollConstants.roll_factor = 3.0;
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
                    case FastRolling: {
                        break;
                        tp_linkRollConstants.roll_factor = 1.3;
                    }
                    default: {}
                }
            }
        }
    };
}  // namespace Cheats

void CheatsMenu::render(Font& font) {
    if (button_is_down(Controller::B) && !button_is_held(Controller::B)) {
        cheats_visible = false;
        mm_visible = true;
        return;
    };

    Utilities::move_cursor(cursor, LINES);

    if (button_is_down(Controller::A) && !button_is_held(Controller::A)) {
        switch (cursor-2) {
            case INVINCIBLE_INDEX: {
                Cheats::Items[INVINCIBLE_INDEX].active = !(Cheats::Items[INVINCIBLE_INDEX].active);
                break;
            }
            case INVINCIBLE_ENEMIES_INDEX: {
                Cheats::Items[INVINCIBLE_ENEMIES_INDEX ].active = !Cheats::Items[INVINCIBLE_ENEMIES_INDEX].active;
                break;
            }
            case INFINITE_AIR_INDEX: {
                Cheats::Items[INFINITE_AIR_INDEX ].active = !Cheats::Items[INFINITE_AIR_INDEX].active;
                break;
            }
            case INFINITE_OIL_INDEX: {
                Cheats::Items[INFINITE_OIL_INDEX].active = !Cheats::Items[INFINITE_OIL_INDEX].active;
                break;
            }
            case INFINITE_BOMBS_INDEX: {
                Cheats::Items[INFINITE_BOMBS_INDEX].active = !Cheats::Items[INFINITE_BOMBS_INDEX].active;
                break;
            }
            case INFINITE_RUPEES_INDEX: {
                Cheats::Items[INFINITE_RUPEES_INDEX].active = !Cheats::Items[INFINITE_RUPEES_INDEX].active;
                break;
            }
            case INFINITE_ARROWS_INDEX: {
                Cheats::Items[INFINITE_ARROWS_INDEX].active = !Cheats::Items[INFINITE_ARROWS_INDEX].active;
                break;
            }
            case MOON_JUMP_INDEX: {
                Cheats::Items[MOON_JUMP_INDEX].active = !Cheats::Items[MOON_JUMP_INDEX].active;
                break;
            }
            case TELEPORT_INDEX: {
                Cheats::Items[TELEPORT_INDEX].active = !Cheats::Items[TELEPORT_INDEX].active;
                break;
            }
            case RELOAD_AREA_INDEX: {
                Cheats::Items[RELOAD_AREA_INDEX].active = !Cheats::Items[RELOAD_AREA_INDEX].active;
                break;
            }
            case FAST_MOVEMENT_INDEX: {
                Cheats::Items[FAST_MOVEMENT_INDEX].active = !Cheats::Items[FAST_MOVEMENT_INDEX].active;
                break;
            }
        }
    }

    Utilities::render_lines_with_items(font, lines, cursor, LINES, Cheats::Items);
};