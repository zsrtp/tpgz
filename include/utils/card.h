#include "font.h"
#include "gcn_c/include/card.h"
#include "menu.h"

extern bool inject_memfile_flag;

namespace Utilities {
int32_t card_write(CardInfo* card_info, void* data, int32_t size, int32_t offset,
                   int32_t sector_size);
int32_t card_read(CardInfo* card_info, void* data, int32_t size, int32_t offset,
                  int32_t sector_size);
void store_mem_card(Card& card);
void store_memfile(Card& card);
void delete_mem_card(Card& card);
void delete_memfile(Card& card);
void load_mem_card(Card& card);
void load_memfile(Card& card);
void load_gz_card(bool& card_load);
}  // namespace Utilities