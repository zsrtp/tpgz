#include "fs.h"
#include "font.h"
#include "gcn_c/include/dvd.h"
#include "libtp_c/include/system.h"
#include "save_injector.h"

void loadFile(const char* filePath, void* buffer, signed long length, signed long offset) {
    DVDFileInfo fileInfo;
    if (DVDOpen(filePath, &fileInfo)) {
        int bytesRead = DVDReadPrio(&fileInfo, buffer, length, offset, 2);
        if (bytesRead > 0) {
            DVDClose(&fileInfo);
        } else {
            tp_osReport("no bytes read!");
        }
    } else {
        tp_osReport("failed to open file %s", filePath);
    }
}