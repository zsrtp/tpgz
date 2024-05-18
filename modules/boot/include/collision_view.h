#pragma once

#include "libtp_c/include/dolphin/gx/gx.h"
#include "libtp_c/include/dolphin/os/OSCache.h"
#include "libtp_c/include/JSystem/J3DGraphBase/J3DPacket.h"
#include "libtp_c/include/SSystem/SComponent/c_xyz.h"
#include "libtp_c/include/SSystem/SComponent/c_sxyz.h"
#include "libtp_c/include/m_Do/m_Do_mtx.h"

enum CollisionIndex {
    VIEW_POLYGON_GROUND,
    VIEW_POLYGON_WALL,
    VIEW_POLYGON_ROOF,
    VIEW_AT_CC,
    VIEW_TG_CC,
    VIEW_CO_CC,

    VIEW_COLLISION_MAX,
};

struct CollisionItem {
    enum CollisionIndex id;
    bool active;
};

extern CollisionItem g_collisionFlags[VIEW_COLLISION_MAX];
extern u8 g_geometryOpacity;

void dDbVw_deleteDrawPacketList();

class dCcS;
void GZ_drawPolygons();
void GZ_drawCc(dCcS* i_this);

namespace dCcS_Data {
    extern u16 at_obj_count;
    extern u16 tg_obj_count;
    extern u16 co_obj_count;
}

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

class mDoExt_cylinderMPacket {
public:
    mDoExt_cylinderMPacket(Mtx m, const GXColor& color, u8 param_2) {
        PSMTXCopy(m, mMatrix);
        mColor = color;
        _44 = param_2;
    }

    ~mDoExt_cylinderMPacket() {}

    /* 0x00 */ J3DPacket base;
    /* 0x10 */ Mtx mMatrix;
    /* 0x40 */ GXColor mColor;
    /* 0x44 */ u8 _44;
};

void mDoExt_cylinderMPacket__dtor(mDoExt_cylinderMPacket* i_this);
void mDoExt_cylinderMPacket__draw(mDoExt_cylinderMPacket* i_this);

class mDoExt_circlePacket {
public:
    mDoExt_circlePacket(cXyz& i_position, f32 i_radius, const GXColor& i_color, u8 param_3, u8 i_lineWidth) {
        m_position = i_position;
        m_radius = i_radius;
        m_color = i_color;
        _24 = param_3;
        m_lineWidth = i_lineWidth;
    }

    ~mDoExt_circlePacket() {}

    /* 0x00 */ J3DPacket base;
    /* 0x10 */ cXyz m_position;
    /* 0x1C */ f32 m_radius;
    /* 0x20 */ GXColor m_color;
    /* 0x24 */ u8 _24;
    /* 0x25 */ u8 m_lineWidth;
};

void mDoExt_circlePacket__dtor(mDoExt_circlePacket* i_this);
void mDoExt_circlePacket__draw(mDoExt_circlePacket* i_this);

void dDbVw_drawCubeXlu(cXyz& pos, cXyz& size, csXyz& angle, const GXColor& color);
void dDbVw_drawSphereXlu(cXyz& position, f32 radius, const GXColor& color, u8 param_3);
void dDbVw_drawCylinderXlu(cXyz& position, f32 radius, f32 height, const GXColor& color, u8 param_4);
void dDbVw_drawCube8pXlu(cXyz* points, const GXColor& color);
void dDbVw_drawTriangleXlu(cXyz* points, const GXColor& color, u8 param_2);
void dDbVw_drawLineXlu(cXyz& pointA, cXyz& pointB, const GXColor& color, u8 param_3, u8 width);
void dDbVw_drawCylinderMXlu(Mtx m, const GXColor& color, u8 param_2);
void dDbVw_drawCircleXlu(cXyz& i_position, f32 i_radius, const GXColor& i_color, u8 param_3, u8 i_lineWidth);