#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "preproceccors.h"



#ifndef MENU_FONT_SIZE
	#define FONT_HEIGHT 40
	#define FONT_WIDTH 0
	#define MENU_FONT_SIZE
#endif

class Menus
{
public:
	Menus(LPDIRECT3DDEVICE9 d3d);
	virtual ~Menus(void);

	void game_over(game_state state);
	void paused(game_state state);
	static void displayText(LPD3DXFONT, LPCSTR, RECT, 
		int, int, int, int);
	
	

private:
	RECT box;
	LPD3DXFONT headline, text;
};



