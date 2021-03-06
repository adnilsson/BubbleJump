#include "Game.h"
#include <time.h>
#include <random>

Game::Game(LPDIRECT3DDEVICE9 d3ddev):levelStep(250), level(0),
	spawnInterval(4*BUBBLE_INIT_RADIUS), maximumSpawnInterval(130), 
	spawnIncrement(BUBBLE_INIT_RADIUS / 2), monster()
{
	player = new Player(d3ddev);
	bubbles = new BubbleList(d3ddev, spawnInterval);
	menus = new Menus(d3ddev);
	Bubble *last = (Bubble *) bubbles->getTail();
	floatingPoints = new PointsList();
	monster = nullptr;

	currentState = GAME_RUNNING;
	bubbleSpacing = last->getY();

}


Game::~Game(void)
{
	delete floatingPoints;
	delete menus;
	delete bubbles;
	Bubble::resetRadius();
}

//draws content according to current game state. Called from  the main message loop.
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

			if(bubbles->collisionCheck(player)){
				player->incScore();
				//Create a new floating point and add to the list of FloatingScores
				FloatingScore *point = new FloatingScore(player->getX()+PLAYER_RADIUS, 
										player->getY(), Bubble::getPointValue());
				
				floatingPoints->addElement(point);
				checkLevelUp();
			}
			else if(monster != nullptr && monster->collisionCheck(player)){

				monster.release();

				FloatingScore *point = new FloatingScore(player->getX()+PLAYER_RADIUS, 
					player->getY(), INT_MAX);
				floatingPoints->addElement(point);

			}

			render_game(d3dSprite, d3dxFont); //Draw objects on screen.
			moveObjects(d3ddev); // Move game obejcts
			if(isGameOver()) changeState(PRE_GAME_OVER);

			break;

		case(GAME_PAUSED):
			bubbles->traverseList(d3dSprite);
			drawMonster(d3dSprite);
			player->drawSpritePart(d3dSprite, player->getSpritePart());
			d3dSprite->End();

			//Text
			displayScore(d3dxFont);
			floatingPoints->traverseList(d3dxFont, currentState);
			menus->paused(currentState);
			break;

		case(PRE_GAME_OVER) : // runs only once (directly upon game over)
			menus->pre_game_over(player->getScore());
			changeState(GAME_OVER);

			/*no break, since we still want to render the GAME_OVER screen when 
			  PRE_GAME_OVER has finished*/

		case(GAME_OVER):
			bubbles->traverseList(d3dSprite);		
			drawMonster(d3dSprite);		//Could return !D3D_OK
			d3dSprite->End();
			displayScore(d3dxFont);
			menus->game_over();
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

	/*Sprites (monster and player might not return D3D_OK, 
	not sure how to handle this)*/
	bubbles->traverseList(d3dSprite);
	drawMonster(d3dSprite);
	player->drawPlayer(d3dSprite); 
		
	d3dSprite->End(); //Finish drawing sprites
	
	//Draw texts
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
		WINDOW_WIDTH/2,  SCOREBOX_HEIGHT/2, 
		WINDOW_WIDTH);

}



void Game::moveObjects(LPDIRECT3DDEVICE9 d3ddev){
	
	if (!player->moveY()){ //Move the player

		bubbles->moveBubbles(player->getVelocity());
		floatingPoints->moveText(player->getVelocity());

		if (monster != nullptr){
			//remove the monster if it was missed, otherwise move it. 
			monster->getY() > WINDOW_HEIGHT ? monster.release() :
				monster->moveY(player->getVelocity());
		}

		bubbleSpacing += abs(player->getSpeed()); //save change in height.
		int spacing = static_cast<int>(bubbleSpacing);

		//enter if a new bubble should be spawned.
		if (spacing > 0 && static_cast<unsigned int>(spacing) >= spawnInterval){

			std::random_device rd;
			std::mt19937 mt(rd());
			std::uniform_int_distribution<int> dist(0, 100);

			int random = dist(mt);

			if ((random == 66 || random == 6) && (monster == nullptr)){
				spawnMonster(d3ddev);
			}
			else{
				//Spawn a bubble to appear from the top of the window.
				bubbles->spawnOneBubble(d3ddev, level);
			}

			//reset distance distance since last spawned bubble
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
	
	if (monster != nullptr) monster->moveX();
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

// Spawn somewhere on the horizontal axis.
void Game::spawnMonster (LPDIRECT3DDEVICE9 d3d){
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(0, (WINDOW_WIDTH - RARE_SPRITE_WIDTH));

	int randomX = dist(mt);
	monster.reset(new RareSpawn(d3d, static_cast<FLOAT>(randomX)));
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