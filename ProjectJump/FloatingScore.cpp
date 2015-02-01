#pragma once
#include "FloatingScore.h"
#include "Menus.h"


LPCSTR FloatingScore::scoreDoubled = "x2!";

FloatingScore::FloatingScore(int argX=0,int argY=0,int argPointValue=0): ListElement()
{
	alpha = 255; //set full visibility
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
	int leftCornerX, leftCornerY;
	int rightCornerX, rightCornerY;

	//determine the position of the textbox (to the right, relative the player)
	leftCornerX = pos.x + POINT_OFFSET;
	leftCornerY = pos.y - POINT_OFFSET*2;
	rightCornerX = leftCornerX + POINT_OFFSET*7;
	rightCornerY = leftCornerY + POINT_OFFSET*2;

	//move the textbox to the left if the texbox is positioned outside of the window
	if(rightCornerX > WINDOW_WIDTH){
		leftCornerX-= 7*POINT_OFFSET;
		rightCornerX -= 7*POINT_OFFSET;
	}

	if(pointValue == INT_MAX){

		Menus::displayText(d3dxFont, scoreDoubled, textbox, 
		leftCornerX, leftCornerY, rightCornerX, rightCornerY);
		return;
	}

	//create  a string representation of player's score
	_itoa_s(pointValue, strScore, 10); 
	strcat_s(score,strScore);

	LPCSTR str = (LPCSTR) &score;

	Menus::displayText(d3dxFont, str, textbox, 
		leftCornerX, leftCornerY, rightCornerX, rightCornerY);
	
	
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