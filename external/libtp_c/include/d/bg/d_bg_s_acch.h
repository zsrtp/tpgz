#ifndef D_BG_D_BG_S_ACCH_H
#define D_BG_D_BG_S_ACCH_H

#include "../../SSystem/SComponent/c_bg_s_poly_info.h"
#include "../../SSystem/SComponent/c_m3d_g_cir.h"
#include "../../SSystem/SComponent/c_m3d_g_cyl.h"
#include "../../SSystem/SComponent/c_m3d_g_lin.h"
#include "../../SSystem/SComponent/c_m3d_g_pla.h"
#include "d_bg_s_gnd_chk.h"
#include "d_bg_s_lin_chk.h"
#include "d_bg_s_roof_chk.h"
#include "d_bg_s_wtr_chk.h"

class dBgS_AcchCir {
public:
    enum {
        /* 0x2 */ WALL_HIT = 2,
        /* 0x4 */ WALL_H_DIRECT = 4,
    };

    f32 GetWallH() { return m_wall_h; }
    f32 GetWallR() { return m_wall_r; }
    void SetWallH(f32 h) { m_wall_h = h; }
    void ClrWallHDirect() { m_flags &= ~WALL_H_DIRECT; }
    bool ChkWallHit() { return m_flags & WALL_HIT; }
    s16 GetWallAngleY() { return m_wall_angle_y; }

    /* 0x00 */ cBgS_PolyInfo mPolyInfo;
    /* 0x10 */ u32 m_flags;
    /* 0x14 */ cM3dGCir m_cir;
    /* 0x28 */ f32 m_wall_rr;
    /* 0x2C */ f32 field_0x2c;
    /* 0x30 */ f32 m_wall_h;
    /* 0x34 */ f32 m_wall_r;
    /* 0x38 */ f32 m_wall_h_direct;
    /* 0x3C */ s16 m_wall_angle_y;
};

class dBgS_Acch {
public:
    enum {
        /* 0x000002 */ GRND_NONE = (1 << 1),
        /* 0x000004 */ WALL_NONE = (1 << 2),
        /* 0x000008 */ ROOF_NONE = (1 << 3),
        /* 0x000010 */ WALL_HIT = (1 << 4),
        /* 0x000020 */ GROUND_HIT = (1 << 5),
        /* 0x000040 */ GROUND_FIND = (1 << 6),
        /* 0x000080 */ GROUND_LANDING = (1 << 7),
        /* 0x000100 */ GROUND_AWAY = (1 << 8),
        /* 0x000200 */ ROOF_HIT = (1 << 9),
        /* 0x000400 */ WATER_NONE = (1 << 10),
        /* 0x000800 */ WATER_HIT = (1 << 11),
        /* 0x001000 */ WATER_IN = (1 << 12),
        /* 0x002000 */ LINE_CHECK = (1 << 13),
        /* 0x004000 */ LINE_CHECK_NONE = (1 << 14),
        /* 0x008000 */ CLR_SPEED_Y = (1 << 15),
        /* 0x010000 */ LINE_CHECK_HIT = (1 << 16),
        /* 0x100000 */ MOVE_BG_ONLY = (1 << 20),
        /* 0x200000 */ GND_THIN_CELLING_OFF = (1 << 21),
        /* 0x400000 */ WALL_SORT = (1 << 22),
        /* 0x800000 */ LINE_DOWN = (1 << 23),
    };

    cXyz* GetPos() { return pm_pos; }
    cXyz* GetOldPos() { return pm_old_pos; }
    f32 GetGroundH() const { return m_ground_h; }
    f32 GetRoofHeight() const { return m_roof_height; }
    int GetTblSize() { return m_tbl_size; }
    bool ChkGroundFind() { return m_flags & GROUND_FIND; }
    bool ChkGroundHit() { return m_flags & GROUND_HIT; }
    bool ChkGroundLanding() { return m_flags & GROUND_LANDING; }
    void ClrGroundLanding() { m_flags &= ~GROUND_LANDING; }
    void ClrGroundAway() { m_flags &= ~GROUND_AWAY; }
    void ClrWallHit() { m_flags &= ~WALL_HIT; }
    void SetRoofNone() { m_flags |= ROOF_NONE; }
    void SetRoofHit() { m_flags |= ROOF_HIT; }
    void SetWaterNone() { m_flags |= WATER_NONE; }
    bool ChkWallHit() { return m_flags & WALL_HIT; }
    void OffLineCheckHit() { m_flags &= ~LINE_CHECK_HIT; }
    void OffLineCheck() { m_flags &= ~LINE_CHECK; }
    bool ChkLineCheckNone() { return m_flags & LINE_CHECK_NONE; }
    bool ChkLineCheck() { return m_flags & LINE_CHECK; }
    void ClrRoofHit() { m_flags &= ~ROOF_HIT; }
    void ClrWaterHit() { m_flags &= ~WATER_HIT; }
    void SetWaterHit() { m_flags |= WATER_HIT; }
    void ClrWaterIn() { m_flags &= ~WATER_IN; }
    void SetWaterIn() { m_flags |= WATER_IN; }
    const u32 MaskWaterIn() { return m_flags & WATER_IN; }
    const bool ChkWaterIn() { return MaskWaterIn();}
    void ClrGroundFind() { m_flags &= ~GROUND_FIND; }
    u32 MaskRoofHit() { return m_flags & ROOF_HIT; }
    bool ChkRoofHit() { return MaskRoofHit(); }
    bool ChkClrSpeedY() { return !(m_flags & CLR_SPEED_Y); }
    void SetGroundFind() { m_flags |= GROUND_FIND; }
    void SetGroundHit() { m_flags |= GROUND_HIT; }
    void SetGroundLanding() { m_flags |= GROUND_LANDING; }
    void SetGroundAway() { m_flags |= GROUND_AWAY; }
    const u32 MaskWaterHit() { return m_flags & WATER_HIT; }
    const bool ChkWaterHit() { return MaskWaterHit(); }
    void ClrWaterNone() { m_flags &= ~WATER_NONE; }
    void SetWaterCheckOffset(f32 offset) { m_wtr_chk_offset = offset; }
    void OnLineCheck() { m_flags |= LINE_CHECK; }
    void ClrRoofNone() { m_flags &= ~ROOF_NONE; }
    void SetRoofCrrHeight(f32 height) { m_roof_crr_height = height; }
    void SetWtrChkMode(int mode) { m_wtr_mode = mode; }
    void SetGrndNone() { m_flags |= GRND_NONE; }
    void ClrGrndNone() { m_flags &= ~GRND_NONE; }
    bool ChkMoveBGOnly() const { return m_flags & MOVE_BG_ONLY; }
    void SetWallHit() { m_flags |= WALL_HIT; }
    void ClrWallNone() { m_flags &= ~WALL_NONE; }
    void OnLineCheckNone() { m_flags |= LINE_CHECK_NONE; }
    void OffLineCheckNone() { m_flags &= ~LINE_CHECK_NONE; }
    void SetWallNone() { m_flags |= WALL_NONE; }
    void OnLineCheckHit() { m_flags |= LINE_CHECK_HIT; }
    cM3dGCyl* GetWallBmdCylP() { return &m_wall_cyl; }

    /* 0x000 */ cBgS_Chk field_0x000;
    /* 0x014 */ dBgS_Chk field_0x014;
    /* 0x02C */ u32 m_flags;
    /* 0x030 */ cXyz* pm_pos;
    /* 0x034 */ cXyz* pm_old_pos;
    /* 0x038 */ cXyz* pm_speed;
    /* 0x03C */ csXyz* pm_angle;
    /* 0x040 */ csXyz* pm_shape_angle;
    /* 0x044 */ cM3dGLin m_lin;
    /* 0x060 */ cM3dGCyl m_wall_cyl;
    /* 0x078 */ int m_bg_index;
    /* 0x07C */ void* field_0x7c;
    /* 0x080 */ u32 field_0x80;
    /* 0x084 */ fopAc_ac_c* m_my_ac;
    /* 0x088 */ int m_tbl_size;
    /* 0x08C */ dBgS_AcchCir* pm_acch_cir;
    /* 0x090 */ f32 field_0x90;
    /* 0x094 */ f32 field_0x94;
    /* 0x098 */ f32 m_ground_h;
    /* 0x09C */ f32 field_0x9c;
    /* 0x0A0 */ cM3dGPla field_0xa0;
    /* 0x0B4 */ u8 field_0xb4;
    /* 0x0B8 */ f32 field_0xb8;
    /* 0x0BC */ f32 field_0xbc;
    /* 0x0C0 */ u8 field_0xc0;
    /* 0x0C4 */ f32 m_roof_height;
    /* 0x0C8 */ f32 m_roof_crr_height;
    /* 0x0CC */ f32 field_0xcc;
    /* 0x0D0 */ f32 m_wtr_chk_offset;
    /* 0x0D4 */ cBgS_PolyInfo* pm_out_poly_info;
    /* 0x0D8 */ f32 field_0xd8;
    /* 0x0DC */ dBgS_GndChk m_gnd;
    /* 0x130 */ dBgS_RoofChk m_roof;
    /* 0x180 */ dBgS_WtrChk m_wtr;
    /* 0x1D4 */ u8 m_wtr_mode;
};

class dBgS_LinkAcch : public dBgS_Acch {};

#endif /* D_BG_D_BG_S_ACCH_H */
