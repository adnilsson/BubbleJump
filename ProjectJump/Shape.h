#pragma once


namespace customShapes{

	class Circle;
	class Rectangle;
	
	// A shape in 2D-space
	class Shape{
	public:
		Shape(double argX = 0, double argY = 0);
		virtual ~Shape();

		// I reaallly want to pass a shape into a single function
		virtual double getDistance(const Circle&) const = 0;
		virtual double getDistance(const Rectangle&) const = 0;

		double getX() const;
		double getY() const;

		void setY(double argY){ y = argY; };
		void setX(double argX){ x = argX; };
	private:
		double x, y; //The center position 
	};



	class Circle : public Shape{
	public:
		Circle(unsigned int initRad = 1) :Shape(), radius(initRad){};
		Circle(unsigned int initRad, double x, double y) :Shape(x, y),
			radius(initRad){};
		virtual ~Circle(){};

		unsigned int getRadius() const;
		double getDistance(const Circle&) const;
		double getDistance(const Rectangle&) const;
		
	private:
		const unsigned int radius;
	};


	class Rectangle : public Shape{
	public:
		Rectangle(unsigned int argWidth = 1, unsigned int argHeight = 1) :Shape(),
			width(argWidth), height(argHeight){};
		Rectangle(unsigned int argWidth, unsigned int argHeight, double x, double y) :
			Shape(x, y),
			width(argWidth), height(argHeight){};
		virtual ~Rectangle(){};

		unsigned int getWidth() const;
		unsigned int getHeight() const;

		double getDistance(const Circle&) const;
		double getDistance(const Rectangle&) const;
	private:
		const unsigned int width, height;
	};


}