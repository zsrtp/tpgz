#include "utils/card.h"
#include "libtp_c/include/system.h"
#include "libtp_c/include/math.h"
#include "saves.h"
#include "commands.h"
#include "fifo_queue.h"

namespace Utilities {
    /**
     * @brief Like CARDWrite, but allows for arbitrary sizes and offsets.
     */
    int32_t card_write(CardInfo* card_info, void* data, int32_t size, int32_t offset, int32_t sector_size) {
        uint8_t* buf = (uint8_t*)tp_memalign(-32, sector_size);
        int32_t result = Ready;
        int32_t read_bytes = 0;

        while (result == Ready && size > 0) {
            result = CARDRead(card_info, buf, sector_size, (offset & ~(sector_size - 1)));
            if (result != Ready) {
                break;
            }
            int32_t rem_size = sector_size - (offset & (sector_size - 1));
            tp_memcpy(buf + (offset & (sector_size - 1)), (void*)((uint32_t)data + read_bytes), MIN(rem_size, size));
            result = CARDWrite(card_info, buf, sector_size, (offset & ~(sector_size - 1)));
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
    int32_t card_read(CardInfo* card_info, void* data, int32_t size, int32_t offset, int32_t sector_size) {
        uint8_t* buf = (uint8_t*)tp_memalign(-32, sector_size);
        int32_t result = Ready;
        int32_t read_bytes = 0;

        while (result == Ready && size > 0) {
            result = CARDRead(card_info, buf, sector_size, (offset & ~(sector_size - 1)));
            if (result != Ready) {
                break;
            }
            int32_t rem_size = sector_size - (offset & (sector_size - 1));
            tp_memcpy((void*)((uint32_t)data + read_bytes), buf + (offset & (sector_size - 1)), MIN(rem_size, size));
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

    void setup_save_file(GZSaveFile& save_file) {
        save_file.header.version = GZ_SAVE_VERSION_NUMBER;
        save_file.header.entries = GZ_SAVE_ENTRIES_AMNT;
        save_file.header.offsetsLoc = offsetof(GZSaveFile, offsets);
        save_file.header.sizesLoc = offsetof(GZSaveFile, sizes);
#define set_entry(idx, attr)                                                            \
    save_file.offsets[idx] = offsetof(GZSaveFile, data) + offsetof(GZSaveLayout, attr); \
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

    int32_t read_save_file(CardInfo* card_info, GZSaveFile& save_file, int32_t sector_size) {
        int32_t result = Ready;
#define assert_result(stmt)           \
    if ((result = (stmt)) != Ready) { \
        return result;                \
    }

        uint32_t pos = 0;
        assert_result(card_read(card_info, &save_file.header, sizeof(save_file.header), pos, sector_size));
        pos += sizeof(save_file.header);
        if (save_file.header.version != GZ_SAVE_VERSION_NUMBER) {
            return -30;  // Custom error code for "Version" (means a mismatch in the version number).
        }
        assert_result(card_read(card_info, save_file.offsets, save_file.header.entries * sizeof(save_file.offsets[0]), save_file.header.offsetsLoc, sector_size));
        assert_result(card_read(card_info, save_file.sizes, save_file.header.entries * sizeof(save_file.sizes[0]), save_file.header.sizesLoc, sector_size));

#define assert_read_entry(idx, ptr, size)                                                                               \
    if (idx < save_file.header.entries) {                                                                               \
        assert_result(card_read(card_info, ptr, MIN(size, save_file.sizes[idx]), save_file.offsets[idx], sector_size)); \
    }
        assert_read_entry(SV_CHEATS_INDEX, save_file.data.CheatItems, sizeof(save_file.data.CheatItems));
        assert_read_entry(SV_TOOLS_INDEX, save_file.data.ToolItems, sizeof(save_file.data.ToolItems));
        assert_read_entry(SV_SCENE_INDEX, save_file.data.SceneItems, sizeof(save_file.data.SceneItems));
        assert_read_entry(SV_WATCHES_INDEX, save_file.data.Watches, sizeof(save_file.data.Watches));
        assert_read_entry(SV_SPRITES_INDEX, save_file.data.sprite_offsets, sizeof(save_file.data.sprite_offsets));
        assert_read_entry(SV_COMMANDS, save_file.data.commands_states, sizeof(save_file.data.commands_states));
        assert_read_entry(SV_DROP_SHADOW_INDEX, &save_file.data.g_drop_shadows, sizeof(save_file.data.g_drop_shadows));
        assert_read_entry(SV_AREA_RELOAD_INDEX, &save_file.data.g_area_reload_behavior, sizeof(save_file.data.g_area_reload_behavior));
        assert_read_entry(SV_CURSOR_COLOR_INDEX, &save_file.data.g_cursor_color, sizeof(save_file.data.g_cursor_color));
        assert_read_entry(SV_FONT_INDEX, &save_file.data.g_font, sizeof(save_file.data.g_font));
#undef assert_read_entry
#undef assert_result

        return result;
    }

    void store_mem_card(Card& card) {
        GZSaveFile save_file;
        Utilities::setup_save_file(save_file);
        Utilities::store_save_layout(save_file.data);
        uint32_t file_size = (uint32_t)(tp_ceil((double)sizeof(save_file) / (double)card.sector_size) * card.sector_size);
        card.card_result = CARDDelete(0, card.file_name_buffer);
        card.card_result = CARDCreate(0, card.file_name_buffer, file_size, &card.card_info);
        if (card.card_result == Ready || card.card_result == Exist) {
            card.card_result = CARDOpen(0, card.file_name_buffer, &card.card_info);
            if (card.card_result == Ready) {
                card.card_result = Utilities::card_write(&card.card_info, &save_file, sizeof(save_file), 0, card.sector_size);
                if (card.card_result == Ready) {
                    tp_osReport("saved card!");
                    FIFOQueue::push("saved card!", Queue);
                } else {
                    tp_osReport("failed to save");
                    char buff[32];
                    tp_sprintf(buff, "failed to save: %d", card.card_result);
                    FIFOQueue::push(buff, Queue);
                }
                card.card_result = CARDClose(&card.card_info);
            }
        }
    }

    void load_mem_card(Card& card) {
        card.card_result = CARDOpen(0, card.file_name_buffer, &card.card_info);
        if (card.card_result == Ready) {
            GZSaveFile save_file;
            store_save_layout(save_file.data);
            card.card_result = read_save_file(&card.card_info, save_file, card.sector_size);
            if (card.card_result == Ready) {
                tp_osReport("loaded card!");
                FIFOQueue::push("loaded card!", Queue);
                load_save_layout(save_file.data);
                SettingsMenu::initFont();
            } else {
                tp_osReport("failed to load");
                char buff[32];
                tp_sprintf(buff, "failed to load: %d", card.card_result);
                FIFOQueue::push(buff, Queue);
            }
            card.card_result = CARDClose(&card.card_info);
        }
    }

    void load_gz_card(bool& card_load) {
        uint8_t frame_count = TP::get_frame_count();
        if (card_load && frame_count > 200) {
            static Card card;
            card.file_name = "tpgz01";
            card.sector_size = SECTOR_SIZE;
            tp_sprintf(card.file_name_buffer, (char*)card.file_name);
            card.card_result = CARDProbeEx(0, NULL, &card.sector_size);
            if (card.card_result == Ready) {
                Utilities::load_mem_card(card);
                card_load = false;
            } else {
                card_load = false;
            }
        }
    }
}  // namespace Utilities