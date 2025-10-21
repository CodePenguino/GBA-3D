#include "util.h"
#include "math/vec4.h"
#include "math.h"
#include "logic/collision.h"
#include "math/mat4.h"
#include <stdarg.h>

// Put a one digit number on the screen
void m4_putn1(const u16 x, const u16 y, const int c, const u8 clrid)
{
	// ERROR!
	if(c > 9)
	{
		m4_puts(x, y, "OVR_ERR!", 3);
		return;
	}
	
	if(c < 0)
	{
		if(c < -9)
		{
			m4_puts(x, y, "UND_ERR!", 3);
			return;
		}
		
		m4_putc(x, y, 45,   clrid);
		m4_putc(x, y, c+48, clrid);
		return;
	}
	
	m4_putc(x, y, c+48, clrid);
}

// Put a two digit number on the screen
void m4_putn2(const u16 x, const u16 y, int c, const u8 clrid)
{
	if(c > 99)
	{
		m4_puts(x, y, "OVR_ERR!", 3);
		return;
	}
	
	// Is there a negative number? Put a negative sign and then the absolute value of c
	if(c < 0)
	{
		if(c < -99)
		{
			m4_puts(x, y, "UND_ERR!", 3);
			return;
		}
		
		c = ABS(c);
		
		m4_putc(x,    y,        45, clrid);
		m4_putc(x+8,  y, (c/10)+48, clrid);
		m4_putc(x+16, y, (c%10)+48, clrid);
		return;
	}
	
	// Randomly pocking into memory, the sequel!
	m4_putc(x,   y, (c/10) + 48, clrid);
	m4_putc(x+8, y, (c%10) + 48, clrid);
}

// Put a three digit number on the screen
void m4_putn3(const u16 x, const u16 y, int c, const u8 clrid)
{
	if(c > 999)
	{
		m4_puts(x, y, "OVR_ERR!", 3);
		return;
	}
	
	const u8 num = c / 10;
	
	if(c < 0)
	{
		if(c < -999)
		{
			m4_puts(x, y, "UND_ERR!", 3);
			return;
		}
		
		c = ABS(c);
		
		m4_putc(x,    y, 45,            clrid);
		m4_putc(x+8,  y, (num/10) + 48, clrid);
		m4_putc(x+16, y, (num%10) + 48, clrid);
		m4_putc(x+24, y, (c%10)   + 48, clrid);
		return;
	}
	
	// Time to make this a trilogy now!
	m4_putc(x,    y, (num/10) + 48, clrid);
	m4_putc(x+8,  y, (num%10) + 48, clrid);
	m4_putc(x+16, y, (c%10)   + 48, clrid);
}

// Put a four digit number on the screen
void m4_putn4(const u16 x, const u16 y, int c, const u8 clrid)
{
	if(c > 9999)
	{
		m4_puts(x, y, "OVR_ERR!", 3);
		return;
	}
	
	if(c < 0)
	{
		if(c < -9999)
		{
			m4_puts(x, y, "UND_ERR!", 3);
			return;
		}
		
		c = ABS(c);
		
		m4_putc(x,    y, 45,               clrid);
		m4_putc(x+8,  y, (c/1000)    + 48, clrid);
		m4_putc(x+16, y, ((c/100)%10)+ 48, clrid);
		m4_putc(x+24, y, ((c/10)%10) + 48, clrid);
		m4_putc(x+32, y, (c%10)      + 48, clrid);
		return;
	}
	
	// I think this is starting to get out of hand...
	m4_putc(x,    y, (c/1000)    + 48, clrid);
	m4_putc(x+8,  y, ((c/100)%10)+ 48, clrid);
	m4_putc(x+16, y, ((c/10)%10) + 48, clrid);
	m4_putc(x+24, y, (c%10)      + 48, clrid);
}

// Tesselate num vertices, which are already sorted on the x-axis (takes in vertices as vec4s)
void m4_tesselateAndDraw(u8 c, int num, ...)
{
	// TODO: Make sure this all actually works!
	va_list valist;
	va_start(valist, num);
	
	vec4 vertices[16];

	// Store all of the vertices from the va list.
	for(u8 i = 0; i < num; i++)
	{
		vertices[i] = va_arg(valist, vec4);
	}
	va_end(valist);

	// From left to right, tesselate the polygon
	for(u8 i = 0; i < (num - 2); i++)
	{
		m4_drawTrianglev4(vertices[0], vertices[1+i], vertices[2+i], c);
	}
}

// Draw a wireframe triangle on the screen.
void m4_drawTriangle(vec2 v0, vec2 v1, vec2 v2, u8 c)
{
	// Sort the triangle's vertices
	if(v1.y < v0.y) v2_swap(&v0, &v1);
	if(v2.y < v1.y) v2_swap(&v1, &v2);
	if(v1.y < v0.y) v2_swap(&v0, &v1);
	
	m4_line(v0.x, v0.y, v1.x, v1.y, c);
	m4_line(v1.x, v1.y, v2.x, v2.y, c);
	m4_line(v2.x, v2.y, v0.x, v0.y, c);
}

// Draw a wireframe triangle on the screen.
void m4_drawTrianglev4(vec4 v0, vec4 v1, vec4 v2, u8 c)
{
	// Sort the triangle's vertices
	if(v1.y < v0.y) v4_swap(&v0, &v1);
	if(v2.y < v1.y) v4_swap(&v1, &v2);
	if(v1.y < v0.y) v4_swap(&v0, &v1);
	
	m4_line(v0.x, v0.y, v1.x, v1.y, c);
	m4_line(v1.x, v1.y, v2.x, v2.y, c);
	m4_line(v2.x, v2.y, v0.x, v0.y, c);
}

// Draw a flat shaded triangle on the screen
void m4_fillTriangle(vec2 v0, vec2 v1, vec2 v2, u8 c)
{
	u8 y;
	// Order all the vertices based on their y-axes
	if(v1.y < v0.y) v2_swap(&v0, &v1);
	if(v2.y < v1.y) v2_swap(&v1, &v2);
	if(v1.y < v0.y) v2_swap(&v0, &v1);

	FIXED startX = int2fx(v0.x), endX = int2fx(v0.x);

	// Find triangle slopes (using run/rise)
	const FIXED m0 = fxdiv(int2fx(v1.x - v0.x), int2fx(v1.y - v0.y));
	const FIXED m1 = fxdiv(int2fx(v2.x - v0.x), int2fx(v2.y - v0.y));
	const FIXED m2 = fxdiv(int2fx(v1.x - v2.x), int2fx(v1.y - v2.y));

	// Draws the flat bottom part of the triangle
	for(y = v0.y; y < v1.y; y++)
	{
		m4_hline(fx2uint(startX), y, fx2uint(endX), c);

		startX += m0;
		endX += m1;
	}

	// Draws the flat top part of the triangle
	for(; y < v2.y; y++)
	{
		m4_hline(fx2uint(startX), y, fx2uint(endX), c);
		
		startX += m2;
		endX += m1;
	}
}

// YOLO >:D (definitely not just copy-pasted from libtonc and edited so it runs slightly faster)
// TODO: Make this in assembly
void m4_scuffedDrawHLine(u8 x1, u8 y, u8 x2, u8 clr, void* dstBase, uint dstP)
{
	// --- Normalize ---
	clr &= 0xFF;
	if(x2<x1)
	{	int tmp= x1; x1= x2; x2= tmp;	}
		
	uint width= x2-x1+1;
	u16 *dstL= (u16*)(dstBase+y*dstP + (x1&~1));

	// --- Left unaligned pixel ---
	if(x1&1)
	{
		*dstL= (*dstL & 0xFF) + (clr<<8);
		width--;
		dstL++;
	}

	// --- Right unaligned pixel ---
	if(width&1)
		dstL[width>>1]= (dstL[width>>1]&~0xFF) + clr;
	width = width>>1;

	// --- Aligned line ---
	memset16(dstL, dup8(clr), width);
}

void m4_fillTrianglev4(vec4 v0, vec4 v1, vec4 v2, u8 c)
{
	u8 y;
	// Order all the vertices based on their y positions
	if(v1.y < v0.y) v4_swap(&v0, &v1);
	if(v2.y < v1.y) v4_swap(&v1, &v2);
	if(v1.y < v0.y) v4_swap(&v0, &v1);

	// Flat top
	if(v0.y == v1.y)
	{
		FIXED startX = int2fx(v0.x), endX = int2fx(v1.x);

		register const FIXED m0 = fxdiv(int2fx(v2.x - v0.x), int2fx(v2.y - v0.y));
		register const FIXED m1 = fxdiv(int2fx(v1.x - v2.x), int2fx(v1.y - v2.y));

		for(y = v0.y; y < v2.y; y++)
		{
			m4_scuffedDrawHLine(fx2uint(startX), y, fx2uint(endX), c, vid_page, M4_WIDTH);

			startX += m0;
			endX += m1;
		}
	}
	// Flat bottom
	else if(v1.y == v2.y)
	{
		FIXED startX = int2fx(v0.x), endX = int2fx(v0.x);

		register const FIXED m0 = fxdiv(int2fx(v1.x - v0.x), int2fx(v1.y - v0.y));
		register const FIXED m1 = fxdiv(int2fx(v2.x - v0.x), int2fx(v2.y - v0.y));

		for(y = v0.y; y < v2.y; y++)
		{
			m4_scuffedDrawHLine(fx2uint(startX), y, fx2uint(endX), c, vid_page, M4_WIDTH);

			startX += m0;
			endX += m1;
		}
	}
	// General
	else
	{
		FIXED startX = int2fx(v0.x), endX = int2fx(v0.x);

		// Find inverse triangle slopes (using run/rise)
		register const FIXED m0 = fxdiv(int2fx(v1.x - v0.x), int2fx(v1.y - v0.y));
		register const FIXED m1 = fxdiv(int2fx(v2.x - v0.x), int2fx(v2.y - v0.y));
		register const FIXED m2 = fxdiv(int2fx(v1.x - v2.x), int2fx(v1.y - v2.y));

		// Draws the flat bottom part of the triangle
		for(y = v0.y; y < v1.y; y++)
		{
			m4_scuffedDrawHLine(fx2uint(startX), y, fx2uint(endX), c, vid_page, M4_WIDTH);

			startX += m0;
			endX += m1;
		}

		// Draws the flat top part of the triangle
		for(; y < v2.y; y++)
		{
			m4_scuffedDrawHLine(fx2uint(startX), y, fx2uint(endX), c, vid_page, M4_WIDTH);

			startX += m2;
			endX += m1;
		}
	}
}
