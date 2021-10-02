#include "font.h"
#include "gcn_c/include/storage.h"
#include "menu.h"

extern bool inject_memfile_flag;

namespace Utilities {
int32_t storage_write(Storage* info, void* data, int32_t size, int32_t offset, int32_t sector_size);
int32_t storage_read(Storage* info, void* data, int32_t size, int32_t offset, int32_t sector_size);
void store_mem_card(Storage& card);
void store_memfile(Storage& card);
void delete_mem_card(Storage& card);
void delete_memfile(Storage& card);
void load_mem_card(Storage& card);
void load_memfile(Storage& card);
void load_gz_card(bool& card_load);
}  // namespace Utilities