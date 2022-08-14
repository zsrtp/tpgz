#include "libtp_c/include/dolphin/os/OS.h"

#ifndef WII_PLATFORM
OSModuleInfo* loadRelFile( const char* file, bool negativeAlignment );
OSModuleInfo* loadRelFileFixed( const char* file, bool negativeAlignment );
#else
OSModuleInfo* loadRelFile( const char* file, bool negativeAlignment, bool fixedLinking );
#endif
bool closeRelFile( OSModuleInfo* relFile, void* bss );
