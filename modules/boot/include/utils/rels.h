#include "libtp_c/include/dolphin/os/OS.h"

typedef struct GZModule {
    OSModuleInfo* rel;
    void* bss;
    uint32_t length;
} GZModule;

GZModule loadRelFile(const char* file, bool negativeAlignment, bool fixedLinking);
bool closeRelFile(GZModule relFile);
