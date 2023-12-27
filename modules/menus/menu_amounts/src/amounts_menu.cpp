#include "menus/menu_amounts/include/amounts_menu.h"
#include <cstdio>
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

KEEP_FUNC AmountsMenu::AmountsMenu(Cursor& cursor, AmountsData& data)
    : Menu(cursor), l_healthNum(data.l_healthNum), l_maxHealthNum(data.l_maxHealthNum),
      l_extraHealthNum(data.l_extraHealthNum), l_arrowNum(data.l_arrowNum),
      l_bag1Num(data.l_bag1Num), l_bag2Num(data.l_bag2Num), l_bag3Num(data.l_bag3Num),
      l_seedNum(data.l_seedNum), l_poeNum(data.l_poeNum), l_hpNum(data.l_hpNum),
      l_rupeeNum(data.l_rupeeNum),
      lines{
          {"health:", HEALTH_INDEX, "Current health by quarter"},
          {"hearts:", MAX_HEALTH_INDEX, "Amount of hearts collected"},

          {"arrows:", ARROW_AMMO_INDEX, "Current arrow count"},
          {"bomb bag 1 num:", BOMB_BAG_1_AMMO_INDEX, "Amount of bombs in bag 1"},
          {"bomb bag 2 num:", BOMB_BAG_2_AMMO_INDEX, "Amount of bombs in bag 2"},
          {"bomb bag 3 num:", BOMB_BAG_3_AMMO_INDEX, "Amount of bombs in bag 3"},
          {"seeds:", SLINGSHOT_AMMO_INDEX, "Current seed count"},
          {"heart pieces:", HEART_PIECE_COUNT_INDEX, "Amount of heart pieces collected"},
          {"poes:", POE_COUNT_INDEX, "Amount of poes collected"},
          {"rupees:", RUPEE_COUNT_INDEX, "Current rupee count"},
      } {}

AmountsMenu::~AmountsMenu() {}

void AmountsMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    // update amounts
    l_healthNum = dComIfGs_getLife();
    l_extraHealthNum = dComIfGs_getMaxLife() % 5;
    l_maxHealthNum = dComIfGs_getMaxLife() / 5;
    l_arrowNum = dComIfGs_getArrowNum();
    l_bag1Num = dComIfGs_getBombNum(BOMB_BAG_1);
    l_bag2Num = dComIfGs_getBombNum(BOMB_BAG_2);
    l_bag3Num = dComIfGs_getBombNum(BOMB_BAG_3);
    l_seedNum = dComIfGs_getPachinkoNum();
    l_poeNum = dComIfGs_getPohSpiritNum();
    l_hpNum = dComIfGs_getMaxLife();
    l_rupeeNum = dComIfGs_getRupee();

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    switch (cursor.y) {
    case HEALTH_INDEX:
        Cursor::moveList(l_healthNum);
        if (l_healthNum > l_maxHealthNum * 4) {
            l_healthNum = l_maxHealthNum * 4;  // Don't allow the player to go overflow
        }
        dComIfGs_setLife(l_healthNum);
        break;
    case MAX_HEALTH_INDEX:
        Cursor::moveList(l_maxHealthNum);
        if (l_hpNum > 20) {
            l_maxHealthNum = 20;  // Don't allow the player to go overflow
        }
        dComIfGs_setMaxLife((l_maxHealthNum * 5) +
                            l_extraHealthNum);  // Add hearts with current heartpiece
        if (l_healthNum > l_maxHealthNum * 4) {
            l_healthNum = l_maxHealthNum * 4;  // Don't allow the player to go overflow in hearts
            dComIfGs_setLife(l_healthNum);
        }
        break;
    Cursor::moveList(l_healthNum);
     if (l_healthNum < 1) {
            l_healthNum = 1;  // Don't allow the player to go under 1 quarter heart
        }
    dComIfGs_setLife(l_healthNum);
    break;
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
  
    lines[HEALTH_INDEX].printf("<%d>", l_healthNum);
    lines[MAX_HEALTH_INDEX].printf("<%d>", l_maxHealthNum);
    lines[ARROW_AMMO_INDEX].printf(" <%d>", l_arrowNum);
    lines[BOMB_BAG_1_AMMO_INDEX].printf(" <%d>", l_bag1Num);
    lines[BOMB_BAG_2_AMMO_INDEX].printf(" <%d>", l_bag2Num);
    lines[BOMB_BAG_3_AMMO_INDEX].printf(" <%d>", l_bag3Num);
    lines[SLINGSHOT_AMMO_INDEX].printf(" <%d>", l_seedNum);
    lines[HEART_PIECE_COUNT_INDEX].printf(" <%d>", l_hpNum);
    lines[POE_COUNT_INDEX].printf(" <%d>", l_poeNum);
    lines[RUPEE_COUNT_INDEX].printf(" <%d>", l_rupeeNum);

    cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
