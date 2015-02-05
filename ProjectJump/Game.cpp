#include "Game.h"
#include <time.h>
#include <random>

Game::Game(LPDIRECT3DDEVICE9 d3ddev):levelStep(250), level(0),
	spawnInterval(4*BUBBLE_INIT_RADIUS), maximumSpawnInterval(130), 
	spawnIncrement(BUBBLE_INIT_RADIUS/2)
{
	player = new Player(d3ddev);
	bubbles = new BubbleList(d3ddev, spawnInterval);
	rareSpawns = new RareSpawnList(d3ddev);
	menus = new Menus(d3ddev);
	Bubble *last = (Bubble *) bubbles->getTail();
	floatingPoints = new PointsList();

	currentState = GAME_RUNNING;
	bubbleSpacing = last->getY();

	D3DXCreateFont(d3ddev,
				   20, 0,	            //height, width (0 = default value)
				   FW_DEMIBOLD,	        //boldness (weight) of text
				   1,
				   FALSE,				//no italics
				   DEFAULT_CHARSET,
				   OUT_DEFAULT_PRECIS,
				   DEFAULT_QUALITY,
				   DEFAULT_PITCH || FF_SWISS, //Spacing, fontFamily
				   L"Arial",			      //fontFace name
				   &d3dxMenuFont			
				   );
}


Game::~Game(void)
{
	delete player;
	delete bubbles;
	delete rareSpawns;
	delete menus;
	delete floatingPoints;
	if(d3dxMenuFont != NULL){
		d3dxMenuFont->Release(); 
		d3dxMenuFont = NULL;
	}
}

//draws content according to current game state.
void Game::render_frame(LPDIRECT3DDEVICE9 d3ddev, LPD3DXSPRITE d3dSprite, LPD3DXFONT d3dxFont){
	
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0); //clear back buffer	

	d3ddev->BeginScene(); //Locks the back buffer
	d3dSprite->Begin(D3DXSPRITE_ALPHABLEND);

	
	switch(currentState){

		case(MAIN_MENU):
			render_menu(d3ddev, d3dSprite);
			break;

		case(GAME_RUNNING):
			//player->setCollision(bubbles->collisionCheck(player)); //check if there is any collision 

			//if there was a collision: Make it possible to display the points attained.
			if(bubbles->collisionCheck(player)){
				player->incScore();
				//Create a new floating point and add to the list of FloatingScores
				FloatingScore *point = new FloatingScore(player->getX()+PLAYER_RADIUS, 
										player->getY(), Bubble::getPointValue());
				
				floatingPoints->addElement(point);
				checkLevelUp();
			}
			else if(rareSpawns->collisionCheck(player)){

				FloatingScore *point = new FloatingScore(player->getX()+PLAYER_RADIUS, 
					player->getY(), INT_MAX);
				floatingPoints->addElement(point);

			}

			render_game(d3dSprite, d3dxFont); //Draw objects on screen.
			moveObjects(d3ddev); // Move game obejcts
			if(isGameOver()) changeState(GAME_OVER);

			break;

		case(GAME_PAUSED):
			bubbles->traverseList(d3dSprite);
			rareSpawns->traverseList(d3dSprite);
			player->drawSprite(d3dSprite);
			d3dSprite->End();

			//Text
			displayScore(d3dxFont);
			floatingPoints->traverseList(d3dxFont, currentState);
			menus->paused(currentState);
			break;

		case(GAME_OVER):
			bubbles->traverseList(d3dSprite);		
			rareSpawns->traverseList(d3dSprite);	
			d3dSprite->End();
			displayScore(d3dxFont);
			menus->game_over(currentState);
			break;
		default:
			OutputDebugString(L"Game.cpp: Unknown game state in render_frame()");
			break;
	
	}

	d3ddev->EndScene(); //unlocks the buffer

	//Flip the frame and back buffer to show our frame. parameters irrelevant to my intended use of D3D
	d3ddev->Present(NULL, NULL, NULL, NULL); 

}

void Game::render_game(LPD3DXSPRITE d3dSprite, LPD3DXFONT d3dxFont){

		
	bubbles->traverseList(d3dSprite); //Draw all bubbles
	rareSpawns->traverseList(d3dSprite);
	player->drawSprite(d3dSprite); //Draw the player
		
	d3dSprite->End(); //Finish drawing sprites
	
	//Draw text
	floatingPoints->traverseList(d3dxFont);
	displayScore(d3dxFont);
}

void Game::render_menu(LPDIRECT3DDEVICE9 d3ddev, LPD3DXSPRITE d3dSprite){

}


bool Game::isGameOver() const{
	if(player->getY() - PLAYER_RADIUS/2 > WINDOW_HEIGHT){
		return true;
	}
	return false;
}

void Game::displayScore(LPD3DXFONT d3dxFont){
	static RECT textbox;

	std::string score = "Score: ";  
	score.append(player->getFormatedScore());
	

	LPCSTR text = (LPCSTR) score.c_str();

	//show score in top left corner. 
	menus->displayText(d3dxFont, text, textbox,
		0, 0, 
		WINDOW_WIDTH, SCOREBOX_HEIGHT);

}



void Game::moveObjects(LPDIRECT3DDEVICE9 d3ddev){
	
		if(!player->moveY()){ //Move the player

		bubbleSpacing += abs(player->getSpeed()); //save change in height.
		
		rareSpawns->moveRaresY(player->getVelocity());
		bubbles->moveBubbles(player->getVelocity());
		floatingPoints->moveText(player->getVelocity());
		
		//enter if a new bubble is to be spawned.
		if(static_cast<int>(bubbleSpacing) >= spawnInterval){ 
			
			std::random_device rd;
			std::mt19937 mt(rd());
			std::uniform_int_distribution<int> dist(0,100);

			int random = dist(mt);

			if(random == 66 || random == 6){
				rareSpawns->spawn(d3ddev);
			}
			else{
				//Spawn a bubble to appear from top of window.
				bubbles->spawnOneBubble(d3ddev, level);
			}

			//reset distance distance since last spawn
			bubbleSpacing = 0.0f;
		}
	}

	// Movement along X-axis.
	
	//Check if right arrow key is pressed
	if(KEY_DOWN(VK_RIGHT)){ 
		if(player->getX() < WINDOW_WIDTH - 2*Bubble::getBaseRadius()){
			player->resetX(false);
		}
	}
	//Otherwise, check if left arrow key is pressed
	else if(KEY_DOWN(VK_LEFT) && player->getX() > player->getOffset()){
			player->resetX(true);
		}
	
	rareSpawns->moveRaresX();
	player->moveX();
	player->accelerate();
}

void Game::checkLevelUp(){
	int next = (Bubble::getPointValue() - (levelStep*level))  / levelStep;
	
	//Increase level if not already at max-level
	if(level < BUBBLE_LEVELS && next > 0 ){
		level += (Bubble::getPointValue() - (levelStep*level))  / levelStep ;	

		Bubble::decRadius();	//make new bubbles smaller.

		//Increase spawn interval if not already at greatest interval
		if(spawnInterval + BUBBLE_INIT_RADIUS > maximumSpawnInterval)
			spawnInterval = maximumSpawnInterval;
		else if (spawnInterval < maximumSpawnInterval) 
			spawnInterval += 8;
	}

}

void Game::changeState(game_state newState){
	currentState = newState;
}

game_state Game::getState() const{
	return currentState;
}

unsigned int Game::getLevel() const{
	return level;
}