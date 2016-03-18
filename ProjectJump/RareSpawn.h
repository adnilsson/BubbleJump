#pragma once
#include "Hitbox.h"
#include "ListElement.h"
#include <memory>
#include "Player.h"
#include "sprite.h"
#include "Shape.h"
#include "Velocity.h"

//New Sprite sheet dimensions
/*const auto RARE_SPRITE_WIDTH  = 256;
const auto RARE_SPRITE_HEIGHT =  1024;	*/

#define RARE_SPRITE_WIDTH 64		
#define RARE_SPRITE_HEIGHT 32	

#define X_VELOCITY 3
#define BONUS_SPEED 3

class RareSpawn: public Sprite
{
public:
	RareSpawn(LPDIRECT3DDEVICE9 d3d, FLOAT posX);
	virtual ~RareSpawn(void);

	void moveY(Velocity *V);
	void moveX();

	bool collisionCheck(Player *player);
	void spawn(LPDIRECT3DDEVICE9 d3d);
	
	// When integrating the new sprite, use this to draw the correct part of the sheet
	//HRESULT drawRareSpawn(LPD3DXSPRITE sprite);
private:
	Velocity *xVelocity;

	Hitbox monsterHitbox;
	
	// New sprite stuff
	/*bool isTurning;		// Only true when changing direction

	RECT spritePart;	//The part that is drawn/rendered
	
	//constant pointer, non-constant data.
	SpriteRect *const movingRight;
	SpriteRect *const leftTurn1; 
	SpriteRect *const leftTurn2; 
	SpriteRect *const leftTurn3;

	SpriteRect *const movingLeft;
	SpriteRect *const rightTurn1; 
	SpriteRect *const rightTurn2; 
	SpriteRect *const rightTurn3;*/

	//TODO Hit/Killboxes
	/* Because every hitbox have to be checked separatly it makes sense
	  to have an array/list of hitboxes that can easaly be iterated over . */ 

};

