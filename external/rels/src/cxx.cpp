/**	@file cxx.h
 *	@brief Custom override of (de)allocation onto specific heaps.
 *
 *  @author Zephiles
 *	@bug No known bugs.
 */
#include "cxx.h"

#include <cstdint>
#include <cstring>

#include "libtp_c/include/JSystem/JKernel/JKRExpHeap.h"
#include "libtp_c/include/dynamic_link.h"
#include "libtp_c/include/m_Do/m_Do_ext.h"

void* getHeapPtr( int32_t id )
{
    static JKRHeap** heapPtrArray[] = {
        &m_Do_ext::AssertHeap,
        &m_Do_ext::DbPrintHeap,
        &m_Do_ext::gameHeap,
        &m_Do_ext::zeldaHeap,
        &m_Do_ext::commandHeap,
        &m_Do_ext::archiveHeap,
        &m_Do_ext::j2dHeap,

#ifndef WII_PLATFORM
        &m_Do_ext::HostIOHeap,
#else
        &DynamicModuleControlBase::m_heap,
#endif     // WII_PLATFORM

    };

    // Make sure the id is valid
    constexpr uint32_t heapPtrArraySize = sizeof( heapPtrArray ) / sizeof( heapPtrArray[0] );
    if ( ( id < 0 ) || ( static_cast<uint32_t>( id ) >= heapPtrArraySize ) )
    {
        // The id is invalid, so use the archive heap by default
#ifndef WII_PLATFORM
        id = HEAP_ARCHIVE;
#else
        id = HEAP_ZELDA;
#endif
    }

    return *heapPtrArray[id];
}

void* operator new( std::size_t size )
{
    void* archiveHeapPtr = m_Do_ext::archiveHeap;
    void* newPtr = do_alloc_JKRExpHeap( archiveHeapPtr, size, 0x20 );
    return memset( newPtr, 0, size );
}
void* operator new[]( std::size_t size )
{
    void* archiveHeapPtr = m_Do_ext::archiveHeap;
    void* newPtr = do_alloc_JKRExpHeap( archiveHeapPtr, size, 0x20 );
    return memset( newPtr, 0, size );
}
void* operator new( std::size_t size, int32_t alignment )
{
    void* archiveHeapPtr = m_Do_ext::archiveHeap;
    void* newPtr = do_alloc_JKRExpHeap( archiveHeapPtr, size, alignment );
    return memset( newPtr, 0, size );
}
void* operator new[]( std::size_t size, int32_t alignment )
{
    void* archiveHeapPtr = m_Do_ext::archiveHeap;
    void* newPtr = do_alloc_JKRExpHeap( archiveHeapPtr, size, alignment );
    return memset( newPtr, 0, size );
}
void operator delete( void* ptr )
{
    void* archiveHeapPtr = m_Do_ext::archiveHeap;
    return do_free_JKRExpHeap( archiveHeapPtr, ptr );
}
void operator delete[]( void* ptr )
{
    void* archiveHeapPtr = m_Do_ext::archiveHeap;
    return do_free_JKRExpHeap( archiveHeapPtr, ptr );
}
void operator delete( void* ptr, std::size_t size )
{
    void* archiveHeapPtr = m_Do_ext::archiveHeap;
    return do_free_JKRExpHeap( archiveHeapPtr, ptr );
}
void operator delete[]( void* ptr, std::size_t size )
{
    void* archiveHeapPtr = m_Do_ext::archiveHeap;
    return do_free_JKRExpHeap( archiveHeapPtr, ptr );
}

void* operator new( size_t size, int32_t alignment, int32_t id )
{
    void* heapPtr = getHeapPtr( id );
    void* newPtr = do_alloc_JKRExpHeap( heapPtr, size, alignment );
    return memset( newPtr, 0, size );
}

void* operator new[]( size_t size, int32_t alignment, int32_t id )
{
    void* heapPtr = getHeapPtr( id );
    void* newPtr = do_alloc_JKRExpHeap( heapPtr, size, alignment );
    return memset( newPtr, 0, size );
}

// Cannot used overloaded delete operator, so must use a generic function
void freeFromHeap( int32_t id, void* ptr )
{
    void* heapPtr = getHeapPtr( id );
    return do_free_JKRExpHeap( heapPtr, ptr );
}
