#ifndef UTIL_H
#define UTIL_H

#include <tonc.h>
#include "math/vec2.h"
#include "math/vec4.h"
#include <tonc_types.h>

void m4_putn1(const u16 x, const u16 y, const int c, const u8 clrid);
void m4_putn2(const u16 x, const u16 y, int c, const u8 clrid);
void m4_putn3(const u16 x, const u16 y, int c, const u8 clrid);
void m4_putn4(const u16 x, const u16 y, int c, const u8 clrid);

void m4_drawLine(vec4 a, vec4 b, u8 c);

void m4_drawTriangle(vec2 v0, vec2 v1, vec2 v2, u8 c);
void m4_drawTrianglev4(vec4 v0, vec4 v1, vec4 v2, u8 c);

void m4_tesselateAndDraw(u8 c, int num, ...);

INLINE void m4_drawTesselatedPolygon(u8 c, int num, vec4* vertices)
{
	for(u8 i = 0; i < (num - 2); i++)
	{
		m4_drawTrianglev4(vertices[0], vertices[1+i], vertices[2+i], c);
	}
}

void m4_fillTriangle(vec2 v0, vec2 v1, vec2 v2, u8 c);
void m4_fillTrianglev4(vec4 v0, vec4 v1, vec4 v2, u8 c);

#endif // UTIL_H
