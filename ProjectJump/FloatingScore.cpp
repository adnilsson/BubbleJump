#pragma once
#include "FloatingScore.h"
#include "Menus.h"


LPCSTR FloatingScore::scoreDoubled = "x2!";

FloatingScore::FloatingScore(FLOAT argX = 0, FLOAT argY = 0, int argPointValue = 0) : ListElement()
{
	alpha = 255;   //set full visibility
	pos.x =argX;
	pos.y =argY;
	pointValue = argPointValue; //if this is INT_MAX, a rareSpawn has been hit.
}


FloatingScore::~FloatingScore(void)
{
}

void FloatingScore::displayPoint(LPD3DXFONT d3dxFont){
	static RECT textbox;
	char score[40] = {'+'};
	char strScore[20];
	int centerX, centerY;

	//determine the position of the textbox (to the right, relative the player)
	centerX = static_cast<int>(pos.x + POINT_OFFSET);
	centerY = static_cast<int>(pos.y - POINT_OFFSET);
	int width = 50;

	//move the textbox to the left if the texbox is positioned outside of the window
	if (centerX + width / 2  > WINDOW_WIDTH){
		centerX -= 3 * POINT_OFFSET;
	}

	//A rareSpawn has been hit
	if(pointValue == INT_MAX){

		Menus::displayText(d3dxFont, scoreDoubled, textbox, 
			centerX, centerY, width, DT_CENTER,
		alpha);
		return;
	}

	//create  a string representation of player's score
	_itoa_s(pointValue, strScore, 10); 
	strcat_s(score,strScore);

	LPCSTR str = (LPCSTR) &score;

	Menus::displayText(d3dxFont, str, textbox,
		centerX, centerY, width, DT_CENTER, alpha);
	
	
}

void FloatingScore::move(Velocity *v){
	pos.y -= v->getSpeed();
}

void FloatingScore::fade(){
	alpha -= FADE_FACTOR;
}

int FloatingScore::getAlpha() const{
	return alpha;
}