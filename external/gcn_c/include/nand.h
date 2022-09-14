#ifndef __NAND_H__
#define __NAND_H__

#include <stdint.h>

#define NAND_FILENAME_MAX 32
#define SECTOR_SIZE 0x400

#define NAND_OPEN_READ 0x01
#define NAND_OPEN_WRITE 0x02
#define NAND_OPEN_RW (NAND_OPEN_READ | NAND_OPEN_WRITE)

typedef struct NANDInfo {
    uint8_t unk[0x90];
} NANDInfo;

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus
#ifdef WII_PLATFORM
int32_t NANDCreate(const char* fileName, uint32_t unk2, int32_t unk3);
int32_t NANDDelete(const char* fileName);
int32_t NANDOpen(const char* fileName, NANDInfo* fileInfo, uint32_t mode);
int32_t NANDSafeOpen(const char* fileName, NANDInfo* fileInfo, uint32_t mode, void* safeCopyBuf,
                     uint32_t size);
int32_t NANDClose(NANDInfo* fileInfo);
int32_t NANDSafeClose(NANDInfo* fileInfo);
int32_t NANDRead(NANDInfo* fileInfo, void* dest, uint32_t length);
int32_t NANDWrite(NANDInfo* fileInfo, void* src, uint32_t length);
int32_t NANDSeek(NANDInfo* fileInfo, uint32_t offset, int32_t unk1);
#endif  // WII_PLATFORM
#ifdef __cplusplus
}
#endif  // __cplusplus

extern uint8_t l_safeCopyBuf[0x4000];

#endif  // __NAND_H__