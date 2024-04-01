#ifndef D_BG_D_BG_W_H
#define D_BG_D_BG_W_H

#include "../../dolphin/types.h"

class dBgS_CaptPoly;
class cBgS_PolyInfo;
class fopAc_ac_c;

struct cBgW__vtable {
    /* 0x00 */ void* RTTI;
    /* 0x04 */ void* field_0x04;
    /* 0x08 */ void* dtor;
    /* 0x0C */ void* ChkMemoryError;
    /* 0x10 */ void* ChkNotReady;
    /* 0x14 */ void* ChkLock;
    /* 0x18 */ void* ChkMoveBg;
    /* 0x1C */ void* ChkMoveFlag;
    /* 0x20 */ void* GetTriPla;
    /* 0x24 */ void* GetTriPnt;
    /* 0x28 */ void* GetBnd;
    /* 0x2C */ void* GetGrpInf;
    /* 0x30 */ void* OffMoveFlag;
    /* 0x34 */ void* GetTopUnder;
    /* 0x38 */ void* SetOldShapeAngleY;
    /* 0x3C */ void* LineCheck;
    /* 0x40 */ void* GroundCross;
    /* 0x44 */ void* ShdwDraw;
    /* 0x48 */ void (*CaptPoly)(void* i_this, dBgS_CaptPoly&);
    /* 0x4C */ void* WallCorrect;
    /* 0x50 */ void* WallCorrectSort;
    /* 0x54 */ void* RoofChk;
    /* 0x58 */ void* SplGrpChk;
    /* 0x5C */ void* SphChk;
    /* 0x60 */ void* GetGrpRoomIndex;
    /* 0x64 */ void* GetExitId;
    /* 0x68 */ void* GetPolyColor;
    /* 0x6C */ void* GetHorseNoEntry;
    /* 0x70 */ void* GetSpecialCode;
    /* 0x74 */ void* GetSpecialCode2;
    /* 0x78 */ void* GetMagnetCode;
    /* 0x7C */ void* GetPolyObjThrough;
    /* 0x80 */ void* GetPolyCamThrough;
    /* 0x84 */ void* GetPolyLinkThrough;
    /* 0x88 */ void* GetPolyArrowThrough;
    /* 0x8C */ void* GetPolyHSStick;
    /* 0x90 */ void* GetPolyBoomerangThrough;
    /* 0x94 */ void* GetPolyRopeThrough;
    /* 0x98 */ void* GetPolyBombThrough;
    /* 0x9C */ void* GetShdwThrough;
    /* 0xA0 */ void* GetUnderwaterRoofCode;
    /* 0xA4 */ void* GetMonkeyBarsCode;
    /* 0xA8 */ void* GetLinkNo;
    /* 0xAC */ void* GetWallCode;
    /* 0xB0 */ void* GetPolyAtt0;
    /* 0xB4 */ void* GetPolyAtt1;
    /* 0xB8 */ void* GetGroundCode;
    /* 0xBC */ void* GetIronBallThrough;
    /* 0xC0 */ void* GetAttackThrough;
    /* 0xC4 */ void* GetCamMoveBG;
    /* 0xC8 */ void* GetRoomCamId;
    /* 0xCC */ void* GetRoomPathId;
    /* 0xD0 */ void* GetRoomPathPntNo;
    /* 0xD4 */ void* GetPolyGrpRoomInfId;
    /* 0xD8 */ void* GetGrpSoundId;
    /* 0xDC */ void* CrrPos;
    /* 0xE0 */ void* TransPos;
    /* 0xE4 */ void* MatrixCrrPos;
    /* 0xE8 */ void* CallRideCallBack;
    /* 0xEC */ void* CallArrowStickCallBack;
};

class cBgW_BgId {
public:
    /* 0x0 */ u16 m_id;
    /* 0x4 */ cBgW__vtable* vtable;

    cBgW_BgId() { Ct(); }
    void Ct() { m_id = 0x100; }
};

class dBgW_Base : public cBgW_BgId {
public:
    enum PushPullLabel {};

    typedef s32 (*PushPull_CallBack)(cBgS_PolyInfo const&, fopAc_ac_c*, s16,
                                     dBgW_Base::PushPullLabel);

    PushPull_CallBack GetPushPullCallback() const { return m_pushPull_Callback; }
    s16 GetDiffShapeAngleY() { return m_diff_ShapeAngleY; }
    u8 GetRoomId() { return m_roomId; }
    bool chkStickWall() { return field_0xb & 1; }
    bool chkStickRoof() { return field_0xb & 2; }

    /* 0x08 */ u8 m_priority;
    /* 0x09 */ u8 m_roomId;
    /* 0x0A */ u8 field_0xa;
    /* 0x0B */ u8 field_0xb;
    /* 0x0C */ s16 m_old_ShapeAngleY;
    /* 0x0E */ s16 m_diff_ShapeAngleY;
    /* 0x10 */ PushPull_CallBack m_pushPull_Callback;
    /* 0x14 */ bool m_pushPull_Ok;
};  // Size: 0x18

static_assert(sizeof(dBgW_Base) == 0x18);

LIBTP_DEFINE_FUNC(cBgW_CheckBGround__Ff, cBgW_CheckBGround_float_, bool, cBgW_CheckBGround, (f32))
LIBTP_DEFINE_FUNC(cBgW_CheckBRoof__Ff, cBgW_CheckBRoof_float_, bool, cBgW_CheckBRoof, (f32))

#endif /* D_BG_D_BG_W_H */
