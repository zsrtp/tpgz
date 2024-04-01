#ifndef OSCACHE_H
#define OSCACHE_H

#include "../types.h"

extern "C" {
// DCEnable
// DCInvalidateRange
void DCFlushRange(void* startAddr, u32 nBytes);
// DCStoreRange
// DCFlushRangeNoSync
void DCStoreRangeNoSync(void* start, u32 nBytes);
// DCZeroRange
void ICInvalidateRange(void* startAddr, u32 nBytes);
// ICFlashInvalidate
// ICEnable
// __LCEnable
// LCEnable
// LCDisable
// LCStoreBlocks
// LCStoreData
// LCQueueWait
// L2GlobalInvalidate
// DMAErrorHandler
// __OSCacheInit
}

#endif /* OSCACHE_H */
