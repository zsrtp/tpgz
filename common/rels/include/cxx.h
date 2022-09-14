/**	@file cxx.h
 *	@brief Custom override of (de)allocation onto specific heaps.
 *
 *	@author Zephiles
 *	@author kipcode66
 *	@bug No known bugs.
 */
#ifndef LIBTP_CXX_H
#define LIBTP_CXX_H

#include <cstdint>
#include <new>

enum HeapID : int32_t {
    HEAP_ASSERT = 0,
    HEAP_DBPRINT,
    HEAP_GAME,
    HEAP_ZELDA,

#ifdef PLATFORM_WII
    // Cannot properly allocate from the command heap on GC
    HEAP_COMMAND,
#endif

    HEAP_ARCHIVE,
    HEAP_J2D,

#ifndef PLATFORM_WII
    HEAP_HOST_IO,
#else
    HEAP_DYNAMIC_LINK,
#endif
};

void* operator new(std::size_t size);
void* operator new[](std::size_t size);
void* operator new(std::size_t size, int32_t alignment);
void* operator new[](std::size_t size, int32_t alignment);
void* operator new(std::size_t size, int32_t alignment, int32_t heapId);
void* operator new[](std::size_t size, int32_t alignment, int32_t heapId);
void operator delete(void* ptr);
void operator delete[](void* ptr);
void operator delete(void* ptr, std::size_t size);
void operator delete[](void* ptr, std::size_t size);

#endif  // LIBTP_CXX_H