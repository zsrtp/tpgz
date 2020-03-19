#include "fs.h"
#include "save_injector.h"
#include "log.h"

typedef struct {
    uint8_t quest_log[0xABC];
} DVDFile;

extern "C" bool DVDOpen(const char* fileName, DVDFile* fileInfo);
extern "C" int DVDReadPrio(DVDFile* fileInfo, void* buffer, int length, int offset, int prio);
extern "C" bool DVDClose(DVDFile* fileInfo);

void loadFile(const char* filePath) {
    Log log;
    DVDFile fileInfo;
    if (DVDOpen(filePath, &fileInfo)) {
        int bytesRead = DVDReadPrio(&fileInfo, &practice_file.qlog_bytes, 2720, 0, 2);
        if (bytesRead > 0) {
            DVDClose(&fileInfo);
            log.PrintLog("bytes read - %d", bytesRead, DEBUG);
        }
    }
}

void loadFile(const char* filePath, FileReadCallback callback) {
    Log log;
    DVDFile fileInfo;
    if (DVDOpen(filePath, &fileInfo)) {
        int bytesRead = DVDReadPrio(&fileInfo, &practice_file.qlog_bytes, 2720, 0, 2);
        if (bytesRead > 0) {
            DVDClose(&fileInfo);
            log.PrintLog("bytes read - %d", bytesRead, DEBUG);
            callback(practice_file.qlog_bytes, bytesRead);
        } else {
            callback(nullptr,bytesRead);
        }
    }
}