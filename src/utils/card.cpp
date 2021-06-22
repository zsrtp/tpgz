#include "utils/card.h"
#include "commands.h"
#include "fifo_queue.h"
#include "utils/loading.h"
#include "libtp_c/include/msl_c/math.h"
#include "libtp_c/include/msl_c/string.h"
#include "libtp_c/include/m_Do/m_Do_printf.h"
#include "menus/practice_menu.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/f_op/f_op_draw_tag.h"
#include "libtp_c/include/SSystem/SComponent/c_counter.h"
#include "menus/memfiles_menu.h"
#include "save_manager.h"

bool inject_memfile_flag = false;

namespace Utilities {
/**
 * @brief Like CARDWrite, but allows for arbitrary sizes and offsets.
 */
int32_t storage_write(Storage* storage, void* data, int32_t size, int32_t offset,
                      int32_t sector_size) {
    uint8_t* buf = (uint8_t*)tp_memalign(-32, sector_size);
    int32_t result = Ready;
    int32_t read_bytes = 0;

    while (result == Ready && size > 0) {
        StorageRead(*storage, buf, sector_size, (offset & ~(sector_size - 1)));
        if (result != Ready) {
            break;
        }
        int32_t rem_size = sector_size - (offset & (sector_size - 1));
        tp_memcpy(buf + (offset & (sector_size - 1)), (void*)((uint32_t)data + read_bytes),
                  MIN(rem_size, size));
        StorageWrite(*storage, buf, sector_size, (offset & ~(sector_size - 1)));
        read_bytes += MIN(rem_size, size);
        size -= rem_size;
        offset += rem_size;
    }
    tp_free(buf);
    return result;
}

/**
 * @brief Like CARDRead, but allows for arbitrary sizes and offsets.
 */
int32_t storage_read(Storage* storage, void* data, int32_t size, int32_t offset,
                     int32_t sector_size) {
    uint8_t* buf = (uint8_t*)tp_memalign(-32, sector_size);
    int32_t result = Ready;
    int32_t read_bytes = 0;

    while (result == Ready && size > 0) {
        StorageRead(*storage, buf, sector_size, (offset & ~(sector_size - 1)));
        if (result != Ready) {
            break;
        }
        int32_t rem_size = sector_size - (offset & (sector_size - 1));
        tp_memcpy((void*)((uint32_t)data + read_bytes), buf + (offset & (sector_size - 1)),
                  MIN(rem_size, size));
        read_bytes += MIN(rem_size, size);
        size -= rem_size;
        offset += rem_size;
    }
    tp_free(buf);
    return result;
}

void store_save_layout(GZSaveLayout& save_layout) {
    tp_memcpy(save_layout.CheatItems, CheatItems, sizeof(CheatItems));
    tp_memcpy(save_layout.ToolItems, ToolItems, sizeof(ToolItems));
    tp_memcpy(save_layout.SceneItems, SceneItems, sizeof(SceneItems));
    tp_memcpy(save_layout.Watches, Watches, sizeof(Watches));
    tp_memcpy(save_layout.sprite_offsets, sprite_offsets, sizeof(sprite_offsets));
    tp_memcpy(save_layout.commands_states, commands_states, sizeof(commands_states));
    save_layout.g_drop_shadows = g_drop_shadows;
    save_layout.g_area_reload_behavior = g_area_reload_behavior;
    save_layout.g_cursor_color = g_cursor_color;
    save_layout.g_font = g_font;
}

void load_save_layout(GZSaveLayout& save_layout) {
    tp_memcpy(CheatItems, save_layout.CheatItems, sizeof(CheatItems));
    tp_memcpy(ToolItems, save_layout.ToolItems, sizeof(ToolItems));
    tp_memcpy(SceneItems, save_layout.SceneItems, sizeof(SceneItems));
    tp_memcpy(Watches, save_layout.Watches, sizeof(Watches));
    tp_memcpy(sprite_offsets, save_layout.sprite_offsets, sizeof(sprite_offsets));
    tp_memcpy(commands_states, save_layout.commands_states, sizeof(commands_states));
    g_drop_shadows = save_layout.g_drop_shadows;
    g_area_reload_behavior = save_layout.g_area_reload_behavior;
    g_cursor_color = save_layout.g_cursor_color;
    g_font = save_layout.g_font;
}

void load_position_data(PositionData& pos_data) {
    memfile_posdata.link = pos_data.link;
    memfile_posdata.cam.target = pos_data.cam.target;
    memfile_posdata.cam.pos = pos_data.cam.pos;
    memfile_posdata.angle = pos_data.angle;
}

void setup_save_file(GZSaveFile& save_file) {
    save_file.header.version = GZ_SAVE_VERSION_NUMBER;
    save_file.header.entries = GZ_SAVE_ENTRIES_AMNT;
    save_file.header.offsetsLoc = offsetof(GZSaveFile, offsets);
    save_file.header.sizesLoc = offsetof(GZSaveFile, sizes);
#define set_entry(idx, attr)                                                                       \
    save_file.offsets[idx] = offsetof(GZSaveFile, data) + offsetof(GZSaveLayout, attr);            \
    save_file.sizes[idx] = sizeof(save_file.data.attr)

    set_entry(SV_CHEATS_INDEX, CheatItems);
    set_entry(SV_TOOLS_INDEX, ToolItems);
    set_entry(SV_SCENE_INDEX, SceneItems);
    set_entry(SV_WATCHES_INDEX, Watches);
    set_entry(SV_SPRITES_INDEX, sprite_offsets);
    set_entry(SV_COMMANDS, commands_states);
    set_entry(SV_DROP_SHADOW_INDEX, g_drop_shadows);
    set_entry(SV_AREA_RELOAD_INDEX, g_area_reload_behavior);
    set_entry(SV_CURSOR_COLOR_INDEX, g_cursor_color);
    set_entry(SV_FONT_INDEX, g_font);
#undef set_entry
}

int32_t read_save_file(Storage* storage, GZSaveFile& save_file, int32_t sector_size) {
    int32_t result = Ready;
#define assert_result(stmt)                                                                        \
    if ((result = (stmt)) != Ready) {                                                              \
        return result;                                                                             \
    }

    uint32_t pos = 0;
    assert_result(
        storage_read(storage, &save_file.header, sizeof(save_file.header), pos, sector_size));
    pos += sizeof(save_file.header);
    if (save_file.header.version != GZ_SAVE_VERSION_NUMBER) {
        return -30;  // Custom error code for "Version" (means a mismatch in the version number).
    }
    assert_result(storage_read(storage, save_file.offsets,
                               save_file.header.entries * sizeof(save_file.offsets[0]),
                               save_file.header.offsetsLoc, sector_size));
    assert_result(storage_read(storage, save_file.sizes,
                               save_file.header.entries * sizeof(save_file.sizes[0]),
                               save_file.header.sizesLoc, sector_size));

#define assert_read_entry(idx, ptr, size)                                                          \
    if (idx < save_file.header.entries) {                                                          \
        assert_result(storage_read(storage, ptr, MIN(size, save_file.sizes[idx]),                  \
                                   save_file.offsets[idx], sector_size));                          \
    }
    assert_read_entry(SV_CHEATS_INDEX, save_file.data.CheatItems,
                      sizeof(save_file.data.CheatItems));
    assert_read_entry(SV_TOOLS_INDEX, save_file.data.ToolItems, sizeof(save_file.data.ToolItems));
    assert_read_entry(SV_SCENE_INDEX, save_file.data.SceneItems, sizeof(save_file.data.SceneItems));
    assert_read_entry(SV_WATCHES_INDEX, save_file.data.Watches, sizeof(save_file.data.Watches));
    assert_read_entry(SV_SPRITES_INDEX, save_file.data.sprite_offsets,
                      sizeof(save_file.data.sprite_offsets));
    assert_read_entry(SV_COMMANDS, save_file.data.commands_states,
                      sizeof(save_file.data.commands_states));
    assert_read_entry(SV_DROP_SHADOW_INDEX, &save_file.data.g_drop_shadows,
                      sizeof(save_file.data.g_drop_shadows));
    assert_read_entry(SV_AREA_RELOAD_INDEX, &save_file.data.g_area_reload_behavior,
                      sizeof(save_file.data.g_area_reload_behavior));
    assert_read_entry(SV_CURSOR_COLOR_INDEX, &save_file.data.g_cursor_color,
                      sizeof(save_file.data.g_cursor_color));
    assert_read_entry(SV_FONT_INDEX, &save_file.data.g_font, sizeof(save_file.data.g_font));
#undef assert_read_entry
#undef assert_result

    return result;
}

int32_t read_memfile(Storage* storage, PositionData& posData, int32_t sector_size) {
    int32_t result = Ready;
#define assert_result(stmt)                                                                        \
    if ((result = (stmt)) != Ready) {                                                              \
        return result;                                                                             \
    }

    assert_result(storage_read(storage, (void*)sTmpBuf, 3818, 0, sector_size));

    assert_result(storage_read(storage, &posData, sizeof(posData), 3819, sector_size));

#undef assert_result
    return result;
}

void store_mem_card(Storage& storage) {
    GZSaveFile save_file;
    Utilities::setup_save_file(save_file);
    Utilities::store_save_layout(save_file.data);
    uint32_t file_size = (uint32_t)(
        tp_ceil((double)sizeof(save_file) / (double)storage.sector_size) * storage.sector_size);
    storage.result = StorageDelete(0, storage.file_name_buffer);
    storage.result = StorageCreate(0, storage.file_name_buffer, file_size, &storage.info);
    if (storage.result == Ready || storage.result == Exist) {
        storage.result = StorageOpen(0, storage.file_name_buffer, &storage.info, OPEN_MODE_RW);
        if (storage.result == Ready) {
            storage.result = Utilities::storage_write(&storage, &save_file, sizeof(save_file), 0,
                                                      storage.sector_size);
            if (storage.result == Ready) {
                tp_osReport("saved card!");
                FIFOQueue::push("saved card!", Queue);
            } else {
                tp_osReport("failed to save");
                char buff[32];
                tp_sprintf(buff, "failed to save: %d", storage.result);
                FIFOQueue::push(buff, Queue);
            }
            storage.result = StorageClose(&storage.info);
        }
    }
}

void store_memfile(Storage& storage) {
    PositionData posData;
    posData.link = dComIfGp_getPlayer()->mCurrent.mPosition;
    posData.cam.target = tp_matrixInfo.matrix_info->target;
    posData.cam.pos = tp_matrixInfo.matrix_info->pos;
    posData.angle = dComIfGp_getPlayer()->mCollisionRot.mY;
    uint32_t file_size =
        (uint32_t)(tp_ceil((double)3818 / (double)storage.sector_size) * storage.sector_size);
    storage.result = StorageDelete(0, storage.file_name_buffer);
    storage.result = StorageCreate(0, storage.file_name_buffer, file_size, &storage.info);
    if (storage.result == Ready || storage.result == Exist) {
        storage.result = StorageOpen(0, storage.file_name_buffer, &storage.info, OPEN_MODE_RW);
        if (storage.result == Ready) {
            dComIfGs_putSave(g_dComIfG_gameInfo.mInfo.mDan.mStageNo);

            g_dComIfG_gameInfo.mInfo.getPlayer().player_return.mSpawnId = 0;
            g_dComIfG_gameInfo.mInfo.getPlayer().player_return.mRoomId =
                g_dComIfG_gameInfo.play.mEvtManager.field_0x1b0 & 0xFF;
            tp_strcpy((char*)g_dComIfG_gameInfo.mInfo.getPlayer().player_return.mCurrentStage,
                      (char*)g_dComIfG_gameInfo.play.mStartStage.mStage);
            storage.result = Utilities::storage_write(&storage, &g_dComIfG_gameInfo, 3818, 0,
                                                      storage.sector_size);

            storage.result = Utilities::storage_write(&storage, &posData, sizeof(posData), 3819,
                                                      storage.sector_size);
            if (storage.result == Ready) {
                tp_osReport("saved memfile!");
                FIFOQueue::push("saved memfile!", Queue);
            } else {
                tp_osReport("failed to save");
                char buff[32];
                tp_sprintf(buff, "failed to save: %d", storage.result);
                FIFOQueue::push(buff, Queue);
            }
            storage.result = StorageClose(&storage.info);
        }
    }
}

void delete_mem_card(Storage& storage) {
    storage.result = StorageDelete(0, storage.file_name_buffer);
    if (storage.result == Ready) {
        tp_osReport("deleted card!");
        FIFOQueue::push("deleted card!", Queue);
    } else {
        tp_osReport("failed to delete");
        char buff[32];
        tp_sprintf(buff, "failed to delete: %d", storage.result);
        FIFOQueue::push(buff, Queue);
    }
}

void delete_memfile(Storage& storage) {
    storage.result = StorageDelete(0, storage.file_name_buffer);
    if (storage.result == Ready) {
        tp_osReport("deleted memfile!");
        FIFOQueue::push("deleted memfile!", Queue);
    } else {
        tp_osReport("failed to delete");
        char buff[32];
        tp_sprintf(buff, "failed to delete: %d", storage.result);
        FIFOQueue::push(buff, Queue);
    }
}

void load_mem_card(Storage& storage) {
    storage.result = StorageOpen(0, storage.file_name_buffer, &storage.info, OPEN_MODE_RW);
    if (storage.result == Ready) {
        GZSaveFile save_file;
        store_save_layout(save_file.data);
        storage.result = read_save_file(&storage, save_file, storage.sector_size);
        if (storage.result == Ready) {
            tp_osReport("loaded card!");
            FIFOQueue::push("loaded card!", Queue);
            load_save_layout(save_file.data);
            SettingsMenu::initFont();
        } else {
            tp_osReport("failed to load");
            char buff[32];
            tp_sprintf(buff, "failed to load: %d", storage.result);
            FIFOQueue::push(buff, Queue);
        }
        storage.result = StorageClose(&storage.info);
    }
}

void load_memfile(Storage& storage) {
    storage.result = StorageOpen(0, storage.file_name_buffer, &storage.info, OPEN_MODE_RW);
    if (storage.result == Ready) {
        PositionData posData;
        storage.result = read_memfile(&storage, posData, storage.sector_size);
        if (storage.result == Ready) {
            tp_osReport("loaded memfile!");
            FIFOQueue::push("loaded memfile!", Queue);
            inject_memfile_flag = true;
            SaveManager::inject_default_before();
            SaveManager::inject_memfile((void*)sTmpBuf);
            SaveManager::inject_default_during();
            SaveManager::inject_default_after();
            load_position_data(posData);
            inject_save_flag = true;
            fifo_visible = true;
            MenuRendering::set_menu(MN_NONE_INDEX);

        } else {
            tp_osReport("failed to load");
            char buff[32];
            tp_sprintf(buff, "failed to load: %d", storage.result);
            FIFOQueue::push(buff, Queue);
        }
        storage.result = StorageClose(&storage.info);
    }
}

#ifdef GCN_PLATFORM
#define FRAME_COUNT 200
#define FILE_NAME "tpgz01"
#endif  // GCN_PLATFORM
#ifdef WII_PLATFORM
#define FRAME_COUNT 500
#define FILE_NAME "tpgz01.dat"
#endif  // WII_PLATFORM

void load_gz_card(bool& card_load) {
    uint8_t frame_count = cCt_getFrameCount();
    if (card_load && frame_count > FRAME_COUNT) {
        static Storage storage;
        storage.file_name = FILE_NAME;
        storage.sector_size = SECTOR_SIZE;
        tp_sprintf(storage.file_name_buffer, (char*)storage.file_name);
#ifndef WII_PLATFORM
        storage.result = CARDProbeEx(0, NULL, &storage.sector_size);
        if (storage.result == Ready) {
            Utilities::load_mem_card(storage);
        }
#else   // WII_PLATFORM
        Utilities::load_mem_card(storage);
#endif  // WII_PLATFORM

        card_load = false;
    }
}
}  // namespace Utilities