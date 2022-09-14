#ifndef JKRARCHIVE_H_
#define JKRARCHIVE_H_

#include "../../addrs.h"
#include "JKRFileLoader.h"
#include <stdint.h>

class JKRHeap;
class JKRDvdFile;
class SArcDataInfo;
class SDirEntry;
class SDIFileEntry;

class JKRArchive : public JKRFileLoader {
public:
    enum EMountMode {
        UNKNOWN_MOUNT_MODE = 0,
        MOUNT_MEM = 1,
        MOUNT_ARAM = 2,
        MOUNT_DVD = 3,
        MOUNT_COMP = 4,
    };

    enum EMountDirection {
        UNKNOWN_MOUNT_DIRECTION = 0,
        MOUNT_DIRECTION_HEAD = 1,
        MOUNT_DIRECTION_TAIL = 2,
    };

    class CArcName {
    public:
        CArcName() {}

        uint16_t getHash() const { return mHash; }

        const char* getString() const { return mData; }

    private:
        uint16_t mHash;
        uint16_t mLength;
        char mData[256];
    };

protected:
    JKRArchive();
    JKRArchive(long, EMountMode);
    virtual ~JKRArchive();

public:
    uint32_t getMountMode() const { return mMountMode; }

protected:
    /* 0x00 */  // vtable
    /* 0x04 */  // JKRFileLoader
    /* 0x38 */ JKRHeap* mHeap;
    /* 0x3C */ uint8_t mMountMode;
    /* 0x3D */ uint8_t field_0x3d[3];
    /* 0x40 */ int32_t mEntryNum;
    /* 0x44 */ SArcDataInfo* mArcInfoBlock;
    /* 0x48 */ SDirEntry* mNodes;
    /* 0x4C */ SDIFileEntry* mFiles;
    /* 0x50 */ int32_t* mExpandedSize;
    /* 0x54 */ char* mStringTable;
    /* 0x58 */ uint32_t field_0x58;
};

typedef void* (*JKernel__operator_new_t)(uint32_t size);
#define JKernel__operator_new ((JKernel__operator_new_t)JKernel__operator_new_addr)

typedef void (*JKernel__operator_delete_t)(void*);
#define JKernel__operator_delete ((JKernel__operator_delete_t)JKernel__operator_delete_addr)

typedef void* (*JKRArchive__getResource2_t)(void* addr, uint32_t resType, const char* filename);
#define JKRArchive__getResource2 ((JKRArchive__getResource2_t)JKRArchive__getResource2_addr)

#endif