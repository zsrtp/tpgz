#pragma once

#ifdef GCN_PLATFORM
#include "libtp_c/include/JSystem/JUtility/JUTGamePad.h"
#define GORGE_VOID_BUTTONS (CButton::L | CButton::Z)
#endif

#ifdef WII_PLATFORM
#include "libtp_c/include/m_Do/m_Re_controller_pad.h"
#define GORGE_VOID_BUTTONS (CButton::Z | CButton::C | CButton::A | CButton::ONE)
#endif

void GZCmd_loadGorgeVoid();

namespace GorgeVoidIndicator {
void execute();
void initState();
void warpToPosition();
}  // namespace GorgeVoidIndicator