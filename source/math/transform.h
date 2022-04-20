#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "mat4.h"
#include "vec3.h"
#include "vec4.h"
#include "../logic/collision.h"
#include "../util.h"

// Transforms a vec4 via a mat4
INLINE vec4 v4_transform(mat4 m, vec4 r)
{
	return (vec4) {
		fxmul(m[0][0], r.x) + fxmul(m[0][1], r.y) + fxmul(m[0][2], r.z) + fxmul(m[0][3], r.w),
		fxmul(m[1][0], r.x) + fxmul(m[1][1], r.y) + fxmul(m[1][2], r.z) + fxmul(m[1][3], r.w),
		fxmul(m[2][0], r.x) + fxmul(m[2][1], r.y) + fxmul(m[2][2], r.z) + fxmul(m[2][3], r.w),
		fxmul(m[3][0], r.x) + fxmul(m[3][1], r.y) + fxmul(m[3][2], r.z) + fxmul(m[3][3], r.w) };
}

INLINE vec4 vert_transform(mat4 m, vec4 r)
{
	r = v4_transform(m, r);
	r = v4_perspective_divide(v4_transform(MAT4_SCREENSPACETRANSFORM, r));

	return r;
}

INLINE FIXED triangle_AreaTimesTwo(vec4 a, vec4 b, vec4 c)
{
	FIXED x1 = b.x - a.x;
	FIXED y1 = b.y - a.y;

	FIXED x2 = c.x - a.x;
	FIXED y2 = c.y - a.y;

	return (x1 * y2 - x2 * y1);
}

void triangle_clip_transform(mat4 m, vec4 v0, vec4 v1, vec4 v2, u8 c)
{
	// Find the correct vertex positions	
	v0 = v4_transform(m, v0);
	v1 = v4_transform(m, v1);
	v2 = v4_transform(m, v2);

	// Actual triangle clipping (this needs to be done BEFORE perspective divide)
	const register BOOL is_a_inside = v0.x <= v0.w && v0.y <= v0.w && v0.z <= v0.w        &&       -v0.x <= v0.w && -v0.y <= v0.w && -v0.z <= v0.w;
	const register BOOL is_b_inside = v1.x <= v1.w && v1.y <= v1.w && v1.z <= v1.w        &&       -v1.x <= v1.w && -v1.y <= v1.w && -v1.z <= v1.w;
	const register BOOL is_c_inside = v2.x <= v2.w && v2.y <= v2.w && v2.z <= v2.w        &&       -v2.x <= v2.w && -v2.y <= v2.w && -v2.z <= v2.w;

	if(is_a_inside && is_b_inside && is_c_inside)
	{
		v0 = v4_perspective_divide(v4_transform(MAT4_SCREENSPACETRANSFORM, v0));
		v1 = v4_perspective_divide(v4_transform(MAT4_SCREENSPACETRANSFORM, v1));
		v2 = v4_perspective_divide(v4_transform(MAT4_SCREENSPACETRANSFORM, v2));

		m4_fillTrianglev4(v0, v1, v2, c);
	}
}

#endif // TRANSFORM_H
