#include "Bubble.h"
#include "preproceccors.h"


const int Bubble::pointIncrement = 5;
unsigned int  Bubble::pointValue = pointIncrement;
int  Bubble::baseRadius = BUBBLE_INIT_RADIUS;

Bubble::Bubble(LPDIRECT3DDEVICE9 d3d, FLOAT posX, int lvl): 
	offset(BUBBLE_INIT_RADIUS), Sprite(d3d, BUBBLE_TEXTURE), ListElement()
{ 
	radius = baseRadius;
	x = posX;
	y = -radius;
	
	setPosition();

	D3DXVECTOR3 zero(offset, offset, 0.0f);
	center = zero;
	
	//Draw the correct part of the bubble sprite.
	int xPos = lvl * BUBBLE_SPRITE_WIDTH;
	SetRect(&spritePart, xPos, 0 , xPos+BUBBLE_SPRITE_WIDTH, BUBBLE_SPRITE_HEIGHT);
	

}

Bubble::~Bubble(void)
{
	//deletion of last bubble
	if(this->getNext() == nullptr)
		pointValue = pointIncrement;
}


void Bubble::move(Velocity *v){
	y = y - v->getSpeed(); 
	setPosition();
}

void Bubble::incPoint(){
	pointValue += pointIncrement;
}

void Bubble::decRadius(){
	if(baseRadius > BUBBLE_MIN_RADIUS){
		baseRadius -= BUBBLE_DECREASE;
	}
}


void Bubble::place(FLOAT yPos){
	y = yPos;
	setPosition();
}


//getter
int Bubble::getRadius() const{
	return radius;
}

unsigned int Bubble::getBaseRadius(){
	return baseRadius;
}

RECT Bubble::getSpritePart() const{
	return spritePart;
}

int Bubble::getPointValue(){
	return pointValue;
}