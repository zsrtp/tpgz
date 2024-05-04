#ifndef C_LIB_H_
#define C_LIB_H_

#include "libtp_c/include/dolphin/types.h"
#include "libtp_c/include/defines.h"

LIBTP_DEFINE_FUNC(cLib_chaseF__FPfff, cLib_chaseF_float____float__float_, int, cLib_chaseF, (f32*, f32, f32))
LIBTP_DEFINE_FUNC(cLib_targetAngleY__FPC3VecPC3Vec, cLib_targetAngleY_Vec_const____Vec_const___, s16, cLib_targetAngleY, (const Vec*, const Vec*))
LIBTP_DEFINE_FUNC(cLib_addCalc__FPfffff, cLib_addCalc_float____float__float__float__float_, f32, cLib_addCalc, (f32*,f32, f32,f32, f32))

#endif