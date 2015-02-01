//--------------------------------------------------------------------------------------
// File: main.cpp
//
// Desc: * Main file. Creates and initializes the window and the needed DirectX 9 interfaces. 
//       * Contains the Game object, used for logic and rendering.
//       * Listens to window events, and changes the game state on relevant key-events.
//
//
// Author: Adrian Nilsson
//--------------------------------------------------------------------------------------

#include "AppWnd.h"
#include "WndCls.h"
#include "preproceccors.h"
#include <d3d9.h>
#include <windowsx.h>
#include <d3dx9.h>
#include "Player.h"
#include "Bubble.h"
#include "Game.h"
#include "BubbleList.h"
#include "Velocity.h"
#include <string>
#include <iostream>

#pragma once

//The D3D library file will be placed in projects object file
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

//Globals
LPCTSTR className = L"GameWindow";
LPCTSTR windowName = L"ProjectJump";
LPDIRECT3D9 d3d;			//pointer to Direct3D interface
LPDIRECT3DDEVICE9 d3ddev;	//pointer to device class. The d3d device handles rendering
LPD3DXSPRITE d3dSprite;		//Pointer to Direct3D Sprite interface
LPD3DXFONT d3dxFont;		//Pointer to a font object used to display text.
Game *game;

//function declarations d3d
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void initD3D(HWND hWnd);
void init_graphics();
void cleanD3D();


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){

	//intialize/setup the window class
	WndCls windowClass(hInstance, className, WndProc);
	if(!windowClass.registerClsEX()){

		MessageBox(NULL, L"Error in registering window class", L"Error", MB_OK | MB_ICONERROR);
		
		return 0;
	}

	//Create and show the window
	AppWnd wnd;
	if (wnd.createWnd(hInstance, className, windowName, 
						SCREEN_WIDTH/2, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 
						NULL, 
						WS_OVERLAPPED | WS_CAPTION  | WS_SYSMENU) == NULL){ //check if window creation was sucessful
		MessageBox(NULL, L"Error in creating window", L"Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	else wnd.show(nCmdShow); 

	initD3D(wnd.getWnd());
	
	MSG msg;

	//Message loop (MAIN LOOP)
	while(true){

		while(PeekMessage(&msg, NULL , 0, 0, PM_REMOVE)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if(msg.message == WM_QUIT) break;

		//Draw sprites, texts and handle logic.
		game->render_frame(d3ddev, d3dSprite, d3dxFont); 

	}

	cleanD3D();
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){

	switch(msg){
	case WM_QUIT:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0); //WM_QUIT = 0
		break;
	case WM_KEYDOWN: //Catch desired key events.

		//If esc is pressed, exit programme.
		if(wParam == VK_ESCAPE) PostQuitMessage(0);

		else if(wParam == VK_SPACE){	        //Space has been pressed
			switch (game->getState()){
			case GAME_RUNNING:					//Pause game
				game->changeState(GAME_PAUSED);
				break;
			case GAME_PAUSED:					//Resume game
				game->changeState(GAME_RUNNING);
				break;
			case GAME_OVER:						//Restart game
				delete game;
				game = new Game(d3ddev);
				break;
			}
		}
		break;
	default:	 //no relevant message was received.
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}


void initD3D(HWND hWnd){

	d3d = Direct3DCreate9(D3D_SDK_VERSION); //Creates the Direct3D Interface

	D3DPRESENT_PARAMETERS d3dpp; //We need to know some properties beforhand, which are contained in this struct
	
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed		= true;					 //game is windowed
	d3dpp.SwapEffect	= D3DSWAPEFFECT_DISCARD; //We want to discard old frames
	d3dpp.hDeviceWindow = hWnd;					 //The window to be used with D3D
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;    //32-bit pixels, no alpha used 
	d3dpp.EnableAutoDepthStencil  = TRUE;        //Allow D3D set up a z-buffer for us.
	d3dpp.AutoDepthStencilFormat  = D3DFMT_D16;

	d3d->CreateDevice(D3DADAPTER_DEFAULT, //Define what video card D3D sould be using.
					  D3DDEVTYPE_HAL,	  //Hardware Abstraction Layer (HAL). Use hardware to process graphics
					  hWnd,				  //window to be associated with the device
					  D3DCREATE_SOFTWARE_VERTEXPROCESSING, //Use the cpu for 3D calculations (compabillity)
					  &d3dpp,			  
					  &d3ddev);			
	

	//initialize the 2D-Sprite interface
	D3DXCreateSprite(d3ddev, &d3dSprite);


	//initialize font object.
	D3DXCreateFont(d3ddev,
				   20, 0,					// height, width (0 = default value)
				   FW_MEDIUM,				//boldness (weight) of text
				   1,
				   FALSE,					//no italics
				   DEFAULT_CHARSET,
				   OUT_DEFAULT_PRECIS,
				   DEFAULT_QUALITY,
				   DEFAULT_PITCH || FF_SWISS, //Spacing, fontFamily
				   L"Arial",				  //fontFace name
				   &d3dxFont			
				   );

	game = new Game(d3ddev);

	d3ddev->SetRenderState(D3DRS_LIGHTING, FALSE); //Turn off advanced 3D lightning. Everything is lit "automatically"
	d3ddev->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(50,50,50)); //Set the ambient light to a dark grey.

}

//Give windows back its memory.
void cleanD3D(){
	delete game;
	if(d3ddev != NULL) d3ddev->Release(); d3ddev = NULL;
	if(d3d != NULL) d3d->Release(); d3d = NULL;
	if(d3dxFont != NULL) d3dxFont->Release(); d3dxFont = NULL;
}



