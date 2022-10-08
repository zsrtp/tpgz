#ifndef __DVD_H__
#define __DVD_H__

#include <stdint.h>

/*
 * DVD state codes
 */
#define DVD_STATE_FATAL_ERROR -1
#define DVD_STATE_END 0
#define DVD_STATE_BUSY 1
#define DVD_STATE_WAITING 2
#define DVD_STATE_COVER_CLOSED 3
#define DVD_STATE_NO_DISK 4
#define DVD_STATE_COVER_OPEN 5
#define DVD_STATE_WRONG_DISK 6
#define DVD_STATE_MOTOR_STOPPED 7
#define DVD_STATE_IGNORED 8
#define DVD_STATE_CANCELED 10
#define DVD_STATE_RETRY 11

/*
 * DVD error codes
 */
#define DVD_ERROR_OK 0
#define DVD_ERROR_FATAL -1
#define DVD_ERROR_IGNORED -2
#define DVD_ERROR_CANCELED -3
#define DVD_ERROR_COVER_CLOSED -4

#define DVD_READ_SIZE 32
#define DVD_OFFSET_SIZE 4

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Forward typedef for struct _DVDCommandBlock
 */
typedef struct _DVDCommandBlock DVDCommandBlock;
typedef struct _DVDFileInfo DVDFileInfo;

/**
 * @brief function pointer typedef for the user's DVD operation callback
 *
 * @param[in] result error code of last operation
 * @param[in] info pointer to user's file info strucutre
 */
typedef void (*DVDCallback)(int32_t result, DVDFileInfo* info);
typedef void (*DVDCBCallback)(int32_t result, DVDCommandBlock* block);

struct DVDDiskID {
    char game_name[4];
    char company[2];
    uint8_t disk_number;
    uint8_t game_version;
    uint8_t is_streaming;
    uint8_t streaming_buffer_size;
    uint8_t padding[22];
} __attribute__((__packed__));

/*!
 * \typedef struct _dvdcmdblk dvdcmdblk
 *
 *        This structure is used internally to control the requested operation.
 */
struct _DVDCommandBlock {
    DVDCommandBlock* next;
    DVDCommandBlock* prev;
    uint32_t command;
    int32_t state;
    uint32_t offset;
    uint32_t length;
    void* buffer;
    uint32_t current_transfer_size;
    uint32_t transferred_size;
    DVDDiskID* disk_id;
    DVDCBCallback callback;
    void* user_data;
} __attribute__((__packed__));

struct _DVDFileInfo {
    DVDCommandBlock blk;
    uint32_t addr;
    uint32_t len;
    DVDCallback cb;
} __attribute__((packed));

bool DVDOpen(const char* param_1, DVDFileInfo* param_2);
bool DVDClose(DVDFileInfo* fileInfo);
int32_t DVDReadPrio(DVDFileInfo* fileInfo, void* buffer, int length, int offset, int prio);

bool DVDGetCurrentDir(char* outBuf, uint32_t bufSize);
bool DVDChangeDir(const char* path);

typedef struct _DVDDirCursor DVDDirCursor;

struct _DVDDirCursor {
    int32_t dir_idx;
    int32_t file_cursor;
    uint32_t num_entries;  // could be an offset, could be a length
} __attribute__((packed));

typedef struct _DVDDirEntryInfo DVDDirEntryInfo;

struct _DVDDirEntryInfo {
    int32_t curr_entrynum;
    int32_t is_dir;
    char* name;
} __attribute__((packed));

bool DVDOpenDir(const char* path, DVDDirCursor* dirinfo);
/**
 * @brief Fetch the current entry and forward the cursor to the next entry.
 *
 * @param[in|out] cursor The cursor to an opened directory.
 * @param[out] entryInfo The data on the current entry.
 * @returns True if the cursor successfully fetched an entry. False otherwise.
 */
bool DVDReadDir(DVDDirCursor* cursor, _DVDDirEntryInfo* entryInfo);
bool DVDCloseDir(DVDDirCursor*);

#ifdef __cplusplus
}
#endif

#endif  // __DVD_H__