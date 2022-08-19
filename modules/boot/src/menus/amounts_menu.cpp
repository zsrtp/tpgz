#include "menus/amounts_menu.h"
#include "libtp_c/include/msl_c/string.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "gz_flags.h"
#include "rels/include/defines.h"

KEEP_FUNC AmountsMenu::AmountsMenu()
    : Menu(), lines{
                  {"arrows:", ARROW_AMMO_INDEX, "Current arrow count"},
                  {"bomb bag 1 num:", BOMB_BAG_1_AMMO_INDEX, "Amount of bombs in bag 1"},
                  {"bomb bag 2 num:", BOMB_BAG_2_AMMO_INDEX, "Amount of bombs in bag 2"},
                  {"bomb bag 3 num:", BOMB_BAG_3_AMMO_INDEX, "Amount of bombs in bag 3"},
                  {"seeds:", SLINGSHOT_AMMO_INDEX, "Current seed count"},
                  {"heart pieces:", HEART_PIECE_COUNT_INDEX, "Amount of heart pieces collected"},
                  {"poes:", POE_COUNT_INDEX, "Amount of poes collected"},
                  {"rupees:", RUPEE_COUNT_INDEX, "Current rupee count"},
              } {}

void AmountsMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    // update amounts
    l_arrowNum = dComIfGs_getArrowNum();
    l_bag1Num = dComIfGs_getBombNum(BOMB_BAG_1);
    l_bag2Num = dComIfGs_getBombNum(BOMB_BAG_2);
    l_bag3Num = dComIfGs_getBombNum(BOMB_BAG_3);
    l_seedNum = dComIfGs_getPachinkoNum();
    l_poeNum = dComIfGs_getPohSpiritNum();
    l_hpNum = dComIfGs_getMaxLife();
    l_rupeeNum = dComIfGs_getRupee();

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        GZ_setMenu(MN_INVENTORY_INDEX);
        return;
    }

    switch (cursor.y) {
    case ARROW_AMMO_INDEX:
        Cursor::moveList(l_arrowNum);
        dComIfGs_setArrowNum(l_arrowNum);
        break;
    case BOMB_BAG_1_AMMO_INDEX:
        Cursor::moveList(l_bag1Num);
        dComIfGs_setBombNum(BOMB_BAG_1, l_bag1Num);
        break;
    case BOMB_BAG_2_AMMO_INDEX:
        Cursor::moveList(l_bag2Num);
        dComIfGs_setBombNum(BOMB_BAG_2, l_bag2Num);
        break;
    case BOMB_BAG_3_AMMO_INDEX:
        Cursor::moveList(l_bag3Num);
        dComIfGs_setBombNum(BOMB_BAG_3, l_bag3Num);
        break;
    case SLINGSHOT_AMMO_INDEX:
        Cursor::moveList(l_seedNum);
        dComIfGs_setPachinkoNum(l_seedNum);
        break;
    case HEART_PIECE_COUNT_INDEX:
        Cursor::moveList(l_hpNum);
        dComIfGs_setMaxLife(l_hpNum);
        break;
    case POE_COUNT_INDEX:
        Cursor::moveList(l_poeNum);
        dComIfGs_setPohSpiritNum(l_poeNum);
        break;
    case RUPEE_COUNT_INDEX:
        Cursor::moveList(l_rupeeNum);
        dComIfGs_setRupee(l_rupeeNum);
        break;
    }

    sprintf(lines[ARROW_AMMO_INDEX].value, " <%d>", l_arrowNum);
    sprintf(lines[BOMB_BAG_1_AMMO_INDEX].value, " <%d>", l_bag1Num);
    sprintf(lines[BOMB_BAG_2_AMMO_INDEX].value, " <%d>", l_bag2Num);
    sprintf(lines[BOMB_BAG_3_AMMO_INDEX].value, " <%d>", l_bag3Num);
    sprintf(lines[SLINGSHOT_AMMO_INDEX].value, " <%d>", l_seedNum);
    sprintf(lines[HEART_PIECE_COUNT_INDEX].value, " <%d>", l_hpNum);
    sprintf(lines[POE_COUNT_INDEX].value, " <%d>", l_poeNum);
    sprintf(lines[RUPEE_COUNT_INDEX].value, " <%d>", l_rupeeNum);

    cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
