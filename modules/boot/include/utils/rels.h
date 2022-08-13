#include "libtp_c/include/dolphin/os/OS.h"

bool loadRelFile( const char* file, bool negativeAlignment );
bool loadRelFileFixed( const char* file, bool negativeAlignment );
bool closeRelFile( OSModuleInfo* relFile, void* bss );
