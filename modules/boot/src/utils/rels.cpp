#include "utils/rels.h"
#include "rels/include/cxx.h"
#include "rels/include/memory.h"
#include "gcn_c/include/dvd.h"
#include "libtp_c/include/dolphin/os/OSCache.h"

extern "C" {
#ifndef WII_PLATFORM
#define resize1_JKRHeap resize__7JKRHeapFPvUlP7JKRHeap
#else
#define resize1_JKRHeap JKRHeap__resize_void
#endif
void resize1_JKRHeap( void* ptr, uint32_t size, void* heap );
}

#ifndef WII_PLATFORM
OSModuleInfo* loadRelFile( const char* file, bool negativeAlignment )
{
    // Try to open the file from the disc
    DVDFileInfo fileInfo;
    if ( !DVDOpen( file, &fileInfo ) )
    {
        return nullptr;
    }

    // Get the length of the file
    uint32_t length = fileInfo.len;

    // Round the length to be in multiples of DVD_READ_SIZE
    length = ( length + DVD_READ_SIZE - 1 ) & ~( DVD_READ_SIZE - 1 );

    // Buffers that DVDReadPrio uses must be aligned to 0x20 bytes
    int32_t alignment;
    if ( !negativeAlignment )
    {
        // Allocate to the front of the heap
        alignment = 0x20;
    }
    else
    {
        // Allocate to the back of the heap
        alignment = -0x20;
    }

    // Allocate bytes for the file
    uint8_t* fileData = new ( alignment ) uint8_t[length];
    DCFlushRange(fileData, length);
    ICInvalidateRange(fileData, length);

    // Read the REL from the disc
    int32_t r = DVDReadPrio( &fileInfo, fileData, length, 0, 2 );
    int32_t result = ( r > 0 ) ? DVD_STATE_END : r;

    // Close the file, as it's no longer needed
    DVDClose( &fileInfo );

    // Make sure the read was successful
    if ( result != DVD_STATE_END )
    {
        delete[] fileData;
        return nullptr;
    }

    // Get the REL's BSS size and allocate memory for it
    OSModuleInfo* relFile = reinterpret_cast<OSModuleInfo*>( fileData );
    uint32_t bssSize = relFile->bssSize;

    // If bssSize is 0, then use an arbitrary size
    if ( bssSize == 0 )
    {
        bssSize = 0x1;
    }
    
    // Handle the alignment for the BSS
    int32_t bssAlignment = relFile->bssAlignment;
    if ( negativeAlignment )
    {
        bssAlignment = -bssAlignment;
    }

    // Allocate the memory to the back of the heap to avoid fragmentation
    uint8_t* bssArea = new ( bssAlignment ) uint8_t[bssSize];

    // Disable interrupts to make sure other REL files do not try to be linked while this one is being linked
    bool enable = OSDisableInterrupts();

    // Link the REL file
    if ( !OSLink( relFile, bssArea ) )
    {
        // Try to unlink to be safe
        OSUnlink( relFile );

        // Restore interrupts
        OSRestoreInterrupts( enable );

        delete[] bssArea;
        delete[] relFile;
        return nullptr;
    }

    // Restore interrupts
    OSRestoreInterrupts( enable );

    // Call the REL's prolog functon
    reinterpret_cast<void ( * )()>( relFile->prologFuncOffset )();

    return relFile;
}

// resize1_JKRHeap = resize__7JKRHeapFPvUlP7JKRHeap
// void resize1_JKRHeap( void* ptr, uint32_t size, void* heap ); // If heap is nullptr, then the function automatically searches for ptr in all heaps
OSModuleInfo* loadRelFileFixed( const char* file, bool negativeAlignment )
{
    // Try to open the file from the disc
    DVDFileInfo fileInfo;
    if ( !DVDOpen( file, &fileInfo ) )
    {
        return nullptr;
    }

    // Allocate 0x60 bytes of memory, as the read size must be in multiples of 0x20 bytes,
    // the BSS area size, the fixed REL size, and the BSS alignment are needed later

    // Allocate to the back of the heap to avoid possible fragmentation
    constexpr uint32_t dataSize = 0x60;
    uint8_t* fileData = new ( -0x20 ) uint8_t[dataSize];
    DCFlushRange(fileData, dataSize);
    ICInvalidateRange(fileData, dataSize);

    // Read the first 0x60 bytes of the file
    int32_t r = DVDReadPrio( &fileInfo, fileData, dataSize, 0, 2 );
    int32_t result = ( r > 0 ) ? DVD_STATE_END : r;

    // Make sure the read was successful
    if ( result != DVD_STATE_END )
    {
        DVDClose( &fileInfo );
        delete[] fileData;
        return nullptr;
    }

    // Get the length of the file
    uint32_t length = fileInfo.len;

    // Round the length to be in multiples of DVD_READ_SIZE
    const uint32_t adjustedLength = ( length + DVD_READ_SIZE - 1 ) & ~( DVD_READ_SIZE - 1 );

    // Increase the fixed REL size to account for the BSS's alignment requirement
    OSModuleInfo* relFile = reinterpret_cast<OSModuleInfo*>( fileData );
    uint32_t fixSize = relFile->fixSize;
    const uint32_t bssAlign = relFile->bssAlignment;

    // Make sure the size is properly aligned
    if ( ( ( fixSize / bssAlign ) * bssAlign ) != fixSize )
    {
        // Align the size
        const uint32_t adjustedFixSize = ( ( -bssAlign & fixSize ) + bssAlign );
        length += adjustedFixSize - fixSize;
        fixSize = adjustedFixSize;
    }

    // Add the BSS size to the length
    const uint32_t bssSize = relFile->bssSize;
    length += bssSize;

    // If the length plus the BSS size is less than the adjusted file size, then use the
    // adjusted length as the size for the allocated memory
    if ( length < adjustedLength )
    {
        length = adjustedLength;
    }

    // Free the 0x60 bytes from earlier
    delete[] fileData;

    // Buffers that DVDReadPrio uses must be aligned to 0x20 bytes
    int32_t alignment;
    if ( !negativeAlignment )
    {
        // Allocate to the front of the heap
        alignment = 0x20;
    }
    else
    {
        // Allocate to the back of the heap
        alignment = -0x20;
    }

    // Allocate memory for the REL and BSS
    fileData = new ( alignment ) uint8_t[length];
    DCFlushRange(fileData, length);
    ICInvalidateRange(fileData, length);

    // Re-assign the relFile variable to the new memory
    relFile = reinterpret_cast<OSModuleInfo*>( fileData );

    // Get the full REL from the disc
    r = DVDReadPrio( &fileInfo, fileData, adjustedLength, 0, 2 );
    result = ( r > 0 ) ? DVD_STATE_END : r;

    // Close the file, as it's no longer needed
    DVDClose( &fileInfo );

    // Make sure the read was successful
    if ( result != DVD_STATE_END )
    {
        delete[] relFile;
        return nullptr;
    }

    // Get the address of the BSS
    void* bssArea = reinterpret_cast<void*>( reinterpret_cast<uint32_t>( fileData ) + fixSize );

    // Disable interrupts to make sure other REL files do not try to be linked while this one is being linked
    bool enable = OSDisableInterrupts();

    // Link the REL file
    if ( !OSLinkFixed( relFile, bssArea ) )
    {
        // Try to unlink to be safe
        OSUnlink( relFile );

        // Restore interrupts
        OSRestoreInterrupts( enable );

        delete[] relFile;
        return nullptr;
    }

    // Restore interrupts
    OSRestoreInterrupts( enable );

    // Resize the allocated memory to remove the space used by the unnecessary relocation data
    resize1_JKRHeap( relFile, fixSize + bssSize, nullptr );

    // Call the REL's prolog functon
    reinterpret_cast<void ( * )()>( relFile->prologFuncOffset )();

    return relFile;
}
#else
// resize1_JKRHeap = JKRHeap::resize(void *, unsigned long, JKRHeap *)
// void resize1_JKRHeap( void* ptr, uint32_t size, void* heap ); // If heap is nullptr, then the function automatically searches for ptr in all heaps
OSModuleInfo* loadRelFile( const char* file, bool negativeAlignment, bool fixedLinking )
{
    // Try to open the file from the disc
    DVDFileInfo fileInfo;
    if ( !DVDOpen( file, &fileInfo ) )
    {
        return nullptr;
    }

    // Get the length of the file
    uint32_t length = fileInfo.len;

    // Round the length to be in multiples of DVD_READ_SIZE
    length = ( length + DVD_READ_SIZE - 1 ) & ~( DVD_READ_SIZE - 1 );

    // Buffers that DVDReadPrio uses must be aligned to 0x20 bytes
    int32_t alignment;
    if ( !negativeAlignment )
    {
        // Allocate to the front of the heap
        alignment = 0x20;
    }
    else
    {
        // Allocate to the back of the heap
        alignment = -0x20;
    }

    // Allocate bytes for the file
    // REL files need to be in MEM1 to function properly, so put it in the Zelda heap
    uint8_t* fileData = new ( alignment, HEAP_ZELDA ) uint8_t[length];
    clear_DC_IC_Cache( fileData, length );

    // Read the REL from the disc
    int32_t r = DVDReadPrio( &fileInfo, fileData, length, 0, 2 );
    int32_t result = ( r > 0 ) ? DVD_STATE_END : r;

    // Close the file, as it's no longer needed
    DVDClose( &fileInfo );

    // Make sure the read was successful
    if ( result != DVD_STATE_END )
    {
        delete[] fileData;
        return nullptr;
    }

    // Get the REL's BSS size and allocate memory for it
    OSModuleInfo* relFile = reinterpret_cast<OSModuleInfo*>( fileData );
    uint32_t bssSize = relFile->bssSize;

    // If bssSize is 0, then use an arbitrary size
    if ( bssSize == 0 )
    {
        bssSize = 0x1;
    }
    
    // Handle the alignment for the BSS
    int32_t bssAlignment = relFile->bssAlignment;
    if ( negativeAlignment )
    {
        bssAlignment = -bssAlignment;
    }

    // Allocate the memory to the back of the heap to avoid fragmentation
    uint8_t* bssArea = new ( bssAlignment ) uint8_t[bssSize];

    // Disable interrupts to make sure other REL files do not try to be linked while this one is being linked
    bool enable = OSDisableInterrupts();

    // Link the REL file
    bool linkSucceeded;
    if ( !fixedLinking )
    {
        linkSucceeded = OSLink( relFile, bssArea );
    }
    else
    {
        linkSucceeded = OSLinkFixed( relFile, bssArea );
    }

    if ( !linkSucceeded )
    {
        // Try to unlink to be safe
        OSUnlink( relFile );

        // Restore interrupts
        OSRestoreInterrupts( enable );

        delete[] bssArea;
        delete[] relFile;
        return nullptr;
    }

    // Restore interrupts
    OSRestoreInterrupts( enable );

    if ( fixedLinking )
    {
        // Resize the allocated memory to remove the space used by the unnecessary relocation data
        uint32_t fixedSize = relFile->fixSize + (uintptr_t)relFile;
        resize1_JKRHeap( relFile, fixedSize, nullptr );
    }

    // Call the REL's prolog functon
    reinterpret_cast<void ( * )()>( relFile->prologFuncOffset )();

    return relFile;
}
#endif

// Pass in nullptr for bss if using fixed linking
bool closeRelFile( OSModuleInfo* relFile, void* bss )
{
    // Make sure a proper pointer for relFile was passed in
    if ( !relFile )
    {
        return false;
    }

    // Call the REL's epilog function to perform any necessary exit code
    reinterpret_cast<void ( * )()>( relFile->epilogFuncOffset )();

    // Disable interrupts to make sure other REL files do not try to be linked while this one is being unlinked
    bool enable = OSDisableInterrupts();

    // All REL functions are done, so the file can be unlinked
    OSUnlink( relFile );

    // Restore interrupts
    OSRestoreInterrupts( enable );

    // TODO Find where to get the `length` to flush and invalidate
    // Clear the cache of the memory used by the REL file since assembly ran from it
    //DCFlushRange(relFile, length);
    //ICInvalidateRange(relFile, length);

    // Cleanup
    delete[] relFile;

    // If the REL was linked via fixed linking, then bss should be nullptr
    if ( bss )
    {
        delete[] (char*)bss;
    }

    return true;
}
