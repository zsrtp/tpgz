#include "libtp_c/include/controller.h"
#include "libtp_c/include/inventory.h"
#include "libtp_c/include/items.h"
#include "libtp_c/include/tp.h"
#include "libtp_c/include/link.h"
#include "libtp_c/include/system.h"
#include "cheats.h"
#include "commands.h"
#include <string.h>

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
        {Invincible, "Invincible", true},
        {InvincibleEnemies, "Invincible Enemies", true},
        {InfiniteAir, "Infinite Air", true},
        {InfiniteOil, "Infinite Oil", true},
        {InfiniteBombs, "Infinite Bombs", true},
        {InfiniteRupees, "Infinite Rupees", true},
        {InfiniteArrows, "Infinite Arrows", true},
        {MoonJumpEnabled, "Moon Jump Enabled", true},
        {TeleportEnabled, "Teleport Enabled", true},
        {ReloadArea, "Reload Area", true},
        {FastRolling, "Fast Rolling", true}};

    void testQueue() {

        
        // FIFOQueue MsgQueue = FIFOQueue(Queue);
        // MsgQueue.renderItems(Queue);
    };

    // finish
    void store_position(){};
    void load_position(){};

    void apply_cheats() {
        testQueue();

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
                        //tp_linkRollConstants.roll_factor = 3.0;
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
    }
}  // namespace Cheats