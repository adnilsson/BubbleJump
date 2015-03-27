#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "preproceccors.h"
#include "Parser.h"



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

	void game_over();
	bool pre_game_over(const BigInteger finalScore);
	void paused(game_state state);

	static void displayText(LPD3DXFONT, LPCSTR, RECT, 
		int, int, int, int = DT_LEFT, int = 255);
	static void displayTextBox(LPD3DXFONT, LPCSTR, RECT,
		int, int, int, int, int = DT_LEFT);
	
	

private:
	RECT box;
	LPD3DXFONT headline, subtitle, text;
	std::string scoreTitle;

	Parser* highScores;
};



