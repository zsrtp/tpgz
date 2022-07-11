#include "menus/memfiles_menu.h"
#include "utils/card.h"
#include "libtp_c/include/msl_c/string.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/f_op/f_op_draw_tag.h"
#include "libtp_c/include/f_op/f_op_scene_req.h"
#include "gz_flags.h"

#define LINE_NUM 4
#define MAX_SAVE_SLOTS 20

Cursor MemfilesMenu::cursor;
bool set_position_data;
bool g_injectMemfile = false;

static uint8_t l_fileNo = 1;
bool l_dataCopied = false;
cXyz l_tmpPos = g_dComIfG_gameInfo.info.mRestart.mRoomPos;
uint16_t l_tmpAngle = g_dComIfG_gameInfo.info.mRestart.mRoomAngleY;
PositionData memfile_posdata;

Line lines[LINE_NUM] = {
    {"file slot:", MEMFILE_SLOT_INDEX, "Select memfile slot"},
    {"save", MEMFILE_SAVE_INDEX, "Save memfile to slot", false},
    {"load", MEMFILE_LOAD_INDEX, "Load memfile from slot", false},
    {"delete", MEMFILE_DELETE_INDEX, "Delete memfile from slot", false},
};

void GZMemfile_setLinkPosition() {
    static int8_t sLoadDelay = 10;

    if (tp_fopScnRq.isLoading == 1) {
        sLoadDelay--;
    }

    // respawn pos gets overwritten by default spawn, so reinject respawn info
    if (!l_dataCopied) {
        l_tmpPos = g_dComIfG_gameInfo.info.mRestart.mRoomPos;
        l_tmpAngle = g_dComIfG_gameInfo.info.mRestart.mRoomAngleY;
        l_dataCopied = true;
    }

    if (sLoadDelay == 0) {
        if (dComIfGp_getPlayer() != nullptr) {
            dComIfGp_getPlayer()->mCurrent.mPosition = memfile_posdata.link;
            tp_matrixInfo.matrix_info->target = memfile_posdata.cam.target;
            tp_matrixInfo.matrix_info->pos = memfile_posdata.cam.pos;
            dComIfGp_getPlayer()->mCollisionRot.mY = memfile_posdata.angle;
            g_dComIfG_gameInfo.info.mRestart.mRoomPos = l_tmpPos;
            g_dComIfG_gameInfo.info.mRestart.mRoomAngleY = l_tmpAngle;
            l_dataCopied = false;
        }
        sLoadDelay = 10;
    }
}

void MemfilesMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        GZ_setMenu(GZ_MEMORY_MENU);
        return;
    }

    switch (cursor.y) {
    case MEMFILE_SLOT_INDEX:
        if (GZ_getButtonRepeat(GZPad::DPAD_LEFT) && l_fileNo > 1) {
            l_fileNo--;
        } else if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT) && l_fileNo < MAX_SAVE_SLOTS) {
            l_fileNo++;
        }
        break;
    }

    static Storage card;
    char fileBuf[9];
    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        switch (cursor.y) {
        case MEMFILE_SAVE_INDEX:
            tp_sprintf(fileBuf, "tpgz_s%d", l_fileNo);
            card.file_name = fileBuf;
            card.sector_size = SECTOR_SIZE;
            tp_sprintf(card.file_name_buffer, card.file_name);
#ifndef WII_PLATFORM
            card.result = CARDProbeEx(0, nullptr, &card.sector_size);
            if (card.result == Ready) {
                GZ_storeMemfile(card);
            }
#endif  // WII_PLATFORM
            GZ_storeMemfile(card);
            break;
        case MEMFILE_LOAD_INDEX:
            tp_sprintf(fileBuf, "tpgz_s%d", l_fileNo);
            card.file_name = fileBuf;
            card.sector_size = SECTOR_SIZE;
            tp_sprintf(card.file_name_buffer, card.file_name);
#ifndef WII_PLATFORM
            card.result = CARDProbeEx(0, NULL, &card.sector_size);
            if (card.result == Ready) {
                GZ_loadMemfile(card);
            }
#endif  // WII_PLATFORM
            break;
        case MEMFILE_DELETE_INDEX:
            tp_sprintf(fileBuf, "tpgz_s%d", l_fileNo);
            card.file_name = fileBuf;
            card.sector_size = SECTOR_SIZE;
            tp_sprintf(card.file_name_buffer, card.file_name);
#ifndef WII_PLATFORM
            card.result = CARDProbeEx(0, nullptr, &card.sector_size);
            if (card.result == Ready) {
                GZ_deleteMemfile(card);
            }
#endif  // WII_PLATFORM
            GZ_deleteMemfile(card);
            break;
        }
    }

    tp_sprintf(lines[MEMFILE_SLOT_INDEX].value, " <%d>", l_fileNo);

    cursor.move(0, LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, LINE_NUM);
}
