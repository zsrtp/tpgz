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

LIBTP_DEFINE_FUNC(entryImm__13J3DDrawBufferFP9J3DPacketUs, J3DDrawBuffer__entryImm_J3DPacket____unsigned_short_,
                  bool, J3DDrawBuffer__entryImm, (J3DDrawBuffer*, J3DPacket* packet, u16))

#define J3DPacket__entry entry__9J3DPacketFP13J3DDrawBuffer
#ifdef WII_PLATFORM
#define J3DPacket__entry J3DPacket__entry_J3DDrawBuffer___
#endif

extern "C" int J3DPacket__entry(J3DPacket*, J3DDrawBuffer*);

class J3DDisplayListObj {
public:
    void* mpData[2];
    u32 mSize;
    u32 mCapacity;
};

struct J3DPacket__vtable_t {
    void* rtti;
    void* padding;
    void* entry;
    void* draw;
    void* dtor;
};

#define J3DPacket__vtable __vt__9J3DPacket
#ifdef WII_PLATFORM
#define J3DPacket__vtable J3DPacket____vt
#endif

extern "C" J3DPacket__vtable_t J3DPacket__vtable;

class J3DPacket {
public:
    J3DPacket() {
        vtable = &J3DPacket__vtable;
        mpNextPacket = NULL;
        mpFirstChild = NULL;
        mpUserData = NULL;
    }

    void clear() {
        mpNextPacket = NULL;
        mpFirstChild = NULL;
    }

    J3DPacket* getNextPacket() const { return mpNextPacket; }

    /* 0x00 */ J3DPacket__vtable_t* vtable;
    /* 0x04 */ J3DPacket* mpNextPacket;
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
