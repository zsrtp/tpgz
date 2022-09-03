#ifndef WII_PLATFORM
#include "card.h"
#include "card_internal.h"
#include "storage.h"
#include <stddef.h>

// We declare those instead of using the standard headers to let
// the linker link them against the ones already in the game's code.
void* memset(void* dst, int val, size_t n);

// +=-=-=-=-=-=-=-=-=-=-=+
// | Deletion functions  |
// +=-=-=-=-=-=-=-=-=-=-=+

int32_t __CARDFreeBlock(int32_t chn, uint16_t block, CARDCallback callback) {
    uint32_t card = (uint32_t)(&__CARDBlock[chn]);
    if (*(int32_t*)card == 0) {
        return NoCard;
    }
    
    uint16_t cardVar = *(uint16_t*)(card + 0x10); // Maximum number of blocks?
    uint16_t* fatBlock = *(uint16_t**)(card + 0x88);
    
    while (block != 0xFFFF) {
        uint32_t tempBlock = (uint32_t)block;
        if ((tempBlock < 5) || (tempBlock >= cardVar)) {
            return Broken;
        }
        
        block = fatBlock[tempBlock];
        fatBlock[tempBlock] = 0;
        fatBlock[3] += 1;
    }
    
    return __CARDUpdateFatBlock(chn, fatBlock, callback);
}

void DeleteCallback(int32_t chn, int32_t result) {
    uint32_t card = (uint32_t)(&__CARDBlock[chn]);
    CARDCallback* cardApiCbAddress = (CARDCallback*)(card + 0xD0);
    CARDCallback cb = *cardApiCbAddress;
    *cardApiCbAddress = (CARDCallback)NULL;
    
    int32_t ret = result;
    if (ret >= Ready) {
        uint16_t* currFileBlockAddr = (uint16_t*)(card + 0xBE);
        
        ret = __CARDFreeBlock(chn, *currFileBlockAddr, cb);
        if (ret >= Ready) {
            return;
        }
    }
    
    __CARDPutControlBlock((void*)card, ret);
    
    if (cb) {
        cb(chn, ret);
    }
}

int32_t __CARDGetFileNo(void* card, const char* fileName, int32_t* fileNo) {
    int32_t cardIsAttached = *(int32_t*)((uint32_t)card);
    if (cardIsAttached == 0) {
        return NoCard;
    }
    
    uint32_t dirBlock = (uint32_t)(__CARDGetDirBlock(card));
    
    int32_t i;
    for (i = 0; i < 127; i++)
    {
        uint8_t* currentDirBlock = (uint8_t*)(dirBlock + (i * 0x40));
        
        if (!__CARDCompareFileName(currentDirBlock, fileName)) {
            continue;
        }
        
        if (__CARDAccess(card, currentDirBlock) < Ready) {
            continue;
        }
        
        *fileNo = i;
        break;
    }
    
    if (i >= 127) {
        return NoFile;
    }
    
    return Ready;
}

int32_t CARDDeleteAsync(int32_t chn, const char* fileName, CARDCallback callback)
{
    uint32_t card;
    int32_t ret = __CARDGetControlBlock(chn, (void**)(&card));
    if (ret < Ready) {
        return ret;
    }
    
    int32_t fileNo;
    ret = __CARDGetFileNo((void*)card, fileName, &fileNo);
    if (ret < Ready) {
        __CARDPutControlBlock((void*)card, ret);
        return ret;
    }
    
    uint32_t dirBlock = (uint32_t)(__CARDGetDirBlock((void*)card));
    uint32_t entry = dirBlock + (fileNo * 0x40);
    
    uint16_t* blockAddr = (uint16_t*)(entry + 0x36);
    uint16_t* currFileBlockAddr = (uint16_t*)(card + 0xBE);
    *currFileBlockAddr = *blockAddr;
    
    memset((void*)entry, -1, 0x40);
    
    CARDCallback cb = callback;
    if (!cb) {
        cb = __CARDDefaultApiCallback;
    }
    
    CARDCallback* cardApiCbAddress = (CARDCallback*)(card + 0xD0);
    *cardApiCbAddress = cb;
    
    ret = __CARDUpdateDir(chn, DeleteCallback);
    if (ret >= Ready) {
        return ret;
    }

    __CARDPutControlBlock((void*)card, ret);
    return ret;
}

int32_t CARDDelete(int32_t chn, const char* fileName)
{
    int32_t ret = CARDDeleteAsync(chn, fileName, __CARDSyncCallback);
    if (ret >= Ready) {
        ret = __CARDSync(chn);
    }
    return ret;
}

// +=-=-=-=-=-=-=-=-=-=-=-=-=-=-=+
// | Other functions go here...  |
// +=-=-=-=-=-=-=-=-=-=-=-=-=-=-=+
#endif
