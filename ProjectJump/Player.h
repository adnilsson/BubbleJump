// Third-party libraries: BigInt (http://mattmccutchen.net/bigint/).

#include <d3d9.h>
#include "debug.h"
#include "Sprite.h"
#include "Velocity.h"
#include "BigIntegerLibrary.hh" //third-party

#pragma once

#define Y_ACCEL 0.07 
#define X_ACCEL 0.05 

//Player stops moving, and bubbles shold move instead, if max height is reached
#define MAX_PLAYER_HEIGHT 250

#define PLAYER_SPRITE_WIDTH 32
#define PLAYER_SPRITE_HEIGHT 32

const FLOAT X_TOP_SPEED = 2.75f;

class Player : public Sprite
{
public:
	Player(LPDIRECT3DDEVICE9 d3d);

	virtual ~Player(void);

	bool moveY(); //give true if player moved
	void moveX( );
	void accelerate();
	void resetX(bool); //Set x-movement to (+-) X_TOP_SPEED
	void setCollision(bool);
	HRESULT drawPlayer(LPD3DXSPRITE);

	//Getters
	FLOAT getOffset() const;
	FLOAT getRadius() const;
	Velocity* getVelocity() const;
	FLOAT getSpeed() const;
	BigInteger getScore() const;
	RECT getSpritePart() const;
	bool getCollision() const;
	bool MaxHeight() const; //change to lower case
	
	std::string getFormatedScore();
	std::string scoreToString() const;

	void incScore();
	void doubleScore();
	void checkHeight();
	bool gameOverCheck();

private:
	const FLOAT radius;
	float offset;		//rect offset to display the correct sprite	
	
	RECT spritePart;
	const SpriteRect *const sinking;	//constant pointer, constant data.
	SpriteRect *const swimming;		    //constant pointer, non-constant data.

	int counter; 

	Velocity *velocity;
	Velocity *xVelocity;

	BigInteger  score;

	bool atMaxHeight; //to keep track if player or bubbles should be moved.
	bool hasCollided;

	void adjustSwimFrame();
	BOOL setSpriteRect();
	bool isSinking(){return velocity->getDirection(); };
	bool animateForward;		//true -> The swim animation is moving to the right
};

