
#include "menus/item_wheel_menu.h"
#include "controller.h"
#include "font.h"
#include "libtp_c/include/system.h"
#include "utils/cursor.h"
#include "utils/lines.h"

#define ITEM_WHEEL_SLOTS 24
#define LINES ITEM_WHEEL_SLOTS
#define TOTAL_ITEMS 58

static Cursor cursor = {0, 0};
int listIdx = 0;
int new_int_item_id;
bool init_once = false;

const uint8_t valid_items[] = {OOCCOO_SR,
                               OOCCOO_JR,
                               OOCCOOS_NOTE,
                               HAWKEYE,
                               GALE_BOOMERANG,
                               SPINNER,
                               BALL_AND_CHAIN,
                               HEROS_BOW,
                               CLAWSHOT,
                               IRON_BOOTS,
                               DOMINION_ROD,
                               DOUBLE_CLAWSHOT,
                               LANTERN,
                               MASTER_SWORD,
                               FISHING_ROD,
                               SLINGSHOT,
                               EMPTY_BOMBBAG,
                               ROD_BEE_LARVA,
                               ROD_CORAL_EARRING,
                               ROD_WORM,
                               ROD_CORAL_EARRING_BEE_LARVA,
                               ROD_CORAL_EARRING_WORM,
                               EMPTY_BOTTLE,
                               RED_POTION,
                               MAGIC_POTION,
                               BLUE_POTION,
                               MILK,
                               HALF_MILK,
                               LANTERN_OIL,
                               WATER,
                               NASTY_SOUP,
                               HOT_SPRING_WATER,
                               FAIRY,
                               REGULAR_BOMBS,
                               WATER_BOMBS,
                               BOMBLINGS,
                               FAIRY_TEARS,
                               WORM,
                               BEE_LARVA,
                               RARE_CHU,
                               RED_CHU,
                               BLUE_CHU,
                               GREEN_CHU,
                               YELLOW_CHU,
                               PURPLE_CHU,
                               SIMPLE_SOUP,
                               GOOD_SOUP,
                               SUPERB_SOUP,
                               RENADOS_LETTER,
                               INVOICE,
                               WOODEN_STATUE,
                               ILIAS_CHARM,
                               HORSE_CALL,
                               AURUS_MEMO,
                               ASHEIS_SKETCH,
                               ANCIENT_SKY_BOOK_EMPTY,
                               ANCIENT_SKY_BOOK_PARTIAL,
                               ANCIENT_SKY_BOOK_FILLED,
                               NO_ITEM};

// probably a better way to do this
bool IsInItemIDEnum(int val) {
    for (size_t i = 0; i < sizeof(valid_items); ++i) {
        if (valid_items[i] == val) {
            return true;
        }
    }
    return false;
}

const uint8_t default_items[ITEM_WHEEL_SLOTS] = {GALE_BOOMERANG,
                                                 LANTERN,
                                                 SPINNER,
                                                 IRON_BOOTS,
                                                 HEROS_BOW,
                                                 HAWKEYE,
                                                 BALL_AND_CHAIN,
                                                 NO_ITEM,
                                                 DOMINION_ROD,
                                                 CLAWSHOT,
                                                 DOUBLE_CLAWSHOT,
                                                 EMPTY_BOTTLE,
                                                 EMPTY_BOTTLE,
                                                 EMPTY_BOTTLE,
                                                 EMPTY_BOTTLE,
                                                 EMPTY_BOMBBAG,
                                                 EMPTY_BOMBBAG,
                                                 EMPTY_BOMBBAG,
                                                 OOCCOO_SR,
                                                 AURUS_MEMO,
                                                 FISHING_ROD,
                                                 HORSE_CALL,
                                                 ANCIENT_SKY_BOOK_EMPTY,
                                                 SLINGSHOT};

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

Line lines[LINES] = {{"Slot 0:", SLOT_0, "", false, nullptr, false},
                     {"Slot 1:", SLOT_1, "", false, nullptr, false},
                     {"Slot 2:", SLOT_2, "", false, nullptr, false},
                     {"Slot 3:", SLOT_3, "", false, nullptr, false},
                     {"Slot 4:", SLOT_4, "", false, nullptr, false},
                     {"Slot 5:", SLOT_5, "", false, nullptr, false},
                     {"Slot 6:", SLOT_6, "", false, nullptr, false},
                     {"Slot 7:", SLOT_7, "", false, nullptr, false},
                     {"Slot 8:", SLOT_8, "", false, nullptr, false},
                     {"Slot 9:", SLOT_9, "", false, nullptr, false},
                     {"Slot 10:", SLOT_10, "", false, nullptr, false},
                     {"Slot 11:", SLOT_11, "", false, nullptr, false},
                     {"Slot 12:", SLOT_12, "", false, nullptr, false},
                     {"Slot 13:", SLOT_13, "", false, nullptr, false},
                     {"Slot 14:", SLOT_14, "", false, nullptr, false},
                     {"Slot 15:", SLOT_15, "", false, nullptr, false},
                     {"Slot 16:", SLOT_16, "", false, nullptr, false},
                     {"Slot 17:", SLOT_17, "", false, nullptr, false},
                     {"Slot 18:", SLOT_18, "", false, nullptr, false},
                     {"Slot 19:", SLOT_19, "", false, nullptr, false},
                     {"Slot 20:", SLOT_20, "", false, nullptr, false},
                     {"Slot 21:", SLOT_21, "", false, nullptr, false},
                     {"Slot 22:", SLOT_22, "", false, nullptr, false},
                     {"Slot 23:", SLOT_23, "", false, nullptr, false}};

void increment_slot_item(int slot_id) {
    uint8_t current_internal_item_id = tp_gameInfo.inventory.item_values.value[slot_id];
    do {
        current_internal_item_id++;
    } while (IsInItemIDEnum(current_internal_item_id) == false);
    tp_gameInfo.inventory.item_values.value[slot_id] = current_internal_item_id;
}

void decrement_slot_item(int slot_id) {
    uint8_t current_internal_item_id = tp_gameInfo.inventory.item_values.value[slot_id];
    do {
        --current_internal_item_id;
    } while (IsInItemIDEnum(current_internal_item_id) == false);
    tp_gameInfo.inventory.item_values.value[slot_id] = current_internal_item_id;
}

uint8_t find_next_empty_slot() {
    for (size_t i = 0; i < ITEM_WHEEL_SLOTS; ++i) {
        if (tp_gameInfo.inventory.item_wheel.slot[i] == 0xFF) {
            return i;
        }
    }
    return 0xFF;
}

void try_add_item(uint8_t inventory_slot) {
    auto item_wheel = tp_gameInfo.inventory.item_wheel.slot;
    uint8_t slot = 0xFF;
    bool item_already_in_wheel = false;
    if (inventory_slot >= ITEM_WHEEL_SLOTS) {
        return;
    }
    for (size_t i = 0; i < ITEM_WHEEL_SLOTS; ++i) {
        if (slot == 0xFF && item_wheel[i] == 0xFF) {
            slot = i;
        }
        if (item_wheel[i] == inventory_slot) {
            item_already_in_wheel = true;
            break;
        }
    }
    if (!item_already_in_wheel && slot != 0xFF) {
        item_wheel[slot] = inventory_slot;
    }
}

void try_remove_item(uint8_t inventory_slot) {
    auto item_wheel = tp_gameInfo.inventory.item_wheel.slot;
    uint8_t slot = 0xFF;
    if (inventory_slot >= ITEM_WHEEL_SLOTS) {
        return;
    }
    for (size_t i = 0; i < ITEM_WHEEL_SLOTS; ++i) {
        if (item_wheel[i] == inventory_slot) {
            slot = i;
            break;
        }
    }
    if (slot != 0xFF) {
        uint8_t last_slot = find_next_empty_slot();
        if (last_slot > ITEM_WHEEL_SLOTS) {
            last_slot = ITEM_WHEEL_SLOTS;
        }
        if (last_slot > 0) {
            last_slot--;
        }
        item_wheel[slot] = item_wheel[last_slot];
        item_wheel[last_slot] = 0xFF;
    }
}

void ItemWheelMenu::render() {
    if (button_is_pressed(BACK_BUTTON)) {
        MenuRendering::set_menu(MN_INVENTORY_INDEX);
        init_once = false;
        return;
    };

    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

    // populate the default line name and description
    for (int i = 0; i < LINES; i++) {
        new_int_item_id = tp_gameInfo.inventory.item_values.value[i];
        for (int j = 0; j < TOTAL_ITEMS; j++) {
            if (lookup_table[j].item_id == new_int_item_id) {
                tp_sprintf(lines[i].value, " <%s>",
                           new_int_item_id != NO_ITEM ? lookup_table[j].item_description : "none");
            }
            if (lookup_table[j].item_id == default_items[i]) {
                tp_sprintf(lines[i].description, "Slot %d default: %s. Press Z to set to default",
                           i, lookup_table[j].item_description);
            } else {
                continue;
            }
        }
    }

    Utilities::move_cursor(cursor, LINES, 0, false, false, false, true);
    Utilities::render_lines(lines, cursor.y, LINES);

    // check selected slot
    uint8_t current_item_slot = ITEM_WHEEL_SLOTS;
    if (cursor.y >= 0 && cursor.y < ITEM_WHEEL_SLOTS) {
        current_item_slot = cursor.y;
    }

    if (Controller::button_is_pressed(Controller::DPAD_RIGHT) ||
        Controller::button_is_pressed(Controller::DPAD_LEFT)) {
        auto change_slot_item = Controller::button_is_pressed(Controller::DPAD_RIGHT) ?
                                    increment_slot_item :
                                    decrement_slot_item;
        if (current_item_slot < ITEM_WHEEL_SLOTS) {
            change_slot_item(current_item_slot);
            if (tp_gameInfo.inventory.item_values.value[current_item_slot] != 0xFF) {
                try_add_item(current_item_slot);
            } else {
                try_remove_item(current_item_slot);
            }
        }
    }

    if (Controller::button_is_down(Controller::Z) && !Controller::button_is_held(Controller::Z)) {
        if (current_item_slot < ITEM_WHEEL_SLOTS) {
            tp_gameInfo.inventory.item_values.value[current_item_slot] =
                default_items[current_item_slot];
            if (default_items[current_item_slot] != 0xFF) {
                try_add_item(current_item_slot);
            } else {
                try_remove_item(current_item_slot);
            }
        }
    }
};
