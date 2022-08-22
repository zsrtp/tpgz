#include <cstdio>
#include "menus/actor_spawn_menu.h"
#include "menus/memory_editor_menu.h"
#include "settings.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/f_op/f_op_actor_mng.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

#ifdef GCN_PLATFORM
#define CONTROLLER_RIGHT GZPad::DPAD_RIGHT
#define CONTROLLER_LEFT GZPad::DPAD_LEFT
#define MEM_SWITCH_BTN GZPad::Y
#define CONTROL_TEXT "Y"
#endif
#ifdef WII_PLATFORM
#define CONTROLLER_RIGHT GZPad::DPAD_RIGHT
#define CONTROLLER_LEFT GZPad::DPAD_LEFT
#define MEM_SWITCH_BTN GZPad::C
#define CONTROL_TEXT "C"
#endif

KEEP_FUNC ActorListMenu::ActorListMenu()
    : Menu(), lines{
                  {"index:", ACTOR_ID_INDEX,
                   "List Index (Dpad to scroll / " CONTROL_TEXT " to view memory)", false},
              } {}

void ActorListMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    switch (cursor.y) {
    case ACTOR_ID_INDEX:
        if (GZ_getButtonRepeat(CONTROLLER_RIGHT) && l_index < g_fopAcTg_Queue.mSize) {
            l_index++;
        } else if (GZ_getButtonRepeat(CONTROLLER_LEFT) && l_index > 0) {
            l_index--;
        }
        break;
    }

    if (l_index > g_fopAcTg_Queue.mSize - 1) {
        l_index = g_fopAcTg_Queue.mSize - 1;
    }

    node_class* node = g_fopAcTg_Queue.mpHead;
    fopAc_ac_c* actorData = NULL;
    for (int i = 0; i < g_fopAcTg_Queue.mSize; i++) {
        if (i == l_index && node != NULL) {
            create_tag_class* tag = (create_tag_class*)node;
            actorData = (fopAc_ac_c*)tag->mpTagData;
            break;
        }
        node = node->mpNextNode;
    }

    if (actorData != NULL) {
        char addressBuf[18];
        snprintf(addressBuf, sizeof(addressBuf), "Address: %08X", (uint32_t)actorData);
        GZ_drawText(addressBuf, 25.0f, 100.f, 0xFFFFFFFF, GZ_checkDropShadows());

        char nameBuf[13];
        snprintf(nameBuf, sizeof(nameBuf), "Proc ID: %d", actorData->mBase.mProcName);
        GZ_drawText(nameBuf, 25.0f, 120.f, 0xFFFFFFFF, GZ_checkDropShadows());

        char paramBuf[17];
        snprintf(paramBuf, sizeof(paramBuf), "Params: %08X", actorData->mBase.mParameters);
        GZ_drawText(paramBuf, 25.0f, 140.f, 0xFFFFFFFF, GZ_checkDropShadows());

        char angleBuf[14];
        snprintf(angleBuf, sizeof(angleBuf), "Angle: %d", actorData->mCollisionRot.mY);
        GZ_drawText(angleBuf, 25.0f, 160.f, 0xFFFFFFFF, GZ_checkDropShadows());

        char posBuf[50];
        snprintf(posBuf, sizeof(posBuf), "Position: %.1f %.1f %.1f", actorData->mCurrent.mPosition.x,
                actorData->mCurrent.mPosition.y, actorData->mCurrent.mPosition.z);
        GZ_drawText(posBuf, 25.0f, 180.f, 0xFFFFFFFF, GZ_checkDropShadows());

        snprintf(lines[ACTOR_ID_INDEX].value, sizeof(lines[ACTOR_ID_INDEX].value), " <%d / %d>", l_index, g_fopAcTg_Queue.mSize - 1);

        if (GZ_getButtonTrig(MEM_SWITCH_BTN)) {
            switch (cursor.y) {
            case ACTOR_ID_INDEX:
                MemoryEditorMenu::mAddressIndex = (uint32_t)actorData;
                g_menuMgr->push(MN_MEMORY_EDITOR_INDEX);
                return;
            }
        }
    }

    cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
