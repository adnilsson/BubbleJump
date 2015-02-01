#pragma once
#include "RareSpawn.h"
#include "List.h"
#include "Player.h"

class RareSpawnList :
	public List
{
public:

	RareSpawnList(LPDIRECT3DDEVICE9 d3d);
	virtual ~RareSpawnList(void);

	void traverseList(LPD3DXSPRITE d3dSprite);
	void moveRaresY(Velocity *v);
	void moveRaresX();
	void spawn(LPDIRECT3DDEVICE9 d3d);

	bool collisionCheck(Player *player);
};

