#include "libtp_c/include/tp.h"
#include "libtp_c/include/inventory.h"
#include "libtp_c/include/flag.h"
#include "font.h"
#include "menu.h"
#include "controller.h"
#include "utils/cursor.hpp"
#include "utils/lines.hpp"
#include <stdio.h>

#define LINES 17

#define MAX_ORDON_SWORD_OPTIONS 3
#define MAX_MASTER_SWORD_OPTIONS 3
#define MAX_WOOD_SHIELD_OPTIONS 3
#define MAX_HYLIAN_SHIELD_OPTIONS 2
#define MAX_HERO_TUNIC_OPTIONS 2
#define MAX_ZORA_ARMOR_OPTIONS 2
#define MAX_MAGIC_ARMOR_OPTIONS 2
#define MAX_BOMB_CAPACITY_OPTIONS 2
#define MAX_WALLET_OPTIONS 3
#define MAX_ARROW_CAPACITY_OPTIONS 3

#define MAX_HIDDEN_SKILL_OPTIONS 2

static Cursor cursor = {0, 0};
bool pause_visible;
static uint8_t ordon_sword_index = 0;
static uint8_t master_sword_index = 0;
static uint8_t wood_shield_index = 0;
static uint8_t hylian_shield_index = 0;
static uint8_t hero_tunic_index = 0;
static uint8_t zora_armor_index = 0;
static uint8_t magic_armor_index = 0;
static uint8_t bomb_capacity_index = 0;
static uint8_t wallet_index = 0;
static uint8_t arrow_capacity_index = 0;

bool ending_blow;
bool shield_bash;
bool backslice;
bool helm_splitter;
bool mortal_draw;
bool jump_strike;
bool great_spin;

bool init_once = false;

Line lines[LINES] = {
    {"Ordon Sword:", ORDON_SWORD_INDEX, "Wooden Sword / Ordon Sword", false, nullptr, MAX_ORDON_SWORD_OPTIONS},
    {"Master Sword:", MASTER_SWORD_INDEX, "Master Sword / Light Sword", false, nullptr, MAX_MASTER_SWORD_OPTIONS},
    {"Wooden Shield:", WOOD_SHIELD_INDEX, "Ordon Shield / Wooden Shield", false, nullptr, MAX_WOOD_SHIELD_OPTIONS},
    {"Hylian Shield:", HYLIAN_SHIELD_INDEX, "Hylian Shield", false, nullptr, MAX_HYLIAN_SHIELD_OPTIONS},
    {"Hero's Tunic:", HERO_TUNIC_INDEX, "Hero's Tunic", false, nullptr, MAX_HERO_TUNIC_OPTIONS},
    {"Zora Armor:", ZORA_ARMOR_INDEX, "Zora Armor", false, nullptr, MAX_ZORA_ARMOR_OPTIONS},
    {"Magic Armor:", MAGIC_ARMOR_INDEX, "Magic Armor", false, nullptr, MAX_MAGIC_ARMOR_OPTIONS},
    {"Bomb Capacity:", BOMB_CAPACITY_INDEX, "Bomb Bag Capacity", false, nullptr, MAX_BOMB_CAPACITY_OPTIONS},
    {"Wallet Upgrade:", WALLET_INDEX, "Wallet Capacity", false, nullptr, MAX_WALLET_OPTIONS},
    {"Arrow Capacity:", ARROW_CAPACITY_INDEX, "Arrow Quiver Capacity", false, nullptr, MAX_ARROW_CAPACITY_OPTIONS},

    {"ending blow:", ENDING_BLOW_INDEX, "Ending Blow", true, &ending_blow},
    {"shield bash:", SHIELD_BASH_INDEX, "Shield Bash", true, &shield_bash},
    {"backslice:", BACKSLICE_INDEX, "Backslice", true, &backslice},
    {"helm splitter:", HELM_SPLITTER_INDEX, "Helm Splitter", true, &helm_splitter},
    {"mortal draw:", MORTAL_DRAW_INDEX, "Mortal Draw", true, &mortal_draw},
    {"jump strike:", JUMP_STRIKE_INDEX, "Jump Strike", true, &jump_strike},
    {"greatspin:", GREAT_SPIN_INDEX, "Greatspin", true, &great_spin}};

void reset_index() {
    ordon_sword_index = 0;
    master_sword_index = 0;
    wood_shield_index = 0;
    hylian_shield_index = 0;
    hero_tunic_index = 0;
    zora_armor_index = 0;
    magic_armor_index = 0;
    bomb_capacity_index = 0;
    wallet_index = 0;
    arrow_capacity_index = 0;
}

void get_equipment() {
    if (tp_gameInfo.inventory.equipment_flags_1 & (1UL << 0)) {
        ordon_sword_index = 2;
    } else if (tp_gameInfo.inventory.wood_sword_flag & (1UL << 7)) {
        ordon_sword_index = 1;
    }

    if (tp_gameInfo.inventory.light_sword_flag & (1UL << 2)) {
        master_sword_index = 2;
    } else if (tp_gameInfo.inventory.equipment_flags_1 & (1UL << 1)) {
        master_sword_index = 1;
    }

    if (tp_gameInfo.inventory.equipment_flags_1 & (1UL << 3)) {
        wood_shield_index = 2;
    } else if (tp_gameInfo.inventory.equipment_flags_1 & (1UL << 2)) {
        wood_shield_index = 1;
    }

    if (tp_gameInfo.inventory.equipment_flags_1 & (1UL << 4)) {
        hylian_shield_index = 1;
    }

    if (tp_gameInfo.inventory.equipment_flags_1 & (1UL << 7)) {
        hero_tunic_index = 1;
    }

    if (tp_gameInfo.inventory.equipment_flags_0 & (1UL << 1)) {
        zora_armor_index = 1;
    }

    if (tp_gameInfo.inventory.equipment_flags_0 & (1UL << 0)) {
        magic_armor_index = 1;
    }

    if (tp_gameInfo.inventory.light_sword_flag & (1UL << 7)) {
        bomb_capacity_index = 1;
    }

    switch (tp_gameInfo.link.wallet_upgrade) {
        case 1: {
            wallet_index = 1;
            break;
        }
        case 2: {
            wallet_index = 2;
            break;
        }
    }

    if (tp_gameInfo.inventory.arrow_capacity == 100) {
        arrow_capacity_index = 2;
    } else if (tp_gameInfo.inventory.arrow_capacity == 60) {
        arrow_capacity_index = 1;
    }
}

void set_equipment() {
    switch (ordon_sword_index) {
        case 0: {
            tp_gameInfo.inventory.equipment_flags_1 &= ~(1UL << 0);
            tp_gameInfo.inventory.wood_sword_flag &= ~(1UL << 7);
            break;
        }
        case 1: {
            tp_gameInfo.inventory.wood_sword_flag |= 1UL << 7;
            tp_gameInfo.inventory.equipment_flags_1 &= ~(1UL << 0);
            break;
        }
        case 2: {
            tp_gameInfo.inventory.equipment_flags_1 |= 1UL << 0;
            tp_gameInfo.inventory.wood_sword_flag &= ~(1UL << 7);
            break;
        }
    }

    switch (master_sword_index) {
        case 0: {
            tp_gameInfo.inventory.equipment_flags_1 &= ~(1UL << 1);
            tp_gameInfo.inventory.light_sword_flag &= ~(1UL << 2);
            break;
        }
        case 1: {
            tp_gameInfo.inventory.equipment_flags_1 |= 1UL << 1;
            tp_gameInfo.inventory.light_sword_flag &= ~(1UL << 2);
            break;
        }
        case 2: {
            tp_gameInfo.inventory.light_sword_flag |= 1UL << 2;
            break;
        }
    }

    switch (wood_shield_index) {
        case 0: {
            tp_gameInfo.inventory.equipment_flags_1 &= ~(1UL << 2);
            tp_gameInfo.inventory.equipment_flags_1 &= ~(1UL << 3);
            break;
        }
        case 1: {
            tp_gameInfo.inventory.equipment_flags_1 |= 1UL << 2;
            break;
        }
        case 2: {
            tp_gameInfo.inventory.equipment_flags_1 |= 1UL << 3;
            break;
        }
    }

    switch (hylian_shield_index) {
        case 0: {
            tp_gameInfo.inventory.equipment_flags_1 &= ~(1UL << 4);
            break;
        }
        case 1: {
            tp_gameInfo.inventory.equipment_flags_1 |= 1UL << 4;
            break;
        }
    }

    switch (hero_tunic_index) {
        case 0: {
            tp_gameInfo.inventory.equipment_flags_1 &= ~(1UL << 7);
            break;
        }
        case 1: {
            tp_gameInfo.inventory.equipment_flags_1 |= 1UL << 7;
            break;
        }
    }

    switch (zora_armor_index) {
        case 0: {
            tp_gameInfo.inventory.equipment_flags_0 &= ~(1UL << 1);
            break;
        }
        case 1: {
            tp_gameInfo.inventory.equipment_flags_0 |= 1UL << 1;
            break;
        }
    }

    switch (magic_armor_index) {
        case 0: {
            tp_gameInfo.inventory.equipment_flags_0 &= ~(1UL << 0);
            break;
        }
        case 1: {
            tp_gameInfo.inventory.equipment_flags_0 |= 1UL << 0;
            break;
        }
    }

    switch (bomb_capacity_index) {
        case 0: {
            tp_gameInfo.inventory.light_sword_flag &= ~(1UL << 7);
            break;
        }
        case 1: {
            tp_gameInfo.inventory.light_sword_flag |= 1UL << 7;
            break;
        }
    }

    switch (wallet_index) {
        case 0: {
            tp_gameInfo.link.wallet_upgrade = 0;
            break;
        }
        case 1: {
            tp_gameInfo.link.wallet_upgrade = 1;
            break;
        }
        case 2: {
            tp_gameInfo.link.wallet_upgrade = 2;
            break;
        }
    }

    switch (arrow_capacity_index) {
        case 0: {
            tp_gameInfo.inventory.arrow_capacity = 30;
            break;
        }
        case 1: {
            tp_gameInfo.inventory.arrow_capacity = 60;
            break;
        }
        case 2: {
            tp_gameInfo.inventory.arrow_capacity = 100;
            break;
        }
    }

}

void PauseMenu::render(Font& font) {
	// update hidden skill flags
    ending_blow = (tp_gameInfo.event_flags.hidden_skills_flags & (1 << 10));
    shield_bash = (tp_gameInfo.event_flags.hidden_skills_flags & (1 << 11));
    backslice = (tp_gameInfo.event_flags.hidden_skills_flags & (1 << 9));
    helm_splitter = (tp_gameInfo.event_flags.hidden_skills_flags & (1 << 8));
    mortal_draw = (tp_gameInfo.event_flags.hidden_skills_flags & (1 << 7));
    jump_strike = (tp_gameInfo.event_flags.hidden_skills_flags & (1 << 6));
    great_spin = (tp_gameInfo.event_flags.hidden_skills_flags & (1 << 5));

    if (button_is_pressed(Controller::B)) {
        init_once = false;
		pause_visible = false;
        inventory_visible = true;
        reset_index();
        return;
    };

    if (!init_once) {
        get_equipment();
        current_input = 0;
        init_once = true;
    }

    ListMember ordon_sword_options[MAX_ORDON_SWORD_OPTIONS] = {
        "",
        "Wooden Sword",
        "Ordon Sword"};

    ListMember master_sword_options[MAX_MASTER_SWORD_OPTIONS] = {
        "",
        "Master Sword",
        "Light Sword"};

    ListMember wood_shield_options[MAX_WOOD_SHIELD_OPTIONS] = {
        "",
        "Ordon Shield",
        "Wooden Shield"};

    ListMember hylian_shield_options[MAX_HYLIAN_SHIELD_OPTIONS] = {
        "",
        "Hylian Shield"};

    ListMember hero_tunic_options[MAX_HERO_TUNIC_OPTIONS] = {
        "",
        "Hero's Tunic"};

    ListMember zora_armor_options[MAX_ZORA_ARMOR_OPTIONS] = {
        "",
        "Zora Armor"};

    ListMember magic_armor_options[MAX_MAGIC_ARMOR_OPTIONS] = {
        "",
        "Magic Armor"};

    ListMember bomb_capacity_options[MAX_BOMB_CAPACITY_OPTIONS] = {
        "30/15/10",
        "60/30/20"};

    ListMember wallet_options[MAX_WALLET_OPTIONS] = {
        "300 Rupees",
        "600 Rupees",
        "1000 Rupees"};

    ListMember arrow_capacity_options[MAX_ARROW_CAPACITY_OPTIONS] = {
        "30 Arrows",
        "60 Arrows",
        "100 Arrows"};


    switch (cursor.y) {
        case ORDON_SWORD_INDEX: {
            cursor.x = ordon_sword_index;
            Utilities::move_cursor(cursor, LINES, MAX_ORDON_SWORD_OPTIONS);
            if (cursor.y == ORDON_SWORD_INDEX) {
                ordon_sword_index = cursor.x;
            }

            break;
        }
        case MASTER_SWORD_INDEX: {
            cursor.x = master_sword_index;
            Utilities::move_cursor(cursor, LINES, MAX_MASTER_SWORD_OPTIONS);
            if (cursor.y == MASTER_SWORD_INDEX) {
                master_sword_index = cursor.x;
            }

            break;
        }
        case WOOD_SHIELD_INDEX: {
            cursor.x = wood_shield_index;
            Utilities::move_cursor(cursor, LINES, MAX_WOOD_SHIELD_OPTIONS);
            if (cursor.y == WOOD_SHIELD_INDEX) {
                wood_shield_index = cursor.x;
            }

            break;
        }
        case HYLIAN_SHIELD_INDEX: {
            cursor.x = hylian_shield_index;
            Utilities::move_cursor(cursor, LINES, MAX_HYLIAN_SHIELD_OPTIONS);
            if (cursor.y == HYLIAN_SHIELD_INDEX) {
                hylian_shield_index = cursor.x;
            }

            break;
        }
        case HERO_TUNIC_INDEX: {
            cursor.x = hero_tunic_index;
            Utilities::move_cursor(cursor, LINES, MAX_HERO_TUNIC_OPTIONS);
            if (cursor.y == HERO_TUNIC_INDEX) {
                hero_tunic_index = cursor.x;
            }

            break;
        }
        case ZORA_ARMOR_INDEX: {
            cursor.x = zora_armor_index;
            Utilities::move_cursor(cursor, LINES, MAX_ZORA_ARMOR_OPTIONS);
            if (cursor.y == ZORA_ARMOR_INDEX) {
                zora_armor_index = cursor.x;
            }

            break;
        }
        case MAGIC_ARMOR_INDEX: {
            cursor.x = magic_armor_index;
            Utilities::move_cursor(cursor, LINES, MAX_MAGIC_ARMOR_OPTIONS);
            if (cursor.y == MAGIC_ARMOR_INDEX) {
                magic_armor_index = cursor.x;
            }

            break;
        }
        case BOMB_CAPACITY_INDEX: {
            cursor.x = bomb_capacity_index;
            Utilities::move_cursor(cursor, LINES, MAX_BOMB_CAPACITY_OPTIONS);
            if (cursor.y == BOMB_CAPACITY_INDEX) {
                bomb_capacity_index = cursor.x;
            }

            break;
        }
        case WALLET_INDEX: {
            cursor.x = wallet_index;
            Utilities::move_cursor(cursor, LINES, MAX_WALLET_OPTIONS);
            if (cursor.y == WALLET_INDEX) {
                wallet_index = cursor.x;
            }

            break;
        }
        case ARROW_CAPACITY_INDEX: {
            cursor.x = arrow_capacity_index;
            Utilities::move_cursor(cursor, LINES, MAX_ARROW_CAPACITY_OPTIONS);
            if (cursor.y == ARROW_CAPACITY_INDEX) {
                arrow_capacity_index = cursor.x;
            }

            break;
        }
        default: {
            Utilities::move_cursor(cursor, LINES, 2);
            break;
        }
    }

	if (current_input == 256 && a_held == false) {
		switch (cursor.y) {
            case ENDING_BLOW_INDEX: {
                tp_gameInfo.event_flags.hidden_skills_flags ^= 1 << 10;
                break;
			}
            case SHIELD_BASH_INDEX: {
                tp_gameInfo.event_flags.hidden_skills_flags ^= 1 << 11;
                break;
            }
            case BACKSLICE_INDEX: {
                tp_gameInfo.event_flags.hidden_skills_flags ^= 1 << 9;
                break;
            }
            case HELM_SPLITTER_INDEX: {
                tp_gameInfo.event_flags.hidden_skills_flags ^= 1 << 8;
                break;
            }
            case MORTAL_DRAW_INDEX: {
                tp_gameInfo.event_flags.hidden_skills_flags ^= 1 << 7;
                break;
            }
            case JUMP_STRIKE_INDEX: {
                tp_gameInfo.event_flags.hidden_skills_flags ^= 1 << 6;
                break;
            }
            case GREAT_SPIN_INDEX: {
                tp_gameInfo.event_flags.hidden_skills_flags ^= 1 << 5;
                break;
            }
		}
	}

    set_equipment();

    sprintf(lines[ORDON_SWORD_INDEX].line, "ordon sword: <%s>", ordon_sword_options[ordon_sword_index].member);
    sprintf(lines[MASTER_SWORD_INDEX].line, "master sword: <%s>", master_sword_options[master_sword_index].member);
    sprintf(lines[WOOD_SHIELD_INDEX].line, "wooden shield: <%s>", wood_shield_options[wood_shield_index].member);
    sprintf(lines[HYLIAN_SHIELD_INDEX].line, "hylian shield: <%s>", hylian_shield_options[hylian_shield_index].member);
    sprintf(lines[HERO_TUNIC_INDEX].line, "hero tunic: <%s>", hero_tunic_options[hero_tunic_index].member);
    sprintf(lines[ZORA_ARMOR_INDEX].line, "zora armor: <%s>", zora_armor_options[zora_armor_index].member);
    sprintf(lines[MAGIC_ARMOR_INDEX].line, "magic armor: <%s>", magic_armor_options[magic_armor_index].member);
    sprintf(lines[BOMB_CAPACITY_INDEX].line, "bomb capacity: <%s>", bomb_capacity_options[bomb_capacity_index].member);
    sprintf(lines[WALLET_INDEX].line, "wallet size: <%s>", wallet_options[wallet_index].member);
    sprintf(lines[ARROW_CAPACITY_INDEX].line, "arrow capacity: <%s>", arrow_capacity_options[arrow_capacity_index].member);

    Utilities::render_lines(font, lines, cursor.y, LINES);
};
