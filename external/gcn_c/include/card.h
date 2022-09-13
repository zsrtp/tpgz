#ifndef __CARD_H__
#define __CARD_H__

#include <stdint.h>

#define CARD_SLOT_A 0  // Memory card slot A
#define CARD_SLOT_B 1  // Memory card slot B

#define CARD_FILENAME_MAX 32
#define CARD_ICON_MAX 8
#define SECTOR_SIZE INT32_MAX

typedef void (*CARDCallback)(int32_t chn, int32_t result);

typedef struct CardInfo {
    int32_t channel;
    int32_t file_number;
    int32_t offset;
    int32_t length;
    uint16_t i_block;
} CardInfo;

typedef struct CARDStat {
    char fileName[CARD_FILENAME_MAX];
    uint32_t length;
    uint32_t time;  // seconds since midnight 01/01/2000
    uint8_t gameName[4];
    uint8_t company[2];

    // read/write (Set by CARDGetStatus/CARDSetStatus)
    uint8_t bannerFormat;
    uint32_t iconAddr;
    uint16_t iconFormat;
    uint16_t iconSpeed;
    uint32_t commentAddr;

    // read-only (Set by CARDGetStatus)
    uint32_t offsetBanner;
    uint32_t offsetBannerTlut;
    uint32_t offsetIcon[CARD_ICON_MAX];
    uint32_t offsetIconTlut;
    uint32_t offsetData;
} CARDStat;

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus
#ifdef WII_PLATFORM
int32_t my_CARDOpen(int32_t channel, char* fileName, CardInfo* fileInfo);
#define CARDOpen my_CARDOpen
#else
int32_t CARDOpen(int32_t channel, char* fileName, CardInfo* fileInfo);
#endif
int32_t CARDRead(CardInfo* fileInfo, void* buf, int32_t length, int32_t offset);
int32_t CARDClose(CardInfo* fileInfo);
int32_t CARDCreate(int32_t channel, char* fileName, uint32_t size, CardInfo* fileInfo);
int32_t CARDProbeEx(int32_t channel, int32_t* memSize, int32_t* sectorSize);
int32_t CARDGetStatus(int32_t channel, int32_t file_number, CARDStat* stat);
int32_t CARDWrite(CardInfo* fileInfo, void* buf, int32_t length, int32_t offset);
int32_t CARDDelete(int32_t chn, const char* fileName);
int32_t CARDDeleteAsync(int32_t chn, const char* fileName, CARDCallback callback);
#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // __CARD_H__