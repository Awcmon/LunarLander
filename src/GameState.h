#pragma once

//Alan Duong, 03/31/19
//Represents a game state (Main Menu, Main Stage, etc).

#include "ofMain.h"
#include "Entity.h"
#include "Input.h"
#include "View.h"

class GameState
{
public:
	virtual void setup() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;

	void init(EntitySystem* _ents, ResourceManager* _rm, Input* _input, View* _view, GameState** _curGameState);

	void changeState(GameState * newGameState);

	EntitySystem* ents;
	ResourceManager* rm;
	Input* input;
	View* view;

	GameState** curGameState;
};

void changeGameState(GameState * newGameState, EntitySystem* ents, ResourceManager* rm, Input* input, View* view, GameState** curGameState);
