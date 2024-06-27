#include <cstdio>
#include "menus/menu_actor_list/include/actor_list_menu.h"
#include "memory_editor.h"
#include "settings.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/f_op/f_op_draw_tag.h"
#include "libtp_c/include/d/d_procname.h"
#include "libtp_c/include/d/menu/d_menu_window.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"
#include "fs.h"
#include "global_data.h"
#include "boot/include/collision_view.h"
#include "libtp_c/include/m_Do/m_Do_printf.h"
#include "libtp_c/include/m_Do/m_Re_controller_pad.h"
#include "libtp_c/include/d/meter/d_meter_HIO.h"

#ifdef GCN_PLATFORM
#define CONTROLLER_RIGHT GZPad::DPAD_RIGHT
#define CONTROLLER_LEFT GZPad::DPAD_LEFT
#define CONTROLLER_Z GZPad::Z
#define CONTROLLER_A GZPad::A
#define MEM_SWITCH_BTN GZPad::Y
#define CONTROL_TEXT "Y"
#define DELETE_TEXT "START"
#define DELETE_BUTTON GZPad::START
#endif
#ifdef WII_PLATFORM
#define CONTROLLER_RIGHT GZPad::DPAD_RIGHT
#define CONTROLLER_LEFT GZPad::DPAD_LEFT
#define CONTROLLER_Z GZPad::Z
#define CONTROLLER_A GZPad::A
#define MEM_SWITCH_BTN GZPad::C
#define CONTROL_TEXT "C"
#define DELETE_TEXT "PLUS"
#define DELETE_BUTTON GZPad::PLUS
#endif

/**
 * @brief Used for storing entries from procs.bin
 */
procBinData l_procData;

void ring_close_proc_wrapper(void* arg) {
    dMw_c__ring_close_proc(arg);
}

void collect_close_proc_wrapper(void* arg) {
    dMw_c__collect_close_proc(arg);
}

void dmap_close_proc_wrapper(void* arg) {
    dMw_c__dmap_close_proc(arg);
}

void fmap_close_proc_wrapper(void* arg) {
    dMw_c__fmap_close_proc(arg);
}

void collect_save_close_proc_wrapper(void* arg) {
    dMw_c__collect_save_close_proc(arg);
}

void collect_option_close_proc_wrapper(void* arg) {
    dMw_c__collect_option_close_proc(arg);
}

void collect_letter_close_proc_wrapper(void* arg) {
    dMw_c__collect_letter_close_proc(arg);
}

void collect_fishing_close_proc_wrapper(void* arg) {
    dMw_c__collect_fishing_close_proc(arg);
}

void collect_skill_close_proc_wrapper(void* arg) {
    dMw_c__collect_skill_close_proc(arg);
}

void collect_insect_close_proc_wrapper(void* arg) {
    dMw_c__collect_insect_close_proc(arg);
}

void insect_close_proc_wrapper(void* arg) {
    dMw_c__insect_close_proc(arg);
}

typedef void (*procFunc)(void*);
procFunc move_proc[] = {
    NULL,
    NULL,
    ring_close_proc_wrapper,
    NULL,
    NULL,
    collect_close_proc_wrapper,
    NULL,
    NULL,
    fmap_close_proc_wrapper,
    NULL,
    NULL,
    dmap_close_proc_wrapper,
    NULL,
    NULL,
    collect_save_close_proc_wrapper,
    NULL,
    NULL,
    collect_option_close_proc_wrapper,
    NULL,
    NULL,
    collect_letter_close_proc_wrapper,
    NULL,
    NULL,
    collect_fishing_close_proc_wrapper,
    NULL,
    NULL,
    collect_skill_close_proc_wrapper,
    NULL,
    NULL,
    collect_insect_close_proc_wrapper,
    NULL,
    NULL,
    NULL,
    insect_close_proc_wrapper
};

/**
 * @brief Checks and closes any menu that's currently open.
 * 
 * @details This function is used to close any menu that's currently open. 
 * It stores the current menu status and then closes the menu by setting the status to none and running the currently open menu's closer function via move_proc function table.
 * 
 * @note Currently the function won't catch if the menu status is in opening or closing status (two statuses during menu transitions). It will only catch the "move" status.
 * We may have to account for this later.
 * 
 * @note The move_proc function table already exists in code. We can probably just map directly to it in the future instead of defining our own.
 * 
 */
void ActorListMenu::checkAndCloseMenu() {
    if (g_meter2_info.mMenuWindowClass) {
        switch (g_meter2_info.mMenuWindowClass->mMenuStatus) {
        case dMw_c::NO_MENU:
            g_dComIfG_gameInfo.play.mPauseFlag = false;
            break;
        case dMw_c::RING_MOVE:
        case dMw_c::COLLECT_MOVE:
        case dMw_c::DMAP_MOVE:
        case dMw_c::FMAP_MOVE:
        case dMw_c::SAVE_MOVE:
        case dMw_c::OPTIONS_MOVE:
        case dMw_c::LETTER_MOVE:
        case dMw_c::FISHING_MOVE:
        case dMw_c::SKILL_MOVE:
        case dMw_c::INSECT_MOVE:
        case dMw_c::INSECT_AGITHA_MOVE:
            l_menuStatus = g_meter2_info.mMenuWindowClass->mMenuStatus;
            l_windowStatus = g_meter2_info.mWindowStatus;
            g_meter2_info.mWindowStatus = dMw_c::NO_MENU;
            move_proc[g_meter2_info.mMenuWindowClass->mMenuStatus](g_meter2_info.mMenuWindowClass);
            g_dComIfG_gameInfo.play.mPauseFlag = false;
        }
    }       
}

/**
 * @brief Checks and restores any menu that was previously open.
 * 
 * @details This function is used to restore any menu that was previously open. 
 * It restores the menu by setting the status to the stored status and setting the currently stored menu status's corresponding window status.
 * 
 * @note There doesn't seem to be the need to run the opener function like there is with the checkAndCloseMenu function.
 * Just restoring the menu status and window status seems to be enough.
 * 
 */
void ActorListMenu::checkAndRestoreMenu() {
    if (l_menuStatus != dMw_c::NO_MENU) {
        g_dComIfG_gameInfo.play.mPauseFlag = true;

        switch (l_menuStatus) {
        case dMw_c::RING_MOVE: 
        case dMw_c::COLLECT_MOVE:
        case dMw_c::FMAP_MOVE:
        case dMw_c::SAVE_MOVE:
        case dMw_c::OPTIONS_MOVE:
        case dMw_c::LETTER_MOVE:
        case dMw_c::FISHING_MOVE:
        case dMw_c::SKILL_MOVE:
        case dMw_c::INSECT_MOVE:
        case dMw_c::INSECT_AGITHA_MOVE:
        case dMw_c::DMAP_MOVE:
            g_meter2_info.mWindowStatus = l_windowStatus;
            g_meter2_info.mMenuWindowClass->mMenuStatus = l_menuStatus;
            break;
        }
    }
}

KEEP_FUNC ActorListMenu::ActorListMenu(Cursor& cursor, ActorListData& data)
        : Menu(cursor),
          l_index(data.l_index),
          lines{
            {"", ACTOR_NAME_INDEX, "Z+A: freeze actor, Z+" DELETE_TEXT ": delete actor, " CONTROL_TEXT " view memory", false},
            {"", ACTOR_POSITION_X_INDEX, "dpad: +/-10.0, Z+dpad: +/-100.0", false},
            {"", ACTOR_POSITION_Y_INDEX, "dpad: +/-10.0, Z+dpad: +/-100.0", false},
            {"", ACTOR_POSITION_Z_INDEX, "dpad: +/-10.0, Z+dpad: +/-100.0", false},
            {"", ACTOR_ANGLE_X_INDEX, "dpad: +/-10, Z+dpad: +/-100", false},
            {"", ACTOR_ANGLE_Y_INDEX, "dpad: +/-10, Z+dpad: +/-100", false},
            {"", ACTOR_ANGLE_Z_INDEX, "dpad: +/-10, Z+dpad: +/-100", false},
            {"", ACTOR_PARAMS_INDEX, "current actor parameters", false},
        } {
            // store camera position and target
            l_cameraPos = matrixInfo.matrix_info->pos;
            l_cameraTarget = matrixInfo.matrix_info->target;

            // remove any currently open menus
            checkAndCloseMenu();

            // initial data load from procs.bin
            updateActorData();
            loadActorName();
        }

ActorListMenu::~ActorListMenu() {
    // restore any previously open menu
    checkAndRestoreMenu();

    // restore camera position and target
    matrixInfo.matrix_info->pos = l_cameraPos;
    matrixInfo.matrix_info->target = l_cameraTarget;

    dComIfGp_getEventManager().mCameraPlay = 0;
    g_drawHIO.mHUDAlpha = 1.0f;

}

template <typename T>
void ActorListMenu::updateValue(T* value, f32 smallChange, f32 largeChange, bool increase, bool largeIncrement) {
    if (value != NULL) {
        *value += (increase ? 1 : -1) * (largeIncrement ? largeChange : smallChange);
    }
}

void ActorListMenu::updateActorData() {
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

    g_currentActor = actorData;
}

void ActorListMenu::loadActorName() {
    if (g_currentActor) {
        int offset = (g_currentActor->mBase.mProcName*32);
        loadFile("tpgz/procs.bin", &l_procData, sizeof(l_procData), offset);
    }
}

void ActorListMenu::draw() {
    g_actorViewEnabled = true;
    cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        // disable gadget and close menu
        g_actorViewEnabled = false;
        g_menuMgr->pop();
        return;
    }

    bool rightPressed = GZ_getButtonRepeat(CONTROLLER_RIGHT,1);
    bool leftPressed = GZ_getButtonRepeat(CONTROLLER_LEFT,1);
    bool zPressed = GZ_getButtonPressed(CONTROLLER_Z);

    f32 smallPosChange = 10.0f, largePosChange = 100.0f;
    int smallAngleChange = 100, largeAngleChange = 1000;

    switch (cursor.y) {
    case ACTOR_NAME_INDEX:
        if (GZ_getButtonRepeat(CONTROLLER_RIGHT)) {
            l_index++;
            if (l_index > g_fopAcTg_Queue.mSize - 1)
                l_index = 0;

            updateActorData();
            loadActorName();
        } 
        
        if (GZ_getButtonRepeat(CONTROLLER_LEFT)) {
            l_index--;
            if (l_index > g_fopAcTg_Queue.mSize - 1)
                l_index = g_fopAcTg_Queue.mSize - 1;

            updateActorData();
            loadActorName();
        }
        
        if (GZ_getButtonPressed(CONTROLLER_Z) && GZ_getButtonPressed(DELETE_BUTTON)) {
            if (g_currentActor) {
                if (g_currentActor->mBase.mProcName != PROC_ALINK) {
                    fopAcM_delete(g_currentActor);
                }
            }
        }

        if (GZ_getButtonPressed(CONTROLLER_Z) && GZ_getButtonPressed(CONTROLLER_A)) {
            if (g_currentActor) {
                g_currentActor->mBase.mPauseFlag = !g_currentActor->mBase.mPauseFlag;
            }
        }

        if (GZ_getButtonTrig(MEM_SWITCH_BTN)) {
            switch (cursor.y) {
            case ACTOR_NAME_INDEX:
                g_memoryEditor_addressIndex = (uint32_t)g_currentActor;
                g_menuMgr->push(MN_MEMORY_EDITOR_INDEX);
                return;
            }
        }

        break;
    case ACTOR_POSITION_X_INDEX:
        if (rightPressed || leftPressed) {
            updateValue(&g_currentActor->current.pos.x, smallPosChange, largePosChange, rightPressed, zPressed);
        }
        break;
    case ACTOR_POSITION_Y_INDEX:
        if (rightPressed || leftPressed) {
            updateValue(&g_currentActor->current.pos.y, smallPosChange, largePosChange, rightPressed, zPressed);
        }
        break;
    case ACTOR_POSITION_Z_INDEX:
        if (rightPressed || leftPressed) {
            updateValue(&g_currentActor->current.pos.z, smallPosChange, largePosChange, rightPressed, zPressed);
        }
        break;
    case ACTOR_ANGLE_X_INDEX:
        if (rightPressed || leftPressed) {
            updateValue(&g_currentActor->shape_angle.x, smallAngleChange, largeAngleChange, rightPressed, zPressed);
        }
        break;
    case ACTOR_ANGLE_Y_INDEX:
        if (rightPressed || leftPressed) {
            updateValue(&g_currentActor->shape_angle.y, smallAngleChange, largeAngleChange, rightPressed, zPressed);
        }
        break;
    case ACTOR_ANGLE_Z_INDEX:
        if (rightPressed || leftPressed) {
            updateValue(&g_currentActor->shape_angle.z, smallAngleChange, largeAngleChange, rightPressed, zPressed);
        }
        break;
    case ACTOR_PARAMS_INDEX:
        // allowing arbitrary updates here causes frequent crashes. removing for now.
        break;
    }

    if (g_currentActor) {
        lines[ACTOR_NAME_INDEX].printf("name:  <%s>", l_procData.procName);
        lines[ACTOR_POSITION_X_INDEX].printf("pos-x: <%.1f>", g_currentActor->current.pos.x);
        lines[ACTOR_POSITION_Y_INDEX].printf("pos-y: <%.1f>", g_currentActor->current.pos.y);
        lines[ACTOR_POSITION_Z_INDEX].printf("pos-z: <%.1f>", g_currentActor->current.pos.z);
        lines[ACTOR_ANGLE_X_INDEX].printf("rot-x: <0x%04X>", static_cast<u16>(g_currentActor->shape_angle.x));
        lines[ACTOR_ANGLE_Y_INDEX].printf("rot-y: <0x%04X>", static_cast<u16>(g_currentActor->shape_angle.y));
        lines[ACTOR_ANGLE_Z_INDEX].printf("rot-z: <0x%04X>", static_cast<u16>(g_currentActor->shape_angle.z));
        lines[ACTOR_PARAMS_INDEX].printf("params: 0x%08X", g_currentActor->mBase.mParameters);
    }

    cursor.move(0, ACTOR_LIST_LINE_COUNT);
    GZ_drawMenuLines(lines, cursor.y, ACTOR_LIST_LINE_COUNT);
}
