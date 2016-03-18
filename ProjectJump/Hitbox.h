#pragma once
#include <memory>
#include "Shape.h"


//A Hitbox is static in a sprite.
class Hitbox{
public:
	Hitbox(bool kill = false) : willKill(kill){};
	Hitbox(customShapes::Circle *, bool kill = false);
	Hitbox(customShapes::Rectangle *, bool kill = false);
	virtual ~Hitbox();

	bool willItKill() const;
	void setShape( customShapes::Shape *);

	double getX() const;
	double getY() const;
	const customShapes::Shape & getShape() const;

	void setY(double argY);
	void setX(double argX);
private:
	const bool willKill;
	std::unique_ptr <customShapes::Shape> box;
};

