#ifndef QUAT_H
#define QUAT_H

#include "vec4.h"
#include "vec3.h"
#include "math.h"

// --- Unused ---

typedef vec4 quat;

INLINE quat quat_conjugate(quat v)
{
	return (quat){-v.x, -v.y, -v.z, v.w};
}

INLINE quat quat_mul(quat a, quat b)
{
	/*return (quat) 
	{   a.x * b.w  +  a.w * b.x  +  a.y * b.z  -  a.z * b.y,
		a.y * b.w  +  a.w * b.y  +  a.z * b.x  -  a.x * b.z,
		a.z * b.w  +  a.w * b.z  +  a.x * b.y  -  a.y * b.x,
		a.w * b.w  -  a.x * b.x  -  a.y * b.y  -  a.z * b.z };*/

	return (quat) 
	{   fxmul(a.x, b.w)  +  fxmul(a.w, b.x)  +  fxmul(a.y, b.z)  -  fxmul(a.z, b.y),
		fxmul(a.y, b.w)  +  fxmul(a.w, b.y)  +  fxmul(a.z, b.x)  -  fxmul(a.x, b.z),
		fxmul(a.z, b.w)  +  fxmul(a.w, b.z)  +  fxmul(a.x, b.y)  -  fxmul(a.y, b.x),
		fxmul(a.w, b.w)  -  fxmul(a.x, b.x)  -  fxmul(a.y, b.y)  -  fxmul(a.z, b.z) };
}

INLINE quat quat_mul_v3(quat a, vec3 b)
{
	/*return (quat)
	{   a.w * b.x  +  a.y * b.z  -  a.z * b.y,
		a.w * b.y  +  a.z * b.x  -  a.x * b.z,
		a.w * b.z  +  a.x * b.y  -  a.y * b.x,
	   -a.x * b.x  -  a.y * b.y  -  a.z * b.z };*/

	return (quat)
	{   fxmul(a.w, b.x)  +  fxmul(a.y, b.z)  - fxmul(a.z, b.y),
		fxmul(a.w, b.y)  +  fxmul(a.z, b.x)  - fxmul(a.x, b.z),
		fxmul(a.w, b.z)  +  fxmul(a.x, b.y)  - fxmul(a.y, b.x),
       -fxmul(a.x, b.x)  -  fxmul(a.y, b.y)  - fxmul(a.z, b.z) };
}

INLINE quat quat_rotate(FIXED angle, vec3 v)
{
	const FIXED halfAngleRad = fx_deg2rad(angle);
	const FIXED sinHalfAngle = fx_sinf(halfAngleRad);

	return (quat)
	{   fxmul(v.x, sinHalfAngle),
		fxmul(v.y, sinHalfAngle),
		fxmul(v.z, sinHalfAngle),
		fx_cosf(halfAngleRad)  };
}

/*INLINE vec3 v3_rotate(vec3 v, FIXED angle, vec3 axes)
{
	quat rotationQ = quat_rotate(angle, axes);
	quat conjQ     = quat_conjugate(rotationQ);

	quat res = quat_mul(quat_mul_v3(rotationQ, v), conjQ);

	v.x = res.x;
	v.y = res.y;
	v.z = res.z;

	return v;
}*/

#endif // QUAT_H
