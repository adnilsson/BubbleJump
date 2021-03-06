//--------------------------------------------------------------------------------------
// File: Game.h
//
// Class desc: * Contains objects that a game consists of, i.e. the player, bubbles, text
//               and rareSpawns.
//             * Handles game logic and rendering as well as movement of the player, 
//               bubbles and rareSpawns
//
//
// Author: Adrian Nilsson
//--------------------------------------------------------------------------------------

#pragma once
#include "Player.h"
#include "BubbleList.h"
#include "PointsList.h"
#include "RareSpawn.h"
#include <memory>
#include "Menus.h"


class Game
{
public:
	Game(LPDIRECT3DDEVICE9);
	virtual ~Game(void);

	//Game vars
	Player *player;
	BubbleList *bubbles;
	PointsList *floatingPoints;
	Menus *menus; 


	//Renders appropriate content for each game state.
	void render_frame(LPDIRECT3DDEVICE9, LPD3DXSPRITE, LPD3DXFONT);

	//setters
	void changeState(game_state);

	//getters
	game_state getState() const;
	unsigned int getLevel() const;

private:
	game_state currentState;
	std::unique_ptr <RareSpawn> monster;

	unsigned int level;
	const unsigned int levelStep;		//number of points required to advance to the next level.
	const unsigned int maximumSpawnInterval;
	const int spawnIncrement;
	unsigned int spawnInterval;
	double bubbleSpacing;				//Distance since last spawn.

	void displayScore(LPD3DXFONT); 		//Display the player's curren score.
	void moveObjects(LPDIRECT3DDEVICE9);
	void checkLevelUp();				//move to the next level if needed.
	bool isGameOver() const;

	void spawnMonster(LPDIRECT3DDEVICE9);
	void drawMonster(LPD3DXSPRITE d3d){ 
		if (monster != nullptr) monster->drawSprite(d3d);};

	void render_game(LPD3DXSPRITE, LPD3DXFONT);
	void render_menu(LPDIRECT3DDEVICE9, LPD3DXSPRITE);
	void render_pause(LPDIRECT3DDEVICE9, LPD3DXSPRITE);

};

