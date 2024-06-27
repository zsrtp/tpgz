#pragma once

#include "libtp_c/include/SSystem/SComponent/c_xyz.h"

enum ProjectionViewIndex {
    VIEW_LJA_PROJECTION,
    VIEW_MIDNA_CHARGE_PROJECTION,

    PROJECTION_VIEW_MAX,
};

struct ProjectionViewItem {
    enum ProjectionViewIndex id;
    bool active;
};

struct ProjectionLine {
    cXyz pos[40];
    bool got_it; // used for lja
};

namespace ProjectionViewer {
void execute();
}  // namespace ProjectionViewer

extern ProjectionLine g_ljaProjectionLine;
extern ProjectionLine g_midnaChargeProjectionLine;
extern ProjectionViewItem g_projectionViewFlags[PROJECTION_VIEW_MAX];
