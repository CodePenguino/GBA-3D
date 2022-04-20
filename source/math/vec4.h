#ifndef VEC4_H
#define VEC4_H

#include <tonc.h>
#include <math.h>
#include "math.h"
#include "mat4.h"
#include "vec3.h"

typedef struct
{
	FIXED x, y, z, w;
} vec4;

// Swap two vec4s
INLINE void v4_swap(vec4* a, vec4* b)
{
    vec4 tmp = *a;
    *a = *b;
    *b = tmp;
}

// Find the length of a vec4
INLINE FIXED v4_length(vec4 v)
{
    return float2fx(sqrtf(v.x * v.x + v.y * v.y));
}

// Find the dot product of two vec4s
INLINE FIXED v4_dot(vec4 a, vec4 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

// Find the cross product of two vec4s
INLINE vec4 v4_cross(vec4 a, vec4 b)
{
    return (vec4){ a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x,
        0 };
}

// Normalize a vec4
INLINE vec4 v4_normalize(vec4 v)
{
    FIXED length = v4_length(v);
    
    v.x = fxdiv(v.x, length);
    v.y = fxdiv(v.y, length);
    v.z = fxdiv(v.z, length);
    v.w = fxdiv(v.w, length);
    
    return v;
}


// Add two vec4s
INLINE vec4 v4_add_v4(vec4 a, vec4 b)
{
	return (vec4){ a.x+b.x, a.y+b.y, a.z+b.z, a.w+b.w };
}

// Sum of a vec4 and int
INLINE vec4 v4_add_int(vec4 a, int b)
{
    return (vec4){ a.x+b, a.y+b, a.z+b, a.w+b };
}

// Subtract two vec4s
INLINE vec4 v4_sub_v4(vec4 a, vec4 b)
{
    return (vec4){ a.x-b.x, a.y-b.y, a.z-b.z, a.w-b.w };
}

// Subtract a vec4 by an int
INLINE vec4 v4_sub_int(vec4 a, int b)
{
    return (vec4){ a.x-b, a.y-b, a.z-b, a.w-b };
}

// Multiply two vec4s together
INLINE vec4 v4_mul_v4(vec4 a, vec4 b)
{
    return (vec4){ a.x*b.x, a.y*b.y, a.z*b.z, a.w*b.w };
}

// Multiply two fixed point vec4s together
INLINE vec4 fx_v4_mul_v4(vec4 a, vec4 b)
{
    return (vec4){ fxmul(a.x,b.x), fxmul(a.y,b.y), fxmul(a.z,b.z), fxmul(a.w,b.w) };
}

// Multiply a vec4 by an int
INLINE vec4 v4_mul_int(vec4 a, int b)
{
    return (vec4){ a.x*b, a.y*b, a.z*b, a.w*b };
}

// Multiply a fixed point vec4 by a fixed point number
INLINE vec4 v4_mul_fx(vec4 a, FIXED b)
{
    return (vec4){ fxmul(a.x,b), fxmul(a.y,b), fxmul(a.z,b), fxmul(a.w,b) };
}

// Divide a vec4 by another
INLINE vec4 v4_div_v4(vec4 a, vec4 b)
{
    return (vec4){ a.x/b.x, a.y/b.y, a.z/b.z, a.w/b.w };
}

// Divide two fixed point vec4s together
INLINE vec4 fx_v4_div_v4(vec4 a, vec4 b)
{
    return (vec4){ fxdiv(a.x,b.x), fxdiv(a.y,b.y), fxdiv(a.z,b.z), fxdiv(a.w,b.w) };
}

// Divide a vec4 by an int
INLINE vec4 v4_div_int(vec4 a, int b)
{
    return (vec4){ a.x/b, a.y/b, a.z/b, a.w/b };
}

// Divide a fixed point vec4 by a fixed point number
INLINE vec4 v4_div_fx(vec4 a, FIXED b)
{
    return (vec4){ fxdiv(a.x,b), fxdiv(a.y,b), fxdiv(a.z,b), fxdiv(a.w,b) };
}

// Rotate a vec4 (not tested)
INLINE vec4 v4_rotate(vec4 v, vec4 axis, int angle)
{
    FIXED sinAngle = fx_sin(-angle);
    FIXED cosAngle = fx_cos(-angle);
    
    // NOTE: Good luck if there's a bug ;)
    return v4_add_v4(v4_cross(v, v4_mul_int(axis, sinAngle)),
                     v4_add_v4(v4_mul_int(v, cosAngle), 
                               v4_mul_int(axis, v4_dot(v, v4_mul_int(axis, 1 - cosAngle)))));
}

INLINE vec4 v4_perspective_divide(vec4 v)
{
	return(vec4){ fxdiv(v.x, v.w), fxdiv(v.y, v.w), fxdiv(v.z, v.w), v.w };
}

// Lerp two vec4s from a range of 0 - 256
INLINE vec4 v4_lerp(FIXED t, vec4 a, vec4 b)
{
	return v4_add_v4(v4_mul_fx(a, fxsub(256, t)), v4_mul_fx(b, t));
}

INLINE vec4 v4_int2fx(vec4 v)
{
	v.x = int2fx(v.x);
	v.y = int2fx(v.y);
	v.z = int2fx(v.z);
	v.w = int2fx(v.w);

	return v;
}

INLINE vec4 v4_fx2int(vec4 v)
{
	v.x = fx2int(v.x);
	v.y = fx2int(v.y);
	v.z = fx2int(v.z);
	v.w = fx2int(v.w);

	return v;
}

INLINE vec4 v4_fx2uint(vec4 v)
{
	v.x = fx2uint(v.x);
	v.y = fx2uint(v.y);
	v.z = fx2uint(v.z);
	v.w = fx2uint(v.w);

	return v;
}

#endif // VEC4_H
