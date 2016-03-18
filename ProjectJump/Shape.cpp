#include <math.h>
#include "Shape.h"


using namespace customShapes;

double distCircleCircle(const Circle &circle1, const Circle &circle2);
double distCircleRect(const Circle &circle, const Rectangle &rect);
//double distRectRect(const Rectangle &rect1, const Rectangle &rect2); //Not needed in the game


//Uses the pythagoran theorem to calculate the distance between two points
double distance(double x1, double y1, double x2, double y2){
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
};


//----------------------------------------------------------------- 


Shape::Shape(double argX, double argY)
{
	x = argX; 
	y = argY;
}


Shape::~Shape()
{
}

double Shape::getX() const{
	return x;
}

double Shape::getY() const{
	return y;
}


//----------------------------------------------------------------- 

// is it possible for a constant reference, to be null? 
double Circle::getDistance(const Circle &otherCircle) const{
	return distCircleCircle(*this, otherCircle);
}

double Circle::getDistance(const Rectangle &rect) const{
	return distCircleRect(*this, rect);
}


unsigned int Circle::getRadius() const{
	return radius;
}


//----------------------------------------------------------------- 

double Rectangle::getDistance(const Circle &circle) const{
	return distCircleRect(circle, *this);
}

//Not yet implemented
double Rectangle::getDistance(const Rectangle &otherRect) const{
	return -1; 
}

unsigned int Rectangle::getWidth() const{
	return width;
}

unsigned int Rectangle::getHeight() const{
	return height;
}

//----------------------------------------------------------------- 


double distCircleCircle(const Circle &circle1, const Circle &circle2){
	return distance(circle1.getX(), circle1.getY(), circle2.getX(), circle2.getY());
}

//Edge to edge distance.
double distCircleRect(const Circle &circle, const Rectangle &rect){
	auto circleX = circle.getX();
	auto circleY = circle.getY();
	auto rectX = rect.getX();
	auto rectY = rect.getY();

	//The coordinates on the Rectangle's edge closest to the Circle
	double closestX, closestY;
	
	//find closestX
	if (circleX < rectX)
		closestX = rectX; // Circle is to the left of the Rectangle
	else if (circleX > rectX + rect.getWidth())
		closestX = rectX + rect.getWidth(); // Circle is to the right of the Rectangle
	else
		closestX = circleX; //The Circle's x-pos is the nearest x-cooridinate
	
	//find closestY, analogous to finding closestX
	if (circleY < rectY)
		closestY = rectY; //above temp's hit-box
	else if (circleY > rectY + rect.getWidth())
		closestY = rectY + rect.getWidth(); //below...
	else
		closestY = circleY; //coordinates coincide

	return distance(circleX, circleY, closestX, closestY) - circle.getRadius();
}

