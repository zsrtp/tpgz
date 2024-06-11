#include "menus/menu_actor_spawn/include/actor_spawn_menu.h"
#include <cstdio>
#include "settings.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/f_op/f_op_actor_mng.h"
#include "gz_flags.h"
#include "pos_settings.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

#ifdef GCN_PLATFORM
#define CONTROLLER_RIGHT GZPad::DPAD_RIGHT
#define CONTROLLER_LEFT GZPad::DPAD_LEFT
#define CONTROLLER_UP GZPad::DPAD_UP
#define CONTROLLER_DOWN GZPad::DPAD_DOWN
#define CONTROLLER_SKIP_10 GZPad::X
#define CONTROLLER_SKIP_MINUS_10 GZPad::Y
#define CONTROL_TEXT "X/Y"
#endif

#ifdef WII_PLATFORM
#define CONTROLLER_RIGHT GZPad::DPAD_RIGHT
#define CONTROLLER_LEFT GZPad::DPAD_LEFT
#define CONTROLLER_UP GZPad::DPAD_UP
#define CONTROLLER_DOWN GZPad::DPAD_DOWN
#define CONTROLLER_SKIP_10 GZPad::ONE
#define CONTROLLER_SKIP_MINUS_10 GZPad::TWO
#define CONTROL_TEXT "1/2"
#endif

#ifdef WII_PLATFORM
extern bool isWidescreen;
#else
#define isWidescreen (false)
#endif

KEEP_FUNC ActorSpawnMenu::ActorSpawnMenu(ActorSpawnData& data)
    : Menu(data.cursor), l_actorID(data.l_actorID), l_actorParams(data.l_actorParams),
      l_actorType(data.l_actorType), l_paramIdx(data.l_paramIdx), l_paramsSelected(false),
      lines{
          {"actor id:", ACTOR_ID_INDEX, "Actor ID (Dpad / " CONTROL_TEXT " to scroll)", false},
          {"actor params:", ACTOR_PARAM_INDEX, "Actor Parameters (default: 0)", false},
          {"actor subtype:", ACTOR_SUBTYPE_INDEX,
           "Actor subtype (default: -1) (Dpad / " CONTROL_TEXT " to scroll)", false},
          {"spawn", ACTOR_SPAWN_INDEX, "Spawn actor at current position", false},
      } {}

ActorSpawnMenu::~ActorSpawnMenu() {}

void actorFastCreateAtLink(short id, uint32_t parameters, int8_t subtype) {
    fopAcM_create(id, parameters, &dComIfGp_getPlayer()->current.pos,
                  dComIfGp_getPlayer()->current.roomNo, &dComIfGp_getPlayer()->current.angle,
                  nullptr, subtype);
}

void ActorSpawnMenu::draw() {
    cursor.setMode(Cursor::MODE_UNRESTRICTED);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        if (l_paramsSelected) {
            cursor.lock_y = false;
            l_paramsSelected = false;
        } else {
            g_menuMgr->pop();
            return;
        }
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        switch (cursor.y) {
        case ACTOR_PARAM_INDEX:
            cursor.lock_y = true;
            l_paramsSelected = true;
            break;
        case ACTOR_SPAWN_INDEX:
            actorFastCreateAtLink(l_actorID, l_actorParams, l_actorType);
            break;
        }
    }

    switch (cursor.y) {
    case ACTOR_ID_INDEX:
        if (GZ_getButtonRepeat(CONTROLLER_RIGHT)) {
            l_actorID++;
        } else if (GZ_getButtonRepeat(CONTROLLER_LEFT)) {
            l_actorID--;
        } else if (GZ_getButtonRepeat(CONTROLLER_SKIP_10)) {
            l_actorID += 10;
        } else if (GZ_getButtonRepeat(CONTROLLER_SKIP_MINUS_10)) {
            l_actorID -= 10;
        }
        break;
    case ACTOR_SUBTYPE_INDEX:
        if (GZ_getButtonRepeat(CONTROLLER_RIGHT)) {
            l_actorType++;
        } else if (GZ_getButtonRepeat(CONTROLLER_LEFT)) {
            l_actorType--;
        } else if (GZ_getButtonRepeat(CONTROLLER_SKIP_10)) {
            l_actorType += 10;
        } else if (GZ_getButtonRepeat(CONTROLLER_SKIP_MINUS_10)) {
            l_actorType -= 10;
        }
        break;
    }

    auto menu_offset = GZ_getSpriteOffset(STNG_SPRITES_MENU);
    float param_offset_x = menu_offset.x + Font::getStrWidth("actor params:  ");
    float param_offset_y = menu_offset.y + 20.0f * (float)(int)ACTOR_PARAM_INDEX;

    char buf[9];
    snprintf(buf, sizeof(buf), "%08X", l_actorParams);
    if (l_paramsSelected) {
        if (GZ_getButtonRepeat(CONTROLLER_RIGHT)) {
            if (l_paramIdx == 7) {
                l_paramIdx = 0;
            } else if (l_paramIdx >= 0 && l_paramIdx < 8) {
                l_paramIdx++;
            }
        }
        if (GZ_getButtonRepeat(CONTROLLER_LEFT)) {
            if (l_paramIdx == 0) {
                l_paramIdx = 7;
            } else if (l_paramIdx >= 0 && l_paramIdx < 8) {
                l_paramIdx--;
            }
        }
        if (GZ_getButtonRepeat(CONTROLLER_UP)) {
            l_actorParams += (0x10000000 >> (l_paramIdx * 4));
        }
        if (GZ_getButtonRepeat(CONTROLLER_DOWN)) {
            l_actorParams -= (0x10000000 >> (l_paramIdx * 4));
        }
        GZ_drawSelectChar(buf, param_offset_x, param_offset_y, l_paramIdx, 7, 0xFFFFFFFF);
    } else {
        Font::GZ_drawStr(buf, param_offset_x, param_offset_y,
                         (cursor.y == ACTOR_PARAM_INDEX ? CURSOR_RGBA : 0xFFFFFFFF),
                         GZ_checkDropShadows());
    }

    lines[ACTOR_ID_INDEX].printf(" <%d>", l_actorID);
    lines[ACTOR_SUBTYPE_INDEX].printf(" <%d>", l_actorType);

    cursor.move(8, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
