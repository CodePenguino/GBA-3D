#ifndef COLLISION_H
#define COLLISION_H

#include <tonc.h>
#include "../math/vec2.h"
#include "../math/vec3.h"
#include "../math/vec4.h"

typedef struct
{
	vec2 position;
	int top, bottom, left, right;
} AABB;

// Checks if a point is inside the screen
INLINE BOOL is_point_onscreen(int xpos, int ypos)
{
	BOOL colX = xpos >= 0 && xpos < SCREEN_WIDTH;
	BOOL colY = ypos >= 0 && ypos < SCREEN_HEIGHT;
    
	return colX && colY;
}

// Checks if a point is inside the screen except with a vec2
INLINE BOOL is_vec2_onscreen(vec2 pos)
{
    BOOL colX = pos.x >= 0 && pos.x < SCREEN_WIDTH;
    BOOL colY = pos.y >= 0 && pos.y < SCREEN_HEIGHT;
    
    return colX && colY;
}

// AABB intersection code, which I haven't tested
INLINE BOOL aabb_intersects(AABB a, AABB b)
{
	int aSizeX = a.right - a.left;
	int aSizeY = a.top - a.bottom;
	int bSizeX = b.right - b.left;
	int bSizeY = b.top - b.bottom;

	BOOL colX = a.position.x < b.position.x + bSizeX && a.position.x + aSizeX > b.position.x;
	BOOL colY = a.position.y < b.position.y + bSizeY && a.position.y + aSizeY > b.position.y;

	return colX && colY;
}

#endif // COLLISION_H
