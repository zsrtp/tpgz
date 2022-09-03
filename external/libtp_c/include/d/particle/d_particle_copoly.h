#ifndef D_PARTICLE_D_PARTICLE_COPOLY_H
#define D_PARTICLE_D_PARTICLE_COPOLY_H

#include "../bg/d_bg_s_acch.h"
#include <stdint.h>

class dPaPo_c {
public:
    /* 0x00 */ uint8_t field_0x00[0x28];
    /* 0x28 */ dBgS_Acch* field_0x28;
    /* 0x2C */ float field_0x2c;
    /* 0x30 */ float field_0x30;
    /* 0x34 */ uint8_t field_0x34;
    /* 0x35 */ uint8_t field_0x35;
    /* 0x36 */ uint8_t field_0x36;
    /* 0x37 */ uint8_t field_0x37;
};

#endif /* D_PARTICLE_D_PARTICLE_COPOLY_H */
