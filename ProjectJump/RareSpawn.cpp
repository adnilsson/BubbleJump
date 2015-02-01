#include "preproceccors.h"
#include "RareSpawn.h"



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

