#include "sprite.h"
#include "ListElement.h"
#include "Velocity.h"

#pragma once

//Sprite dimensions
#define BUBBLE_SPRITE_WIDTH 32		//each bubble sprite is 32px wide
#define BUBBLE_SPRITE_HEIGHT 32	
#define BUBBLE_INIT_RADIUS 16		//you start with the largest bubble
#define BUBBLE_MIN_RADIUS 5			//the smallest bubbles has a radius of 5px

//Game-dependent constants
#define BUBBLE_DECREASE 1			//the radius is decreased by 1px between each bubble sprite.
#define BUBBLE_LEVELS 12			//there are 13 different bubble sprites, indexed from 0.


class Bubble : public Sprite, public ListElement
{
public:
	Bubble(LPDIRECT3DDEVICE9 d3d, FLOAT posX, int lvl);
	virtual ~Bubble(void);

	static const int pointIncrement;

	void move(Velocity *v);
	void place(FLOAT Y);
	
	static void incPoint();
	static void decRadius();

	int getRadius() const;
	RECT getSpritePart() const;
	static unsigned int getBaseRadius();
	static int getPointValue();
	

private:
	const FLOAT offset;
	int radius;
	RECT spritePart;
	static unsigned int pointValue; //points given by a bubble, initially 10
	static int	baseRadius; //radius assigned to new bubbles, initially 16
};

