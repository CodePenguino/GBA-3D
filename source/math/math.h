#ifndef MATH_H
#define MATH_H

#include <tonc.h>

// Pi in fixed point format
#define FX_PI 804

#define fx_deg2rad(x) (fxmul(x, fxdiv(FX_PI, 46080)))
#define fx_rad2deg(x) (fxdiv(fxmul(x, 46080), FX_PI))

// Swap two integers
void swap(int* x, int* y);

#define fx_sin(x) (lu_sin((x*182) * -0xffff) >> 4)
#define fx_cos(x) (lu_cos((x*182) *  0xffff) >> 4)

#define fx_sinf(x) (lu_sin(fx2uint(x*182) * -0xffff) >> 4)
#define fx_cosf(x) (lu_cos(fx2uint(x*182) *  0xffff) >> 4)

// Linear interpolation from range 0-256 between two fixed point numbers
INLINE FIXED lerpf(FIXED t, FIXED a, FIXED b)
{
    return fxadd(fxmul(fxsub(256,t), a), fxmul(t, b));
}

// Linear interpolation from range 0-256  between two integers
INLINE FIXED lerp(FIXED t, int a, int b)
{
	return lerpf(t, int2fx(a), int2fx(b));
}

#endif // MATH_H
