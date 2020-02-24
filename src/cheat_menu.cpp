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
#include <string.h>
#define LINES 13

static int cursor = 2;
// static float current_offset = 0.0f;
// static int current_index = 0;
// bool trigger_menu_anim = false;

Line lines[LINES] = {
    {"cheats", 0},
    {"", 1},
    {"invincible", 2, "makes link invincible"},
    {"invincible enemies", 3, "makes some enemies invicible (area reload required)"},
    {"infinite air", 4, "gives link infinite air underwater"},
    {"infinite oil", 5, "gives link infinite lantern oil"},
    {"infinite bombs", 6, "gives link 99 bombs in all bags"},
    {"infinite rupees", 7, "link will always have 1000 rupees"},
    {"infinite arrows", 8, "gives link 99 arrows"},
    {"moon jump", 9, "hold R+A to moon jump"},
    {"teleport", 10, "use dpad+up to set position, use dpad+down to load position"},
    {"area reload", 11, "use L+R+Start to reload current area"},
    {"fast movement", 12, "move much faster (human rolling only for now)"}};

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

void CheatsMenu::render(Font &font) {
        if (button_is_down(Controller::B) && !button_is_held(Controller::B)) {
            cheats_visible = false;
            mm_visible = true;
            return;
        };

        if (button_is_down(Controller::DPAD_DOWN) && !button_is_held(Controller::DPAD_DOWN)) {
            if (cursor < LINES - 1) {
                cursor++;
            } else if (cursor == LINES - 1) {
                cursor = 2;
            }
        };

        if (button_is_down(Controller::DPAD_UP) && !button_is_held(Controller::DPAD_UP)) {
            if (cursor > 2) {
                cursor--;
            } else if (cursor == 2) {
                cursor = LINES - 1;
            }
        };

        if (button_is_down(Controller::A) && !button_is_held(Controller::A)) {
            switch (cursor) {
                case INVINCIBLE_INDEX: {
                }
                case INVINCIBLE_ENEMIES_INDEX: {
                }
                case INFINITE_AIR_INDEX: {
                }
                case INFINITE_OIL_INDEX: {
                }
                case INFINITE_BOMBS_INDEX: {
                }
                case INFINITE_RUPEES_INDEX: {
                }
                case INFINITE_ARROWS_INDEX: {
                }
                case MOON_JUMP_INDEX: {
                    Cheats::Items[7].active = true;
                }
                case TELEPORT_INDEX: {
                }
                case RELOAD_AREA_INDEX: {
                }
                case FAST_MOVEMENT_INDEX: {
                    Cheats::Items[10].active = true;
                }
            }
        }
        font.renderChars("tpgz v0.1", 13.0f, 15.0f, 0x008080FF);

        if (cheats_visible == true) {
            for (int i = 0; i < LINES; i++) {
                float offset = (60.0f + ((float)i * 20.0f));
                int cursor_color = 0xFFFFFF00;
                int description_color = 0xFFFFFF00;
                int cursor_alpha = 0xFF;
                int description_alpha = 0xFF;
                if (lines[i].idx != cursor) {
                    cursor_alpha = 0x80;
                }
                if (lines[i].idx != cursor) {
                    description_alpha = 0x00;
                }

                // if (g_gorge_active) {
                //     strcpy(lines[GORGE_INDEX].line, "gorge void [X]");
                // } else {
                //     strcpy(lines[GORGE_INDEX].line, "gorge void [ ]");
                // }

                // if (g_roll_check_active) {
                //     strcpy(lines[ROLL_INDEX].line, "roll check [X]");
                // } else {
                //     strcpy(lines[ROLL_INDEX].line, "roll check [ ]");
                // }

                cursor_color |= cursor_alpha;
                description_color |= description_alpha;
                font.renderChars(lines[i].line, 15.0f, offset, cursor_color);
                font.renderChars(lines[i].description, 15.0f, 440.f, description_color);
            };
        }
    };