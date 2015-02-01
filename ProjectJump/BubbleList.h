#include "Bubble.h"
#include "Player.h"
#include "List.h"
#include "Velocity.h"
#include <d3dx9.h>

#pragma once

class BubbleList: public List
{
public:
	BubbleList(LPDIRECT3DDEVICE9 d3d, int interval = 100);
	~BubbleList(void);

	void traverseList(LPD3DXSPRITE d3dSprite);
	void moveBubbles(Velocity *v);
	void spawnOneBubble(LPDIRECT3DDEVICE9 d3d, unsigned int level);

	bool collisionCheck(Player *player);
	
	void setMove(bool);

};

