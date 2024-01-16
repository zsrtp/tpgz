#ifndef JKRHEAP_H
#define JKRHEAP_H

#include "../../dolphin/os/OS.h"
#include "../JSupport/JSUList.h"
#include "JKRDisposer.h"
#include "../../addrs.h"

class JKRHeap;
typedef void (*JKRErrorHandler)(void*, u32, int);

class JKRHeap : public JKRDisposer {
public:
    class TState {
    public:
        u32 mUsedSize;
        u32 mCheckCode;
        u32 mBuf;
        u32 field_0xc;
        JKRHeap* mHeap;
        u32 mId;

    public:
        u32 getUsedSize() const { return mUsedSize; }
        u32 getCheckCode() const { return mCheckCode; }
        JKRHeap* getHeap() const { return mHeap; }
        u32 getId() const { return mId; }
    };

public:
    void setDebugFill(bool debugFill) { mDebugFill = debugFill; }
    bool getDebugFill() const { return mDebugFill; }
    void* getStartAddr() const { return (void*)mStart; }
    void* getEndAddr() const { return (void*)mEnd; }
    u32 getSize() const { return mSize; }
    bool getErrorFlag() const { return mErrorFlag; }

    JKRHeap* getParent() const {
        JSUTree<JKRHeap>* parent = mChildTree.getParent();
        return parent->getObject();
    }

    JSUTree<JKRHeap>& getHeapTree() { return mChildTree; }
    // void appendDisposer(JKRDisposer* disposer) { mDisposerList.append(&disposer->mLink); }
    // void removeDisposer(JKRDisposer* disposer) { mDisposerList.remove(&disposer->mLink); }
    // void lock() { OSLockMutex(&mMutex); }
    // void unlock() { OSUnlockMutex(&mMutex); }
    u32 getHeapSize() { return mSize; }

public:
    /* 0x00 */  // vtable
    /* 0x04 */  // JKRDisposer
    /* 0x18 */ OSMutex mMutex;
    /* 0x30 */ u8* mStart;
    /* 0x34 */ u8* mEnd;
    /* 0x38 */ u32 mSize;
    /* 0x3C */ bool mDebugFill;
    /* 0x3D */ bool mCheckMemoryFilled;
    /* 0x3E */ u8 mAllocationMode;  // EAllocMode?
    /* 0x3F */ u8 mGroupId;
    /* 0x40 */ JSUTree<JKRHeap> mChildTree;
    /* 0x5C */ JSUList<JKRDisposer> mDisposerList;
    /* 0x68 */ bool mErrorFlag;
    /* 0x69 */ bool mInitFlag;
    /* 0x6A */ u8 padding_0x6a[2];

public:
    static void setState_uint32_tID_(TState* state, u32 id) { state->mId = id; }
    static void setState_uUsedSize_(TState* state, u32 usedSize) {
        state->mUsedSize = usedSize;
    }
    static void setState_uint32_tCheckCode_(TState* state, u32 checkCode) {
        state->mCheckCode = checkCode;
    }
    static void* getState_buf_(TState* state) { return &state->mBuf; }
    static void* getState_(TState* state) { return getState_buf_(state); }
};

// typedef void* (*JKRHeap__alloc_t)(u32 size, int align, JKRHeap* heap);
// #define JKRHeap__alloc ((JKRHeap__alloc_t)JKRHeap__alloc_addr)

// inline void* operator new(u32 size) {
//     return JKRHeap__alloc(size, 4, NULL);
// }

extern "C" {
/**
 *	@brief Allocates a number of bytes in a given heap
 *
 *	@param size The number of bytes to be allocated
 *	@param heap The heap pointer
 *	@param alignment The alignment to use for the address of the allocated memory
 */
void* __nw_JKRHeap(u32 size, void* heap, s32 alignment);
/**
 *	@brief Frees memory used in any of the game's vanilla heaps
 *
 *	@param ptr The pointer to the memory to free
 */
void __dl_JKRHeap(void* ptr);
}

#endif /* JKRHEAP_H */
