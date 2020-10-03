#include "font.h"
#include "gcn_c/include/card.h"
#include "save_injector.h"
#include "menu.h"

namespace Utilities {
    int32_t card_write(CardInfo* card_info, void* data, int32_t size, int32_t offset, int32_t sector_size);
    int32_t card_read(CardInfo* card_info, void* data, int32_t size, int32_t offset, int32_t sector_size);
    void store_mem_card(Card &card);
    void load_mem_card(Card& card);
    void load_gz_card(bool& card_load);
    void change_font(Font& font, const _Font& font_bytes, const char* font_texture_data);
}  // namespace Utilities