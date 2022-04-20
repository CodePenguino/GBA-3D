#ifndef VEC2_H
#define VEC2_H

#include <math.h>
#include <string.h>
#include <tonc.h>
#include "math.h"

typedef struct
{
	FIXED x;
	FIXED y;
} vec2;

// Swap two vec2s around, taking in their addresses
INLINE void v2_swap(vec2* a, vec2* b)
{
	vec2 tmp = *a;
	*a = *b;
	*b = tmp;
}

// Find the length of a vec2
INLINE FIXED v2_length(vec2 v)
{
	return float2fx(sqrtf(v.x * v.x + v.y * v.y));
}

// Find the dot product of two vec2s
INLINE FIXED v2_dot(vec2 a, vec2 b)
{
	return a.x * b.x + a.y * b.y;
}

// Normalize a fixed point vec2
INLINE vec2 v2_normalize(vec2 v)
{
	FIXED length = v2_length(v);
    
    v.x = fxdiv(v.x, length);
    v.y = fxdiv(v.y, length);
    
	return v;
}

// TODO: Test this code. This is probably going to break...
// Rotate a fixed point vec2 by an angle (in degrees)
INLINE vec2 v2_rotate(vec2 v, int angle)
{
	FIXED rad    = fx_deg2rad(angle);
    FIXED cosine = fx_cos(fx2uint(rad));
    FIXED sine   = fx_sin(fx2uint(rad));
    
    return (vec2){ fxmul(v.x, cosine) - fxmul(v.y, sine), fxmul(v.x, sine) + fxmul(v.y, cosine) };
}

// Add two vec2s
INLINE vec2 v2_add_v2(vec2 a, vec2 b)
{
	return (vec2){ a.x + b.x, a.y + b.y };
}

// Sum of a vec2 and int
INLINE vec2 v2_add_int(vec2 a, int b)
{
	return (vec2){ a.x + b, a.y + b };
}

// Subtract two vec2s
INLINE vec2 v2_sub_v2(vec2 a, vec2 b)
{
	return (vec2){ a.x - b.x, a.y - b.y };
}

// Subtract a vec2 by an int
INLINE vec2 v2_sub_int(vec2 a, int b)
{
	return (vec2){ a.x - b, a.y - b };
}

// Multiply two vec2s together
INLINE vec2 v2_mul_v2(vec2 a, vec2 b)
{
	return (vec2){ a.x * b.x, a.y * b.y };
}

// Multiply two fixed point vec2s together
INLINE vec2 fx_v2_mul_v2(vec2 a, vec2 b)
{
	return (vec2){ fxmul(a.x, b.x), fxmul(a.y, b.y) };
}

// Multiply a vec2 by an int
INLINE vec2 v2_mul_int(vec2 a, int b)
{
	return (vec2){ a.x * b, a.y * b };
}

// Multiply a (fixed point) vec2 by a fixed point number
INLINE vec2 v2_mul_fx(vec2 a, FIXED b)
{
	return (vec2){ fxmul(a.x, b), fxmul(a.y, b) };
}

// Divide a vec2 by another
INLINE vec2 v2_div_v2(vec2 a, vec2 b)
{
	return (vec2){ a.x / b.x, a.y / b.y };
}

// Divide two fixed point vec2s together
INLINE vec2 fx_v2_div_v2(vec2 a, vec2 b)
{
	return (vec2){ fxdiv(a.x, b.x), fxdiv(a.y, b.y) };
}

// Divide a vec2 by an int
INLINE vec2 v2_div_int(vec2 a, int b)
{
	return (vec2){ a.x / b, a.y / b };
}

// Divide a (fixed point) vec2 by a fixed point number
INLINE vec2 v2_div_fx(vec2 a, FIXED b)
{
	return (vec2){ fxdiv(a.x, b), fxdiv(a.y, b) };
}

INLINE vec2 v2_lerp(FIXED t, vec2 a, vec2 b)
{
	return v2_add_v2(v2_mul_fx(a, fxsub(256, t)), v2_mul_fx(b, t));
}

INLINE vec2 v2_int2fx(vec2 v)
{
    v.x = int2fx(v.x);
    v.y = int2fx(v.y);

    return v;
}

INLINE vec2 v2_fx2int(vec2 v)
{
    v.x = fx2int(v.x);
    v.y = fx2int(v.y);

    return v;
}

INLINE vec2 v2_fx2uint(vec2 v)
{
    v.x = fx2uint(v.x);
    v.y = fx2uint(v.y);

    return v;
}

#endif // VEC2_H
