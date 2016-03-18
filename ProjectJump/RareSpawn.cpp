#include "preproceccors.h"
#include <random>
#include "RareSpawn.h"
#include <time.h>


//extern FLOAT distance(FLOAT, FLOAT, FLOAT, FLOAT);

RareSpawn::RareSpawn(LPDIRECT3DDEVICE9 d3d, FLOAT posX)
	:Sprite(d3d, RARE_SPAWN_TEXTURE),
	monsterHitbox(Hitbox(new customShapes::Rectangle(RARE_SPRITE_WIDTH, RARE_SPRITE_HEIGHT,
	x, y), false))
	/*movingRight(new SpriteRect(0, 64, 0, 128)),
	leftTurn1(new SpriteRect(0, 64, 128, 256)),
	leftTurn2(new SpriteRect(0, 64, 256, 384)),
	leftTurn3(new SpriteRect(0, 64, 384, 512)),
	movingLeft(new SpriteRect(0, 64, 512, 640)),
	rightTurn1(new SpriteRect(0, 64, 640, 768)),
	rightTurn2(new SpriteRect(0, 64, 768, 896)),
	rightTurn3(new SpriteRect(0, 64, 896, 1024))*/{


	// TODO: Make moving right or left, choose arbitrarly
	/*if (SetRect(&spritePart, 0, 0, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT) == 0){
		MessageBox(NULL,
			(LPCWSTR)L"SetRect failed in RareSpawn constructor.",
			(LPCWSTR)L"Error",
			MB_ICONERROR | MB_OK);
		return;
	}*/

	x = posX;
	y = -RARE_SPRITE_HEIGHT;
	center = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	xVelocity = new Velocity(X_VELOCITY, X_VELOCITY);

	setPosition();

}


RareSpawn::~RareSpawn(void)
{
	delete xVelocity;
}


/* Movement Pattern:
	1. go from right to left
	2. when the edge is reached, turn right
	3. go from left to right
	4. when the edge is reached, turn left
	5. repeat
Starts from either 1 or 3.
*/
/*HRESULT RareSpawn::drawRareSpawn(LPD3DXSPRITE sprite){

}*/

void RareSpawn::moveY(Velocity *v){
	y += abs(v->getSpeed());
	monsterHitbox.setY(y);
	setPosition();
}

void RareSpawn::moveX(){
	
	FLOAT deltaX = xVelocity->getSpeed();
	
	if(xVelocity->getDirection()){
		//(direction == true) means to the right
		
		if (x + deltaX < WINDOW_WIDTH - RARE_SPRITE_WIDTH){
			x += xVelocity->getSpeed();
			monsterHitbox.setX(x);
		}
		else xVelocity->flipVelocity();
		setPosition();
		return;
	}
	//Otherwise we move to the left
	else if(x - deltaX > 0){
		x -= xVelocity->getSpeed();
		monsterHitbox.setX(x);
		setPosition();
	}
	else xVelocity->flipVelocity();
	
}


//Collision is between a circle (player) and either two rectangles XOR a
// rectangle and two circles(rare spawn).
//The hit-box of a RareSpawn is equal to its sprite dimensions. <--- NO LONGER TRUE
//The center of a RareSpawn is the top left corner of the sprite.
bool RareSpawn::collisionCheck(Player *player){

	using namespace customShapes;

	Circle playerHitbox =  Circle(9, player->getX(), player->getY());
	//customShapes::Rectangle monsterHitbox = customShapes::Rectangle(RARE_SPRITE_WIDTH, RARE_SPRITE_HEIGHT, this->getX(), this->getY());
	const customShapes::Rectangle &tmp = dynamic_cast<const customShapes::Rectangle &> (monsterHitbox.getShape());

	if (playerHitbox.getDistance(tmp) <= 0) {
		Velocity *v = player->getVelocity();
		Vector *b = v->getVector();
		v->resetSpeed();
		b->size -= BONUS_SPEED;

		//Make sure the player is moving upward after collision.
		if (v->getDirection())  v->flipVelocity();

		player->doubleScore();	//Give points
		return true;
	}
	return false;
	/*const FLOAT playerX = player->getX();
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


	return false;*/
}
