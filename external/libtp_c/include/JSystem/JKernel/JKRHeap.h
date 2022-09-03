#ifndef JKRHEAP_H
#define JKRHEAP_H

#include "../../dolphin/os/OS.h"
#include "../JSupport/JSUList.h"
#include "JKRDisposer.h"
#include "../../addrs.h"

class JKRHeap;
typedef void (*JKRErrorHandler)(void*, uint32_t, int);

class JKRHeap : public JKRDisposer {
public:
    class TState {
    public:
        uint32_t mUsedSize;
        uint32_t mCheckCode;
        uint32_t mBuf;
        uint32_t field_0xc;
        JKRHeap* mHeap;
        uint32_t mId;

    public:
        uint32_t getUsedSize() const { return mUsedSize; }
        uint32_t getCheckCode() const { return mCheckCode; }
        JKRHeap* getHeap() const { return mHeap; }
        uint32_t getId() const { return mId; }
    };

public:
    void setDebugFill(bool debugFill) { mDebugFill = debugFill; }
    bool getDebugFill() const { return mDebugFill; }
    void* getStartAddr() const { return (void*)mStart; }
    void* getEndAddr() const { return (void*)mEnd; }
    uint32_t getSize() const { return mSize; }
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
    uint32_t getHeapSize() { return mSize; }

public:
    /* 0x00 */  // vtable
    /* 0x04 */  // JKRDisposer
    /* 0x18 */ OSMutex mMutex;
    /* 0x30 */ uint8_t* mStart;
    /* 0x34 */ uint8_t* mEnd;
    /* 0x38 */ uint32_t mSize;
    /* 0x3C */ bool mDebugFill;
    /* 0x3D */ bool mCheckMemoryFilled;
    /* 0x3E */ uint8_t mAllocationMode;  // EAllocMode?
    /* 0x3F */ uint8_t mGroupId;
    /* 0x40 */ JSUTree<JKRHeap> mChildTree;
    /* 0x5C */ JSUList<JKRDisposer> mDisposerList;
    /* 0x68 */ bool mErrorFlag;
    /* 0x69 */ bool mInitFlag;
    /* 0x6A */ uint8_t padding_0x6a[2];

public:
    static void setState_uint32_tID_(TState* state, uint32_t id) { state->mId = id; }
    static void setState_uUsedSize_(TState* state, uint32_t usedSize) {
        state->mUsedSize = usedSize;
    }
    static void setState_uint32_tCheckCode_(TState* state, uint32_t checkCode) {
        state->mCheckCode = checkCode;
    }
    static void* getState_buf_(TState* state) { return &state->mBuf; }
    static void* getState_(TState* state) { return getState_buf_(state); }
};

// typedef void* (*JKRHeap__alloc_t)(uint32_t size, int align, JKRHeap* heap);
// #define JKRHeap__alloc ((JKRHeap__alloc_t)JKRHeap__alloc_addr)

// inline void* operator new(uint32_t size) {
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
void* __nw_JKRHeap(uint32_t size, void* heap, int32_t alignment);
/**
 *	@brief Frees memory used in any of the game's vanilla heaps
 *
 *	@param ptr The pointer to the memory to free
 */
void __dl_JKRHeap(void* ptr);
}

#endif /* JKRHEAP_H */
