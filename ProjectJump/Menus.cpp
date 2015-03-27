#include "Menus.h"
#include <assert.h>


Menus::Menus(LPDIRECT3DDEVICE9 d3d)
{
	highScores = new Parser();

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
		24, 0,	                   // height, width (0 = default value)
		FW_BOLD,			       //boldness (weight) of text
		1,
		FALSE,				       //no italics
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH || FF_SWISS, //Spacing, fontFamily
		L"Arial",			       //fontFace name
		&subtitle
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
	if (subtitle != NULL) subtitle->Release(); subtitle = NULL;
	if (text != NULL) text->Release(); text = NULL;

}

bool Menus::pre_game_over(BigInteger finalScore){
	if (highScores->updateScore(finalScore)){
		scoreTitle = "New high score!";
		return true;
	}
	scoreTitle = "High Scores: ";
	return false;
}

void Menus::game_over(){
	int centerX = WINDOW_WIDTH / 2;
	int centerY = static_cast<int>(0.5* WINDOW_HEIGHT / 2);
	const int width = 200;	


	std::string scores = highScores->getPrintableLine();
		
		displayText(headline, "Game Over!", box, 
			centerX, centerY,   //Upper left corner
			width, DT_CENTER);  //Lower right corner

		displayText(text, "(press space to restart)", box, 
			centerX, centerY + 30, //Upper left corner
			width, DT_CENTER);     //Lower right corner

		//Should indicade wether the player has set a new high score or not.
		displayText(subtitle, (LPCSTR)scoreTitle.c_str(), box,
			centerX, static_cast<int>(centerY * 1.55),
			width, DT_LEFT);

		//Current high scores (updated with an eventual new high score).
		displayTextBox(text, (LPCSTR) scores.c_str(), box,
			centerX, centerY *2,
			width, 50, DT_LEFT);
	
	
}

void Menus::paused(game_state state){
	int centerX = WINDOW_WIDTH / 2;
	int centerY = static_cast<int>(0.5 * WINDOW_HEIGHT / 2);
	int width = 200;

	if(state == GAME_PAUSED){
		
		displayText(headline, "Paused \n h", box, 
			centerX, centerY,   //Upper left corner
			width, DT_CENTER);  //Lower right corner

		displayText(text, "(press space to resume)", box,
			centerX, centerY + 30, //Upper left corner
			width, DT_CENTER);     //Lower right corner
			
	}
}

 
/*
--------------- PARAMS ---------------

d3dxFont:		The font object to draw.
str:			Text to be displayed.
textBox:		Container for the font object. limits the area where text will 
				be displayed.
centerX/Y:		Coordinates of the center of the textBox.
width:			Desired width of the textbox.
textAlignment:  Where to place text in the textBox. Defaults to DT_LEFT.
alpha:			Sets the text's opacity. Defaults to 255 (fully opac).
				Used for fading score increments from bubbles. 
*/
void Menus::displayText(LPD3DXFONT d3dxFont, LPCSTR str, RECT textBox,
						int centerX, int centerY, int width, 
						int textAlignment, int alpha){

	TEXTMETRIC textMetrics;
	int upperX, upperY;
	int lowerX, lowerY;

	if (!d3dxFont->GetTextMetricsW(&textMetrics)){
		MessageBox(NULL,
			(LPCWSTR)L"Failed to retrieve text metrics in fuction displayText",
			(LPCWSTR)L"Error",
			MB_ICONERROR | MB_OK);
		return;
	}

	upperX = centerX - width / 2;
	upperY = centerY - textMetrics.tmHeight / 2;
	
	lowerX = centerX + width / 2;
	lowerY = centerY + textMetrics.tmHeight / 2;


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
		textAlignment | DT_TOP,
		D3DCOLOR_ARGB(alpha, 255, 255, 255)) == NULL){
			
		MessageBox(NULL,
			(LPCWSTR)L"DrawTextA failed to display text in Menus.cpp",
			(LPCWSTR)L"Error",
			MB_ICONERROR | MB_OK);
	}

}


/*
Like displayText(), but takes a height param so that we can display several
rows of text. Used to display high-scores
--------------- PARAMS ---------------

d3dxFont:		The font object to draw.
str:			Text to be displayed.
textBox:		Container for the font object. limits the area where text will
be displayed.
centerX/Y:		Coordinates of the center of the textBox.
width:			Desired width of the textbox.
height:			Desired height of the textbox.
textAlignment:  Where to place text in the textBox. Defaults to DT_LEFT.
*/
void Menus::displayTextBox(LPD3DXFONT d3dxFont, LPCSTR str, RECT textBox,
	int centerX, int centerY, int width, int height,
	int textAlignment){

	int upperX, upperY;
	int lowerX, lowerY;

	upperX = centerX - width / 2;
	upperY = centerY - height;

	lowerX = centerX + width / 2;
	lowerY = centerY + height;


	if (!SetRect(&textBox, upperX, upperY, lowerX, lowerY)){
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
		textAlignment | DT_TOP,
		D3DCOLOR_ARGB(255, 255, 255, 255)) == NULL){

		MessageBox(NULL,
			(LPCWSTR)L"DrawTextA failed to display text in Menus.cpp",
			(LPCWSTR)L"Error",
			MB_ICONERROR | MB_OK);
	}

}
