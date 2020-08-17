#include <stdio.h>
#include "libtp_c/include/system.h"
#include "font.h"
#include "menu.h"
#include "controller.h"
#include "utils/cursor.hpp"
#include "utils/lines.hpp"

#define ITEM_WHEEL_SLOTS 24
#define LINES ITEM_WHEEL_SLOTS
#define TOTAL_ITEMS 58

static Cursor cursor = {0,0};
int listIdx = 0;
int new_int_item_id;
bool init_once = false;
bool item_wheel_visible;

// probably a better way to do this
bool IsInItemIDEnum(int val) {
    switch (val) {
        case OOCCOO_SR: {
            return true;
            break;
        }
        case OOCCOO_JR: {
            return true;
            break;
        }
        case OOCCOOS_NOTE: {
            return true;
            break;
        }
        case HAWKEYE: {
            return true;
            break;
        }
        case GALE_BOOMERANG: {
            return true;
            break;
        }
        case SPINNER: {
            return true;
            break;
        }
        case BALL_AND_CHAIN: {
            return true;
            break;
        }
        case HEROS_BOW: {
            return true;
            break;
        }
        case CLAWSHOT: {
            return true;
            break;
        }
        case IRON_BOOTS: {
            return true;
            break;
        }
        case DOMINION_ROD: {
            return true;
            break;
        }
        case DOUBLE_CLAWSHOT: {
            return true;
            break;
        }
        case LANTERN: {
            return true;
            break;
        }
        case SLINGSHOT: {
            return true;
            break;
        }
        case FISHING_ROD: {
            return true;
            break;
        }
        case EMPTY_BOMBBAG: {
            return true;
            break;
        }
        case ROD_BEE_LARVA: {
            return true;
            break;
        }
        case ROD_CORAL_EARRING: {
            return true;
            break;
        }
        case ROD_WORM: {
            return true;
            break;
        }
        case ROD_CORAL_EARRING_BEE_LARVA: {
            return true;
            break;
        }
        case ROD_CORAL_EARRING_WORM: {
            return true;
            break;
        }
        case EMPTY_BOTTLE: {
            return true;
            break;
        }
        case RED_POTION: {
            return true;
            break;
        }
        case MAGIC_POTION: {
            return true;
            break;
        }
        case BLUE_POTION: {
            return true;
            break;
        }
        case MILK: {
            return true;
            break;
        }
        case HALF_MILK: {
            return true;
            break;
        }
        case LANTERN_OIL: {
            return true;
            break;
        }
        case WATER: {
            return true;
            break;
        }
        case NASTY_SOUP: {
            return true;
            break;
        }
        case HOT_SPRING_WATER: {
            return true;
            break;
        }
        case FAIRY: {
            return true;
            break;
        }
        case REGULAR_BOMBS: {
            return true;
            break;
        }
        case WATER_BOMBS: {
            return true;
            break;
        }
        case BOMBLINGS: {
            return true;
            break;
        }
        case FAIRY_TEARS: {
            return true;
            break;
        }
        case WORM: {
            return true;
            break;
        }
        case BEE_LARVA: {
            return true;
            break;
        }
        case RARE_CHU: {
            return true;
            break;
        }
        case RED_CHU: {
            return true;
            break;
        }
        case BLUE_CHU: {
            return true;
            break;
        }
        case GREEN_CHU: {
            return true;
            break;
        }
        case YELLOW_CHU: {
            return true;
            break;
        }
        case PURPLE_CHU: {
            return true;
            break;
        }
        case SIMPLE_SOUP: {
            return true;
            break;
        }
        case GOOD_SOUP: {
            return true;
            break;
        }
        case SUPERB_SOUP: {
            return true;
            break;
        }
        case RENADOS_LETTER: {
            return true;
            break;
        }
        case INVOICE: {
            return true;
            break;
        }
        case WOODEN_STATUE: {
            return true;
            break;
        }
        case ILIAS_CHARM: {
            return true;
            break;
        }
        case HORSE_CALL: {
            return true;
            break;
        }
        case AURUS_MEMO: {
            return true;
            break;
        }
        case ASHEIS_SKETCH: {
            return true;
            break;
        }
        case ANCIENT_SKY_BOOK_EMPTY: {
            return true;
            break;
        }
        case ANCIENT_SKY_BOOK_PARTIAL: {
            return true;
            break;
        }
        case ANCIENT_SKY_BOOK_FILLED: {
            return true;
            break;
        }
        case NO_ITEM: {
            return true;
            break;
        }
        default: {
            return false;
            break;
        }
    }
}

const SlotItem default_items[ITEM_WHEEL_SLOTS] = {
    {SLOT_0, GALE_BOOMERANG},
    {SLOT_1, LANTERN},
    {SLOT_2, SPINNER},
    {SLOT_3, IRON_BOOTS},
    {SLOT_4, HEROS_BOW},
    {SLOT_5, HAWKEYE},
    {SLOT_6, BALL_AND_CHAIN},
    {SLOT_7, NO_ITEM},
    {SLOT_8, DOMINION_ROD},
    {SLOT_9, CLAWSHOT},
    {SLOT_10, DOUBLE_CLAWSHOT},
    {SLOT_11, EMPTY_BOTTLE},
    {SLOT_12, EMPTY_BOTTLE},
    {SLOT_13, EMPTY_BOTTLE},
    {SLOT_14, EMPTY_BOTTLE},
    {SLOT_15, EMPTY_BOMBBAG},
    {SLOT_16, EMPTY_BOMBBAG},
    {SLOT_17, EMPTY_BOMBBAG},
    {SLOT_18, OOCCOO_SR},
    {SLOT_19, AURUS_MEMO},
    {SLOT_20, FISHING_ROD},
    {SLOT_21, HORSE_CALL},
    {SLOT_22, ANCIENT_SKY_BOOK_EMPTY},
    {SLOT_23, SLINGSHOT}};

SlotItem slot_items[ITEM_WHEEL_SLOTS] = {
    {SLOT_0, tp_gameInfo.inventory.item_values.gale_boomerang_id},
    {SLOT_1, tp_gameInfo.inventory.item_values.lantern_id},
    {SLOT_2, tp_gameInfo.inventory.item_values.spinner_id},
    {SLOT_3, tp_gameInfo.inventory.item_values.iron_boots_id},
    {SLOT_4, tp_gameInfo.inventory.item_values.hero_s_bow_id},
    {SLOT_5, tp_gameInfo.inventory.item_values.hawkeye_id},
    {SLOT_6, tp_gameInfo.inventory.item_values.ball_and_chain_id},
    {SLOT_7, tp_gameInfo.inventory.item_values._unk_0},
    {SLOT_8, tp_gameInfo.inventory.item_values.dominion_rod_id},
    {SLOT_9, tp_gameInfo.inventory.item_values.clawshot_id},
    {SLOT_10, tp_gameInfo.inventory.item_values.double_clawshot_id},
    {SLOT_11, tp_gameInfo.inventory.item_values.bottle_1_id},
    {SLOT_12, tp_gameInfo.inventory.item_values.bottle_2_id},
    {SLOT_13, tp_gameInfo.inventory.item_values.bottle_3_id},
    {SLOT_14, tp_gameInfo.inventory.item_values.bottle_4_id},
    {SLOT_15, tp_gameInfo.inventory.item_values.bomb_bag_1_id},
    {SLOT_16, tp_gameInfo.inventory.item_values.bomb_bag_2_id},
    {SLOT_17, tp_gameInfo.inventory.item_values.bomb_bag_3_id},
    {SLOT_18, tp_gameInfo.inventory.item_values.ooccoo_id},
    {SLOT_19, tp_gameInfo.inventory.item_values.auru_s_memo_ashei_s_sketch_id},
    {SLOT_20, tp_gameInfo.inventory.item_values.fishing_rod_earring_id},
    {SLOT_21, tp_gameInfo.inventory.item_values.horse_call_id},
    {SLOT_22, tp_gameInfo.inventory.item_values.ancient_sky_book_id},
    {SLOT_23, tp_gameInfo.inventory.item_values.slingshot_id}};

void set_slot_to_item_id(int slot_id, int item_id) {
    // find the right slot
    for (int i = 0; i < ITEM_WHEEL_SLOTS; i++) {
        if (slot_items[i].slot_id == slot_id) {
            // set it to the new item id passed in
            slot_items[i].item_id = item_id;
        } else {
            continue;
        }
    }
}

void increment_slot_item(uint8_t& current_internal_item_id, int slot_id) {
    current_internal_item_id = slot_items[slot_id].item_id;
    do {
        current_internal_item_id++;
    } while (IsInItemIDEnum(current_internal_item_id) == false);
    set_slot_to_item_id(slot_id, current_internal_item_id);
}

const ItemLookup lookup_table[TOTAL_ITEMS] = {
    {OOCCOO_SR, "ooccoo sr."},
    {OOCCOO_JR, "ooccoo jr."},
    {OOCCOOS_NOTE, "ooccoo's note"},
    {HAWKEYE, "hawkeye"},
    {GALE_BOOMERANG, "gale boomerang"},
    {SPINNER, "spinner"},
    {BALL_AND_CHAIN, "ball and chain"},
    {HEROS_BOW, "hero's bow"},
    {CLAWSHOT, "clawshot"},
    {IRON_BOOTS, "iron boots"},
    {DOMINION_ROD, "dominion rod"},
    {DOUBLE_CLAWSHOT, "double clawshot"},
    {LANTERN, "lantern"},
    {SLINGSHOT, "slingshot"},
    {FISHING_ROD, "fishing rod"},
    {EMPTY_BOMBBAG, "empty bomb bag"},
    {ROD_BEE_LARVA, "fishing rod (bee larva)"},
    {ROD_CORAL_EARRING, "fishing rod (coral earring)"},
    {ROD_WORM, "fishing rod (worm)"},
    {ROD_CORAL_EARRING_BEE_LARVA, "fishing rod (coral earring/bee larva)"},
    {ROD_CORAL_EARRING_WORM, "fishing rod (coral earring/worm)"},
    {EMPTY_BOTTLE, "empty bottle"},
    {RED_POTION, "red potion"},
    {MAGIC_POTION, "magic potion"},
    {BLUE_POTION, "blue potion"},
    {MILK, "milk"},
    {HALF_MILK, "half milk"},
    {LANTERN_OIL, "lantern oil"},
    {WATER, "water"},
    {NASTY_SOUP, "nasty soup"},
    {HOT_SPRING_WATER, "hot spring water"},
    {FAIRY, "fairy"},
    {REGULAR_BOMBS, "regular bombs"},
    {WATER_BOMBS, "water bombs"},
    {BOMBLINGS, "bomblings"},
    {FAIRY_TEARS, "fairy tears"},
    {WORM, "worm"},
    {BEE_LARVA, "bee larva"},
    {RARE_CHU, "rare chu"},
    {RED_CHU, "red chu"},
    {BLUE_CHU, "blue chu"},
    {GREEN_CHU, "green chu"},
    {YELLOW_CHU, "yellow chu"},
    {PURPLE_CHU, "purple chu"},
    {SIMPLE_SOUP, "simple soup"},
    {GOOD_SOUP, "good soup"},
    {SUPERB_SOUP, "superb soup"},
    {RENADOS_LETTER, "renados letter"},
    {INVOICE, "invoice"},
    {WOODEN_STATUE, "wooden statue"},
    {ILIAS_CHARM, "ilia's charm"},
    {HORSE_CALL, "horse call"},
    {AURUS_MEMO, "auru's memo"},
    {ASHEIS_SKETCH, "ashei's sketch"},
    {ANCIENT_SKY_BOOK_EMPTY, "ancient sky book (empty)"},
    {ANCIENT_SKY_BOOK_PARTIAL, "ancient sky book (partial)"},
    {ANCIENT_SKY_BOOK_FILLED, "ancient sky book (filled)"},
    {NO_ITEM, "no item"}};

Line lines[LINES] = {
    {"", SLOT_0, "", false, nullptr, false},
    {"", SLOT_1, "", false, nullptr, false},
    {"", SLOT_2, "", false, nullptr, false},
    {"", SLOT_3, "", false, nullptr, false},
    {"", SLOT_4, "", false, nullptr, false},
    {"", SLOT_5, "", false, nullptr, false},
    {"", SLOT_6, "", false, nullptr, false},
    {"", SLOT_7, "", false, nullptr, false},
    {"", SLOT_8, "", false, nullptr, false},
    {"", SLOT_9, "", false, nullptr, false},
    {"", SLOT_10, "", false, nullptr, false},
    {"", SLOT_11, "", false, nullptr, false},
    {"", SLOT_12, "", false, nullptr, false},
    {"", SLOT_13, "", false, nullptr, false},
    {"", SLOT_14, "", false, nullptr, false},
    {"", SLOT_15, "", false, nullptr, false},
    {"", SLOT_16, "", false, nullptr, false},
    {"", SLOT_17, "", false, nullptr, false},
    {"", SLOT_18, "", false, nullptr, false},
    {"", SLOT_19, "", false, nullptr, false},
    {"", SLOT_20, "", false, nullptr, false},
    {"", SLOT_21, "", false, nullptr, false},
    {"", SLOT_22, "", false, nullptr, false},
    {"", SLOT_23, "", false, nullptr, false}};

void ItemWheelMenu::render(Font& font) {
    if (button_is_pressed(Controller::B)) {
        item_wheel_visible = false;
        inventory_visible = true;
        init_once = false;
        return;
    };

    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

    // populate the default line name and description
    for (int i = 0; i < LINES; i++) {
        for (int k = 0; k < ITEM_WHEEL_SLOTS; k++) {
            // find the right slot to pull the value from
            if (slot_items[k].slot_id == i) {
                new_int_item_id = slot_items[k].item_id;
            }
        }
        for (int j = 0; j < TOTAL_ITEMS; j++) {
            if (lookup_table[j].item_id == new_int_item_id) {
                sprintf(lines[i].line, "slot %d: %s", default_items[i].slot_id, lookup_table[j].item_description);
            }
            if (lookup_table[j].item_id == default_items[i].item_id) {
                sprintf(lines[i].description, "slot %d default: %s. Press Z to set to default", i, lookup_table[j].item_description);
            } else {
                continue;
            }
        }
    }

    Utilities::move_cursor(cursor, LINES);
    Utilities::render_lines(font, lines, cursor.y, LINES);

    // update to current items
    slot_items[0].item_id = tp_gameInfo.inventory.item_values.gale_boomerang_id;
    slot_items[1].item_id = tp_gameInfo.inventory.item_values.lantern_id;
    slot_items[2].item_id = tp_gameInfo.inventory.item_values.spinner_id;
    slot_items[3].item_id = tp_gameInfo.inventory.item_values.iron_boots_id;
    slot_items[4].item_id = tp_gameInfo.inventory.item_values.hero_s_bow_id;
    slot_items[5].item_id = tp_gameInfo.inventory.item_values.hawkeye_id;
    slot_items[6].item_id = tp_gameInfo.inventory.item_values.ball_and_chain_id;
    slot_items[7].item_id = tp_gameInfo.inventory.item_values._unk_0;
    slot_items[8].item_id = tp_gameInfo.inventory.item_values.dominion_rod_id;
    slot_items[9].item_id = tp_gameInfo.inventory.item_values.clawshot_id;
    slot_items[10].item_id = tp_gameInfo.inventory.item_values.double_clawshot_id;
    slot_items[11].item_id = tp_gameInfo.inventory.item_values.bottle_1_id;
    slot_items[12].item_id = tp_gameInfo.inventory.item_values.bottle_2_id;
    slot_items[13].item_id = tp_gameInfo.inventory.item_values.bottle_3_id;
    slot_items[14].item_id = tp_gameInfo.inventory.item_values.bottle_4_id;
    slot_items[15].item_id = tp_gameInfo.inventory.item_values.bomb_bag_1_id;
    slot_items[16].item_id = tp_gameInfo.inventory.item_values.bomb_bag_2_id;
    slot_items[17].item_id = tp_gameInfo.inventory.item_values.bomb_bag_3_id;
    slot_items[18].item_id = tp_gameInfo.inventory.item_values.ooccoo_id;
    slot_items[19].item_id = tp_gameInfo.inventory.item_values.auru_s_memo_ashei_s_sketch_id;
    slot_items[20].item_id = tp_gameInfo.inventory.item_values.fishing_rod_earring_id;
    slot_items[21].item_id = tp_gameInfo.inventory.item_values.horse_call_id;
    slot_items[22].item_id = tp_gameInfo.inventory.item_values.ancient_sky_book_id;
    slot_items[23].item_id = tp_gameInfo.inventory.item_values.slingshot_id;

    if (current_input == 256 && a_held == false) {
        switch (cursor.y) {
            uint8_t current_internal_item_id;
            case SLOT_0: {
                increment_slot_item(current_internal_item_id,SLOT_0);
                tp_gameInfo.inventory.item_values.gale_boomerang_id = current_internal_item_id;
                tp_gameInfo.inventory.item_wheel.slot[6] = SLOT_0;
                break;
            }
            case SLOT_1: {
                increment_slot_item(current_internal_item_id,SLOT_1);
                tp_gameInfo.inventory.item_values.lantern_id = current_internal_item_id;
                tp_gameInfo.inventory.item_wheel.slot[7] = SLOT_1;
                break;
            }
            case SLOT_2: {
                increment_slot_item(current_internal_item_id,SLOT_2);
                tp_gameInfo.inventory.item_values.spinner_id = current_internal_item_id;
                tp_gameInfo.inventory.item_wheel.slot[3] = SLOT_2;
                break;
            }
            case SLOT_3: {
                increment_slot_item(current_internal_item_id,SLOT_3);
                tp_gameInfo.inventory.item_values.iron_boots_id = current_internal_item_id;
                tp_gameInfo.inventory.item_wheel.slot[5] = SLOT_3;
                break;
            }
            case SLOT_4: {
                increment_slot_item(current_internal_item_id,SLOT_4);
                tp_gameInfo.inventory.item_values.hero_s_bow_id = current_internal_item_id;
                tp_gameInfo.inventory.item_wheel.slot[4] = SLOT_4;
                break;
            }
            case SLOT_5: {
                increment_slot_item(current_internal_item_id,SLOT_5);
                tp_gameInfo.inventory.item_values.hawkeye_id = current_internal_item_id;
                tp_gameInfo.inventory.item_wheel.slot[10] = SLOT_5;
                break;
            }
            case SLOT_6: {
                increment_slot_item(current_internal_item_id,SLOT_6);
                tp_gameInfo.inventory.item_values.ball_and_chain_id = current_internal_item_id;
                tp_gameInfo.inventory.item_wheel.slot[2] = SLOT_6;
                break;
            }
            case SLOT_7: {
                increment_slot_item(current_internal_item_id,SLOT_7);
                tp_gameInfo.inventory.item_values._unk_0 = current_internal_item_id;
                tp_gameInfo.inventory.item_wheel.slot[23] = SLOT_7;
                break;
            }
            case SLOT_8: {
                increment_slot_item(current_internal_item_id,SLOT_8);
                tp_gameInfo.inventory.item_values.dominion_rod_id = current_internal_item_id;
                tp_gameInfo.inventory.item_wheel.slot[1] = SLOT_8;
                break;
            }
            case SLOT_9: {
                increment_slot_item(current_internal_item_id,SLOT_9);
                tp_gameInfo.inventory.item_values.clawshot_id = current_internal_item_id;
                tp_gameInfo.inventory.item_wheel.slot[20] = SLOT_9;
                break;
            }
            case SLOT_10: {
                increment_slot_item(current_internal_item_id,SLOT_10);
                tp_gameInfo.inventory.item_values.double_clawshot_id = current_internal_item_id;
                tp_gameInfo.inventory.item_wheel.slot[0] = SLOT_10;
                break;
            }
            case SLOT_11: {
                increment_slot_item(current_internal_item_id,SLOT_11);
                tp_gameInfo.inventory.item_values.bottle_1_id = current_internal_item_id;
                tp_gameInfo.inventory.item_wheel.slot[14] = SLOT_11;
                break;
            }
            case SLOT_12: {
                increment_slot_item(current_internal_item_id,SLOT_12);
                tp_gameInfo.inventory.item_values.bottle_2_id = current_internal_item_id;
                tp_gameInfo.inventory.item_wheel.slot[15] = SLOT_12;
                break;
            }
            case SLOT_13: {
                increment_slot_item(current_internal_item_id,SLOT_13);
                tp_gameInfo.inventory.item_values.bottle_3_id = current_internal_item_id;
                tp_gameInfo.inventory.item_wheel.slot[16] = SLOT_13;
                break;
            }
            case SLOT_14: {
                increment_slot_item(current_internal_item_id,SLOT_14);
                tp_gameInfo.inventory.item_values.bottle_4_id = current_internal_item_id;
                tp_gameInfo.inventory.item_wheel.slot[17] = SLOT_14;
                break;
            }
            case SLOT_15: {
                increment_slot_item(current_internal_item_id,SLOT_15);
                tp_gameInfo.inventory.item_values.bomb_bag_1_id = current_internal_item_id;
                tp_gameInfo.inventory.item_wheel.slot[11] = SLOT_15;
                break;
            }
            case SLOT_16: {
                increment_slot_item(current_internal_item_id,SLOT_16);
                tp_gameInfo.inventory.item_values.bomb_bag_2_id = current_internal_item_id;
                tp_gameInfo.inventory.item_wheel.slot[12] = SLOT_16;
                break;
            }
            case SLOT_17: {
                increment_slot_item(current_internal_item_id,SLOT_17);
                tp_gameInfo.inventory.item_values.bomb_bag_3_id = current_internal_item_id;
                tp_gameInfo.inventory.item_wheel.slot[13] = SLOT_17;
                break;
            }
            case SLOT_18: {
                increment_slot_item(current_internal_item_id,SLOT_18);
                tp_gameInfo.inventory.item_values.ooccoo_id = current_internal_item_id;
                tp_gameInfo.inventory.item_wheel.slot[22] = SLOT_18;
                break;
            }
            case SLOT_19: {
                increment_slot_item(current_internal_item_id,SLOT_19);
                tp_gameInfo.inventory.item_values.auru_s_memo_ashei_s_sketch_id = current_internal_item_id;
                tp_gameInfo.inventory.item_wheel.slot[21] = SLOT_19;
                break;
            }
            case SLOT_20: {
                increment_slot_item(current_internal_item_id,SLOT_20);
                tp_gameInfo.inventory.item_values.fishing_rod_earring_id = current_internal_item_id;
                tp_gameInfo.inventory.item_wheel.slot[9] = SLOT_20;
                break;
            }
            case SLOT_21: {
                increment_slot_item(current_internal_item_id,SLOT_21);
                tp_gameInfo.inventory.item_values.horse_call_id = current_internal_item_id;
                tp_gameInfo.inventory.item_wheel.slot[19] = SLOT_21;
                break;
            }
            case SLOT_22: {
                increment_slot_item(current_internal_item_id,SLOT_22);
                tp_gameInfo.inventory.item_values.ancient_sky_book_id = current_internal_item_id;
                tp_gameInfo.inventory.item_wheel.slot[18] = SLOT_22;
                break;
            }
            case SLOT_23: {
                increment_slot_item(current_internal_item_id,SLOT_23);
                tp_gameInfo.inventory.item_values.slingshot_id = current_internal_item_id;
                tp_gameInfo.inventory.item_wheel.slot[8] = SLOT_23;
                break;
            }
        }
    }

    if (current_input == 16) {
        switch (cursor.y) {
            case SLOT_0: {
                tp_gameInfo.inventory.item_values.gale_boomerang_id = GALE_BOOMERANG;
                set_slot_to_item_id(SLOT_0, GALE_BOOMERANG);
                break;
            }
            case SLOT_1: {
                tp_gameInfo.inventory.item_values.lantern_id = LANTERN;
                set_slot_to_item_id(SLOT_1, LANTERN);
                break;
            }
            case SLOT_2: {
                tp_gameInfo.inventory.item_values.spinner_id = SPINNER;
                set_slot_to_item_id(SLOT_2, SPINNER);
                break;
            }
            case SLOT_3: {
                tp_gameInfo.inventory.item_values.iron_boots_id = IRON_BOOTS;
                set_slot_to_item_id(SLOT_3, IRON_BOOTS);
                break;
            }
            case SLOT_4: {
                tp_gameInfo.inventory.item_values.hero_s_bow_id = HEROS_BOW;
                set_slot_to_item_id(SLOT_4, HEROS_BOW);
                break;
            }
            case SLOT_5: {
                tp_gameInfo.inventory.item_values.hawkeye_id = HAWKEYE;
                set_slot_to_item_id(SLOT_5, HAWKEYE);
                break;
            }
            case SLOT_6: {
                tp_gameInfo.inventory.item_values.ball_and_chain_id = BALL_AND_CHAIN;
                set_slot_to_item_id(SLOT_6, BALL_AND_CHAIN);
                break;
            }
            case SLOT_7: {
                tp_gameInfo.inventory.item_values._unk_0 = NO_ITEM;
                set_slot_to_item_id(SLOT_7, NO_ITEM);
                break;
            }
            case SLOT_8: {
                tp_gameInfo.inventory.item_values.dominion_rod_id = DOMINION_ROD;
                set_slot_to_item_id(SLOT_8, DOMINION_ROD);
                break;
            }
            case SLOT_9: {
                tp_gameInfo.inventory.item_values.clawshot_id = CLAWSHOT;
                set_slot_to_item_id(SLOT_9, CLAWSHOT);
                break;
            }
            case SLOT_10: {
                tp_gameInfo.inventory.item_values.double_clawshot_id = DOUBLE_CLAWSHOT;
                set_slot_to_item_id(SLOT_10, DOUBLE_CLAWSHOT);
                break;
            }
            case SLOT_11: {
                tp_gameInfo.inventory.item_values.bottle_1_id = EMPTY_BOTTLE;
                set_slot_to_item_id(SLOT_11, EMPTY_BOTTLE);
                break;
            }
            case SLOT_12: {
                tp_gameInfo.inventory.item_values.bottle_2_id = EMPTY_BOTTLE;
                set_slot_to_item_id(SLOT_12, EMPTY_BOTTLE);
                break;
            }
            case SLOT_13: {
                tp_gameInfo.inventory.item_values.bottle_3_id = EMPTY_BOTTLE;
                set_slot_to_item_id(SLOT_13, EMPTY_BOTTLE);
                break;
            }
            case SLOT_14: {
                tp_gameInfo.inventory.item_values.bottle_4_id = EMPTY_BOTTLE;
                set_slot_to_item_id(SLOT_14, EMPTY_BOTTLE);
                break;
            }
            case SLOT_15: {
                tp_gameInfo.inventory.item_values.bomb_bag_1_id = EMPTY_BOMBBAG;
                set_slot_to_item_id(SLOT_15, EMPTY_BOMBBAG);
                break;
            }
            case SLOT_16: {
                tp_gameInfo.inventory.item_values.bomb_bag_2_id = EMPTY_BOMBBAG;
                set_slot_to_item_id(SLOT_16, EMPTY_BOMBBAG);
                break;
            }
            case SLOT_17: {
                tp_gameInfo.inventory.item_values.bomb_bag_3_id = EMPTY_BOMBBAG;
                set_slot_to_item_id(SLOT_17, EMPTY_BOMBBAG);
                break;
            }
            case SLOT_18: {
                tp_gameInfo.inventory.item_values.ooccoo_id = OOCCOO_SR;
                set_slot_to_item_id(SLOT_18, OOCCOO_SR);
                break;
            }
            case SLOT_19: {
                tp_gameInfo.inventory.item_values.auru_s_memo_ashei_s_sketch_id = AURUS_MEMO;
                set_slot_to_item_id(SLOT_19, AURUS_MEMO);
                break;
            }
            case SLOT_20: {
                tp_gameInfo.inventory.item_values.fishing_rod_earring_id = FISHING_ROD;
                set_slot_to_item_id(SLOT_20, FISHING_ROD);
                break;
            }
            case SLOT_21: {
                tp_gameInfo.inventory.item_values.horse_call_id = HORSE_CALL;
                set_slot_to_item_id(SLOT_21, HORSE_CALL);
                break;
            }
            case SLOT_22: {
                tp_gameInfo.inventory.item_values.ancient_sky_book_id = ANCIENT_SKY_BOOK_EMPTY;
                set_slot_to_item_id(SLOT_22, ANCIENT_SKY_BOOK_EMPTY);
                break;
            }
            case SLOT_23: {
                tp_gameInfo.inventory.item_values.slingshot_id = SLINGSHOT;
                set_slot_to_item_id(SLOT_23, SLINGSHOT);
                break;
            }
        }
    }
};