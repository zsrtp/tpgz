#ifndef J2DGRAPH_J2DPANE_H
#define J2DGRAPH_J2DPANE_H

#include <stdint.h>
#include "../JSupport/JSUList.h"
#include "../JGeometry.h"
#include "../../dolphin/mtx/mtx.h"
#include "../../addrs.h"

struct J2DAnmTransform {};

class J2DPane;

LIBTP_DEFINE_FUNC(__ct__7J2DPaneFv, J2DPane__J2DPane_void_, void, J2DPane__J2DPane1,
                  (J2DPane * thisx))

class J2DPane {
public:
    J2DPane() { J2DPane__J2DPane1(this); }

    float getHeight() const { return mBounds.getHeight(); }
    float getWidth() const { return mBounds.getWidth(); }
    // JSUTree<J2DPane>* getFirstChild() { return mPaneTree.getFirstChild(); }
    // const JSUTree<J2DPane>* getPaneTree() { return &mPaneTree; }

    /* 0x000 */ void* vtable;
    /* 0x004 */ uint16_t _4;
    /* 0x006 */ uint8_t _6[2];
    /* 0x008 */ int id;
    /* 0x00c */ uint8_t _c[4];
    /* 0x010 */ uint64_t mInfoTag;
    /* 0x018 */ uint64_t mUserInfoTag;
    /* 0x020 */ JGeometry::TBox2<float> mBounds;
    /* 0x030 */ JGeometry::TBox2<float> mGlobalBounds;
    /* 0x040 */ JGeometry::TBox2<float> mClipRect;
    /* 0x050 */ Mtx mPositionMtx;
    /* 0x080 */ Mtx mGlobalMtx;
    /* 0x0b0 */ bool mVisible;
    /* 0x0b1 */ uint8_t mCullMode;
    /* 0x0b2 */ uint8_t mAlpha;
    /* 0x0b3 */ uint8_t mColorAlpha;
    /* 0x0b4 */ bool mIsInfluencedAlpha;
    /* 0x0b5 */ bool mConnected;
    /* 0x0b6 */ char mRotAxis;
    /* 0x0b7 */ uint8_t mBasePosition;
    /* 0x0b8 */ float mRotateX;
    /* 0x0bc */ float mRotateY;
    /* 0x0c0 */ float mRotateZ;
    /* 0x0c4 */ float mRotateOffsetX;
    /* 0x0c8 */ float mRotateOffsetY;
    /* 0x0cc */ float mScaleX;
    /* 0x0d0 */ float mScaleY;
    /* 0x0d4 */ float mTranslateX;
    /* 0x0d8 */ float mTranslateY;
    /* 0x0dc */  // JSUTree<J2DPane> mPaneTree;
    uint8_t temp[0xF8 - 0xDC];
    /* 0x0f8 */ const J2DAnmTransform* mTransform;
    /* 0x0fc */ uint32_t _fc;
};
#endif  // J2DGRAPH_J2DPANE_H