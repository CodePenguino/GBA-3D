#ifndef MAT4_H
#define MAT4_H

#include <tonc.h>
#include <string.h>
#include "math.h"

typedef FIXED mat4[4][4];

// Definitely not just copy-pasted from cglm's github ;)
#define MAT4_IDENTITY_INIT {{256, 0, 0, 0}, \
                            {0, 256, 0, 0}, \
                            {0, 0, 256, 0}, \
                            {0, 0, 0, 256}}

#define MAT4_REVERSE_IDENTITY_INIT {{0, 0, 0, 256}, \
                                    {0, 0, 256, 0}, \
                                    {0, 256, 0, 0}, \
                                    {256, 0, 0, 0}}


#define MAT4_ZERO_INIT {{0, 0, 0, 0}, \
                        {0, 0, 0, 0}, \
                        {0, 0, 0, 0}, \
                        {0, 0, 0, 0}}

#define MAT4_SCREENSPACETRANSFORM_INIT {{120, 0, 0, 119}, \
                                        {0, -80, 0, 79 }, \
                                        {0, 0, 256, 0  }, \
                                        {0, 0, 0,   256}}

#define MAT4_IDENTITY             ((mat4)MAT4_IDENTITY_INIT)
#define MAT4_REVERSE_IDENTITY     ((mat4)MAT4_REVERSE_IDENTITY_INIT)
#define MAT4_ZERO                 ((mat4)MAT4_ZERO_INIT)
#define MAT4_SCREENSPACETRANSFORM ((mat4)MAT4_SCREENSPACETRANSFORM_INIT)

// Copy a mat4 to another
INLINE void mat4_copy(mat4* mat, mat4* dest)
{
	memcpy(dest, mat, 64);
}

// Set up an identity matrix
INLINE void mat4_identity(mat4* dest)
{
	mat4 t = MAT4_IDENTITY_INIT;
	mat4_copy(&t, dest);
}

// Zero out a matrix
INLINE void mat4_zero(mat4* dest)
{
	mat4 t = MAT4_ZERO_INIT;
	mat4_copy(&t, dest);
}

// Multiply two matrices together
INLINE void mat4_mul(mat4 dest, mat4 a, mat4 b)
{
	for(u8 y = 0; y < 4; y++)
	{
		for(u8 x = 0; x < 4; x++)
		{
			dest[y][x] = fxmul(a[y][0], b[0][x]) +
			             fxmul(a[y][1], b[1][x]) +
			             fxmul(a[y][2], b[2][x]) +
			             fxmul(a[y][3], b[3][x]);
		}
	}
}

// Multiply a matrix and an integer
INLINE void mat4_mul_int(mat4 dest, mat4 a, int b)
{
	for(u8 y = 0; y < 4; y++)
	{
		for(u8 x = 0; x < 4; x++)
		{
			dest[y][x] = a[y][0] * b +
			             a[y][1] * b +
			             a[y][2] * b +
			             a[y][3] * b;
		}
	}
}

// Multiply a matrix with a fixed point number
INLINE void mat4_mul_fx(mat4 dest, mat4 a, FIXED b)
{
	for(u8 y = 0; y < 4; y++)
	{
		for(u8 x = 0; x < 4; x++)
		{
			dest[y][x] = fxmul(a[y][0], b) +
			             fxmul(a[y][1], b) +
			             fxmul(a[y][2], b) +
			             fxmul(a[y][3], b);
		}
	}
}

// Translating with a matrix
INLINE void mat4_translate(mat4* dest, FIXED x, FIXED y, FIXED z)
{
	mat4 t = MAT4_IDENTITY_INIT;
	t[0][3] = x;
	t[1][3] = y;
	t[2][3] = z;

	memcpy(dest, &t, 64);
}

// Rotating (by integer angles) with a matrix
INLINE void mat4_rotate(mat4* dest, int x, int y, int z)
{
	mat4 rx = MAT4_IDENTITY_INIT, ry = MAT4_IDENTITY_INIT, rz = MAT4_IDENTITY_INIT;

	rz[0][0] = fx_cos(z);
	rz[0][1] = -fx_sin(z);
	rz[1][0] = fx_sin(z);
	rz[1][1] = fx_cos(z);

	rx[1][1] = fx_cos(x);
	rx[1][2] = -fx_sin(x);
	rx[2][1] = fx_sin(x);
	rx[2][2] = fx_cos(x);

	ry[0][0] = fx_cos(y);
	ry[0][2] = -fx_sin(y);
	ry[2][0] = fx_sin(y);
	ry[2][2] = fx_cos(y);

	mat4 mult;
	mat4_mul(mult, ry, rx);
	mat4_mul(*dest, rz, mult);
}

// Rotating (by integer angles) with a matrix
INLINE void mat4_rotatef(mat4* dest, FIXED x, FIXED y, FIXED z)
{
	mat4 rx = MAT4_IDENTITY_INIT, ry = MAT4_IDENTITY_INIT, rz = MAT4_IDENTITY_INIT;

	rz[0][0] = fx_cosf(z);
	rz[0][1] = -fx_sinf(z);
	rz[1][0] = fx_sinf(z);
	rz[1][1] = fx_cosf(z);

	rx[1][1] = fx_cosf(x);
	rx[1][2] = -fx_sinf(x);
	rx[2][1] = fx_sinf(x);
	rx[2][2] = fx_cosf(x);

	ry[0][0] = fx_cosf(y);
	ry[0][2] = -fx_sinf(y);
	ry[2][0] = fx_sinf(y);
	ry[2][2] = fx_cosf(y);

	mat4 mult;
	mat4_mul(mult, ry, rx);
	mat4_mul(*dest, rz, mult);
}

// Rotating in the x-axis (by integer angles) with a matrix
INLINE void mat4_rotatex(mat4* dest, int x)
{
	mat4 rx = MAT4_IDENTITY_INIT;
	
	rx[1][1] = fx_cos(x);
	rx[1][2] = -fx_sin(x);
	rx[2][1] = fx_sin(x);
	rx[2][2] = fx_cos(x);

	mat4_copy(&rx, dest);
}

// Rotating in the y-axis (by integer angles) with a matrix
INLINE void mat4_rotatey(mat4* dest, int y)
{
	mat4 ry = MAT4_IDENTITY_INIT;

	ry[0][0] = fx_cos(y);
	ry[0][2] = -fx_sin(y);
	ry[2][0] = fx_sin(y);
	ry[2][2] = fx_cos(y);

	mat4_copy(&ry, dest);
}

// Rotating in the z-axis (by integer angles) with a matrix
INLINE void mat4_rotatez(mat4* dest, int z)
{
	mat4 rz = MAT4_IDENTITY_INIT;

	rz[0][0] = fx_cos(z);
	rz[0][1] = -fx_sin(z);
	rz[1][0] = fx_sin(z);
	rz[1][1] = fx_cos(z);

	mat4_copy(&rz, dest);
}

// Scaling with a matrix
INLINE void mat4_scale(mat4* dest, FIXED x, FIXED y, FIXED z)
{
	mat4 t = MAT4_IDENTITY_INIT;
	t[0][0] = x;
	t[1][1] = y;
	t[2][2] = z;

	memcpy(dest, &t, 64);
}

INLINE void mat4_perspective(mat4* dest, FIXED zNear, FIXED zFar)
{
	const FIXED tanHalfFOV = 179;
	const FIXED zRange = zNear - zFar;
	const FIXED aspectRatio = 384;

	mat4 m = MAT4_IDENTITY_INIT;

	m[0][0] = fxdiv(256, fxmul(tanHalfFOV, aspectRatio));
	m[1][1] = lu_div(tanHalfFOV);
	m[2][2] = fxdiv(-zNear - zFar, zRange);
	m[2][3] = fxdiv(fxmul(fxmul(512, zFar), zNear), zRange);
	m[3][3] = 0;
	m[3][2] = 256;

	memcpy(dest, &m, 64);
}

#endif // MAT4_H
