#include <d3d9.h>

#ifndef GAME_CONSTANTS
#define GAME_CONSTANTS

//Check if a key is pressed
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

//screen resoulution
#define SCREEN_WIDTH  1920
#define SCREEN_HEIGHT 1080

//Game Window dimentions
#define WINDOW_WIDTH  400
#define WINDOW_HEIGHT 700

#define PLAYER_RADIUS 9
#define BUBBLE_INIT_RADIUS 16		//you start with the largest bubble
#define BUBBLE_MIN_RADIUS 5			//the smallest bubbles has a radius of 5px
#define PLAYER_ANIMATION_CONSTANT 10 //Animation speed constant

//textbox sizes
#define SCOREBOX_HEIGHT 20

//Texture paths
#define PLAYER_TEXTURE     L"newPlayer.png"
#define BUBBLE_TEXTURE     L"bubbles.png"
#define RARE_SPAWN_TEXTURE L"hitlerpus.png"


//Define what information should be contained in our vertices
#define CUSTOM_FVF (D3DFVF_XYZ  | D3DFVF_NORMAL )

//Stuct representing a vertex on the CUSTOM_FVF format
struct CUSTOMVERTEX {FLOAT X, Y, Z; D3DVECTOR normal;};

enum game_state{
	MAIN_MENU, 
	GAME_RUNNING, 
	GAME_PAUSED,
	PRE_GAME_OVER,
	GAME_OVER
};


#endif




