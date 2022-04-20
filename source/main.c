#include "tonc_bios.h"
#include "tonc_input.h"
#include "tonc_math.h"
#include "tonc_memmap.h"
#include "tonc_nocash.h"
#include "tonc_text.h"
#include "tonc_tte.h"
#include "tonc_video.h"
#include <tonc.h>
#include "math.h"
#include "util.h"
#include "logic/collision.h"
#include "math/mat4.h"
#include "math/transform.h"
#include "math/vec4.h"
#include "logic/wall.h"
#include "logic/player.h"
#include "../resources/WallTexture1.h"

u32 posX = 0, posY = 0, posZ = 0;
mat4 perspective;

void m4Init()
{
	if (vid_page == vid_mem_front) // Front page displayed, swap to back
	{
		REG_DISPCNT = DCNT_MODE4 | DCNT_BG2 | DCNT_PAGE; 
	} else { // Back page displayed, swap to front.
		REG_DISPCNT = DCNT_MODE4 | DCNT_BG2;
	}
	
	pal_bg_mem[0] = CLR_TEAL;
	pal_bg_mem[1] = CLR_WHITE;
	pal_bg_mem[2] = CLR_FUCHSIA;
	pal_bg_mem[3] = CLR_RED;
	pal_bg_mem[4] = RGB8(0, 255, 0);
	pal_bg_mem[5] = RGB8(0, 0, 255);
	pal_bg_mem[6] = RGB8(255, 255, 0);
	pal_bg_mem[7] = CLR_BLACK;
}

u32 time;

void draw_scene()
{
	mat4 translation; mat4_translate(&translation, -posX, posY, 1024+posZ);
	mat4 rotation; mat4_rotate(&rotation, 0, time, time);

	mat4 temp; mat4_mul(temp, translation, rotation);
	mat4 transform; mat4_mul(transform, perspective, temp);

	vec4 p1 = {-128, -128, 0, 256};
    vec4 p2 = {0, 128, 0, 256};
	vec4 p3 = {128, -128, 0, 256};

	m4_fill(0);

	//for(u8 i = 0; i < 25; i++)
	triangle_clip_transform(transform, p1, p2, p3, 6);

	//m4_putn4(20, 20, time, 1);

	time++;
}

int main() 
{
	// Libtonc setup
	txt_init_std();
	irq_init(NULL);
	irq_add(II_VBLANK, NULL);
	
	m4Init();

	mat4_perspective(&perspective, 4, 3000);

	const FIXED move_speed = 5;

	for(;;)
	{
		key_poll();

		draw_scene();

		if(key_is_down(KEY_LEFT))
		{
			posX -= move_speed;
		}

		if(key_is_down(KEY_RIGHT))
		{
			posX += move_speed;
		}

		if(key_is_down(KEY_UP))
		{
			posZ -= move_speed;
		}

		if(key_is_down(KEY_DOWN))
		{
			posZ += move_speed;
		}

		if(key_is_down(KEY_L))
		{
			posY += 3;
		}
		
		if(key_is_down(KEY_R))
		{
			posY -= 3;
		}

		// In case you want to use vsync, put a VBlankIntrWait(); before vid_flip();
		VBlankIntrWait();
		vid_flip();
	}
	
	return 0;
}
