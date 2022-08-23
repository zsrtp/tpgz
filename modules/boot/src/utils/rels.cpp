#include "utils/rels.h"
#include <cstring>
#include "rels/include/cxx.h"
#include "rels/include/memory.h"
#include "gcn_c/include/dvd.h"
#include "libtp_c/include/dolphin/os/OSCache.h"

extern "C" {
#ifndef WII_PLATFORM
#define resize1_JKRHeap resize__7JKRHeapFPvUlP7JKRHeap
#else
#define resize1_JKRHeap JKRHeap__resize_void____unsigned_long__JKRHeap___
#endif
void resize1_JKRHeap(void* ptr, uint32_t size, void* heap);
}

namespace tpgz::dyn {

GZModule::GZModule(const char* path) {
    strncpy(m_path, path, sizeof(m_path));
}
GZModule::~GZModule() {
    if (m_loaded) {
        close();
    }
}

#ifndef WII_PLATFORM
bool GZModule::load(bool negativeAlignment) {
    if (m_loaded) {
        return true;
    }

    // Try to open the file from the disc
    DVDFileInfo fileInfo;
    if (!DVDOpen(m_path, &fileInfo)) {
        return false;
    }

    // Get the length of the file
    uint32_t length = fileInfo.len;

    // Round the length to be in multiples of DVD_READ_SIZE
    length = (length + DVD_READ_SIZE - 1) & ~(DVD_READ_SIZE - 1);

    // Buffers that DVDReadPrio uses must be aligned to 0x20 bytes
    int32_t alignment;
    if (!negativeAlignment) {
        // Allocate to the front of the heap
        alignment = 0x20;
    } else {
        // Allocate to the back of the heap
        alignment = -0x20;
    }

    // Allocate bytes for the file
    uint8_t* fileData = new (alignment) uint8_t[length];
    clear_DC_IC_Cache(fileData, length);

    // Read the REL from the disc
    int32_t r = DVDReadPrio(&fileInfo, fileData, length, 0, 2);
    int32_t result = (r > 0) ? DVD_STATE_END : r;

    // Close the file, as it's no longer needed
    DVDClose(&fileInfo);

    // Make sure the read was successful
    if (result != DVD_STATE_END) {
        delete[] fileData;
        return false;
    }

    // Get the REL's BSS size and allocate memory for it
    OSModuleInfo* relFile = reinterpret_cast<OSModuleInfo*>(fileData);
    uint32_t bssSize = relFile->bssSize;

    // If bssSize is 0, then use an arbitrary size
    if (bssSize == 0) {
        bssSize = 0x1;
    }

    // Handle the alignment for the BSS
    int32_t bssAlignment = relFile->bssAlignment;
    if (negativeAlignment) {
        bssAlignment = -bssAlignment;
    }

    // Allocate the memory to the back of the heap to avoid fragmentation
    uint8_t* bssArea = new (bssAlignment) uint8_t[bssSize];

    // Disable interrupts to make sure other REL files do not try to be linked while this one is
    // being linked
    bool enable = OSDisableInterrupts();

    // Link the REL file
    if (!OSLink(relFile, bssArea)) {
        // Try to unlink to be safe
        OSUnlink(relFile);

        // Restore interrupts
        OSRestoreInterrupts(enable);

        delete[] bssArea;
        delete[] relFile;
        return false;
    }

    // Restore interrupts
    OSRestoreInterrupts(enable);

    // Call the REL's prolog functon
    reinterpret_cast<void (*)()>(relFile->prologFuncOffset)();

    m_rel = relFile;
    m_bss = bssArea;
    m_length = length;
    m_loaded = true;
    return true;
}

bool GZModule::loadFixed(bool negativeAlignment) {
    if (m_loaded) {
        return true;
    }

    // Try to open the file from the disc
    DVDFileInfo fileInfo;
    if (!DVDOpen(m_path, &fileInfo)) {
        return false;
    }

    // Allocate 0x60 bytes of memory, as the read size must be in multiples of 0x20 bytes,
    // the BSS area size, the fixed REL size, and the BSS alignment are needed later

    // Allocate to the back of the heap to avoid possible fragmentation
    constexpr uint32_t dataSize = 0x60;
    uint8_t* fileData = new (-0x20) uint8_t[dataSize];
    clear_DC_IC_Cache(fileData, dataSize);

    // Read the first 0x60 bytes of the file
    int32_t r = DVDReadPrio(&fileInfo, fileData, dataSize, 0, 2);
    int32_t result = (r > 0) ? DVD_STATE_END : r;

    // Make sure the read was successful
    if (result != DVD_STATE_END) {
        DVDClose(&fileInfo);
        delete[] fileData;
        return false;
    }

    // Get the length of the file
    uint32_t length = fileInfo.len;

    // Round the length to be in multiples of DVD_READ_SIZE
    const uint32_t adjustedLength = (length + DVD_READ_SIZE - 1) & ~(DVD_READ_SIZE - 1);

    // Increase the fixed REL size to account for the BSS's alignment requirement
    OSModuleInfo* relFile = reinterpret_cast<OSModuleInfo*>(fileData);
    uint32_t fixSize = relFile->fixSize;
    const uint32_t bssAlign = relFile->bssAlignment;

    // Make sure the size is properly aligned
    if (((fixSize / bssAlign) * bssAlign) != fixSize) {
        // Align the size
        const uint32_t adjustedFixSize = ((-bssAlign & fixSize) + bssAlign);
        length += adjustedFixSize - fixSize;
        fixSize = adjustedFixSize;
    }

    // Add the BSS size to the length
    const uint32_t bssSize = relFile->bssSize;
    length += bssSize;

    // If the length plus the BSS size is less than the adjusted file size, then use the
    // adjusted length as the size for the allocated memory
    if (length < adjustedLength) {
        length = adjustedLength;
    }

    // Free the 0x60 bytes from earlier
    delete[] fileData;

    // Buffers that DVDReadPrio uses must be aligned to 0x20 bytes
    int32_t alignment;
    if (!negativeAlignment) {
        // Allocate to the front of the heap
        alignment = 0x20;
    } else {
        // Allocate to the back of the heap
        alignment = -0x20;
    }

    // Allocate memory for the REL and BSS
    fileData = new (alignment) uint8_t[length];
    clear_DC_IC_Cache(fileData, length);

    // Re-assign the relFile variable to the new memory
    relFile = reinterpret_cast<OSModuleInfo*>(fileData);

    // Get the full REL from the disc
    r = DVDReadPrio(&fileInfo, fileData, adjustedLength, 0, 2);
    result = (r > 0) ? DVD_STATE_END : r;

    // Close the file, as it's no longer needed
    DVDClose(&fileInfo);

    // Make sure the read was successful
    if (result != DVD_STATE_END) {
        delete[] relFile;
        return false;
    }

    // Get the address of the BSS
    void* bssArea = reinterpret_cast<void*>(reinterpret_cast<uint32_t>(fileData) + fixSize);

    // Disable interrupts to make sure other REL files do not try to be linked while this one is
    // being linked
    bool enable = OSDisableInterrupts();

    // Link the REL file
    if (!OSLinkFixed(relFile, bssArea)) {
        // Try to unlink to be safe
        OSUnlink(relFile);

        // Restore interrupts
        OSRestoreInterrupts(enable);

        delete[] relFile;
        return false;
    }

    // Restore interrupts
    OSRestoreInterrupts(enable);

    // Resize the allocated memory to remove the space used by the unnecessary relocation data
    resize1_JKRHeap(relFile, fixSize + bssSize, nullptr);

    // Call the REL's prolog functon
    reinterpret_cast<void (*)()>(relFile->prologFuncOffset)();

    m_rel = relFile;
    m_bss = nullptr;
    m_length = fixSize + bssSize;
    m_loaded = true;
    return true;
}
#else
bool GZModule::load(bool negativeAlignment, bool fixedLinking) {
    if (m_loaded) {
        return true;
    }

    // Try to open the file from the disc
    DVDFileInfo fileInfo;
    if (!DVDOpen(m_path, &fileInfo)) {
        return false;
    }

    // Get the length of the file
    uint32_t length = fileInfo.len;

    // Round the length to be in multiples of DVD_READ_SIZE
    length = (length + DVD_READ_SIZE - 1) & ~(DVD_READ_SIZE - 1);

    // Buffers that DVDReadPrio uses must be aligned to 0x20 bytes
    int32_t alignment;
    if (!negativeAlignment) {
        // Allocate to the front of the heap
        alignment = 0x20;
    } else {
        // Allocate to the back of the heap
        alignment = -0x20;
    }

    // Allocate bytes for the file
    // REL files need to be in MEM1 to function properly, so put it in the Zelda heap
    uint8_t* fileData = new (alignment) uint8_t[length];
    clear_DC_IC_Cache(fileData, length);

    // Read the REL from the disc
    int32_t r = DVDReadPrio(&fileInfo, fileData, length, 0, 2);
    int32_t result = (r > 0) ? DVD_STATE_END : r;

    // Close the file, as it's no longer needed
    DVDClose(&fileInfo);

    // Make sure the read was successful
    if (result != DVD_STATE_END) {
        delete[] fileData;
        return false;
    }

    // Get the REL's BSS size and allocate memory for it
    OSModuleInfo* relFile = reinterpret_cast<OSModuleInfo*>(fileData);
    uint32_t bssSize = relFile->bssSize;

    // If bssSize is 0, then use an arbitrary size
    if (bssSize == 0) {
        bssSize = 0x1;
    }

    // Handle the alignment for the BSS
    int32_t bssAlignment = relFile->bssAlignment;
    if (negativeAlignment) {
        bssAlignment = -bssAlignment;
    }

    // Allocate the memory to the back of the heap to avoid fragmentation
    uint8_t* bssArea = new (bssAlignment) uint8_t[bssSize];

    // Disable interrupts to make sure other REL files do not try to be linked while this one is
    // being linked
    bool enable = OSDisableInterrupts();

    // Link the REL file
    bool linkSucceeded;
    if (!fixedLinking) {
        linkSucceeded = OSLink(relFile, bssArea);
    } else {
        linkSucceeded = OSLinkFixed(relFile, bssArea);
    }

    if (!linkSucceeded) {
        // Try to unlink to be safe
        OSUnlink(relFile);

        // Restore interrupts
        OSRestoreInterrupts(enable);

        delete[] bssArea;
        delete[] relFile;
        return false;
    }

    // Restore interrupts
    OSRestoreInterrupts(enable);

    if (fixedLinking) {
        // Resize the allocated memory to remove the space used by the unnecessary relocation data.
        // relFile->fixSize becomes a pointer.
        uint32_t fixedSize = relFile->fixSize - (uint32_t)relFile;
        resize1_JKRHeap(relFile, fixedSize, nullptr);
        length = fixedSize;
    }

    // Call the REL's prolog functon
    reinterpret_cast<void (*)()>(relFile->prologFuncOffset)();

    m_rel = relFile;
    m_bss = bssArea;
    m_length = length;
    m_loaded = true;
    return true;
}
bool GZModule::load(bool negativeAlignment) {
    return load(negativeAlignment, false);
}
bool GZModule::loadFixed(bool negativeAlignment) {
    return load(negativeAlignment, true);
}
#endif

bool GZModule::close() {
    if (!m_loaded) {
        return true;
    }

    auto relFile = m_rel;
    auto bss = m_bss;
    auto length = m_length;

    // Make sure a proper pointer for relFile was passed in
    if (!relFile) {
        return false;
    }

    // Call the REL's epilog function to perform any necessary exit code
    reinterpret_cast<void (*)()>(relFile->epilogFuncOffset)();

    // Disable interrupts to make sure other REL files do not try to be linked while this one is
    // being unlinked
    bool enable = OSDisableInterrupts();

    // All REL functions are done, so the file can be unlinked
    OSUnlink(relFile);

    // Restore interrupts
    OSRestoreInterrupts(enable);

    // Clear the cache of the memory used by the REL file since assembly ran from it
    clear_DC_IC_Cache(relFile, length);

    // Cleanup
    delete[] relFile;

    // If the REL was linked via fixed linking, then bss should be nullptr
    if (bss) {
        delete[](char*) bss;
    }

    m_loaded = false;
    return true;
}

bool GZModule::isLoaded() {
    return m_loaded;
}

const char* GZModule::getPath() const {
    return m_path;
}

}  // namespace tpgz::dyn
