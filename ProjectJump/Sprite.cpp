#include "Sprite.h"


Sprite::Sprite(LPDIRECT3DDEVICE9 d3d, LPCTSTR texturePath): x(0), y(0){

	HRESULT check;
	check = D3DXCreateTextureFromFileEx(d3d, texturePath,D3DX_DEFAULT, D3DX_DEFAULT, 0, 
								NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,D3DX_DEFAULT, D3DX_DEFAULT, 
								D3DCOLOR_XRGB(255,0,255), NULL, NULL, &sprite); //Load a sprite texture
	
	if(check!= D3D_OK)MessageBox( NULL,
        (LPCWSTR)L"Failed to create texture from file",
        (LPCWSTR)L"Error",
		MB_ICONERROR | MB_OK); 

}


Sprite::~Sprite(void)
{
	if(sprite!=NULL)sprite->Release();
}

HRESULT Sprite::drawSprite(LPD3DXSPRITE d3dSprite){
		
	return d3dSprite->Draw(sprite, NULL, &center, &position, D3DCOLOR_ARGB(255,255,255,255));
}

HRESULT Sprite::drawSpritePart(LPD3DXSPRITE d3dSprite, const RECT pPart){
		
	return d3dSprite->Draw(sprite, &pPart, &center, &position, D3DCOLOR_ARGB(255,255,255,255));
}

//getters
const D3DXVECTOR3 Sprite::getPosition() {return position;}
FLOAT Sprite::getX() const {return x;}
FLOAT Sprite::getY() const {return y;}

void Sprite::setPosition(){
	D3DXVECTOR3 temp(x, y, 0.0f);
	
	position = temp;
}