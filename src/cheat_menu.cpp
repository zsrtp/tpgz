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
    {"area reload", 11, "use L+R+Start to reload current area", true},
    {"fast movement", 12, "move much faster (human rolling only for now)", true}};

namespace Cheats {
    using namespace Controller;

    enum CheatId {
        Invincible,
        InvincibleEnemies,
        InfiniteAir,
        InfiniteOil,
        InfiniteBombs,
        InfiniteRupees,
        InfiniteArrows,
        MoonJumpEnabled,
        TeleportEnabled,
        ReloadArea,
        FastRolling
    };

    struct Cheat {
        enum CheatId id;
        char name[32];
        bool active;
        bool togglable;
    };

    static Cheat Items[CHEAT_AMNT] = {
        {Invincible, "Invincible", false},
        {InvincibleEnemies, "Invincible Enemies", false},
        {InfiniteAir, "Infinite Air", false},
        {InfiniteOil, "Infinite Oil", false},
        {InfiniteBombs, "Infinite Bombs", false},
        {InfiniteRupees, "Infinite Rupees", false},
        {InfiniteArrows, "Infinite Arrows", false},
        {MoonJumpEnabled, "Moon Jump Enabled", false},
        {TeleportEnabled, "Teleport Enabled", false},
        {ReloadArea, "Reload Area", false},
        {FastRolling, "Fast Rolling", false}};

    // finish
    void store_position(){};
    void load_position(){};

    void apply_cheats() {
        Link::Link *link = Link::get_link();
        Inventory::Inventory *inventory = Inventory::get_inventory();
        for (auto cheat : Items) {
            if (cheat.active) {
                switch (cheat.id) {
                    case Invincible: {
                        link->heart_quarters = (link->heart_pieces / 5) * 4;
                    }
                    case InvincibleEnemies: {
                        // libtp::system::memory::write::<u32>(0x8008_7F28, 0x4BF7_D158);
                    }
                    case InfiniteAir: {
                        *(Link::get_air()) = 600;
                    }
                    case InfiniteOil: {
                        link->lamp_fuel = 0x5460;
                    }
                    case InfiniteBombs: {
                        inventory->bomb_bag_1_amnt = 99;
                        inventory->bomb_bag_2_amnt = 99;
                        inventory->bomb_bag_3_amnt = 99;
                    }
                    case InfiniteRupees: {
                        link->rupees = 1000;
                    }
                    case InfiniteArrows: {
                        inventory->arrow_count = 99;
                    }
                    case FastRolling: {
                        tp_linkRollConstants.roll_factor = 3.0;
                    }
                    default: {}
                }
            } else {
                switch (cheat.id) {
                    case InvincibleEnemies: {
                        //libtp::system::memory::write::<u32>(0x8008_7F28, 0xA81B_0562);
                    }
                    case FastRolling: {
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

    move_cursor(cursor, LINES);

    if (button_is_down(Controller::A) && !button_is_held(Controller::A)) {
        switch (cursor) {
            case INVINCIBLE_INDEX: {
                Cheats::Items[INVINCIBLE_INDEX - 2].active = !Cheats::Items[INVINCIBLE_INDEX - 2].active;
            }
            case INVINCIBLE_ENEMIES_INDEX: {
                Cheats::Items[INVINCIBLE_ENEMIES_INDEX - 2].active = !Cheats::Items[INVINCIBLE_ENEMIES_INDEX - 2].active;
            }
            case INFINITE_AIR_INDEX: {
                Cheats::Items[INFINITE_AIR_INDEX - 2].active = !Cheats::Items[INFINITE_AIR_INDEX - 2].active;
            }
            case INFINITE_OIL_INDEX: {
                Cheats::Items[INFINITE_OIL_INDEX - 2].active = !Cheats::Items[INFINITE_OIL_INDEX - 2].active;
            }
            case INFINITE_BOMBS_INDEX: {
                Cheats::Items[INFINITE_BOMBS_INDEX - 2].active = !Cheats::Items[INFINITE_BOMBS_INDEX - 2].active;
            }
            case INFINITE_RUPEES_INDEX: {
                Cheats::Items[INFINITE_RUPEES_INDEX - 2].active = !Cheats::Items[INFINITE_RUPEES_INDEX - 2].active;
            }
            case INFINITE_ARROWS_INDEX: {
                Cheats::Items[INFINITE_ARROWS_INDEX - 2].active = !Cheats::Items[INFINITE_ARROWS_INDEX - 2].active;
            }
            case MOON_JUMP_INDEX: {
                Cheats::Items[MOON_JUMP_INDEX].active = !Cheats::Items[MOON_JUMP_INDEX].active;
            }
            case TELEPORT_INDEX: {
                Cheats::Items[TELEPORT_INDEX].active = !Cheats::Items[TELEPORT_INDEX].active;
            }
            case RELOAD_AREA_INDEX: {
                Cheats::Items[RELOAD_AREA_INDEX].active = !Cheats::Items[RELOAD_AREA_INDEX].active;
            }
            case FAST_MOVEMENT_INDEX: {
                Cheats::Items[FAST_MOVEMENT_INDEX].active = !Cheats::Items[FAST_MOVEMENT_INDEX].active;
            }
        }
    }

    render_lines(font, lines, cursor, LINES);
};