#include <d3d9.h>
#include <d3dx9.h>
#include "debug.h"
#include "Sprite.h"

#pragma once

struct Vector{
	Vector(){};
	Vector(bool dir, FLOAT sSize = -1.0f){direction = dir; size = sSize;};

	bool direction; //Up or down (false/true), Left or Right (false/true)
	FLOAT size;
};

class Velocity
{
public:
	Velocity(void);
	Velocity(FLOAT initVelocity, FLOAT resetVelocity = -6.0f);
	virtual ~Velocity(void);


	Vector* getVector() const;
	bool	getDirection() const;
	FLOAT	getSpeed() const;

	void  setDirection(bool);
	void  resetSpeed();
	void  resetSpeed(bool);
	void  flipVelocity();  //Make velocity positive/negative (true/false) (down/up)

private: 
	Vector* velocity;
	const FLOAT startVelocity;
};

