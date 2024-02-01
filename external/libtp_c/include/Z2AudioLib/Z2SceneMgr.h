#ifndef Z2SCENEMGR_H
#define Z2SCENEMGR_H

#include "../JSystem/JAudio2/JAISound.h"

class Z2SceneMgr {
public:
    bool isSceneExist() { return sceneExist; }

private:
    /* 0x00 */ long BGM_ID;
    /* 0x04 */ int sceneNum;
    /* 0x08 */ int timer;
    /* 0x0C */ s8 roomNum;
    /* 0x0D */ u8 SeWave_1;
    /* 0x0E */ u8 SeWaveToErase_1;
    /* 0x0F */ u8 SeWave_2;
    /* 0x10 */ u8 SeWaveToErase_2;
    /* 0x11 */ u8 BgmWave_1;
    /* 0x12 */ u8 BgmWaveToErase_1;
    /* 0x13 */ u8 BgmWave_2;
    /* 0x14 */ u8 BgmWaveToErase_2;
    /* 0x15 */ u8 SeWave_3;
    /* 0x16 */ u8 SeWaveToErase_3;
    /* 0x17 */ u8 field_0x17;
    /* 0x18 */ u8 field_0x18;
    /* 0x19 */ u8 field_0x19;
    /* 0x1A */ u8 field_0x1a;
    /* 0x1B */ u8 field_0x1b;
    /* 0x1C */ bool inGame;
    /* 0x1D */ bool sceneExist;
    /* 0x1E */ bool inDarkness;
};  // Size = 0x20

#endif /* Z2SCENEMGR_H */