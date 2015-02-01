#include "list.h"
#include "FloatingScore.h"
#include "preproceccors.h"
#include <d3dx9.h>

#pragma once

class PointsList :
	public List
{
public:
	PointsList(void);
	~PointsList(void);

	void traverseList(LPD3DXFONT, game_state = GAME_RUNNING);
	void moveText(Velocity*);
};

