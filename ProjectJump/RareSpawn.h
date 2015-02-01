#pragma once
#include "sprite.h"
#include "ListElement.h"
#include "Velocity.h"


#define RARE_SPRITE_WIDTH 64		
#define RARE_SPRITE_HEIGHT 32	

#define X_VELOCITY 3
#define BONUS_SPEED 3

class RareSpawn :
	public Sprite, public ListElement
{
public:
	RareSpawn(LPDIRECT3DDEVICE9 d3d, FLOAT posX);
	virtual ~RareSpawn(void);

	void moveY(Velocity *V);
	void moveX();

private:
	Velocity *xVelocity;
};

