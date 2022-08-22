#include "menus/menu_memfiles/include/memfiles_menu.h"
#include <cstdio>
#include "memfiles.h"
#include "utils/card.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/f_op/f_op_draw_tag.h"
#include "libtp_c/include/f_op/f_op_scene_req.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

#define MAX_SAVE_SLOTS 20

bool g_injectMemfile;
bool set_position_data;
PositionData memfile_posdata;

KEEP_FUNC MemfilesMenu::MemfilesMenu(MemfilesData& data)
    : Menu(), cursor(data.cursor), l_fileNo(data.l_fileNo), lines{
                  {"file slot:", MEMFILE_SLOT_INDEX, "Select memfile slot"},
                  {"save", MEMFILE_SAVE_INDEX, "Save memfile to slot", false},
                  {"load", MEMFILE_LOAD_INDEX, "Load memfile from slot", false},
                  {"delete", MEMFILE_DELETE_INDEX, "Delete memfile from slot", false},
              } {}

MemfilesMenu::~MemfilesMenu() {}

void MemfilesMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
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
            snprintf(fileBuf, sizeof(fileBuf), "tpgz_s%d", l_fileNo);
            card.file_name = fileBuf;
            card.sector_size = SECTOR_SIZE;
            snprintf(card.file_name_buffer, sizeof(card.file_name_buffer), card.file_name);
#ifndef WII_PLATFORM
            card.result = CARDProbeEx(0, nullptr, &card.sector_size);
            if (card.result == Ready) {
                GZ_storeMemfile(card);
            }
#else
            GZ_storeMemfile(card);
#endif  // WII_PLATFORM
            break;
        case MEMFILE_LOAD_INDEX:
            snprintf(fileBuf, sizeof(fileBuf), "tpgz_s%d", l_fileNo);
            card.file_name = fileBuf;
            card.sector_size = SECTOR_SIZE;
            snprintf(card.file_name_buffer, sizeof(card.file_name_buffer), card.file_name);
#ifndef WII_PLATFORM
            card.result = CARDProbeEx(0, NULL, &card.sector_size);
            if (card.result == Ready) {
                GZ_loadMemfile(card);
            }
#else
            GZ_loadMemfile(card);
#endif  // WII_PLATFORM
            break;
        case MEMFILE_DELETE_INDEX:
            snprintf(fileBuf, sizeof(fileBuf), "tpgz_s%d", l_fileNo);
            card.file_name = fileBuf;
            card.sector_size = SECTOR_SIZE;
            snprintf(card.file_name_buffer, sizeof(card.file_name_buffer), card.file_name);
#ifndef WII_PLATFORM
            card.result = CARDProbeEx(0, nullptr, &card.sector_size);
            if (card.result == Ready) {
                GZ_deleteMemfile(card);
            }
#else
            GZ_deleteMemfile(card);
#endif  // WII_PLATFORM
            break;
        }
    }

    lines[MEMFILE_SLOT_INDEX].printf(" <%d>", l_fileNo);

    cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
