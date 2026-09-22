#ifndef __STORAGE_H__
#define __STORAGE_H__

#include <stdint.h>

#ifndef WII_PLATFORM
#include "card.h"
#define STORAGE_FILENAME_MAX CARD_FILENAME_MAX
#define FileInfo CardInfo
#define OPEN_MODE_READ
#define OPEN_MODE_WRITE
#define OPEN_MODE_RW
#define STORAGE_SEEK_BEG 0
#define STORAGE_SEEK_CUR 1
#define STORAGE_SEEK_END 2
#else  // WII_PLATFORM
#include "nand.h"
#define STORAGE_FILENAME_MAX NAND_FILENAME_MAX
#define FileInfo NANDInfo
#define OPEN_MODE_READ NAND_OPEN_READ
#define OPEN_MODE_WRITE NAND_OPEN_WRITE
#define OPEN_MODE_RW NAND_OPEN_RW
#define STORAGE_SEEK_BEG NAND_SEEK_BEG
#define STORAGE_SEEK_CUR NAND_SEEK_CUR
#define STORAGE_SEEK_END NAND_SEEK_END
#endif  // WII_PLATFORM

enum StorageError {
    Ready = 0,
    Busy = -1,
    WrongDevice = -2,
    NoCard = -3,
    NoFile = -4,
    IoError = -5,
    Broken = -6,
    Exist = -7,
    NoEnt = -8,
    InsSpace = -9,
    NoPerm = -10,
    Limit = -11,
    NameTooLong = -12,
    Encoding = -13,
    Canceled = -14,
    FatalError = -128
};

typedef struct Storage {
    FileInfo info;
    int32_t sector_size;
    const char* file_name;
    int32_t result;
    char file_name_buffer[STORAGE_FILENAME_MAX * 2];
    uint32_t result_size;
    uint32_t position;
} Storage;

#ifndef WII_PLATFORM
#define StorageFreeBlocks(ch, byteNotUsed, filesNotUsed) CARDFreeBlocks(ch, byteNotUsed, filesNotUsed)
#define StorageCreate(ch, fileName, size, fileBuffer) CARDCreate(ch, fileName, size, fileBuffer)
#define StorageDelete(ch, fileName) CARDDelete(ch, fileName)
#define StorageOpen(ch, fileName, fileInfo, mode) CARDOpen(ch, fileName, fileInfo)
#define StorageClose(fileInfo) CARDClose(fileInfo)
#define StorageRead(storage, data, length)                                                         \
    ({ (storage).result = CARDRead(&(storage).info, data, length, (storage).position); (storage).position += length; (storage).result; })
#define StorageWrite(storage, data, length)                                                        \
    ({ (storage).result = CARDWrite(&(storage).info, data, length, (storage).position); (storage).position += length; (storage).result; })
inline int32_t StorageSeek(Storage* storage, int32_t offset, int32_t whence) {
    switch (whence) {
        case STORAGE_SEEK_BEG:
            storage->position = (uint32_t)offset;
            break;
        case STORAGE_SEEK_CUR:
            storage->position += offset;
            break;
        case STORAGE_SEEK_END:
            storage->position = storage->info.length + offset;
            break;
        default:
            return IoError;
    }
    return storage->position;
}
#else  // WII_PLATFORM
#define StorageFreeBlocks(ch, byteNotUsed, filesNotUsed)
#define StorageCreate(ch, fileName, size, fileBuffer)                                              \
    ({                                                                                             \
        (void)size;                                                                                \
        (void)fileBuffer;                                                                          \
        NANDCreate(fileName, 0x34, 0);                                                             \
    })
#define StorageDelete(ch, fileName) NANDDelete(fileName)
#define StorageOpen(ch, fileName, fileInfo, mode) NANDOpen(fileName, fileInfo, mode)
#define StorageClose(fileInfo) NANDClose(fileInfo)
#define StorageRead(storage, data, length)                                                         \
    ({                                                                                             \
        (storage).result_size = NANDRead(&(storage).info, data, length);                           \
        (storage).result = Ready;                                                                  \
    })
#define StorageWrite(storage, data, length)                                                        \
    ({                                                                                             \
        (storage).result_size = NANDWrite(&(storage).info, data, length);                          \
        (storage).result = Ready;                                                                  \
    })
#define StorageSeek(storage, offset, whence) NANDSeek(&(*(storage)).info, offset, whence)
#endif  // WII_PLATFORM

#endif  // __STORAGE_H__