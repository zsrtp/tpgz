#include "font.h"
#include "gcn_c/include/card.h"
#include "save_injector.h"
#include "menu.h"

namespace Utilities {
    void load_mem_card(MemCard::Card& card, SaveLayout& save_layout);
    void load_gz_card(bool& card_load);
    void change_font(Font& font, const _Font& font_bytes, const char* font_texture_data);
}  // namespace Utilities