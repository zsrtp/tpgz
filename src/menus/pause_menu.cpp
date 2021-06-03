#include "menus/pause_menu.h"
#include "controller.h"
#include "font.h"
#include "libtp_c/include/msl_c/string.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/utils.h"
#include "utils/cursor.h"
#include "utils/lines.h"

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
    {"ordon sword:", ORDON_SWORD_INDEX, "Wooden Sword / Ordon Sword", false, nullptr,
     MAX_ORDON_SWORD_OPTIONS},
    {"master sword:", MASTER_SWORD_INDEX, "Master Sword / Light Sword", false, nullptr,
     MAX_MASTER_SWORD_OPTIONS},
    {"wooden shield:", WOOD_SHIELD_INDEX, "Ordon Shield / Wooden Shield", false, nullptr,
     MAX_WOOD_SHIELD_OPTIONS},
    {"hylian shield:", HYLIAN_SHIELD_INDEX, "Hylian Shield", false, nullptr,
     MAX_HYLIAN_SHIELD_OPTIONS},
    {"hero's tunic:", HERO_TUNIC_INDEX, "Hero's Tunic", false, nullptr, MAX_HERO_TUNIC_OPTIONS},
    {"zora armor:", ZORA_ARMOR_INDEX, "Zora Armor", false, nullptr, MAX_ZORA_ARMOR_OPTIONS},
    {"magic armor:", MAGIC_ARMOR_INDEX, "Magic Armor", false, nullptr, MAX_MAGIC_ARMOR_OPTIONS},
    {"bomb capacity:", BOMB_CAPACITY_INDEX, "Bomb Bag Capacity", false, nullptr,
     MAX_BOMB_CAPACITY_OPTIONS},
    {"wallet upgrade:", WALLET_INDEX, "Wallet Capacity", false, nullptr, MAX_WALLET_OPTIONS},
    {"arrow capacity:", ARROW_CAPACITY_INDEX, "Arrow Quiver Capacity", false, nullptr,
     MAX_ARROW_CAPACITY_OPTIONS},
    {"ending blow:", ENDING_BLOW_INDEX, "Ending Blow", true, &ending_blow},
    {"shield bash:", SHIELD_BASH_INDEX, "Shield Bash", true, &shield_bash},
    {"backslice:", BACKSLICE_INDEX, "Backslice", true, &backslice},
    {"helm splitter:", HELM_SPLITTER_INDEX, "Helm Splitter", true, &helm_splitter},
    {"mortal draw:", MORTAL_DRAW_INDEX, "Mortal Draw", true, &mortal_draw},
    {"jump strike:", JUMP_STRIKE_INDEX, "Jump Strike", true, &jump_strike},
    {"greatspin:", GREAT_SPIN_INDEX, "Greatspin", true, &great_spin}};

void resetIndex() {
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

void getEquipment() {
    if (dComIfGs_isItemFirstBit(SWORD)) {
        ordon_sword_index = 2;
    } else if (dComIfGs_isItemFirstBit(WOOD_STICK)) {
        ordon_sword_index = 1;
    }

    if (dComIfGs_isItemFirstBit(LIGHT_SWORD)) {
        master_sword_index = 2;
    } else if (dComIfGs_isItemFirstBit(MASTER_SWORD)) {
        master_sword_index = 1;
    }

    if (dComIfGs_isItemFirstBit(SHIELD)) {
        wood_shield_index = 2;
    } else if (dComIfGs_isItemFirstBit(WOOD_SHIELD)) {
        wood_shield_index = 1;
    }

    if (dComIfGs_isItemFirstBit(HYLIA_SHIELD)) {
        hylian_shield_index = 1;
    }

    if (dComIfGs_isItemFirstBit(WEAR_KOKIRI)) {
        hero_tunic_index = 1;
    }

    if (dComIfGs_isItemFirstBit(WEAR_ZORA)) {
        zora_armor_index = 1;
    }

    if (dComIfGs_isItemFirstBit(ARMOR)) {
        magic_armor_index = 1;
    }

    if (dComIfGs_isItemFirstBit(BOMB_BAG_LV2)) {
        bomb_capacity_index = 1;
    }

    switch (dComIfGs_getWalletSize()) {
    case 1: {
        wallet_index = 1;
        break;
    }
    case 2: {
        wallet_index = 2;
        break;
    }
    }

    if (dComIfGs_getArrowMax() == 100) {
        arrow_capacity_index = 2;
    } else if (dComIfGs_getArrowMax() == 60) {
        arrow_capacity_index = 1;
    }
}

void setEquipment() {
    switch (ordon_sword_index) {
    case 0: {
        dComIfGs_offItemFirstBit(WOOD_STICK);
        dComIfGs_offItemFirstBit(SWORD);
        break;
    }
    case 1: {
        dComIfGs_onItemFirstBit(WOOD_STICK);
        dComIfGs_offItemFirstBit(SWORD);
        break;
    }
    case 2: {
        dComIfGs_onItemFirstBit(SWORD);
        dComIfGs_offItemFirstBit(WOOD_STICK);
        break;
    }
    }

    switch (master_sword_index) {
    case 0: {
        dComIfGs_offItemFirstBit(MASTER_SWORD);
        dComIfGs_offItemFirstBit(LIGHT_SWORD);
        break;
    }
    case 1: {
        dComIfGs_onItemFirstBit(MASTER_SWORD);
        dComIfGs_offItemFirstBit(LIGHT_SWORD);
        break;
    }
    case 2: {
        dComIfGs_onItemFirstBit(LIGHT_SWORD);
        break;
    }
    }

    switch (wood_shield_index) {
    case 0: {
        dComIfGs_offItemFirstBit(SHIELD);
        dComIfGs_offItemFirstBit(WOOD_SHIELD);
        break;
    }
    case 1: {
        dComIfGs_onItemFirstBit(WOOD_SHIELD);
        break;
    }
    case 2: {
        dComIfGs_onItemFirstBit(SHIELD);
        break;
    }
    }

    switch (hylian_shield_index) {
    case 0: {
        dComIfGs_offItemFirstBit(HYLIA_SHIELD);
        break;
    }
    case 1: {
        dComIfGs_onItemFirstBit(HYLIA_SHIELD);
        break;
    }
    }

    switch (hero_tunic_index) {
    case 0: {
        dComIfGs_offItemFirstBit(WEAR_KOKIRI);
        break;
    }
    case 1: {
        dComIfGs_onItemFirstBit(WEAR_KOKIRI);
        break;
    }
    }

    switch (zora_armor_index) {
    case 0: {
        dComIfGs_offItemFirstBit(WEAR_ZORA);
        break;
    }
    case 1: {
        dComIfGs_onItemFirstBit(WEAR_ZORA);
        break;
    }
    }

    switch (magic_armor_index) {
    case 0: {
        dComIfGs_offItemFirstBit(ARMOR);
        break;
    }
    case 1: {
        dComIfGs_onItemFirstBit(ARMOR);
        break;
    }
    }

    switch (bomb_capacity_index) {
    case 0: {
        dComIfGs_offItemFirstBit(BOMB_BAG_LV2);
        break;
    }
    case 1: {
        dComIfGs_onItemFirstBit(BOMB_BAG_LV2);
        break;
    }
    }

    switch (wallet_index) {
    case 0: {
        dComIfGs_setWalletSize(WALLET);
        break;
    }
    case 1: {
        dComIfGs_setWalletSize(BIG_WALLET);
        break;
    }
    case 2: {
        dComIfGs_setWalletSize(GIANT_WALLET);
        break;
    }
    }

    switch (arrow_capacity_index) {
    case 0: {
        dComIfGs_setArrowMax(30);
        break;
    }
    case 1: {
        dComIfGs_setArrowMax(60);
        break;
    }
    case 2: {
        dComIfGs_setArrowMax(100);
        break;
    }
    }
}

void PauseMenu::render() {
    // update hidden skill flags
    ending_blow = dComIfGs_isEventBit(0x2904);
    shield_bash = dComIfGs_isEventBit(0x2908);
    backslice = dComIfGs_isEventBit(0x2902);
    helm_splitter = dComIfGs_isEventBit(0x2901);
    mortal_draw = dComIfGs_isEventBit(0x2A80);
    jump_strike = dComIfGs_isEventBit(0x2A40);
    great_spin = dComIfGs_isEventBit(0x2A20);

    if (button_is_pressed(BACK_BUTTON)) {
        init_once = false;
        MenuRendering::set_menu(MN_INVENTORY_INDEX);
        resetIndex();
        return;
    };

    if (!init_once) {
        getEquipment();
        current_input = 0;
        init_once = true;
    }

    ListMember ordon_sword_options[MAX_ORDON_SWORD_OPTIONS] = {"none", "wooden sword",
                                                               "ordon sword"};

    ListMember master_sword_options[MAX_MASTER_SWORD_OPTIONS] = {"none", "master sword",
                                                                 "light sword"};

    ListMember wood_shield_options[MAX_WOOD_SHIELD_OPTIONS] = {"none", "ordon shield",
                                                               "wooden shield"};

    ListMember hylian_shield_options[MAX_HYLIAN_SHIELD_OPTIONS] = {"none", "hylian shield"};

    ListMember hero_tunic_options[MAX_HERO_TUNIC_OPTIONS] = {"none", "hero's tunic"};

    ListMember zora_armor_options[MAX_ZORA_ARMOR_OPTIONS] = {"none", "zora armor"};

    ListMember magic_armor_options[MAX_MAGIC_ARMOR_OPTIONS] = {"none", "magic armor"};

    ListMember bomb_capacity_options[MAX_BOMB_CAPACITY_OPTIONS] = {"30/15/10", "60/30/20"};

    ListMember wallet_options[MAX_WALLET_OPTIONS] = {"300 Rupees", "600 Rupees", "1000 Rupees"};

    ListMember arrow_capacity_options[MAX_ARROW_CAPACITY_OPTIONS] = {"30 Arrows", "60 Arrows",
                                                                     "100 Arrows"};

    switch (cursor.y) {
    case ORDON_SWORD_INDEX: {
        cursor.x = ordon_sword_index;
        Utilities::move_cursor(cursor, LINES, MAX_ORDON_SWORD_OPTIONS, false, false, false, true);
        if (cursor.y == ORDON_SWORD_INDEX) {
            ordon_sword_index = cursor.x;
        }

        break;
    }
    case MASTER_SWORD_INDEX: {
        cursor.x = master_sword_index;
        Utilities::move_cursor(cursor, LINES, MAX_MASTER_SWORD_OPTIONS, false, false, false, true);
        if (cursor.y == MASTER_SWORD_INDEX) {
            master_sword_index = cursor.x;
        }

        break;
    }
    case WOOD_SHIELD_INDEX: {
        cursor.x = wood_shield_index;
        Utilities::move_cursor(cursor, LINES, MAX_WOOD_SHIELD_OPTIONS, false, false, false, true);
        if (cursor.y == WOOD_SHIELD_INDEX) {
            wood_shield_index = cursor.x;
        }

        break;
    }
    case HYLIAN_SHIELD_INDEX: {
        cursor.x = hylian_shield_index;
        Utilities::move_cursor(cursor, LINES, MAX_HYLIAN_SHIELD_OPTIONS, false, false, false, true);
        if (cursor.y == HYLIAN_SHIELD_INDEX) {
            hylian_shield_index = cursor.x;
        }

        break;
    }
    case HERO_TUNIC_INDEX: {
        cursor.x = hero_tunic_index;
        Utilities::move_cursor(cursor, LINES, MAX_HERO_TUNIC_OPTIONS, false, false, false, true);
        if (cursor.y == HERO_TUNIC_INDEX) {
            hero_tunic_index = cursor.x;
        }

        break;
    }
    case ZORA_ARMOR_INDEX: {
        cursor.x = zora_armor_index;
        Utilities::move_cursor(cursor, LINES, MAX_ZORA_ARMOR_OPTIONS, false, false, false, true);
        if (cursor.y == ZORA_ARMOR_INDEX) {
            zora_armor_index = cursor.x;
        }

        break;
    }
    case MAGIC_ARMOR_INDEX: {
        cursor.x = magic_armor_index;
        Utilities::move_cursor(cursor, LINES, MAX_MAGIC_ARMOR_OPTIONS, false, false, false, true);
        if (cursor.y == MAGIC_ARMOR_INDEX) {
            magic_armor_index = cursor.x;
        }

        break;
    }
    case BOMB_CAPACITY_INDEX: {
        cursor.x = bomb_capacity_index;
        Utilities::move_cursor(cursor, LINES, MAX_BOMB_CAPACITY_OPTIONS, false, false, false, true);
        if (cursor.y == BOMB_CAPACITY_INDEX) {
            bomb_capacity_index = cursor.x;
        }

        break;
    }
    case WALLET_INDEX: {
        cursor.x = wallet_index;
        Utilities::move_cursor(cursor, LINES, MAX_WALLET_OPTIONS, false, false, false, true);
        if (cursor.y == WALLET_INDEX) {
            wallet_index = cursor.x;
        }

        break;
    }
    case ARROW_CAPACITY_INDEX: {
        cursor.x = arrow_capacity_index;
        Utilities::move_cursor(cursor, LINES, MAX_ARROW_CAPACITY_OPTIONS, false, false, false,
                               true);
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

    if (current_input == SELECTION_BUTTON && a_held == false) {
        switch (cursor.y) {
        case ENDING_BLOW_INDEX: {
            setEventFlag(0x2904);
            break;
        }
        case SHIELD_BASH_INDEX: {
            setEventFlag(0x2908);
            break;
        }
        case BACKSLICE_INDEX: {
            setEventFlag(0x2902);
            break;
        }
        case HELM_SPLITTER_INDEX: {
            setEventFlag(0x2901);
            break;
        }
        case MORTAL_DRAW_INDEX: {
            setEventFlag(0x2A80);
            break;
        }
        case JUMP_STRIKE_INDEX: {
            setEventFlag(0x2A40);
            break;
        }
        case GREAT_SPIN_INDEX: {
            setEventFlag(0x2A20);
            break;
        }
        }
    }

    setEquipment();

    tp_sprintf(lines[ORDON_SWORD_INDEX].value, " <%s>",
               ordon_sword_options[ordon_sword_index].member);
    tp_sprintf(lines[MASTER_SWORD_INDEX].value, " <%s>",
               master_sword_options[master_sword_index].member);
    tp_sprintf(lines[WOOD_SHIELD_INDEX].value, " <%s>",
               wood_shield_options[wood_shield_index].member);
    tp_sprintf(lines[HYLIAN_SHIELD_INDEX].value, " <%s>",
               hylian_shield_options[hylian_shield_index].member);
    tp_sprintf(lines[HERO_TUNIC_INDEX].value, " <%s>", hero_tunic_options[hero_tunic_index].member);
    tp_sprintf(lines[ZORA_ARMOR_INDEX].value, " <%s>", zora_armor_options[zora_armor_index].member);
    tp_sprintf(lines[MAGIC_ARMOR_INDEX].value, " <%s>",
               magic_armor_options[magic_armor_index].member);
    tp_sprintf(lines[BOMB_CAPACITY_INDEX].value, " <%s>",
               bomb_capacity_options[bomb_capacity_index].member);
    tp_sprintf(lines[WALLET_INDEX].value, " <%s>", wallet_options[wallet_index].member);
    tp_sprintf(lines[ARROW_CAPACITY_INDEX].value, " <%s>",
               arrow_capacity_options[arrow_capacity_index].member);

    Utilities::render_lines(lines, cursor.y, LINES);
};
