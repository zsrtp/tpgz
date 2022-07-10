#include "font.h"
#include "gcn_c/include/storage.h"
#include "menu.h"

int32_t GZ_storageWrite(Storage* info, void* data, int32_t size, int32_t offset, int32_t sector_size);
int32_t GZ_storageRead(Storage* info, void* data, int32_t size, int32_t offset, int32_t sector_size);
void GZ_storeMemCard(Storage& card);
void GZ_storeMemfile(Storage& card);
void GZ_deleteMemCard(Storage& card);
void GZ_deleteMemfile(Storage& card);
void GZ_loadMemCard(Storage& card);
void GZ_loadMemfile(Storage& card);
void GZ_loadGZSave(bool& card_load);