#include <cstdio>
#include "menus/menu_actor_list/include/actor_list_menu.h"
#include "memory_editor.h"
#include "settings.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/f_op/f_op_actor_mng.h"
#include "libtp_c/include/d/d_procname.h"
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

KEEP_FUNC ActorListMenu::ActorListMenu(Cursor& cursor, ActorListData& data)
    : Menu(cursor),
      l_index(data.l_index), lines{
                                 {"index:", ACTOR_ID_INDEX,
                                  "List Index (Dpad to scroll / " CONTROL_TEXT " to view memory)",
                                  false},
                                 {"freeze", 1, "Freeze/Unfreeze selected actor", false},
                                 {"delete", 2, "Delete selected actor", false},
                             } {}

ActorListMenu::~ActorListMenu() {}

void ActorListMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
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

    switch (cursor.y) {
    case ACTOR_ID_INDEX:
        if (GZ_getButtonRepeat(CONTROLLER_RIGHT) && l_index < g_fopAcTg_Queue.mSize) {
            l_index++;
        } else if (GZ_getButtonRepeat(CONTROLLER_LEFT) && l_index > 0) {
            l_index--;
        }
        break;
    case 1:
        if (GZ_getButtonTrig(SELECTION_BUTTON)) {
            if (actorData != NULL) {
                actorData->mBase.mPauseFlag = !actorData->mBase.mPauseFlag;
            }
        }
        break;
    case 2:
        if (GZ_getButtonTrig(SELECTION_BUTTON)) {
            if (actorData != NULL && fopAcM_GetName(actorData) != PROC_ALINK) {
                fopAcM_delete(actorData);
            }
        }
    }

    if (l_index > g_fopAcTg_Queue.mSize - 1) {
        l_index = g_fopAcTg_Queue.mSize - 1;
    }

    if (actorData != NULL) {
        char addressBuf[18];
        snprintf(addressBuf, sizeof(addressBuf), "Address: %08X", (uint32_t)actorData);
        GZ_drawText(addressBuf, 25.0f, 120.f, 0xFFFFFFFF, GZ_checkDropShadows());

        char nameBuf[16];
        snprintf(nameBuf, sizeof(nameBuf), "Proc ID: %d", actorData->mBase.mProcName);
        GZ_drawText(nameBuf, 25.0f, 140.f, 0xFFFFFFFF, GZ_checkDropShadows());

        char paramBuf[17];
        snprintf(paramBuf, sizeof(paramBuf), "Params: %08X", actorData->mBase.mParameters);
        GZ_drawText(paramBuf, 25.0f, 160.f, 0xFFFFFFFF, GZ_checkDropShadows());

        char angleBuf[14];
        snprintf(angleBuf, sizeof(angleBuf), "Angle: %d", actorData->shape_angle.y);
        GZ_drawText(angleBuf, 25.0f, 180.f, 0xFFFFFFFF, GZ_checkDropShadows());

        char posBuf[50];
        snprintf(posBuf, sizeof(posBuf), "Position: %.1f %.1f %.1f",
                 actorData->current.pos.x, actorData->current.pos.y,
                 actorData->current.pos.z);
        GZ_drawText(posBuf, 25.0f, 200.f, 0xFFFFFFFF, GZ_checkDropShadows());

        lines[ACTOR_ID_INDEX].printf(" <%d / %d>", l_index, g_fopAcTg_Queue.mSize - 1);

        if (GZ_getButtonTrig(MEM_SWITCH_BTN)) {
            switch (cursor.y) {
            case ACTOR_ID_INDEX:
                g_memoryEditor_addressIndex = (uint32_t)actorData;
                g_menuMgr->push(MN_MEMORY_EDITOR_INDEX);
                return;
            }
        }
    }

    cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
