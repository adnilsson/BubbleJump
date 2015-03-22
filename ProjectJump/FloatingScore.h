#pragma once
#include "ListElement.h"
#include "Velocity.h"
#include <d3dx9.h>

#define FADE_FACTOR 3
#define POINT_OFFSET 25

struct position{
	FLOAT x;
	FLOAT y;
};

class FloatingScore :
	public ListElement
{
public:
	FloatingScore(FLOAT, FLOAT, int);
	virtual ~FloatingScore(void);

	void displayPoint(LPD3DXFONT);
	void move(Velocity*);
	void fade();

	int getAlpha() const;

private:
	position pos;
	int pointValue;
	int alpha;
	static LPCSTR scoreDoubled;
 
};

