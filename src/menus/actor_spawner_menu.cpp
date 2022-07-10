#include "menus/actor_spawn_menu.h"
#include "menus/settings_menu.h"
#include "libtp_c/include/msl_c/string.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/f_op/f_op_actor_mng.h"
#include "gz_flags.h"

#define LINE_NUM 4
#ifdef GCN_PLATFORM
#define CONTROLLER_RIGHT GZPad::DPAD_RIGHT
#define CONTROLLER_LEFT GZPad::DPAD_LEFT
#define CONTROLLER_UP GZPad::DPAD_UP
#define CONTROLLER_DOWN GZPad::DPAD_DOWN
#define CONTROLLER_SKIP_10 GZPad::X
#define CONTROLLER_SKIP_MINUS_10 GZPad::Y
#endif
#ifdef WII_PLATFORM
#define CONTROLLER_RIGHT GZPad::DPAD_RIGHT
#define CONTROLLER_LEFT GZPad::DPAD_LEFT
#define CONTROLLER_UP GZPad::DPAD_UP
#define CONTROLLER_DOWN GZPad::DPAD_DOWN
#define CONTROLLER_SKIP_10 Controller::ONE
#define CONTROLLER_SKIP_MINUS_10 Controller::TWO
#endif

Cursor ActorSpawnMenu::cursor;

uint16_t l_actorID = 0;
uint32_t l_actorParams = 0;
int8_t l_actorType = -1;
uint8_t l_paramIdx = 0;
bool l_paramsSelected = false;

Line lines[LINE_NUM] = {
    {"actor id:", ACTOR_ID_INDEX, "Actor ID (Dpad / X/Y to scroll)", false},
    {"actor params:", ACTOR_PARAM_INDEX, "Actor Parameters (default: 0)", false},
    {"actor subtype:", ACTOR_SUBTYPE_INDEX,
    "Actor subtype (default: -1) (Dpad / X/Y to scroll)", false},
    {"spawn", ACTOR_SPAWN_INDEX, "Spawn actor at current position", false},
};

void actorFastCreateAtLink(short id, uint32_t parameters, int8_t subtype) {
    fopAcM_create(id, parameters, &dComIfGp_getPlayer()->mCurrent.mPosition,
                  dComIfGp_getPlayer()->mCurrent.mRoomNo, &dComIfGp_getPlayer()->mCurrent.mAngle,
                  nullptr, subtype);
}

void ActorSpawnMenu::draw() {
    cursor.setMode(Cursor::MODE_UNRESTRICTED);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        if (l_paramsSelected) {
            cursor.lock_y = false;
            l_paramsSelected = false;
        } else {
            GZ_setMenu(GZ_SCENE_MENU);
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

    char buf[9];
    tp_sprintf(buf, "%08X", l_actorParams);
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
            switch (l_paramIdx) {
            case 0:
                l_actorParams += 0x10000000;
                break;
            case 1:
                l_actorParams += 0x1000000;
                break;
            case 2:
                l_actorParams += 0x100000;
                break;
            case 3:
                l_actorParams += 0x10000;
                break;
            case 4:
                l_actorParams += 0x1000;
                break;
            case 5:
                l_actorParams += 0x100;
                break;
            case 6:
                l_actorParams += 0x10;
                break;
            case 7:
                l_actorParams += 0x1;
                break;
            }
        }
        if (GZ_getButtonRepeat(CONTROLLER_DOWN)) {
            switch (l_paramIdx) {
            case 0:
                l_actorParams -= 0x10000000;
                break;
            case 1:
                l_actorParams -= 0x1000000;
                break;
            case 2:
                l_actorParams -= 0x100000;
                break;
            case 3:
                l_actorParams -= 0x10000;
                break;
            case 4:
                l_actorParams -= 0x1000;
                break;
            case 5:
                l_actorParams -= 0x100;
                break;
            case 6:
                l_actorParams -= 0x10;
                break;
            case 7:
                l_actorParams -= 0x1;
                break;
            }
        }
        GZ_drawSelectChar(buf, 170.0f, 80.0f, l_paramIdx, 7, 0xFFFFFFFF);
    } else {
        Font::GZ_drawStr(buf, 170.0f, 80.0f,
                             (cursor.y == ACTOR_PARAM_INDEX ? CURSOR_RGBA : 0xFFFFFFFF),
                             GZ_checkDropShadows());
    }

    tp_sprintf(lines[ACTOR_ID_INDEX].value, " <%d>", l_actorID);
    tp_sprintf(lines[ACTOR_SUBTYPE_INDEX].value, " <%d>", l_actorType);

    cursor.move(8, LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, LINE_NUM);
}
