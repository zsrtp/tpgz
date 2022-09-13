#pragma once

#include <cstdint>
#include "libtp_c/include/dolphin/mtx/vec.h"
#include "libtp_c/include/SSystem/SComponent/c_xyz.h"

struct PositionData {
    cXyz link;
    CameraMatrix cam;
    uint16_t angle;
};

extern bool g_injectMemfile;
extern bool set_position_data;
extern PositionData memfile_posdata;

void GZ_setLinkPosition();