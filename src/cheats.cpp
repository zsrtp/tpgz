#include "libtp_c/include/controller.h"
#include "libtp_c/include/inventory.h"
#include "libtp_c/include/items.h"
#include "libtp_c/include/tp.h"
#include "libtp_c/include/link.h"
#include "libtp_c/include/system.h"
#include "cheats.h"
#include <string.h>

namespace Cheats {
    using namespace Controller;

    static int before_cs_val = 0;
    static int after_cs_val = 0;
    static bool held_last_frame = false;
    static bool got_it = false;

    const int CHEAT_AMNT = 12;

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
        FastRolling,
        GorgeVoid
    };

    struct Cheat {
        CheatId id;
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
        {FastRolling, "Fast Rolling", true},
        {GorgeVoid, "Gorge Void Indicator", true}
    };

    void moon_jump() {
        if (tp_gameInfo.momentum_ptr) {
            tp_gameInfo.momentum_ptr->link_momentum.y = 56.0f;
        };
    };

    void reload_area() {
        tp_gameInfo.warp.enabled = true;
    };

    void process_inputs() {
        for (auto c : Commands) {
            if (c.active == true && tp_mPadStatus.sval == c.buttons) {
                c.command();
                Controller::set_buttons_down(0x0);
                Controller::set_buttons_pressed(0x0);
                tp_mPadButton.sval = 0x0;
                tp_mPadStatus.sval = 0x0;
            };
        };
    };

    void apply_cheats() {
        Link::Link link = *Link::get_link();
        Inventory::Inventory inventory = *Inventory::get_inventory();
        for (auto cheat : Items) {
            if (cheat.active) {
                switch (cheat.id) {
                    case Invincible: {
                        link.heart_quarters = (link.heart_pieces / 5) * 4;
                    }
                    case InvincibleEnemies: {
                        // libtp::system::memory::write::<u32>(0x8008_7F28, 0x4BF7_D158);
                    }
                    case InfiniteAir: {
                        uint16_t air = *Link::get_air();
                        air = 600;
                    }
                    case InfiniteOil: {
                        link.lamp_fuel = 0x5460;
                    }
                    case InfiniteBombs: {
                        inventory.bomb_bag_1_amnt = 99;
                        inventory.bomb_bag_2_amnt = 99;
                        inventory.bomb_bag_3_amnt = 99;
                    }
                    case InfiniteRupees: {
                        link.rupees = 1000;
                    }
                    case InfiniteArrows: {
                        inventory.arrow_count = 99;
                    }
                    case MoonJumpEnabled: {
                        Cheats::Commands[Cheats::Command::moon_jump].active = true;
                    }
                    case TeleportEnabled: {
                        Cheats::Commands[Cheats::Command::load_position].active = true;
                        Cheats::Commands[Cheats::Command::store_position].active = true;
                    }
                    case ReloadArea: {
                        Cheats::Commands[Cheats::Command::reload_area].active = true;
                    }
                    case FastRolling: {
                        tp_linkRollConstants.roll_factor = 3.0;
                    }
                    case GorgeVoid: {
                        if (tp_gameInfo.freeze_game == 1 && tp_gameInfo.cs_val == 0x128 && strcmp((const char *)tp_gameInfo.current_stage, "F_SP121") == 0) {
                            before_cs_val++;
                        } else if (before_cs_val == 132 && (tp_gameInfo.freeze_game == 2 || tp_gameInfo.cs_val == 0x900) && strcmp((const char *)tp_gameInfo.current_stage, "F_SP121") == 0) {
                            after_cs_val++;
                        }

                        if (before_cs_val > 122 && after_cs_val < 10) {
                            // only report if you didn't hold it last frame
                            if (tp_mPadStatus.sval != (Pad::L | Pad::A)) {
                                held_last_frame = false;
                            }

                            if (got_it == false && held_last_frame == false && before_cs_val < 132 && tp_mPadStatus.sval == (Pad::L | Pad::A)) {
                                // went early
                                int final_val = 132 - before_cs_val;
                                tp_osReport("%df early", final_val);
                                held_last_frame = true;
                                Controller::set_buttons_down(0x0);
                                Controller::set_buttons_pressed(0x0);
                                tp_mPadButton.sval = 0x0;
                                tp_mPadStatus.sval = 0x0;
                            }

                            else if (got_it == false && held_last_frame == false && before_cs_val == 132 &&
                                     tp_mPadStatus.sval == (Pad::L | Pad::A) && after_cs_val == 0) {
                                // got it
                                held_last_frame = true;
                                tp_osReport("<3");
                                Controller::set_buttons_down(0x0);
                                Controller::set_buttons_pressed(0x0);
                                tp_mPadButton.sval = 0x0;
                                tp_mPadStatus.sval = 0x0;
                                got_it = true;
                            }

                            else if (got_it == false && held_last_frame == false && after_cs_val > 0 && tp_mPadStatus.sval == (Pad::L | Pad::A)) {
                                // went late
                                tp_osReport("%df late", after_cs_val);
                                held_last_frame = true;
                                Controller::set_buttons_down(0x0);
                                Controller::set_buttons_pressed(0x0);
                                tp_mPadButton.sval = 0x0;
                                tp_mPadStatus.sval = 0x0;
                            }

                            if (tp_mPadStatus.sval == (Pad::R | Pad::A)) {
                                Inventory::set_rupee_flags();
                                Controller::set_buttons_down(0x0);
                                Controller::set_buttons_pressed(0x0);
                                tp_mPadButton.sval = 0x0;
                                tp_mPadStatus.sval = 0x0;
                            }
                        }
                    }
                }
            } else {
                switch (cheat.id) {
                    case InvincibleEnemies: {
                        //libtp::system::memory::write::<u32>(0x8008_7F28, 0xA81B_0562);
                    }
                    case MoonJumpEnabled: {
                        Cheats::Commands[Cheats::Command::moon_jump].active = false;
                    }
                    case TeleportEnabled: {
                        Cheats::Commands[Cheats::Command::load_position].active = false;
                        Cheats::Commands[Cheats::Command::store_position].active = false;
                    }
                    case ReloadArea: {
                        Cheats::Commands[Cheats::Command::reload_area].active = false;
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