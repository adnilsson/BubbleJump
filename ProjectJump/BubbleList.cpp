#include "BubbleList.h"
#include "preproceccors.h"
#include <time.h>
#include <math.h>
#include <random>
#include <iostream>

#pragma once


//Uses the pythagoran theorem to calculate the distance between two points
FLOAT distance(FLOAT x1, FLOAT y1,
               FLOAT x2 , FLOAT y2){
		
		return sqrt( pow(x2-x1, 2) + pow(y2-y1, 2) );
}


BubbleList::BubbleList(LPDIRECT3DDEVICE9 d3d, int interval) : List()
{
	Bubble* temp;

	//How many bubbles will fit the screen?
	int n = (WINDOW_HEIGHT -(BUBBLE_INIT_RADIUS*4 + interval)) / (interval); 

	for (int i = 0; i < n; i++){
		
		spawnOneBubble(d3d, 0);
		temp = (Bubble *) getHead(); 

		while(temp != nullptr){
			temp->place(temp->getY() + interval);
			temp = (Bubble*) temp->getNext();
		}

	}
	
	//The first bubble is positioned directly under the player
	Bubble * first = new Bubble(d3d, WINDOW_WIDTH/2,0);
	first->place(WINDOW_HEIGHT - BUBBLE_INIT_RADIUS * 4 );

	addElement(first);

	temp = nullptr;
	delete temp;
}



BubbleList::~BubbleList(void)
{

}

/* 

Uses a normal distribution to choose the coordinate for the new bubble
This will cause bubbles to tend to the center of the screen.

     
*/
void BubbleList::spawnOneBubble(LPDIRECT3DDEVICE9 d3d, unsigned int level){
	int upperBound = WINDOW_WIDTH - Bubble::getBaseRadius();
	int lowerBound = Bubble::getBaseRadius();
	FLOAT randomX;

	std::random_device rd;
	std::mt19937 mt(rd());
	std::normal_distribution<double> nd((WINDOW_WIDTH/2) /*mean*/, 
		                                 85 /*standard dev.*/);

	//Generate random coordinates between bubble_radius and ½*(WINDOW_WIDTH)
	do{
		randomX =  static_cast<FLOAT>(nd(mt));
	}
	while(randomX < lowerBound || randomX > upperBound);


	Bubble *element = new Bubble(d3d, randomX, level);
	addElement(element);
}

 
void BubbleList::traverseList(LPD3DXSPRITE d3dSprite){
		Bubble *temp = (Bubble*) getHead();

		while(temp != nullptr){
			//remove a bubble if its not visible
			if(temp->getY() >= WINDOW_HEIGHT + temp->getRadius()){
					Bubble *tmp = (Bubble*) temp->getNext();
					removeElement(temp);
					temp = tmp;
					continue;
				}
			//draw bubble
			if(temp->drawSpritePart(d3dSprite, temp->getSpritePart()) != D3D_OK){
				break;
			}
			temp = (Bubble*) temp->getNext();
		}

}


bool BubbleList::collisionCheck(Player *player){
	
	const FLOAT pX = player->getX();
	const FLOAT pY = player->getY();

	Velocity *v = player->getVelocity();

	Bubble *temp = static_cast<Bubble*>(getHead());

	while(temp != nullptr){
		
		//see if distance between bubble and player is less than the sum of their radii
		if( distance(pX, pY, temp->getX(), temp->getY()) 
			< temp->getRadius() + player->getRadius()){
			//collision has occured

			v->resetSpeed();
			if(v->getDirection())  v->flipVelocity(); //Make sure the player is moving upward after collision.
			Bubble::incPoint();	//make bubbles worth more points
			

			this->removeElement(temp); //remove the hit bubble
			return true;
		}
		temp = (Bubble*) temp->getNext();
	}
	return false;
}



//Move all Bubbles in the BubbleList
void BubbleList::moveBubbles(Velocity *v){
	Bubble *temp = (Bubble*) getHead();

	while(temp != nullptr){
		temp->move(v); //move the bubble
		temp = (Bubble*) temp->getNext();
	}
}





