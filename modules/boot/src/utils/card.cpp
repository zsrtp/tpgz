#include "commands.h"
#include "settings.h"
#include "fifo_queue.h"
#include "libtp_c/include/SSystem/SComponent/c_counter.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/f_op/f_op_draw_tag.h"
#include "libtp_c/include/m_Do/m_Do_printf.h"
#include "libtp_c/include/msl_c/math.h"
#include "libtp_c/include/msl_c/string.h"
#include "libtp_c/include/utils.h"
#include "menus/memfiles_menu.h"
#include "gz_flags.h"
#include "save_manager.h"
#include "utils/card.h"
#include "utils/loading.h"
#include "rels/include/defines.h"
#include "rels/include/cxx.h"
#include "menus/utils/menu_mgr.h"
#include "rels/include/defines.h"

#ifdef WII_PLATFORM
KEEP_VAR void* g_tmpBuf;
#endif

/**
 * @brief Like CARDWrite, but allows for arbitrary sizes and offsets.
 */
int32_t GZ_storageWrite(Storage* storage, void* data, int32_t size, int32_t offset,
                        int32_t sector_size) {
    uint8_t* buf = new (-32) uint8_t[sector_size];
    int32_t result = Ready;
    int32_t read_bytes = 0;

    while (result == Ready && size > 0) {
        StorageRead(*storage, buf, sector_size, (offset & ~(sector_size - 1)));
        if (result != Ready) {
            break;
        }
        int32_t rem_size = sector_size - (offset & (sector_size - 1));
        memcpy(buf + (offset & (sector_size - 1)), (void*)((uint32_t)data + read_bytes),
               MIN(rem_size, size));
        StorageWrite(*storage, buf, sector_size, (offset & ~(sector_size - 1)));
        read_bytes += MIN(rem_size, size);
        size -= rem_size;
        offset += rem_size;
    }
    delete[] buf;
    return result;
}

/**
 * @brief Like CARDRead, but allows for arbitrary sizes and offsets.
 */
int32_t GZ_storageRead(Storage* storage, void* data, int32_t size, int32_t offset,
                       int32_t sector_size) {
    uint8_t* buf = new (-32) uint8_t[sector_size];
    int32_t result = Ready;
    int32_t read_bytes = 0;

    while (result == Ready && size > 0) {
        StorageRead(*storage, buf, sector_size, (offset & ~(sector_size - 1)));
        if (result != Ready) {
            break;
        }
        int32_t rem_size = sector_size - (offset & (sector_size - 1));
        memcpy((void*)((uint32_t)data + read_bytes), buf + (offset & (sector_size - 1)),
               MIN(rem_size, size));
        read_bytes += MIN(rem_size, size);
        size -= rem_size;
        offset += rem_size;
    }
    delete[] buf;
    return result;
}

void GZ_storeSaveLayout(GZSaveLayout& save_layout) {
    memcpy(save_layout.mCheats, g_cheats, sizeof(g_cheats));
    memcpy(save_layout.mTools, g_tools, sizeof(g_tools));
    memcpy(save_layout.mSceneFlags, g_sceneFlags, sizeof(g_sceneFlags));
    memcpy(save_layout.mWatches, g_watches, sizeof(g_watches));
    memcpy(save_layout.mSpriteOffsets, g_spriteOffsets, sizeof(g_spriteOffsets));
    memcpy(save_layout.mCommandStates, g_commandStates, sizeof(g_commandStates));
    save_layout.mDropShadows = g_dropShadows;
    save_layout.mReloadType = g_reloadType;
    save_layout.mCursorColType = g_cursorColorType;
    save_layout.mFontType = g_fontType;
}

void GZ_loadSaveLayout(GZSaveLayout& save_layout) {
    memcpy(g_cheats, save_layout.mCheats, sizeof(g_cheats));
    memcpy(g_tools, save_layout.mTools, sizeof(g_tools));
    memcpy(g_sceneFlags, save_layout.mSceneFlags, sizeof(g_sceneFlags));
    memcpy(g_watches, save_layout.mWatches, sizeof(g_watches));
    memcpy(g_spriteOffsets, save_layout.mSpriteOffsets, sizeof(g_spriteOffsets));
    memcpy(g_commandStates, save_layout.mCommandStates, sizeof(g_commandStates));
    g_dropShadows = save_layout.mDropShadows;
    g_reloadType = save_layout.mReloadType;
    g_cursorColorType = save_layout.mCursorColType;
    g_fontType = save_layout.mFontType;
}

void GZ_loadPositionData(PositionData& pos_data) {
    memfile_posdata.link = pos_data.link;
    memfile_posdata.cam.target = pos_data.cam.target;
    memfile_posdata.cam.pos = pos_data.cam.pos;
    memfile_posdata.angle = pos_data.angle;
}

void GZ_setupSaveFile(GZSaveFile& save_file) {
    save_file.header.version = GZ_SAVE_VERSION_NUMBER;
    save_file.header.entries = GZ_SAVE_ENTRIES_AMNT;
    save_file.header.offsetsLoc = offsetof(GZSaveFile, offsets);
    save_file.header.sizesLoc = offsetof(GZSaveFile, sizes);
#define set_entry(idx, attr)                                                                       \
    save_file.offsets[idx] = offsetof(GZSaveFile, data) + offsetof(GZSaveLayout, attr);            \
    save_file.sizes[idx] = sizeof(save_file.data.attr)

    set_entry(SV_CHEATS_INDEX, mCheats);
    set_entry(SV_TOOLS_INDEX, mTools);
    set_entry(SV_SCENE_INDEX, mSceneFlags);
    set_entry(SV_WATCHES_INDEX, mWatches);
    set_entry(SV_SPRITES_INDEX, mSpriteOffsets);
    set_entry(SV_COMMANDS, mCommandStates);
    set_entry(SV_DROP_SHADOW_INDEX, mDropShadows);
    set_entry(SV_AREA_RELOAD_INDEX, mReloadType);
    set_entry(SV_CURSOR_COLOR_INDEX, mCursorColType);
    set_entry(SV_FONT_INDEX, mFontType);
#undef set_entry
}

int32_t GZ_readSaveFile(Storage* storage, GZSaveFile& save_file, int32_t sector_size) {
    int32_t result = Ready;
#define assert_result(stmt)                                                                        \
    if ((result = (stmt)) != Ready) {                                                              \
        return result;                                                                             \
    }

    uint32_t pos = 0;
    assert_result(
        GZ_storageRead(storage, &save_file.header, sizeof(save_file.header), pos, sector_size));
    pos += sizeof(save_file.header);
    if (save_file.header.version != GZ_SAVE_VERSION_NUMBER) {
        return -30;  // Custom error code for "Version" (means a mismatch in the version number).
    }
    assert_result(GZ_storageRead(storage, save_file.offsets,
                                 save_file.header.entries * sizeof(save_file.offsets[0]),
                                 save_file.header.offsetsLoc, sector_size));
    assert_result(GZ_storageRead(storage, save_file.sizes,
                                 save_file.header.entries * sizeof(save_file.sizes[0]),
                                 save_file.header.sizesLoc, sector_size));

#define assert_read_entry(idx, ptr, size)                                                          \
    if (idx < save_file.header.entries) {                                                          \
        assert_result(GZ_storageRead(storage, ptr, MIN(size, save_file.sizes[idx]),                \
                                     save_file.offsets[idx], sector_size));                        \
    }
    assert_read_entry(SV_CHEATS_INDEX, save_file.data.mCheats, sizeof(save_file.data.mCheats));
    assert_read_entry(SV_TOOLS_INDEX, save_file.data.mTools, sizeof(save_file.data.mTools));
    assert_read_entry(SV_SCENE_INDEX, save_file.data.mSceneFlags,
                      sizeof(save_file.data.mSceneFlags));
    assert_read_entry(SV_WATCHES_INDEX, save_file.data.mWatches, sizeof(save_file.data.mWatches));
    assert_read_entry(SV_SPRITES_INDEX, save_file.data.mSpriteOffsets,
                      sizeof(save_file.data.mSpriteOffsets));
    assert_read_entry(SV_COMMANDS, save_file.data.mCommandStates,
                      sizeof(save_file.data.mCommandStates));
    assert_read_entry(SV_DROP_SHADOW_INDEX, &save_file.data.mDropShadows,
                      sizeof(save_file.data.mDropShadows));
    assert_read_entry(SV_AREA_RELOAD_INDEX, &save_file.data.mReloadType,
                      sizeof(save_file.data.mReloadType));
    assert_read_entry(SV_CURSOR_COLOR_INDEX, &save_file.data.mCursorColType,
                      sizeof(save_file.data.mCursorColType));
    assert_read_entry(SV_FONT_INDEX, &save_file.data.mFontType, sizeof(save_file.data.mFontType));
#undef assert_read_entry
#undef assert_result

    return result;
}

int32_t GZ_readMemfile(Storage* storage, PositionData& posData, int32_t sector_size) {
    int32_t result = Ready;
#define assert_result(stmt)                                                                        \
    if ((result = (stmt)) != Ready) {                                                              \
        return result;                                                                             \
    }

    assert_result(GZ_storageRead(storage, MEMFILE_BUF, sizeof(dSv_info_c), 0, sector_size));

    assert_result(
        GZ_storageRead(storage, &posData, sizeof(posData), sizeof(dSv_info_c) + 1, sector_size));

#undef assert_result
    return result;
}

KEEP_FUNC void GZ_storeMemCard(Storage& storage) {
    GZSaveFile save_file;
    GZ_setupSaveFile(save_file);
    GZ_storeSaveLayout(save_file.data);
    uint32_t file_size = (uint32_t)(ceil((double)sizeof(save_file) / (double)storage.sector_size) *
                                    storage.sector_size);
    storage.result = StorageDelete(0, storage.file_name_buffer);
    storage.result = StorageCreate(0, storage.file_name_buffer, file_size, &storage.info);
    if (storage.result == Ready || storage.result == Exist) {
        storage.result = StorageOpen(0, storage.file_name_buffer, &storage.info, OPEN_MODE_RW);
        if (storage.result == Ready) {
            storage.result =
                GZ_storageWrite(&storage, &save_file, sizeof(save_file), 0, storage.sector_size);
            if (storage.result == Ready) {
                OSReport("saved card!");
                FIFOQueue::push("saved card!", Queue);
            } else {
                OSReport("failed to save");
                char buff[32];
                sprintf(buff, "failed to save: %d", storage.result);
                FIFOQueue::push(buff, Queue);
            }
            storage.result = StorageClose(&storage.info);
        }
    }
}

void GZ_storeMemfile(Storage& storage) {
    PositionData posData;
    posData.link = dComIfGp_getPlayer()->mCurrent.mPosition;
    posData.cam.target = matrixInfo.matrix_info->target;
    posData.cam.pos = matrixInfo.matrix_info->pos;
    posData.angle = dComIfGp_getPlayer()->mCollisionRot.mY;
    uint32_t file_size = (uint32_t)(ceil((double)sizeof(dSv_info_c) / (double)storage.sector_size) *
                                    storage.sector_size);

    storage.result = StorageDelete(0, storage.file_name_buffer);
    storage.result = StorageCreate(0, storage.file_name_buffer, file_size, &storage.info);

    if (storage.result == Ready || storage.result == Exist) {
        storage.result = StorageOpen(0, storage.file_name_buffer, &storage.info, OPEN_MODE_RW);
        if (storage.result == Ready) {
            dComIfGs_putSave(g_dComIfG_gameInfo.info.mDan.mStageNo);

            setReturnPlace(g_dComIfG_gameInfo.play.mStartStage.mStage,
                           g_dComIfG_gameInfo.play.mEvent.field_0x12c, 0);

            storage.result = GZ_storageWrite(&storage, &g_dComIfG_gameInfo, sizeof(dSv_info_c), 0,
                                             storage.sector_size);
            storage.result = GZ_storageWrite(&storage, &posData, sizeof(posData),
                                             sizeof(dSv_info_c) + 1, storage.sector_size);
            if (storage.result == Ready) {
                FIFOQueue::push("saved memfile!", Queue);
            } else {
                char buff[32];
                sprintf(buff, "failed to save: %d", storage.result);
                FIFOQueue::push(buff, Queue);
            }
            storage.result = StorageClose(&storage.info);
        }
    }
}

KEEP_FUNC void GZ_deleteMemCard(Storage& storage) {
    storage.result = StorageDelete(0, storage.file_name_buffer);
    if (storage.result == Ready) {
        FIFOQueue::push("deleted card!", Queue);
    } else {
        char buff[32];
        sprintf(buff, "failed to delete: %d", storage.result);
        FIFOQueue::push(buff, Queue);
    }
}

void GZ_deleteMemfile(Storage& storage) {
    storage.result = StorageDelete(0, storage.file_name_buffer);
    if (storage.result == Ready) {
        FIFOQueue::push("deleted memfile!", Queue);
    } else {
        char buff[32];
        sprintf(buff, "failed to delete: %d", storage.result);
        FIFOQueue::push(buff, Queue);
    }
}

void GZ_loadMemCard(Storage& storage) {
    storage.result = StorageOpen(0, storage.file_name_buffer, &storage.info, OPEN_MODE_RW);
    if (storage.result == Ready) {
        GZSaveFile save_file;
        GZ_storeSaveLayout(save_file.data);
        storage.result = GZ_readSaveFile(&storage, save_file, storage.sector_size);
        if (storage.result == Ready) {
            FIFOQueue::push("loaded card!", Queue);
            GZ_loadSaveLayout(save_file.data);
            GZ_initFont();
        } else {
            char buff[32];
            sprintf(buff, "failed to load: %d", storage.result);
            FIFOQueue::push(buff, Queue);
        }
        storage.result = StorageClose(&storage.info);
    }
}

void GZ_loadMemfile(Storage& storage) {
    storage.result = StorageOpen(0, storage.file_name_buffer, &storage.info, OPEN_MODE_RW);
    if (storage.result == Ready) {
        PositionData posData;
        storage.result = GZ_readMemfile(&storage, posData, storage.sector_size);
        if (storage.result == Ready) {
            FIFOQueue::push("loaded memfile!", Queue);
            g_injectMemfile = true;
            SaveManager::injectDefault_before();
            SaveManager::injectMemfile(MEMFILE_BUF);
            SaveManager::injectDefault_during();
            SaveManager::injectDefault_after();
            GZ_loadPositionData(posData);
            set_position_data = true;
            g_injectSave = true;
            g_fifoVisible = true;
            g_menuMgr->hide();
        } else {
            char buff[32];
            sprintf(buff, "failed to load: %d", storage.result);
            FIFOQueue::push(buff, Queue);
        }
        storage.result = StorageClose(&storage.info);
    }
}

#define FRAME_COUNT 200
#define FILE_NAME "tpgz01"

void GZ_loadGZSave(bool& card_load) {
    uint8_t frame_count = cCt_getFrameCount();
    if (card_load && frame_count > FRAME_COUNT) {
        static Storage storage;
        storage.file_name = FILE_NAME;
        storage.sector_size = SECTOR_SIZE;
        sprintf(storage.file_name_buffer, (char*)storage.file_name);
#ifndef WII_PLATFORM
        storage.result = CARDProbeEx(0, NULL, &storage.sector_size);
        if (storage.result == Ready) {
            GZ_loadMemCard(storage);
        }
#else   // WII_PLATFORM
        GZ_loadMemCard(storage);
#endif  // WII_PLATFORM

        card_load = false;
    }
}