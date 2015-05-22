#include "Velocity.h"
#include "preproceccors.h"


Velocity::Velocity(void) :startVelocity(-6.0f)
{
	velocity = new Vector(true, startVelocity);
}

Velocity::Velocity(FLOAT initVelocity, FLOAT resetVelocity):startVelocity(resetVelocity)
{
	velocity = new Vector(true, initVelocity);
}


Velocity::~Velocity(void)
{
	delete velocity;
}


void Velocity::flipVelocity(){
	velocity->direction = !(velocity->direction);
}

void Velocity::setDirection(bool dir){
	velocity->direction = dir;
}

void Velocity::resetSpeed(){
	if(velocity->size > startVelocity)
		velocity->size = startVelocity;
}

//used with movement along the x-axis
void Velocity::resetSpeed(bool leftKey){
	if(leftKey) velocity->size = -startVelocity;
	else velocity->size = startVelocity;
}

Vector* Velocity::getVector()const{
	return velocity;
}

/*Returns true if going down or right depending on 
what direction the vector describes.*/
bool Velocity::getDirection()const{	
	return velocity->direction;
}

//Gives the magnitude of the vector.
FLOAT Velocity::getSpeed()const{
	return velocity->size;
}
