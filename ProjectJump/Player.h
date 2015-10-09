// Third-party libraries: BigInt (http://mattmccutchen.net/bigint/).

#include <chrono>
#include <d3d9.h>
#include "debug.h"
#include "Sprite.h"
#include "Velocity.h"
#include "BigIntegerLibrary.hh" //third-party

#pragma once

#define Y_ACCEL 0.07 
#define X_ACCEL 0.05 

//y- point at which the player stops moving, and bubbles start to move instead
#define MAX_PLAYER_HEIGHT 250

#define PLAYER_SPRITE_WIDTH 32
#define PLAYER_SPRITE_HEIGHT 32

const FLOAT X_TOP_SPEED = 2.75f;

const std::chrono::milliseconds frameDelay(105);

class Player : public Sprite
{
public:
	Player(LPDIRECT3DDEVICE9 d3d);

	virtual ~Player(void);

	bool moveY(); //true if player moved in the latest frame
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
	bool maxHeight() const; 
	
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
	const SpriteRect *const sinking;	//constant pointer, constant data (static sprite).
	SpriteRect *const swimming;		    //constant pointer, non-constant data.

	// Used with PLAYER_ANIMATION_CONSTANT to decide when to move sprite frame.
	//TODO: I want this to be time-dependent.
	std::chrono::steady_clock::time_point prevAnimFrame;

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

