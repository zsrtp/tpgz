#ifndef D_KANKYO_D_KANKYO_H
#define D_KANKYO_D_KANKYO_H

#include "../../SSystem/SComponent/c_xyz.h"
#include "../../dolphin/gx/GXTexture.h"
#include "../../JSystem/J3DGraphBase/J3DStruct.h"
#include "../../JSystem/J3DGraphBase/J3DPacket.h"

struct LIGHT_INFLUENCE {
    /* 0x00 */ cXyz field_0x00;
    /* 0x0C */ _GXColorS10 mColor;
    /* 0x14 */ float field_0x14;
    /* 0x18 */ float field_0x18;
    /* 0x1C */ int field_0x1c;
};

struct WIND_INFLUENCE {
    /* 0x00 */ cXyz field_0x00;
    /* 0x0C */ cXyz field_0x0c;
    /* 0x18 */ uint8_t field_0x18[0xC];
    /* 0x24 */ int field_0x24;
    /* 0x28 */ uint8_t field_0x28;
    /* 0x29 */ uint8_t field_0x29;
};

struct WIND_INF_ENTITY {
    /* 0x00 */ uint8_t field_0x0[0x10];
    /* 0x10 */ WIND_INFLUENCE field_0x10;
};  // Size: 0x3C

struct EFLIGHT_PROC {
    /* 0x00 */ uint8_t field_0x0;
    /* 0x01 */ uint8_t field_0x1;
    /* 0x04 */ int field_0x4;
    /* 0x08 */ LIGHT_INFLUENCE field_0x8;
};

struct SND_INFLUENCE {
    /* 0x00 */ cXyz field_0x0;
    /* 0x0C */ int field_0xc;
    /* 0x10 */ int field_0x10;
    /* 0x14 */ uint32_t field_0x14;
};

struct DALKMIST_INFLUENCE {
    /* 0x00 */ uint8_t field_0x0[0x10];
};

struct DUNGEON_LIGHT {
    /* 0x00 */ cXyz field_0x0;
    /* 0x0C */ uint8_t field_0xc[0x20];
    /* 0x2C */  // LIGHT_INFLUENCE field_0x2c; this breaks ctor for some reason
    uint8_t field_0x2c[0x20];
};  // Size: 0x4C

struct BOSS_LIGHT {
    /* 0x00 */ cXyz field_0x0;
    /* 0x0C */ int field_0xc;
    /* 0x10 */ int field_0x10;
    /* 0x14 */ int field_0x14;
    /* 0x18 */ int field_0x18;
    /* 0x1C */ int field_0x1c;
    /* 0x20 */ int field_0x20;
    /* 0x24 */ uint8_t field_0x24;
    /* 0x25 */ uint8_t field_0x25;
    /* 0x26 */ uint8_t field_0x26;
};  // Size: 0x28

struct GB_WIND_INFLUENCE {
    /* 0x00 */ cXyz pos;
    /* 0x0C */ int field_0xc;
    /* 0x10 */ float pow;
};

struct EF_THUNDER {
    /* 0x00 */ uint8_t field_0x0;
    /* 0x01 */ uint8_t field_0x1;
    /* 0x02 */ uint8_t field_0x2;
    /* 0x04 */ int field_0x4;
    /* 0x08 */ float field_0x8;
    /* 0x0C */ float field_0xc;
    /* 0x10 */ float field_0x10;
    /* 0x14 */ float field_0x14;
    /* 0x18 */ float field_0x18;
    /* 0x1C */ float field_0x1c;
    /* 0x20 */ uint8_t field_0x20[4];
    /* 0x24 */ LIGHT_INFLUENCE field_0x24;
};

struct GB_MAPLE_COL_CHANGE {
    /* 0x00 */ J3DLightObj field_0x0;
};  // Size: 0x74

class dKy_tevstr_c {
public:
    /* 0x000 */ J3DLightObj field_0x000;
    /* 0x074 */ J3DLightObj field_0x074[6];
    /* 0x32C */ cXyz field_0x32c;
    /* 0x338 */ cXyz field_0x338;
    /* 0x344 */ float field_0x344;
    /* 0x348 */ int field_0x348;
    /* 0x34C */ int field_0x34c;
    /* 0x350 */ int field_0x350;
    /* 0x354 */ int field_0x354;
    /* 0x358 */ int field_0x358;
    /* 0x35C */ int field_0x35c;
    /* 0x360 */ int field_0x360;
    /* 0x364 */ int field_0x364;
    /* 0x368 */ float field_0x368;
    /* 0x36C */ float field_0x36c;
    /* 0x370 */ float field_0x370;
    /* 0x374 */ float field_0x374;
    /* 0x378 */ uint16_t field_0x378;
    /* 0x37A */ uint8_t field_0x37a;
    /* 0x37B */ uint8_t field_0x37b;
    /* 0x37C */ uint8_t field_0x37c;
    /* 0x37D */ uint8_t field_0x37d;
    /* 0x37E */ uint8_t field_0x37e;
    /* 0x37F */ uint8_t field_0x37f;
    /* 0x380 */ uint8_t field_0x380;
    /* 0x381 */ uint8_t field_0x381;
    /* 0x382 */ uint8_t field_0x382;
    /* 0x383 */ uint8_t field_0x383;
    /* 0x384 */ uint8_t field_0x384;
    /* 0x385 */ uint8_t field_0x385;
};  // Size = 0x388?

static_assert(sizeof(dKy_tevstr_c) == 0x388);

class dKankyo_sun_Packet : public J3DPacket {
public:
    /* 0x10 */ cXyz field_0x10[2];
};

class dKankyo_sunlenz_Packet : public J3DPacket {
public:
    /* 0x10 */ uint8_t field_0x10[0x14];
    /* 0x24 */ cXyz field_0x24[8];
};

struct RAIN_EFF {
    /* 0x00 */ uint8_t field_0x0[4];
    /* 0x04 */ cXyz field_0x04;
    /* 0x10 */ cXyz field_0x10;
    /* 0x1C */ uint8_t field_0x1c[0x1c];
};  // Size: 0x38

class dKankyo_rain_Packet : public J3DPacket {
public:
    /* 0x10 */ uint8_t field_0x10[8];
    /* 0x18 */ RAIN_EFF field_0x18[250];
};

struct SNOW_EFF {
    /* 0x00 */ uint8_t field_0x0[4];
    /* 0x04 */ cXyz field_0x04;
    /* 0x10 */ cXyz field_0x10;
    /* 0x1C */ uint8_t field_0x1c[0x1c];
};  // Size: 0x38

class dKankyo_snow_Packet : public J3DPacket {
public:
    /* 0x10 */ uint8_t field_0x10[4];
    /* 0x14 */ SNOW_EFF field_0x14[500];
};

struct STAR_EFF {
    /* 0x00 */ uint8_t field_0x0[4];
    /* 0x04 */ cXyz field_0x04;
    /* 0x10 */ cXyz field_0x10;
    /* 0x1C */ uint8_t field_0x1c[0x18];
};  // Size: 0x34

class dKankyo_star_Packet : public J3DPacket {
public:
    /* 0x10 */ uint8_t field_0x10[4];
    /* 0x14 */ STAR_EFF field_0x14[1];
};

struct HOUSI_EFF {
    /* 0x00 */ uint8_t field_0x0[4];
    /* 0x04 */ cXyz field_0x04;
    /* 0x10 */ cXyz field_0x10;
    /* 0x1C */ cXyz field_0x1c;
    /* 0x28 */ uint8_t field_0x28[0x28];
};  // Size: 0x50

class dKankyo_housi_Packet : public J3DPacket {
public:
    /* 0x10 */ uint8_t field_0x10[0x10];
    /* 0x20 */ HOUSI_EFF field_0x18[300];
};

struct CLOUD_EFF {
    /* 0x00 */ uint8_t field_0x0[4];
    /* 0x04 */ cXyz field_0x04;
    /* 0x10 */ cXyz field_0x10;
    /* 0x1C */ cXyz field_0x1c;
    /* 0x28 */ uint8_t field_0x28[0x10];
};  // Size: 0x38

class dKankyo_cloud_Packet : public J3DPacket {
public:
    /* 0x10 */ uint8_t field_0x10[8];
    /* 0x18 */ CLOUD_EFF field_0x18[50];
};

struct VRKUMO_EFF {
    /* 0x00 */ uint8_t field_0x0[4];
    /* 0x04 */ cXyz field_0x04;
    /* 0x10 */ cXyz field_0x10;
    /* 0x1C */ uint8_t field_0x1c[0x10];
};  // Size: 0x2C

class dKankyo_vrkumo_Packet : public J3DPacket {
public:
    /* 0x10 */ uint8_t field_0x10[0x10];
    /* 0x20 */ VRKUMO_EFF field_0x18[100];
};

// might be fake
class dKankyo_shstar_Packet : public J3DPacket {};

struct ODOUR_EFF {
    /* 0x00 */ uint8_t field_0x0[4];
    /* 0x04 */ cXyz field_0x04;
    /* 0x10 */ cXyz field_0x10;
    /* 0x1C */ uint8_t field_0x1c[0x14];
};  // Size: 0x30

class dKankyo_odour_Packet : public J3DPacket {
public:
    /* 0x10 */ uint8_t field_0x10[4];
    /* 0x14 */ ODOUR_EFF field_0x18[2000];
};

struct MUD_EFF {
    /* 0x00 */ uint8_t field_0x0[4];
    /* 0x04 */ cXyz field_0x04;
    /* 0x10 */ cXyz field_0x10;
    /* 0x1C */ cXyz field_0x1c;
    /* 0x28 */ uint8_t field_0x28[0x20];
};  // Size: 0x48

class dKankyo_mud_Packet : public J3DPacket {
public:
    /* 0x10 */ uint8_t field_0x10[8];
    /* 0x18 */ MUD_EFF field_0x18[100];
};

struct EVIL_EFF {
    /* 0x00 */ uint8_t field_0x0[4];
    /* 0x04 */ cXyz field_0x04;
    /* 0x10 */ cXyz field_0x10;
    /* 0x1C */ csXyz field_0x1c;
    /* 0x22 */ uint8_t field_0x22[0x22];
};  // Size: 0x44

class dKankyo_evil_Packet : public J3DPacket {
public:
    /* 0x10 */ uint8_t field_0x10[8];
    /* 0x18 */ EVIL_EFF field_0x18[2000];
};

struct GXFogAdjTable {
    uint16_t field_0x0[10];
};

class fopAc_ac_c;

class dScnKy_env_light_c {
public:
    /* 0x0000 */ void* vtable;
    /* 0x0004 */ void* field_0x4;
    /* 0x0008 */ void* field_0x8;
    /* 0x000C */ void* field_0xc;
    /* 0x0010 */ void* field_0x10;
    /* 0x0014 */ void* field_0x14;
    /* 0x0018 */ LIGHT_INFLUENCE field_0x18;
    /* 0x0038 */ LIGHT_INFLUENCE field_0x38[30];
    /* 0x03F8 */ LIGHT_INFLUENCE* mPLight[100];
    /* 0x0588 */ LIGHT_INFLUENCE* mEfPLight[5];
    /* 0x059C */ uint8_t field_0x59c[400];
    /* 0x072C */ int field_0x72c[5];
    /* 0x0740 */ LIGHT_INFLUENCE field_0x740;
    /* 0x0760 */ uint8_t field_0x760[4];
    /* 0x0764 */ LIGHT_INFLUENCE mBGpartsActiveLight[2];
    /* 0x07A4 */ EFLIGHT_PROC field_0x7a4;
    /* 0x07CC */ void* stagPlightInfo;  // might be part of EFLIGHT_PROC
    /* 0x07D0 */ WIND_INFLUENCE* mPntWind[30];
    /* 0x0848 */ WIND_INF_ENTITY field_0x848[5];
    /* 0x0974 */ SND_INFLUENCE mSound;
    /* 0x098C */ uint8_t field_0x98c;
    /* 0x0990 */ DALKMIST_INFLUENCE* mDalkmistInf[10];
    /* 0x09B8 */ DUNGEON_LIGHT field_0x9b8[8];
    /* 0x0C18 */ BOSS_LIGHT field_0x0c18[8];
    /* 0x0D58 */ BOSS_LIGHT field_0x0d58[6];
    /* 0x0E48 */ GB_WIND_INFLUENCE field_0xe48;
    /* 0x0E5C */ float custom_windpower;
    /* 0x0E60 */ float field_0xe60;
    /* 0x0E64 */ uint16_t field_0xe64;
    /* 0x0E66 */ uint16_t field_0xe66;
    /* 0x0E68 */ int16_t field_0xe68;
    /* 0x0E6A */ int16_t field_0xe6a;
    /* 0x0E6C */ uint8_t field_0xe6c;
    /* 0x0E6D */ uint8_t field_0xe6d;
    /* 0x0E6E */ uint8_t field_0xe6e;  // E5C - E6E might all be part of GB_WIND_INFLUENCE
    /* 0x0E6F */ uint8_t field_0xe6f;
    /* 0x0E70 */ uint8_t field_0xe70;
    /* 0x0E74 */ dKankyo_sun_Packet* field_0xe74;
    /* 0x0E78 */ dKankyo_sunlenz_Packet* field_0xe78;
    /* 0x0E7C */ uint8_t field_0xe7c;
    /* 0x0E80 */ int mRainCheck;
    /* 0x0E84 */ dKankyo_rain_Packet* field_0xe84;
    /* 0x0E88 */ uint8_t field_0xe88;
    /* 0x0E8C */ int field_0xe8c;
    /* 0x0E90 */ uint8_t field_0xe90;
    /* 0x0E91 */ uint8_t field_0xe91;
    /* 0x0E92 */ uint8_t field_0xe92;
    /* 0x0E94 */ dKankyo_snow_Packet* field_0xe94;
    /* 0x0E98 */ uint8_t field_0xe98;
    /* 0x0E9C */ int field_0xe9c;
    /* 0x0EA0 */ float field_0xea0;
    /* 0x0EA4 */ dKankyo_star_Packet* field_0xea4;
    /* 0x0EA8 */ uint8_t field_0xea8;
    /* 0x0EA9 */ uint8_t field_0xea9;
    /* 0x0EAC */ int field_0xeac;
    /* 0x0EB0 */ dKankyo_housi_Packet* field_0xeb0;
    /* 0x0EB4 */ uint8_t field_0xeb4;
    /* 0x0EB5 */ uint8_t field_0xeb5;
    /* 0x0EB8 */ int field_0xeb8;
    /* 0x0EBC */ float field_0xebc;
    /* 0x0EC0 */ dKankyo_cloud_Packet* field_0xec0;
    /* 0x0EC4 */ uint8_t field_0xec4;
    /* 0x0EC8 */ int field_0xec8;
    /* 0x0ECC */ float field_0xecc;
    /* 0x0ED0 */ dKankyo_vrkumo_Packet* field_0xed0;
    /* 0x0ED4 */ EF_THUNDER field_0xef4;
    /* 0x0F18 */ uint8_t field_0xf18[4];
    /* 0x0F1C */ dKankyo_shstar_Packet* field_0xf1c;
    /* 0x0F20 */ uint8_t field_0xf20;
    /* 0x0F21 */ uint8_t field_0xf21;
    /* 0x0F24 */ int field_0xf24;
    /* 0x0F28 */ dKankyo_odour_Packet* field_0xf28;
    /* 0x0F2C */ uint8_t field_0xf2c;
    /* 0x0F30 */ void* field_0xf30;
    /* 0x0F34 */ float field_0xf34;
    /* 0x0F38 */ int field_0xf38;
    /* 0x0F3C */ uint8_t field_0xf3c;
    /* 0x0F3D */ uint8_t field_0xf3d;
    /* 0x0F40 */ float field_0xf40;
    /* 0x0F44 */ void* field_0xf44;
    /* 0x0F48 */ void* field_0xf48;
    /* 0x0F4C */ void* field_0xf4c;
    /* 0x0F50 */ GB_MAPLE_COL_CHANGE field_0xf50[2];
    /* 0x1038 */ uint8_t field_0x1038;
    /* 0x103C */ int field_0x103c;
    /* 0x1040 */ uint8_t field_0x1040[4];
    /* 0x1044 */ uint8_t field_0x1044;
    /* 0x1048 */ int field_0x1048;
    /* 0x104C */ dKankyo_mud_Packet* field_0x104c;
    /* 0x1050 */ uint8_t field_0x1050;
    /* 0x1051 */ uint8_t field_0x1051;
    /* 0x1054 */ int field_0x1054;
    /* 0x1058 */ dKankyo_evil_Packet* field_0x1058;
    /* 0x105C */ void* field_0x105c;
    /* 0x1060 */ fopAc_ac_c* field_0x1060;
    /* 0x1064 */ float field_0x1064;
    /* 0x1068 */ float field_0x1068;
    /* 0x106C */ float field_0x106c;
    /* 0x1070 */ cXyz field_0x1070;
    /* 0x107C */ cXyz mPLightNearPos;
    /* 0x1088 */ cXyz field_0x1088;
    /* 0x1094 */ cXyz field_0x1094;
    /* 0x10A0 */ cXyz field_0x10a0;
    /* 0x10AC */ GXFogAdjTable field_0x10ac;
    /* 0x10C0 */ uint16_t field_0x10c0;
    /* 0x10C2 */ uint16_t field_0x10c2;
    /* 0x10C4 */ uint16_t field_0x10c4;
    /* 0x10C6 */ uint16_t field_0x10c6;
    /* 0x10C8 */ uint16_t field_0x10c8;
    /* 0x10CA */ uint16_t field_0x10ca;
    /* 0x10CC */ uint16_t field_0x10cc;
    /* 0x10CE */ uint16_t field_0x10ce;
    /* 0x10D0 */ uint16_t field_0x10d0;
    /* 0x10D2 */ uint16_t field_0x10d2;
    /* 0x10D4 */ uint16_t field_0x10d4;
    /* 0x10D6 */ uint16_t field_0x10d6;
    /* 0x10D8 */ uint16_t field_0x10d8;
    /* 0x10DA */ uint16_t field_0x10da;
    /* 0x10DC */ uint16_t field_0x10dc;
    /* 0x10DE */ uint16_t field_0x10de;
    /* 0x10E0 */ uint16_t field_0x10e0;
    /* 0x10E2 */ uint16_t field_0x10e2;
    /* 0x10E4 */ uint16_t field_0x10e4;
    /* 0x10E6 */ uint16_t field_0x10e6;
    /* 0x10E8 */ uint16_t field_0x10e8;
    /* 0x10EA */ uint16_t field_0x10ea;
    /* 0x10EC */ uint16_t field_0x10ec;
    /* 0x10EE */ uint16_t field_0x10ee;
    /* 0x10F0 */ int16_t field_0x10f0;
    /* 0x10F2 */ int16_t field_0x10f2;
    /* 0x10F4 */ int16_t field_0x10f4;
    /* 0x10F6 */ int16_t field_0x10f6;
    /* 0x10F8 */ int16_t field_0x10f8;
    /* 0x10FA */ int16_t field_0x10fa;
    /* 0x10FC */ int16_t field_0x10fc;
    /* 0x10FE */ int16_t field_0x10fe;
    /* 0x1100 */ _GXColorS10 field_0x1100;
    /* 0x1108 */ _GXColorS10 field_0x1108;
    /* 0x1110 */ int16_t field_0x1110;
    /* 0x1112 */ int16_t field_0x1112;
    /* 0x1114 */ int16_t field_0x1114;
    /* 0x1116 */ int16_t field_0x1116;
    /* 0x1118 */ int16_t field_0x1118;
    /* 0x111A */ int16_t field_0x111a;
    /* 0x111C */ int16_t field_0x111c;
    /* 0x111E */ int16_t field_0x111e;
    /* 0x1120 */ int16_t field_0x1120;
    /* 0x1122 */ int16_t field_0x1122;
    /* 0x1124 */ int16_t field_0x1124;
    /* 0x1126 */ int16_t field_0x1126;
    /* 0x1128 */ _GXColorS10 field_0x1128;
    /* 0x1130 */ uint8_t field_0x1130[0x28];
    /* 0x1158 */ _GXColorS10 field_0x1158;
    /* 0x1160 */ int16_t field_0x1160;
    /* 0x1162 */ int16_t field_0x1162;
    /* 0x1164 */ int16_t field_0x1164;
    /* 0x1166 */ uint8_t field_0x1166[10];
    /* 0x1170 */ int16_t field_0x1170;
    /* 0x1172 */ int16_t field_0x1172;
    /* 0x1174 */ int16_t field_0x1174;
    /* 0x1176 */ uint8_t field_0x1176[10];
    /* 0x1180 */ int16_t field_0x1180;
    /* 0x1182 */ int16_t field_0x1182;
    /* 0x1184 */ int16_t field_0x1184;
    /* 0x1186 */ uint8_t field_0x1186[10];
    /* 0x1190 */ int16_t field_0x1190;
    /* 0x1192 */ int16_t field_0x1192;
    /* 0x1194 */ int16_t field_0x1194;
    /* 0x1196 */ uint8_t field_0x1196[10];
    /* 0x11A0 */ int16_t field_0x11a0;
    /* 0x11A2 */ int16_t field_0x11a2;
    /* 0x11A4 */ int16_t field_0x11a4;
    /* 0x11A6 */ uint8_t field_0x11a6[10];
    /* 0x11B0 */ int16_t field_0x11b0;
    /* 0x11B2 */ int16_t field_0x11b2;
    /* 0x11B4 */ int16_t field_0x11b4;
    /* 0x11B6 */ int16_t field_0x11b6;
    /* 0x11B8 */ int16_t field_0x11b8;
    /* 0x11BA */ int16_t field_0x11ba;
    /* 0x11BC */ int16_t field_0x11bc;
    /* 0x11BE */ uint8_t field_0x11be[2];
    /* 0x11C0 */ int16_t field_0x11c0;
    /* 0x11C2 */ int16_t field_0x11c2;
    /* 0x11C4 */ int16_t field_0x11c4;
    /* 0x11C8 */ float field_0x11c8;
    /* 0x11CC */ float field_0x11cc;
    /* 0x11D0 */ float field_0x11d0;
    /* 0x11D4 */ float field_0x11d4;
    /* 0x11D8 */ float field_0x11d8;
    /* 0x11DC */ float field_0x11dc;
    /* 0x11E0 */ float field_0x11e0;
    /* 0x11E4 */ float field_0x11e4;
    /* 0x11E8 */ float field_0x11e8;
    /* 0x11EC */ float field_0x11ec;
    /* 0x11F0 */ float field_0x11f0;
    /* 0x11F4 */ float field_0x11f4;
    /* 0x11F8 */ float field_0x11f8;
    /* 0x11FC */ float field_0x11fc;
    /* 0x1200 */ float field_0x1200;
    /* 0x1204 */ float field_0x1204;
    /* 0x1208 */ float field_0x1208;
    /* 0x120C */ float field_0x120c;
    /* 0x1210 */ float field_0x1210;
    /* 0x1214 */ float mAllcolRatio;
    /* 0x1218 */ float mActcolRatio;
    /* 0x121C */ float mBgcolRatio;
    /* 0x1220 */ float mFogcolRatio;
    /* 0x1224 */ float mVrboxSoracolRatio;
    /* 0x1228 */ float mVrboxKumocolRatio;
    /* 0x122C */ float field_0x122c;
    /* 0x1230 */ float field_0x1230;
    /* 0x1234 */ float field_0x1234;
    /* 0x1238 */ float field_0x1238;
    /* 0x123C */ float field_0x123c;
    /* 0x1240 */ float field_0x1240;
    /* 0x1244 */ float mDaytime;
    /* 0x1248 */ float mNexttime;
    /* 0x124C */ float field_0x124c;
    /* 0x1250 */ float mDarkDaytime;
    /* 0x1254 */ float field_0x1254;
    /* 0x1258 */ float field_0x1258;
    /* 0x125C */ float field_0x125c;
    /* 0x1260 */ float field_0x1260;
    /* 0x1264 */ float field_0x1264;
    /* 0x1268 */ float field_0x1268;
    /* 0x126C */ float field_0x126c;
    /* 0x1270 */ float field_0x1270;
    /* 0x1274 */ float field_0x1274;
    /* 0x1278 */ float field_0x1278;
    /* 0x127C */ float field_0x127c;
    /* 0x1280 */ int field_0x1280;
    /* 0x1284 */ uint8_t field_0x1284[4];
    /* 0x1288 */ int field_0x1288;
    /* 0x128C */ uint8_t field_0x128c[12];
    /* 0x1298 */ int field_0x1298;
    /* 0x129C */ int field_0x129c;
    /* 0x12A0 */ int field_0x12a0;
    /* 0x12A4 */ int field_0x12a4;
    /* 0x12A8 */ int field_0x12a8;
    /* 0x12AC */ uint8_t field_0x12ac[4];
    /* 0x12B0 */ int field_0x12b0;
    /* 0x12B4 */ int field_0x12b4;
    /* 0x12B8 */ uint8_t field_0x12b8[4];
    /* 0x12BC */ uint16_t field_0x12bc;
    /* 0x12BE */ uint16_t field_0x12be;
    /* 0x12C0 */ uint16_t field_0x12c0;
    /* 0x12C2 */ uint8_t field_0x12c2;
    /* 0x12C3 */ uint8_t field_0x12c3;
    /* 0x12C4 */ uint8_t field_0x12c4;
    /* 0x12C5 */ uint8_t mWeatherPalette;
    /* 0x12C6 */ uint8_t field_0x12c6;
    /* 0x12C7 */ uint8_t field_0x12c7;
    /* 0x12C8 */ uint8_t field_0x12c8;
    /* 0x12C9 */ uint8_t field_0x12c9;
    /* 0x12CA */ uint8_t field_0x12ca;
    /* 0x12CB */ uint8_t field_0x12cb;
    /* 0x12CC */ uint8_t field_0x12cc;
    /* 0x12CD */ uint8_t field_0x12cd;
    /* 0x12CE */ uint8_t field_0x12ce;
    /* 0x12CF */ uint8_t field_0x12cf;
    /* 0x12D0 */ uint8_t field_0x12d0;
    /* 0x12D1 */ uint8_t mItemGetCol_chg;
    /* 0x12D2 */ uint8_t field_0x12d2;
    /* 0x12D3 */ uint8_t field_0x12d3;
    /* 0x12D4 */ uint8_t field_0x12d4;
    /* 0x12D5 */ uint8_t field_0x12d5;
    /* 0x12D6 */ uint8_t field_0x12d6;
    /* 0x12D7 */ uint8_t mShadowMode;
    /* 0x12D8 */ uint8_t mCameraInWater;
    /* 0x12DC */ void* field_0x12dc;
    /* 0x12E0 */ void* field_0x12e0;
    /* 0x12E4 */ void* field_0x12e4;
    /* 0x12E8 */ void* field_0x12e8;
    /* 0x12EC */ void* field_0x12ec;
    /* 0x12F0 */ void* field_0x12f0;
    /* 0x12F4 */ void* field_0x12f4;
    /* 0x12F8 */ uint8_t field_0x12f8;
    /* 0x12F9 */ uint8_t field_0x12f9;
    /* 0x12FA */ uint8_t field_0x12fa;
    /* 0x12FB */ uint8_t field_0x12fb;
    /* 0x12FC */ uint8_t field_0x12fc;
    /* 0x12FD */ uint8_t mDarktimeWeek;
    /* 0x12FE */ uint8_t field_0x12fe;
    /* 0x1300 */ uint16_t field_0x1300;
    /* 0x1302 */ uint16_t field_0x1302;
    /* 0x1304 */ float field_0x1304;
    /* 0x1308 */ uint8_t field_0x1308;
    /* 0x1309 */ uint8_t field_0x1309;
    /* 0x130A */ uint8_t field_0x130a;
    /* 0x130B */ uint8_t field_0x130b;
    /* 0x130C */ uint8_t field_0x130c;
};  // Size: 0x1310

static_assert(sizeof(dScnKy_env_light_c) == 4880);

extern "C" {
extern dScnKy_env_light_c g_env_light;
}

#endif /* D_KANKYO_D_KANKYO_H */
