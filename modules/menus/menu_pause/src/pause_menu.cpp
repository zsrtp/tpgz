#include "menus/menu_pause/include/pause_menu.h"
#include <cstdio>
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/utils.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

#define MAX_ORDON_SWORD_OPT 3
#define MAX_MASTER_SWORD_OPT 3
#define MAX_WOOD_SHIELD_OPT 3
#define MAX_HYLIAN_SHIELD_OPT 2
#define MAX_HERO_TUNIC_OPT 2
#define MAX_ZORA_ARMOR_OPT 2
#define MAX_MAGIC_ARMOR_OPT 2
#define MAX_BOMB_CAPACITY_OPT 2
#define MAX_WALLET_OPT 3
#define MAX_ARROW_CAPACITY_OPT 3
#define MAX_HIDDEN_SKILL_OPT 2

KEEP_VAR PauseData* pauseData;

KEEP_FUNC PauseMenu::PauseMenu(Cursor& cursor)
    : Menu(cursor),
      lines{{"ordon sword:", ORDON_SWORD_INDEX, "Wooden Sword / Ordon Sword", false, nullptr,
             MAX_ORDON_SWORD_OPT},
            {"master sword:", MASTER_SWORD_INDEX, "Master Sword / Light Sword", false, nullptr,
             MAX_MASTER_SWORD_OPT},
            {"wooden shield:", WOOD_SHIELD_INDEX, "Ordon Shield / Wooden Shield", false, nullptr,
             MAX_WOOD_SHIELD_OPT},
            {"hylian shield:", HYLIAN_SHIELD_INDEX, "Hylian Shield", false, nullptr,
             MAX_HYLIAN_SHIELD_OPT},
            {"hero's tunic:", HERO_TUNIC_INDEX, "Hero's Tunic", false, nullptr, MAX_HERO_TUNIC_OPT},
            {"zora armor:", ZORA_ARMOR_INDEX, "Zora Armor", false, nullptr, MAX_ZORA_ARMOR_OPT},
            {"magic armor:", MAGIC_ARMOR_INDEX, "Magic Armor", false, nullptr, MAX_MAGIC_ARMOR_OPT},
            {"bomb capacity:", BOMB_CAPACITY_INDEX, "Bomb Bag Capacity", false, nullptr,
             MAX_BOMB_CAPACITY_OPT},
            {"wallet upgrade:", WALLET_INDEX, "Wallet Capacity", false, nullptr, MAX_WALLET_OPT},
            {"arrow capacity:", ARROW_CAPACITY_INDEX, "Arrow Quiver Capacity", false, nullptr,
             MAX_ARROW_CAPACITY_OPT},
            {"ending blow:", ENDING_BLOW_INDEX, "Ending Blow", true, [](){return pauseData->l_ebFlag;}},
            {"shield bash:", SHIELD_BASH_INDEX, "Shield Bash", true, [](){return pauseData->l_sbFlag;}},
            {"backslice:", BACKSLICE_INDEX, "Backslice", true, [](){return pauseData->l_bsFlag;}},
            {"helm splitter:", HELM_SPLITTER_INDEX, "Helm Splitter", true, [](){return pauseData->l_hsFlag;}},
            {"mortal draw:", MORTAL_DRAW_INDEX, "Mortal Draw", true, [](){return pauseData->l_mdFlag;}},
            {"jump strike:", JUMP_STRIKE_INDEX, "Jump Strike", true, [](){return pauseData->l_jsFlag;}},
            {"greatspin:", GREAT_SPIN_INDEX, "Greatspin", true, [](){return pauseData->l_gsFlag;}}} {}

PauseMenu::~PauseMenu() {}

void PauseMenu::resetIndex() {
    pauseData->l_ordonSword_idx = 0;
    pauseData->l_masterSword_idx = 0;
    pauseData->l_woodShield_idx = 0;
    pauseData->l_hyShield_idx = 0;
    pauseData->l_tunic_idx = 0;
    pauseData->l_zoraArmor_idx = 0;
    pauseData->l_magicArmor_idx = 0;
    pauseData->l_bombCap_idx = 0;
    pauseData->l_wallet_idx = 0;
    pauseData->l_arrowCap_idx = 0;
}

void PauseMenu::getEquipment() {
    if (dComIfGs_isItemFirstBit(SWORD)) {
        pauseData->l_ordonSword_idx = 2;
    } else if (dComIfGs_isItemFirstBit(WOOD_STICK)) {
        pauseData->l_ordonSword_idx = 1;
    }

    if (dComIfGs_isItemFirstBit(LIGHT_SWORD)) {
        pauseData->l_masterSword_idx = 2;
    } else if (dComIfGs_isItemFirstBit(MASTER_SWORD)) {
        pauseData->l_masterSword_idx = 1;
    }

    if (dComIfGs_isItemFirstBit(SHIELD)) {
        pauseData->l_woodShield_idx = 2;
    } else if (dComIfGs_isItemFirstBit(WOOD_SHIELD)) {
        pauseData->l_woodShield_idx = 1;
    }

    if (dComIfGs_isItemFirstBit(HYLIA_SHIELD)) {
        pauseData->l_hyShield_idx = 1;
    }

    if (dComIfGs_isItemFirstBit(WEAR_KOKIRI)) {
        pauseData->l_tunic_idx = 1;
    }

    if (dComIfGs_isItemFirstBit(WEAR_ZORA)) {
        pauseData->l_zoraArmor_idx = 1;
    }

    if (dComIfGs_isItemFirstBit(ARMOR)) {
        pauseData->l_magicArmor_idx = 1;
    }

    if (dComIfGs_isItemFirstBit(BOMB_BAG_LV2)) {
        pauseData->l_bombCap_idx = 1;
    }

    switch (dComIfGs_getWalletSize()) {
    case 1:
        pauseData->l_wallet_idx = 1;
        break;
    case 2:
        pauseData->l_wallet_idx = 2;
        break;
    }

    if (dComIfGs_getArrowMax() == 100) {
        pauseData->l_arrowCap_idx = 2;
    } else if (dComIfGs_getArrowMax() == 60) {
        pauseData->l_arrowCap_idx = 1;
    }
}

void PauseMenu::setEquipment() {
    switch (pauseData->l_ordonSword_idx) {
    case 0:
        dComIfGs_offItemFirstBit(WOOD_STICK);
        dComIfGs_offItemFirstBit(SWORD);
        break;
    case 1:
        dComIfGs_onItemFirstBit(WOOD_STICK);
        dComIfGs_offItemFirstBit(SWORD);
        break;
    case 2:
        dComIfGs_onItemFirstBit(SWORD);
        dComIfGs_offItemFirstBit(WOOD_STICK);
        break;
    }

    switch (pauseData->l_masterSword_idx) {
    case 0:
        dComIfGs_offItemFirstBit(MASTER_SWORD);
        dComIfGs_offItemFirstBit(LIGHT_SWORD);
        break;
    case 1:
        dComIfGs_onItemFirstBit(MASTER_SWORD);
        dComIfGs_offItemFirstBit(LIGHT_SWORD);
        break;
    case 2:
        dComIfGs_onItemFirstBit(LIGHT_SWORD);
        break;
    }

    switch (pauseData->l_woodShield_idx) {
    case 0:
        dComIfGs_offItemFirstBit(SHIELD);
        dComIfGs_offItemFirstBit(WOOD_SHIELD);
        break;
    case 1:
        dComIfGs_onItemFirstBit(WOOD_SHIELD);
        break;
    case 2:
        dComIfGs_onItemFirstBit(SHIELD);
        break;
    }

    switch (pauseData->l_hyShield_idx) {
    case 0:
        dComIfGs_offItemFirstBit(HYLIA_SHIELD);
        break;
    case 1:
        dComIfGs_onItemFirstBit(HYLIA_SHIELD);
        break;
    }

    switch (pauseData->l_tunic_idx) {
    case 0:
        dComIfGs_offItemFirstBit(WEAR_KOKIRI);
        break;
    case 1:
        dComIfGs_onItemFirstBit(WEAR_KOKIRI);
        break;
    }

    switch (pauseData->l_zoraArmor_idx) {
    case 0:
        dComIfGs_offItemFirstBit(WEAR_ZORA);
        break;
    case 1:
        dComIfGs_onItemFirstBit(WEAR_ZORA);
        break;
    }

    switch (pauseData->l_magicArmor_idx) {
    case 0:
        dComIfGs_offItemFirstBit(ARMOR);
        break;
    case 1:
        dComIfGs_onItemFirstBit(ARMOR);
        break;
    }

    switch (pauseData->l_bombCap_idx) {
    case 0:
        dComIfGs_offItemFirstBit(BOMB_BAG_LV2);
        break;
    case 1:
        dComIfGs_onItemFirstBit(BOMB_BAG_LV2);
        break;
    }

    switch (pauseData->l_wallet_idx) {
    case 0:
        dComIfGs_setWalletSize(WALLET);
        break;
    case 1:
        dComIfGs_setWalletSize(BIG_WALLET);
        break;
    case 2:
        dComIfGs_setWalletSize(GIANT_WALLET);
        break;
    }

    switch (pauseData->l_arrowCap_idx) {
    case 0:
        dComIfGs_setArrowMax(30);
        break;
    case 1:
        dComIfGs_setArrowMax(60);
        break;
    case 2:
        dComIfGs_setArrowMax(100);
        break;
    }
}

void PauseMenu::draw() {
    static bool init = false;
    cursor.setMode(Cursor::MODE_LIST);

    if (!init) {
        getEquipment();
        init = true;
    }

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        init = false;
        g_menuMgr->pop();
        resetIndex();
        return;
    }

    // update hidden skill flags
    pauseData->l_ebFlag = dComIfGs_isEventBit(0x2904);
    pauseData->l_sbFlag = dComIfGs_isEventBit(0x2908);
    pauseData->l_bsFlag = dComIfGs_isEventBit(0x2902);
    pauseData->l_hsFlag = dComIfGs_isEventBit(0x2901);
    pauseData->l_mdFlag = dComIfGs_isEventBit(0x2A80);
    pauseData->l_jsFlag = dComIfGs_isEventBit(0x2A40);
    pauseData->l_gsFlag = dComIfGs_isEventBit(0x2A20);

    ListMember ordonSword_opt[3] = {"none", "wooden sword", "ordon sword"};
    ListMember masterSword_opt[3] = {"none", "master sword", "light sword"};
    ListMember woodShield_opt[3] = {"none", "ordon shield", "wooden shield"};
    ListMember hyShield_opt[2] = {"none", "hylian shield"};
    ListMember tunic_opt[2] = {"none", "hero's tunic"};
    ListMember zoraArmor_opt[2] = {"none", "zora armor"};
    ListMember magicArmor_opt[2] = {"none", "magic armor"};
    ListMember bombCap_opt[2] = {"30/15/10", "60/30/20"};
    ListMember wallet_opt[3] = {"300 Rupees", "600 Rupees", "1000 Rupees"};
    ListMember arrowCap_opt[3] = {"30 Arrows", "60 Arrows", "100 Arrows"};

    switch (cursor.y) {
    case ORDON_SWORD_INDEX:
        cursor.x = pauseData->l_ordonSword_idx;
        cursor.move(MAX_ORDON_SWORD_OPT, MENU_LINE_NUM);

        if (cursor.y == ORDON_SWORD_INDEX) {
            pauseData->l_ordonSword_idx = cursor.x;
        }
        break;
    case MASTER_SWORD_INDEX:
        cursor.x = pauseData->l_masterSword_idx;
        cursor.move(MAX_MASTER_SWORD_OPT, MENU_LINE_NUM);

        if (cursor.y == MASTER_SWORD_INDEX) {
            pauseData->l_masterSword_idx = cursor.x;
        }
        break;
    case WOOD_SHIELD_INDEX:
        cursor.x = pauseData->l_woodShield_idx;
        cursor.move(MAX_WOOD_SHIELD_OPT, MENU_LINE_NUM);

        if (cursor.y == WOOD_SHIELD_INDEX) {
            pauseData->l_woodShield_idx = cursor.x;
        }
        break;
    case HYLIAN_SHIELD_INDEX:
        cursor.x = pauseData->l_hyShield_idx;
        cursor.move(MAX_HYLIAN_SHIELD_OPT, MENU_LINE_NUM);

        if (cursor.y == HYLIAN_SHIELD_INDEX) {
            pauseData->l_hyShield_idx = cursor.x;
        }
        break;
    case HERO_TUNIC_INDEX:
        cursor.x = pauseData->l_tunic_idx;
        cursor.move(MAX_HERO_TUNIC_OPT, MENU_LINE_NUM);

        if (cursor.y == HERO_TUNIC_INDEX) {
            pauseData->l_tunic_idx = cursor.x;
        }
        break;
    case ZORA_ARMOR_INDEX:
        cursor.x = pauseData->l_zoraArmor_idx;
        cursor.move(MAX_ZORA_ARMOR_OPT, MENU_LINE_NUM);

        if (cursor.y == ZORA_ARMOR_INDEX) {
            pauseData->l_zoraArmor_idx = cursor.x;
        }
        break;
    case MAGIC_ARMOR_INDEX:
        cursor.x = pauseData->l_magicArmor_idx;
        cursor.move(MAX_MAGIC_ARMOR_OPT, MENU_LINE_NUM);

        if (cursor.y == MAGIC_ARMOR_INDEX) {
            pauseData->l_magicArmor_idx = cursor.x;
        }
        break;
    case BOMB_CAPACITY_INDEX:
        cursor.x = pauseData->l_bombCap_idx;
        cursor.move(MAX_BOMB_CAPACITY_OPT, MENU_LINE_NUM);

        if (cursor.y == BOMB_CAPACITY_INDEX) {
            pauseData->l_bombCap_idx = cursor.x;
        }
        break;
    case WALLET_INDEX:
        cursor.x = pauseData->l_wallet_idx;
        cursor.move(MAX_WALLET_OPT, MENU_LINE_NUM);

        if (cursor.y == WALLET_INDEX) {
            pauseData->l_wallet_idx = cursor.x;
        }
        break;
    case ARROW_CAPACITY_INDEX:
        cursor.x = pauseData->l_arrowCap_idx;
        cursor.move(MAX_ARROW_CAPACITY_OPT, MENU_LINE_NUM);

        if (cursor.y == ARROW_CAPACITY_INDEX) {
            pauseData->l_arrowCap_idx = cursor.x;
        }
        break;
    default:
        cursor.move(0, MENU_LINE_NUM);
        break;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        switch (cursor.y) {
        case ENDING_BLOW_INDEX:
            setEventFlag(0x2904);
            break;
        case SHIELD_BASH_INDEX:
            setEventFlag(0x2908);
            break;
        case BACKSLICE_INDEX:
            setEventFlag(0x2902);
            break;
        case HELM_SPLITTER_INDEX:
            setEventFlag(0x2901);
            break;
        case MORTAL_DRAW_INDEX:
            setEventFlag(0x2A80);
            break;
        case JUMP_STRIKE_INDEX:
            setEventFlag(0x2A40);
            break;
        case GREAT_SPIN_INDEX:
            setEventFlag(0x2A20);
            break;
        }
    }

    setEquipment();

    lines[ORDON_SWORD_INDEX].printf(" <%s>", ordonSword_opt[pauseData->l_ordonSword_idx].member);
    lines[MASTER_SWORD_INDEX].printf(" <%s>", masterSword_opt[pauseData->l_masterSword_idx].member);
    lines[WOOD_SHIELD_INDEX].printf(" <%s>", woodShield_opt[pauseData->l_woodShield_idx].member);
    lines[HYLIAN_SHIELD_INDEX].printf(" <%s>", hyShield_opt[pauseData->l_hyShield_idx].member);
    lines[HERO_TUNIC_INDEX].printf(" <%s>", tunic_opt[pauseData->l_tunic_idx].member);
    lines[ZORA_ARMOR_INDEX].printf(" <%s>", zoraArmor_opt[pauseData->l_zoraArmor_idx].member);
    lines[MAGIC_ARMOR_INDEX].printf(" <%s>", magicArmor_opt[pauseData->l_magicArmor_idx].member);
    lines[BOMB_CAPACITY_INDEX].printf(" <%s>", bombCap_opt[pauseData->l_bombCap_idx].member);
    lines[WALLET_INDEX].printf(" <%s>", wallet_opt[pauseData->l_wallet_idx].member);
    lines[ARROW_CAPACITY_INDEX].printf(" <%s>", arrowCap_opt[pauseData->l_arrowCap_idx].member);

    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
