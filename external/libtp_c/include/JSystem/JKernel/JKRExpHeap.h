#ifndef JKREXPHEAP_H
#define JKREXPHEAP_H

#include "JKRHeap.h"
#include "../../defines.h"

class JKRExpHeap : public JKRHeap {
public:
    class CMemBlock {
        friend class JKRExpHeap;

    public:
        void newGroupId(uint8_t groupId) { this->mGroupId = groupId; }
        // bool isValid() const { return this->mMagic == 'HM'; }
        bool _isTempMemBlock() const { return (this->mFlags & 0x80) ? true : false; }
        int getAlignment() const { return this->mFlags & 0x7f; }
        void* getContent() const { return (void*)(this + 1); }
        CMemBlock* getPrevBlock() const { return this->mPrev; }
        CMemBlock* getNextBlock() const { return this->mNext; }
        uint32_t getSize() const { return this->size; }
        uint8_t getGroupId() const { return this->mGroupId; }
        static CMemBlock* getBlock(void* data) { return (CMemBlock*)((uint32_t)data + -0x10); }

    private:
        uint16_t mMagic;
        uint8_t mFlags;  // a|bbbbbbb a=temporary b=alignment
        uint8_t mGroupId;
        uint32_t size;
        CMemBlock* mPrev;
        CMemBlock* mNext;
    };
    friend class CMemBlock;

public:
    CMemBlock* getHeadUsedList() const { return mHeadUsedList; }

    uint8_t field_0x6c;
    uint8_t mCurrentGroupId;
    bool field_0x6e;
    void* field_0x70;
    uint32_t field_0x74;
    CMemBlock* mHeadFreeList;
    CMemBlock* mTailFreeList;
    CMemBlock* mHeadUsedList;
    CMemBlock* mTailUsedList;
};

extern "C" {
extern JKRHeap* AssertHeap;
extern JKRHeap* DbPrintHeap;
extern JKRHeap* gameHeap;
extern JKRHeap* zeldaHeap;
extern JKRHeap* commandHeap;
extern JKRHeap* archiveHeap;  // Archive heap pointer
extern JKRHeap* j2dHeap;

#ifndef WII_PLATFORM
extern JKRHeap* HostIOHeap;
#endif  // WII_PLATFORM
}

extern "C" {
/**
 *	@brief Allocates a number of bytes in a given heap
 *
 *	@param heap The heap pointer
 *	@param size The number of bytes to be allocated
 *	@param alignment The amount of bytes that the address of the memory should be aligned to.
 *Negative values will allocate from the tail of the heap instead of the head.
 */
void* do_alloc_JKRExpHeap(void* heap, uint32_t size, int32_t alignment);

/**
 *	@brief Frees a number of bytes in a given heap
 *
 *	@param heap The heap pointer
 *	@param size The number of bytes to be freed
 */
void do_free_JKRExpHeap(void* heap, void* ptr);
}

// TODO Change hardcoded addresses to names linked through .lst files.
// #define zeldaHeap (*(JKRExpHeap**)(tp_zeldaHeap_addr))
// #define gameHeap (*(JKRExpHeap**)(tp_gameHeap_addr))
// #define archiveHeap (*(JKRExpHeap**)(tp_archiveHeap_addr))

LIBTP_DEFINE_FUNC(getUsedSize__10JKRExpHeapCFUc, JKRExpHeap__getUsedSize_unsigned,
                  int32_t, JKRExpHeap__getUsedSize, (uint8_t))

LIBTP_DEFINE_FUNC(getFreeSize__7JKRHeapFv, JKRHeap__getFreeSize_void_,
                  int32_t, JKRHeap__getFreeSize, (JKRHeap* addr))

LIBTP_DEFINE_FUNC(getTotalFreeSize__7JKRHeapFv, JKRHeap__getTotalFreeSize_void_,
                  int32_t, JKRHeap__getTotalFreeSize, (JKRHeap* addr))

LIBTP_DEFINE_FUNC(do_getTotalFreeSize__10JKRExpHeapFv, JKRExpHeap__do_getTotalFreeSize_void_,
                  int32_t, JKRExpHeap__do_getTotalFreeSize, (JKRExpHeap* addr))

#endif /* JKREXPHEAP_H */
