#include "preproceccors.h"
#include <random>
#include "RareSpawn.h"
#include <time.h>


extern FLOAT distance(FLOAT, FLOAT, FLOAT, FLOAT);

RareSpawn::RareSpawn(LPDIRECT3DDEVICE9 d3d, FLOAT posX):
     Sprite(d3d, RARE_SPAWN_TEXTURE), ListElement(){

		 x = posX;
		 y = -RARE_SPRITE_HEIGHT;
		 center = D3DXVECTOR3(0.0f,0.0f,0.0f);
		 xVelocity = new Velocity(X_VELOCITY,X_VELOCITY);

		 setPosition();

}


RareSpawn::~RareSpawn(void)
{
	delete xVelocity;
}


void RareSpawn::moveY(Velocity *v){
	y += abs(v->getSpeed());
	setPosition();
}

void RareSpawn::moveX(){
	
	FLOAT deltaX = xVelocity->getSpeed();
	
	if(xVelocity->getDirection()){
		//(direction == true) means to the right
		
		if(x + deltaX < WINDOW_WIDTH - RARE_SPRITE_WIDTH)
			x += xVelocity->getSpeed();
		else xVelocity->flipVelocity();
		setPosition();
		return;
	}
	//Otherwise we move to the left
	else if(x - deltaX > 0){
		x -= xVelocity->getSpeed();
		setPosition();
	}
	else xVelocity->flipVelocity();
	
}


//Collision is between a circle (player) and a rectangle (rare spawn).
//The hit-box of a RareSpawn is equal to its sprite dimensions.
//The center of a RareSpawn is the top left corner of the sprite.
bool RareSpawn::collisionCheck(Player *player){

	const FLOAT playerX = player->getX();
	const FLOAT playerY = player->getY();
	FLOAT closestX, closestY, rareX, rareY;

	Velocity *v = player->getVelocity();


	rareX = this->getX();
	rareY = this->getY();

	//find closestX		
	if (playerX < rareX)
		closestX = rareX; //Player is to the left of temp's hit-box
	else if (playerX > rareX + RARE_SPRITE_WIDTH)
		closestX = rareX + RARE_SPRITE_WIDTH; //Player is to the right - || -
	else
		closestX = playerX; //Player's x-pos coincide with temp's x-pos

	//find closestY, analogous to finding closestX
	if (playerY < rareY)
		closestY = rareY; //above temp's hit-box
	else if (playerY > rareY + RARE_SPRITE_HEIGHT)
		closestY = rareY + RARE_SPRITE_HEIGHT; //below...
	else
		closestY = playerY; //coordinates coincide

	//if collision has occurred
	if (distance(playerX, playerY, closestX, closestY)
		< player->getRadius()){
		
		Vector *b = v->getVector();
		v->resetSpeed();
		b->size -= BONUS_SPEED;

		//Make sure the player is moving upward after collision.
		if (v->getDirection())  v->flipVelocity(); 
		
		player->doubleScore();	//Give points
		return true;
	}


	return false;
}
