#ifndef JKREXPHEAP_H
#define JKREXPHEAP_H

#include "JKRHeap.h"
#include "../../defines.h"

class JKRExpHeap : public JKRHeap {
public:
    class CMemBlock {
        friend class JKRExpHeap;

    public:
        void newGroupId(u8 groupId) { this->mGroupId = groupId; }
        // bool isValid() const { return this->mMagic == 'HM'; }
        bool _isTempMemBlock() const { return (this->mFlags & 0x80) ? true : false; }
        int getAlignment() const { return this->mFlags & 0x7f; }
        void* getContent() const { return (void*)(this + 1); }
        CMemBlock* getPrevBlock() const { return this->mPrev; }
        CMemBlock* getNextBlock() const { return this->mNext; }
        u32 getSize() const { return this->size; }
        u8 getGroupId() const { return this->mGroupId; }
        static CMemBlock* getBlock(void* data) { return (CMemBlock*)((u32)data + -0x10); }

    private:
        u16 mMagic;
        u8 mFlags;  // a|bbbbbbb a=temporary b=alignment
        u8 mGroupId;
        u32 size;
        CMemBlock* mPrev;
        CMemBlock* mNext;
    };
    friend class CMemBlock;

public:
    CMemBlock* getHeadUsedList() const { return mHeadUsedList; }

    u8 field_0x6c;
    u8 mCurrentGroupId;
    bool field_0x6e;
    void* field_0x70;
    u32 field_0x74;
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
void* do_alloc_JKRExpHeap(void* heap, u32 size, s32 alignment);

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
                  s32, JKRExpHeap__getUsedSize, (u8))

LIBTP_DEFINE_FUNC(getFreeSize__7JKRHeapFv, JKRHeap__getFreeSize_void_,
                  s32, JKRHeap__getFreeSize, (JKRHeap* addr))

LIBTP_DEFINE_FUNC(getTotalFreeSize__7JKRHeapFv, JKRHeap__getTotalFreeSize_void_,
                  s32, JKRHeap__getTotalFreeSize, (JKRHeap* addr))

LIBTP_DEFINE_FUNC(do_getTotalFreeSize__10JKRExpHeapFv, JKRExpHeap__do_getTotalFreeSize_void_,
                  s32, JKRExpHeap__do_getTotalFreeSize, (JKRExpHeap* addr))

#endif /* JKREXPHEAP_H */
