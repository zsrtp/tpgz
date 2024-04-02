#ifndef LIB_TP_MATH
#define LIB_TP_MATH

#define M_PI ((double)3.141592653589793238462643383279502884e+00)

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#include <stdint.h>

#include "../addrs.h"
#include "../defines.h"

extern "C" {
double atan(double x);
double ceil(double x);
double copysign(double x, double y);
double cos(double x);
double floor(double x);
double frexp(double x, int* exponent);
double ldexp(double x, int exponent);
#ifndef WII_PLATFORM
double modf(double x, double* iptr);
#endif
double sin(double x);
double tan(double x);
double acos(double x);
double asin(double x);
double atan2(double x, double y);
double exp(double x);
double fmod(double x, double y);
double pow(double x, double y);
double fastSqrt(double x);
double sqrt(double x);
}

LIBTP_DEFINE_FUNC(fabsf__3stdFf, fabsf, float, std__fabsf, (float))

#endif  // !LIB_TP_MATH
