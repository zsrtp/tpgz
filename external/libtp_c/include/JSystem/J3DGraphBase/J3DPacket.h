#ifndef J3DPACKET_H
#define J3DPACKET_H

#include "../../dolphin/mtx/mtx.h"
#include "../../dolphin/types.h"
#include <cstddef>

class J3DMatPacket;
class J3DDrawBuffer;
class J3DMaterial;
class J3DMaterialAnm;
class J3DModel;
class J3DMtxBuffer;
class J3DShape;
class J3DTexMtx;
class J3DTexture;
class J3DPacket;

class J3DDrawBuffer {
public:
    J3DPacket** mpBuf;
    u32 mBufSize;
    u32 mDrawType;
    u32 mSortType;
    f32 mZNear;
    f32 mZFar;
    f32 mZRatio;
    Mtx* mpZMtx;
    J3DPacket* mpCallBackPacket;
};

typedef void (*J3DDrawBuffer__entryImm_t)(J3DDrawBuffer*, J3DPacket* packet, u16);
#define J3DDrawBuffer__entryImm ((J3DDrawBuffer__entryImm_t)J3DDrawBuffer__entryImm_addr)

class J3DDisplayListObj {
public:
    void* mpData[2];
    u32 mSize;
    u32 mCapacity;
};

class J3DPacket {
public:
    J3DPacket() {
        mpNextSibling = NULL;
        mpFirstChild = NULL;
        mpUserData = NULL;
    }

    void clear() {
        mpNextSibling = NULL;
        mpFirstChild = NULL;
    }

    J3DPacket* getNextPacket() const { return mpNextSibling; }

    /* 0x00 */ void* vtable;
    /* 0x04 */ J3DPacket* mpNextSibling;
    /* 0x08 */ J3DPacket* mpFirstChild;
    /* 0x0C */ void* mpUserData;
};

class J3DDrawPacket : public J3DPacket {
public:
    int mFlags;
    char mPad0[0x0C];  // unk
    J3DDisplayListObj* mpDisplayListObj;
    J3DTexMtx* mpTexMtx;
};

class J3DShapePacket : public J3DDrawPacket {
public:
    J3DShape* mpShape;
    J3DMtxBuffer* mpMtxBuffer;
    Mtx* mpViewMtx;
    u32 mDiffFlag;
    J3DModel* mpModel;
};

class J3DMatPacket : public J3DDrawPacket {
public:
    J3DShapePacket* mpShapePacket;
    J3DShapePacket* mpFirstShapePacket;
    J3DMaterial* mpMaterial;
    s32 mSortFlags;
    J3DTexture* mpTexture;
    J3DMaterialAnm* mpMaterialAnm;
};

#endif /* J3DPACKET_H */
