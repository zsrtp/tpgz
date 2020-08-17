#include "utils/card.hpp"
#include "libtp_c/include/system.h"

namespace Utilities {
    void load_mem_card(MemCard::Card &card, SaveLayout &save_layout) {
        card.card_result = CARDOpen(0, card.file_name_buffer, &card.card_info);
        if (card.card_result == Ready) {
            card.card_result = CARDRead(&card.card_info, &save_layout, 512, 0x0000);
            if (card.card_result == Ready) {
                tp_osReport("loaded card!");
                memcpy(CheatItems, save_layout.CheatItems, sizeof(save_layout.CheatItems));
                memcpy(ToolItems, save_layout.ToolItems, sizeof(save_layout.ToolItems));
            } else {
                tp_osReport("failed to load");
            }
            card.card_result = CARDClose(&card.card_info);
        }
    }

    void load_gz_card(bool &card_load) {
        uint8_t frame_count = TP::get_frame_count();
        if (card_load && frame_count > 200) {
            static SaveLayout save_layout;
            static MemCard::Card card;
            card.file_name = "tpgz01";
            card.sector_size = SECTOR_SIZE;
            sprintf(card.file_name_buffer, card.file_name);
            card.card_result = CARDProbeEx(0, NULL, &card.sector_size);
            if (card.card_result == Ready) {
                Utilities::load_mem_card(card, save_layout);
                card_load = false;
            } else {
                card_load = false;
            }
        }
    }
}