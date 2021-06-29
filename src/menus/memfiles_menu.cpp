#include "menus/memfiles_menu.h"
#include "controller.h"
#include "gcn_c/include/card.h"
#include "font.h"
#include "utils/card.h"
#include "libtp_c/include/msl_c/string.h"
#include "utils/cursor.h"
#include "utils/lines.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/f_op/f_op_draw_tag.h"
#include "libtp_c/include/f_op/f_op_scene_req.h"

#define LINES 4
#define MAX_SAVE_SLOTS 20

static Cursor cursor = {0, 0};
bool init_once = false;
static uint8_t file_no = 1;
uint8_t save_delay = 0;
int8_t memfile_load_delay = 10;
bool set_position_data = false;
bool copy_respawn_data = false;
char fileBuf[9];

PositionData memfile_posdata;
cXyz tmpPos = g_dComIfG_gameInfo.mInfo.mRestart.mRoomPos;
uint16_t tmpAngle = g_dComIfG_gameInfo.mInfo.mRestart.mRoomAngleY;

Line lines[LINES] = {{"file slot:", MEMFILE_SLOT_INDEX, "Select memfile slot"},
                     {"save", MEMFILE_SAVE_INDEX, "Save memfile to slot", false},
                     {"load", MEMFILE_LOAD_INDEX, "Load memfile from slot", false},
                     {"delete", MEMFILE_DELETE_INDEX, "Delete memfile from slot", false}};

void set_memfile_position() {
    //  respawn pos gets overwritten by default spawn, so reinject respawn info
    if (!copy_respawn_data) {
        tmpPos = g_dComIfG_gameInfo.mInfo.mRestart.mRoomPos;
        tmpAngle = g_dComIfG_gameInfo.mInfo.mRestart.mRoomAngleY;
        copy_respawn_data = true;
    }

    if (tp_fopScnRq.isLoading == 0) {
        memfile_load_delay--;
    }

    if (memfile_load_delay == 0) {
        dComIfGp_getPlayer()->mCurrent.mPosition = memfile_posdata.link;
        tp_matrixInfo.matrix_info->target = memfile_posdata.cam.target;
        tp_matrixInfo.matrix_info->pos = memfile_posdata.cam.pos;
        dComIfGp_getPlayer()->mCollisionRot.mY = memfile_posdata.angle;
        g_dComIfG_gameInfo.mInfo.mRestart.mRoomPos = tmpPos;
        g_dComIfG_gameInfo.mInfo.mRestart.mRoomAngleY = tmpAngle;
        set_position_data = false;
        copy_respawn_data = false;
        memfile_load_delay = 10;
    }
}

void MemfilesMenu::render() {
    if (button_is_pressed(BACK_BUTTON) && save_delay == 0) {
        init_once = false;
        MenuRendering::set_menu(MN_MEMORY_INDEX);
        return;
    }

    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

    if (save_delay > 0) {
        save_delay--;
    }

    switch (cursor.y) {
    case MEMFILE_SLOT_INDEX: {
        if (button_is_pressed(Controller::DPAD_LEFT) && file_no > 1) {
            file_no--;
        } else if (button_is_pressed(Controller::DPAD_RIGHT) && file_no < MAX_SAVE_SLOTS) {
            file_no++;
        }
        break;
    }
    }

    if (current_input == SELECTION_BUTTON && a_held == false) {
        switch (cursor.y) {
        case MEMFILE_SAVE_INDEX: {
            static Card card;
            tp_sprintf(fileBuf, "tpgz_s%d", file_no);
            card.file_name = fileBuf;
            card.sector_size = SECTOR_SIZE;
            tp_sprintf(card.file_name_buffer, card.file_name);
            card.card_result = CARDProbeEx(0, nullptr, &card.sector_size);
            if (card.card_result == Ready) {
                Utilities::store_memfile(card);
            }
            save_delay = 20;
            break;
        }
        case MEMFILE_LOAD_INDEX: {
            static Card card;
            tp_sprintf(fileBuf, "tpgz_s%d", file_no);
            card.file_name = fileBuf;
            card.sector_size = SECTOR_SIZE;
            tp_sprintf(card.file_name_buffer, card.file_name);
            card.card_result = CARDProbeEx(0, NULL, &card.sector_size);
            if (card.card_result == Ready) {
                Utilities::load_memfile(card);
            }
            break;
        }
        case MEMFILE_DELETE_INDEX: {
            static Card card;
            tp_sprintf(fileBuf, "tpgz_s%d", file_no);
            card.file_name = fileBuf;
            card.sector_size = SECTOR_SIZE;
            tp_sprintf(card.file_name_buffer, card.file_name);
            card.card_result = CARDProbeEx(0, nullptr, &card.sector_size);
            if (card.card_result == Ready) {
                Utilities::delete_memfile(card);
            }
            save_delay = 20;
            break;
        }
        }
    }

    tp_sprintf(lines[MEMFILE_SLOT_INDEX].value, " <%d>", file_no);

    Utilities::move_cursor(cursor, LINES, 0, false, false, false, true);
    Utilities::render_lines(lines, cursor.y, LINES);
};
