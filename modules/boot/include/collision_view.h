#pragma once

#include "libtp_c/include/dolphin/gx/gx.h"
#include "libtp_c/include/dolphin/os/OSCache.h"
#include "libtp_c/include/JSystem/J3DGraphBase/J3DPacket.h"
#include "libtp_c/include/SSystem/SComponent/c_xyz.h"
#include "libtp_c/include/SSystem/SComponent/c_sxyz.h"

#define COLLISION_FLAGS_AMNT 4

enum CollisionIndex {
    VIEW_POLYGON_INDEX,
    VIEW_AT_INDEX,
    VIEW_TG_INDEX,
    VIEW_CO_INDEX,
};

struct CollisionItem {
    enum CollisionIndex id;
    bool active;
};

extern CollisionItem g_collisionFlags[COLLISION_FLAGS_AMNT];

void dDbVw_deleteDrawPacketList();

class dCcS;
void GZ_drawPolygons();
void GZ_drawCc(dCcS* i_this);

//----------------------------------------
//             DRAW PACKETS
//----------------------------------------

extern u32 l_drawPacketListNum;

class mDoExt_cubePacket {
public:
    mDoExt_cubePacket(cXyz& position, cXyz& size, csXyz& angle, const GXColor& color) {
        mPosition = position;
        mSize = size;
        mAngle = angle;
        mColor = color;
    }

    ~mDoExt_cubePacket() {}

    /* 0x00 */ J3DPacket base;
    /* 0x10 */ cXyz mPosition;
    /* 0x1C */ cXyz mSize;
    /* 0x28 */ csXyz mAngle;
    /* 0x2E */ GXColor mColor;
};

void mDoExt_cubePacket__dtor(mDoExt_cubePacket* i_this);
void mDoExt_cubePacket__draw(mDoExt_cubePacket* i_this);

class mDoExt_spherePacket {
public:
    mDoExt_spherePacket(cXyz& position, f32 size, const GXColor& color, u8 param_3) {
        mPosition = position;
        mSize = size;
        mColor = color;
        _24 = param_3;
    }

    ~mDoExt_spherePacket() {}

    /* 0x00 */ J3DPacket base;
    /* 0x10 */ cXyz mPosition;
    /* 0x1C */ f32 mSize;
    /* 0x20 */ GXColor mColor;
    /* 0x24 */ u8 _24;
};

void mDoExt_spherePacket__dtor(mDoExt_spherePacket* i_this);
void mDoExt_spherePacket__draw(mDoExt_spherePacket* i_this);

class mDoExt_cylinderPacket {
public:
    mDoExt_cylinderPacket(cXyz& position, f32 radius, f32 height, const GXColor& color, u8 param_4) {
        mPosition = position;
        mRadius = radius;
        mHeight = height;
        mColor = color;
        _28 = param_4;
    }

    ~mDoExt_cylinderPacket() {}

    /* 0x00 */ J3DPacket base;
    /* 0x10 */ cXyz mPosition;
    /* 0x1C */ f32 mRadius;
    /* 0x20 */ f32 mHeight;
    /* 0x24 */ GXColor mColor;
    /* 0x28 */ u8 _28;
};

void mDoExt_cylinderPacket__dtor(mDoExt_cylinderPacket* i_this);
void mDoExt_cylinderPacket__draw(mDoExt_cylinderPacket* i_this);

class mDoExt_cube8pPacket {
public:
    mDoExt_cube8pPacket(cXyz* points, const GXColor& color) {
        cXyz* pnt_array = points;

        for (int i = 0; i < 8; i++) {
            mPoints[i] = *pnt_array;
            pnt_array++;
        }

        DCStoreRangeNoSync(mPoints, 0x60);
        mColor = color;
    }

    ~mDoExt_cube8pPacket() {}

    /* 0x00 */ J3DPacket base;
    /* 0x10 */ cXyz mPoints[8];
    /* 0x70 */ GXColor mColor;
};

void mDoExt_cube8pPacket__dtor(mDoExt_cube8pPacket* i_this);
void mDoExt_cube8pPacket__draw(mDoExt_cube8pPacket* i_this);

class mDoExt_trianglePacket {
public:
    mDoExt_trianglePacket(cXyz* points, const GXColor& color, u8 param_2) {
        cXyz* pnt_array = points;

        for (int i = 0; i < 3; i++) {
            mPoints[i] = *pnt_array;
            pnt_array++;
        }

        DCStoreRangeNoSync(mPoints, 0x24);
        mColor = color;
        _38 = param_2;
    }

    ~mDoExt_trianglePacket() {}

    /* 0x00 */ J3DPacket base;
    /* 0x10 */ cXyz mPoints[3];
    /* 0x34 */ GXColor mColor;
    /* 0x38 */ u8 _38;
};

void mDoExt_trianglePacket__dtor(mDoExt_trianglePacket* i_this);
void mDoExt_trianglePacket__draw(mDoExt_trianglePacket* i_this);

class mDoExt_linePacket {
public:
    mDoExt_linePacket(cXyz& pointA, cXyz& pointB, const GXColor& color, u8 param_3, u8 width) {
        mPointA = pointA;
        mPointB = pointB;
        mColor = color;
        _2C = param_3;
        mWidth = width;
    }

    ~mDoExt_linePacket() {}

    /* 0x00 */ J3DPacket base;
    /* 0x10 */ cXyz mPointA;
    /* 0x1C */ cXyz mPointB;
    /* 0x28 */ GXColor mColor;
    /* 0x2C */ u8 _2C;
    /* 0x2D */ u8 mWidth;
};

void mDoExt_linePacket__dtor(mDoExt_linePacket* i_this);
void mDoExt_linePacket__draw(mDoExt_linePacket* i_this);