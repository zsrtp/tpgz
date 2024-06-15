#ifndef J2DGRAPH_J2DPANE_H
#define J2DGRAPH_J2DPANE_H

#include "../../dolphin/types.h"
#include "../JSupport/JSUList.h"
#include "../JGeometry.h"
#include "../../dolphin/mtx/mtx.h"

struct J2DAnmTransform {};

class J2DPane;

LIBTP_DEFINE_FUNC(__ct__7J2DPaneFv, J2DPane__J2DPane_void_,
                  void, J2DPane__J2DPane1, (J2DPane* thisx))

class J2DPane {
public:
    J2DPane() { J2DPane__J2DPane1(this); }

    f32 getHeight() const { return mBounds.getHeight(); }
    f32 getWidth() const { return mBounds.getWidth(); }
    // JSUTree<J2DPane>* getFirstChild() { return mPaneTree.getFirstChild(); }
    // const JSUTree<J2DPane>* getPaneTree() { return &mPaneTree; }

    /* 0x000 */ void* vtable;
    /* 0x004 */ u16 _4;
    /* 0x006 */ u8 _6[2];
    /* 0x008 */ int id;
    /* 0x00c */ u8 _c[4];
    /* 0x010 */ uint64_t mInfoTag;
    /* 0x018 */ uint64_t mUserInfoTag;
    /* 0x020 */ JGeometry::TBox2<f32> mBounds;
    /* 0x030 */ JGeometry::TBox2<f32> mGlobalBounds;
    /* 0x040 */ JGeometry::TBox2<f32> mClipRect;
    /* 0x050 */ Mtx mPositionMtx;
    /* 0x080 */ Mtx mGlobalMtx;
    /* 0x0b0 */ bool mVisible;
    /* 0x0b1 */ u8 mCullMode;
    /* 0x0b2 */ u8 mAlpha;
    /* 0x0b3 */ u8 mColorAlpha;
    /* 0x0b4 */ bool mIsInfluencedAlpha;
    /* 0x0b5 */ bool mConnected;
    /* 0x0b6 */ char mRotAxis;
    /* 0x0b7 */ u8 mBasePosition;
    /* 0x0b8 */ f32 mRotateX;
    /* 0x0bc */ f32 mRotateY;
    /* 0x0c0 */ f32 mRotateZ;
    /* 0x0c4 */ f32 mRotateOffsetX;
    /* 0x0c8 */ f32 mRotateOffsetY;
    /* 0x0cc */ f32 mScaleX;
    /* 0x0d0 */ f32 mScaleY;
    /* 0x0d4 */ f32 mTranslateX;
    /* 0x0d8 */ f32 mTranslateY;
    /* 0x0dc */  // JSUTree<J2DPane> mPaneTree;
    u8 temp[0xF8 - 0xDC];
    /* 0x0f8 */ const J2DAnmTransform* mTransform;
    /* 0x0fc */ u32 _fc;
};
#endif  // J2DGRAPH_J2DPANE_H