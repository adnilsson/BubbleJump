#include "Hitbox.h"


Hitbox::Hitbox( customShapes::Circle *shape, bool kill): 
box(shape), willKill(kill){
}

Hitbox::Hitbox(customShapes::Rectangle *shape, bool kill) :
box(shape), willKill(kill){
}


Hitbox::~Hitbox()
{
}

bool Hitbox::willItKill() const{
	return willKill;
}

void Hitbox::setShape(customShapes::Shape *newShape){
	box.reset(newShape);
}

double Hitbox::getX() const{
	return box.get()->getX();
}

double Hitbox::getY() const{
	return box.get()->getY();
}


const customShapes::Shape& Hitbox::getShape() const{
	return *(box.get());
}

void Hitbox::setX(double argX){
	return box.get()->setX(argX);
}

void Hitbox::setY(double argY){
	return box.get()->setY(argY);
}
