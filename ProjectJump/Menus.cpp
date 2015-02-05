#include "Menus.h"
#include <assert.h>


Menus::Menus(LPDIRECT3DDEVICE9 d3d)
{
	D3DXCreateFont(d3d,
		FONT_HEIGHT, 0,	          // height, width (0 = default value)
		FW_BOLD,			      //boldness (weight) of text
		1,
		FALSE,				      //no italics
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH || FF_SWISS, //Spacing, fontFamily
		L"Arial",			       //fontFace name
		&headline
		);

	D3DXCreateFont(d3d,
		16, 0,	                   // height, width (0 = default value)
		FW_MEDIUM,			       //boldness (weight) of text
		1,
		FALSE,				       //no italics
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH || FF_SWISS, //Spacing, fontFamily
		L"Arial",			       //fontFace name
		&text
		);
}


Menus::~Menus(void)
{
	if (headline != NULL) headline->Release(); headline = NULL;
	if (text != NULL) text->Release(); text = NULL;
}

void Menus::game_over(game_state state){
	int upperX = WINDOW_WIDTH/2 -100, upperY = WINDOW_HEIGHT/2 -90;
	int lowerX = WINDOW_WIDTH, lowerY = WINDOW_HEIGHT/2;

	if(state == GAME_OVER){
		
		displayText(headline, "Game Over!", box, 
			upperX, upperY,  //Upper left corner
			lowerX, lowerY); //Lower right corner

		displayText(text, "(press space to restart)", box, 
			upperX + 30, upperY + 50, //Upper left corner
			lowerX, lowerY + 50);     //Lower right corner
	}

	
}

void Menus::paused(game_state state){
	int upperX = WINDOW_WIDTH/2 -60, upperY = WINDOW_HEIGHT/2 -90;
	int lowerX = WINDOW_WIDTH, lowerY = WINDOW_HEIGHT/2;

	if(state == GAME_PAUSED){
		
		displayText(headline, "Paused", box, 
			upperX, upperY,   //Upper left corner
			lowerX, lowerY);  //Lower right corner

		displayText(text, "(press space to resume)", box,
			upperX - 10, upperY + 50, //Upper left corner
			lowerX, lowerY + 50);     //Lower right corner
	}
}

//Takes a font object, the string to print and the box with coordinates (which is 
//the area where the string will be printed) and draws the text. 
void Menus::displayText(LPD3DXFONT d3dxFont, LPCSTR str, RECT textBox,
						int upperX, int upperY, int lowerX, int lowerY,
						int alpha){
	if(!SetRect(&textBox, upperX, upperY, lowerX, lowerY)){
		MessageBox(NULL,
			      (LPCWSTR)L"failed to create textbox in fuction displayText",
				  (LPCWSTR)L"Error",
				  MB_ICONERROR | MB_OK);
		return;
	}

	assert(d3dxFont != NULL);

	if (d3dxFont->DrawTextA(NULL,
		str,
		strlen(str),
		&textBox,
		DT_LEFT | DT_TOP,
		D3DCOLOR_ARGB(alpha, 255, 255, 255)) == NULL){
			
		MessageBox(NULL,
			(LPCWSTR)L"DrawTextA failed to display text in Menus.cpp",
			(LPCWSTR)L"Error",
			MB_ICONERROR | MB_OK);
	}

}
