
#include "menus/item_wheel_menu.h"
#include "controller.h"
#include "font.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/msl_c/string.h"
#include "utils/cursor.h"
#include "utils/lines.h"

#define ITEM_WHEEL_SLOTS 24
#define LINES ITEM_WHEEL_SLOTS
#define TOTAL_ITEMS 58

static Cursor cursor = {0, 0};
int listIdx = 0;
int new_int_item_id;
bool init_once = false;

const uint8_t valid_items[] = {DUNGEON_EXIT,
                               DUNGEON_BACK,
                               TKS_LETTER,
                               HAWK_EYE,
                               BOOMERANG,
                               SPINNER,
                               IRONBALL,
                               BOW,
                               HOOKSHOT,
                               HVY_BOOTS,
                               COPY_ROD,
                               W_HOOKSHOT,
                               KANTERA,
                               MASTER_SWORD,
                               FISHING_ROD_1,
                               PACHINKO,
                               BOMB_BAG_LV1,
                               BEE_ROD,
                               JEWEL_ROD,
                               WORM_ROD,
                               JEWEL_BEE_ROD,
                               JEWEL_WORM_ROD,
                               EMPTY_BOTTLE,
                               RED_BOTTLE,
                               GREEN_BOTTLE,
                               BLUE_BOTTLE,
                               MILK_BOTTLE,
                               HALF_MILK_BOTTLE,
                               OIL_BOTTLE,
                               WATER_BOTTLE,
                               UGLY_SOUP,
                               HOT_SPRING,
                               FAIRY,
                               NORMAL_BOMB,
                               WATER_BOMB,
                               POKE_BOMB,
                               FAIRY_DROP,
                               WORM,
                               BEE_CHILD,
                               CHUCHU_RARE,
                               CHUCHU_RED,
                               CHUCHU_BLUE,
                               CHUCHU_GREEN,
                               CHUCHU_YELLOW,
                               CHUCHU_PURPLE,
                               LV1_SOUP,
                               LV2_SOUP,
                               LV3_SOUP,
                               LETTER,
                               BILL,
                               WOOD_STATUE,
                               IRIAS_PENDANT,
                               HORSE_FLUTE,
                               RAFRELS_MEMO,
                               ASHS_SCRIBBLING,
                               ANCIENT_DOCUMENT,
                               AIR_LETTER,
                               ANCIENT_DOCUMENT2,
                               NO_ITEM};

const uint8_t default_items[ITEM_WHEEL_SLOTS] = {BOOMERANG,
                                                 KANTERA,
                                                 SPINNER,
                                                 HVY_BOOTS,
                                                 BOW,
                                                 HAWK_EYE,
                                                 IRONBALL,
                                                 NO_ITEM,
                                                 COPY_ROD,
                                                 HOOKSHOT,
                                                 W_HOOKSHOT,
                                                 EMPTY_BOTTLE,
                                                 EMPTY_BOTTLE,
                                                 EMPTY_BOTTLE,
                                                 EMPTY_BOTTLE,
                                                 BOMB_BAG_LV1,
                                                 BOMB_BAG_LV1,
                                                 BOMB_BAG_LV1,
                                                 DUNGEON_EXIT,
                                                 RAFRELS_MEMO,
                                                 FISHING_ROD_1,
                                                 HORSE_FLUTE,
                                                 ANCIENT_DOCUMENT,
                                                 PACHINKO};

const ItemLookup lookup_table[TOTAL_ITEMS] = {
    {DUNGEON_EXIT, "ooccoo sr."},
    {DUNGEON_BACK, "ooccoo jr."},
    {TKS_LETTER, "ooccoo's note"},
    {HAWK_EYE, "hawkeye"},
    {BOOMERANG, "gale boomerang"},
    {SPINNER, "spinner"},
    {IRONBALL, "ball and chain"},
    {BOW, "hero's bow"},
    {HOOKSHOT, "clawshot"},
    {HVY_BOOTS, "iron boots"},
    {COPY_ROD, "dominion rod"},
    {W_HOOKSHOT, "double clawshot"},
    {KANTERA, "lantern"},
    {PACHINKO, "slingshot"},
    {FISHING_ROD_1, "fishing rod"},
    {BOMB_BAG_LV1, "empty bomb bag"},
    {BEE_ROD, "fishing rod (bee larva)"},
    {JEWEL_ROD, "fishing rod (coral earring)"},
    {WORM_ROD, "fishing rod (worm)"},
    {JEWEL_BEE_ROD, "fishing rod (coral earring/bee larva)"},
    {JEWEL_WORM_ROD, "fishing rod (coral earring/worm)"},
    {EMPTY_BOTTLE, "empty bottle"},
    {RED_BOTTLE, "red potion"},
    {GREEN_BOTTLE, "magic potion"},
    {BLUE_BOTTLE, "blue potion"},
    {MILK_BOTTLE, "milk"},
    {HALF_MILK_BOTTLE, "half milk"},
    {OIL_BOTTLE, "lantern oil"},
    {WATER_BOTTLE, "water"},
    {UGLY_SOUP, "nasty soup"},
    {HOT_SPRING, "hot spring water"},
    {FAIRY, "fairy"},
    {NORMAL_BOMB, "regular bombs"},
    {WATER_BOMB, "water bombs"},
    {POKE_BOMB, "bomblings"},
    {FAIRY_DROP, "fairy tears"},
    {WORM, "worm"},
    {BEE_CHILD, "bee larva"},
    {CHUCHU_RARE, "rare chu"},
    {CHUCHU_RED, "red chu"},
    {CHUCHU_BLUE, "blue chu"},
    {CHUCHU_GREEN, "green chu"},
    {CHUCHU_YELLOW, "yellow chu"},
    {CHUCHU_PURPLE, "purple chu"},
    {LV1_SOUP, "simple soup"},
    {LV2_SOUP, "good soup"},
    {LV3_SOUP, "superb soup"},
    {LETTER, "renados letter"},
    {BILL, "invoice"},
    {WOOD_STATUE, "wooden statue"},
    {IRIAS_PENDANT, "ilia's charm"},
    {HORSE_FLUTE, "horse call"},
    {RAFRELS_MEMO, "auru's memo"},
    {ASHS_SCRIBBLING, "ashei's sketch"},
    {ANCIENT_DOCUMENT, "ancient sky book (empty)"},
    {AIR_LETTER, "ancient sky book (partial)"},
    {ANCIENT_DOCUMENT2, "ancient sky book (filled)"},
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

void ItemWheelMenu::render() {
    if (button_is_pressed(BACK_BUTTON)) {
        MenuRendering::set_menu(MN_INVENTORY_INDEX);
        init_once = false;
        return;
    }

    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

    for (int i = 0; i < LINES; i++) {
        new_int_item_id = dComIfGs_getItem(i, false);
        
        for (int j = 0; j < TOTAL_ITEMS; j++) {
            if (lookup_table[j].item_id == new_int_item_id) {
                tp_sprintf(lines[i].value, " <%s>", new_int_item_id != NO_ITEM ? lookup_table[j].item_description : "none");
            }
            if (lookup_table[j].item_id == default_items[i]) {
                tp_sprintf(lines[i].description, "Slot %d default: %s. Press Z to set to default", i, lookup_table[j].item_description);
            } else {
            continue;
            }
        }
    }

    if (button_is_pressed(Controller::DPAD_UP) || button_is_pressed(Controller::DPAD_DOWN)) {
        listIdx = 0;
    }

    if (button_is_pressed(Controller::DPAD_RIGHT)) {
        listIdx++;
        if (listIdx > TOTAL_ITEMS) {
            listIdx = 0;
        }
        dComIfGs_setItem(cursor.y, valid_items[listIdx]);
    }

    if (button_is_pressed(Controller::DPAD_LEFT)) {
        listIdx--;
        if (listIdx < 0) {
            listIdx = 58;
        }
        dComIfGs_setItem(cursor.y, valid_items[listIdx]);
    }

    if (button_is_pressed(Controller::Z)) {
        dComIfGs_setItem(cursor.y, default_items[cursor.y]);
    }


    Utilities::move_cursor(cursor, LINES, 0, false, false, false, true);
    Utilities::render_lines(lines, cursor.y, LINES);
}
