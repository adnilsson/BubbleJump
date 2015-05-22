#include <d3d9.h>
#include <d3dx9.h>
#include "debug.h"
#pragma once

class Sprite
{
public:
	
	struct SpriteRect{
		SpriteRect(int xLeft, int xRight, int yTop, int yBottom){
			this->xLeft = xLeft;
			this->xRight = xRight;
			this->yTop = yTop;
			this->yBottom = yBottom;
		}
		int xLeft, xRight;
		int yTop, yBottom;
	};

	Sprite(LPDIRECT3DDEVICE9 d3d,LPCTSTR texturePath);
	virtual ~Sprite(void);

	HRESULT drawSprite(LPD3DXSPRITE d3dSprite);
	HRESULT drawSpritePart(LPD3DXSPRITE d3dSprite, const RECT pPart);

	const D3DXVECTOR3 getPosition();
	void setPosition();

	FLOAT getY() const;
	FLOAT getX() const;

protected:
		FLOAT x, y;
		D3DXVECTOR3 position;
		D3DXVECTOR3 center;
		LPDIRECT3DTEXTURE9 sprite;	//Pointer to sprite texture

};

