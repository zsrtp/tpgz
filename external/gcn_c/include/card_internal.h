/*!
 *  This file contains the declaration of internal CARD functions and structures.
 */
#ifndef __CARD_INTERNAL_H__
#define __CARD_INTERNAL_H__
#include "card.h"
#include <stddef.h>
#include <stdbool.h>

typedef struct CARDBlock {
    uint8_t unk[0x110];
} CARDBlock;

// Specifically have to use this one and not make a new one
extern CARDBlock __CARDBlock[2];  // One for each memory card slot

// Vanilla functions used in main code
void __CARDDefaultApiCallback(int32_t chn, int32_t result);
void __CARDSyncCallback(int32_t chn, int32_t result);
int32_t __CARDGetControlBlock(int32_t chn, void** card);
int32_t __CARDPutControlBlock(void* card, int32_t result);
int32_t __CARDSync(int32_t chn);
int32_t __CARDUpdateFatBlock(int32_t chn, void* fatBlock, CARDCallback callback);
void* __CARDGetDirBlock(void* card);
int32_t __CARDUpdateDir(int32_t chn, CARDCallback callback);
bool __CARDCompareFileName(void* dirBlock, const char* fileName);
int32_t __CARDAccess(void* card, void* dirBlock);

#endif  // __CARD_INTERNAL_H__