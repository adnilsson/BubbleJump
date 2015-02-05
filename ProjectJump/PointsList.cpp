#include "PointsList.h"


PointsList::PointsList(void): List()
{
}


PointsList::~PointsList(void)
{
}

//draw and fade every FloatingScore in the list.
void PointsList::traverseList(LPD3DXFONT d3dxFont, game_state state){


	//The first element will fade first, so check if head needs to be removed.
	if( getHead() != nullptr && 
		((FloatingScore*) getHead())->getAlpha() - FADE_FACTOR < 0){
		
		removeElement(getHead());
	}

	FloatingScore *temp = (FloatingScore*) getHead();

	while(temp != nullptr){
			
		temp->displayPoint(d3dxFont); 
		if(state == GAME_RUNNING) temp->fade();
		temp = (FloatingScore*) temp->getNext();
	}
}


void PointsList::moveText(Velocity *v){
	FloatingScore *temp = (FloatingScore*) getHead();

		while(temp != nullptr){
			
			temp->move(v); 
			temp = (FloatingScore*) temp->getNext();
		}
}