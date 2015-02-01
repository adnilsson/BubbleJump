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

	//Getters
	FLOAT getOffset() const;
	FLOAT getRadius() const;
	Velocity* getVelocity() const;
	FLOAT getSpeed() const;
	BigInteger getScore() const;
	bool getCollision() const;
	
	std::string getFormatedScore();

	void incScore();
	void doubleScore();

	bool MaxHeight() const;
	void checkHeight();
	bool gameOverCheck();

private:
	const FLOAT radius, offset;
	BigInteger  score;
	
	Velocity *velocity;
	Velocity *xVelocity;
	
	bool atMaxHeight; //to keep track if player or bubbles should be moved.
	bool hasCollided;
};

