#pragma once
#include "RareSpawnList.h"
#include <random>
#include <time.h>
#include "preproceccors.h"


//Defined in BubbleList.cpp
extern FLOAT distance(FLOAT, FLOAT,FLOAT, FLOAT);

RareSpawnList::RareSpawnList(LPDIRECT3DDEVICE9 d3d): List()
{

}


RareSpawnList::~RareSpawnList(void)
{
	RareSpawn *i = (RareSpawn*) getHead();
	RareSpawn *tmp;

	//Remove all elements inside the list.
	while(i != NULL){	

		tmp = (RareSpawn*) i->getNext();
		removeElement(i);
		i = tmp;
	}

}

void RareSpawnList::traverseList(LPD3DXSPRITE d3dSprite){
	RareSpawn *i = (RareSpawn*) getHead();

	while(i != NULL){

		//Remove if the RareSpawn isn't visible
		if(i->getY() >= WINDOW_HEIGHT ){
					RareSpawn *tmp = (RareSpawn*) i->getNext();
					removeElement(i);
					i = tmp;
					continue;
		}

		if(i->drawSprite(d3dSprite) != D3D_OK){
			break;
		}

		i = (RareSpawn*) i->getNext();
	}

}

void RareSpawnList::moveRaresY(Velocity *v){
	RareSpawn *temp =  (RareSpawn*) getHead();
	
	while(temp != NULL){
		temp->moveY(v);
		temp = (RareSpawn*) temp->getNext();
	}

}

void RareSpawnList::moveRaresX(){
	RareSpawn *temp =  (RareSpawn*) getHead();
	
	while(temp != NULL){
		temp->moveX();
		temp = (RareSpawn*) temp->getNext();
	}
}


void RareSpawnList::spawn(LPDIRECT3DDEVICE9 d3d){
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(0,(WINDOW_WIDTH - RARE_SPRITE_WIDTH));

	int randomX  = dist(mt);
	RareSpawn *element = new RareSpawn(d3d, static_cast<FLOAT>(randomX));
	addElement(element);
}


//Collision is between a circle (player) and a rectangle (rare spawn).
//The hit-box of a RareSpawn is equal to its sprite dimensions.
//The center of a RareSpawn is the top left corner of the sprite.
bool RareSpawnList::collisionCheck(Player *player){
	
	const FLOAT playerX = player->getX();
	const FLOAT playerY = player->getY();
	FLOAT closestX, closestY, rareX, rareY;
	//boolean hasCollided = false;

	Velocity *v = player->getVelocity();

	RareSpawn *temp = (RareSpawn*) getHead();

	while(temp != NULL){

		rareX = temp->getX();
		rareY = temp->getY();

		//find closestX		
		if(playerX < rareX)		
			closestX = rareX; //Player is to the left of temp's hit-box
		else if (playerX > rareX + RARE_SPRITE_WIDTH)	
			closestX = rareX + RARE_SPRITE_WIDTH; //Player is to the right - || -
		else    
			closestX = playerX; //Player's x-pos coincide with temp's x-pos

		//find closestY, analogous to finding closestX
		if(playerY < rareY)
			closestY = rareY; //above temp's hit-box
		else if(playerY > rareY + RARE_SPRITE_HEIGHT)
			closestY = rareY + RARE_SPRITE_HEIGHT; //below...
		else 
			closestY = playerY; //coordinates coincide

		
		if(distance(playerX, playerY, closestX, closestY) 
			<  player->getRadius() ){
			//collision has occurred
			

			Vector *b = v->getVector();
			v->resetSpeed();
			b->size -= BONUS_SPEED;

			if(v->getDirection())  v->flipVelocity(); //Make sure the player is moving upward after collision.
			player->doubleScore();	//give points

			this->removeElement(temp);
			return true;
		}
		temp = (RareSpawn*) temp->getNext();  
	}

	return false;
}




