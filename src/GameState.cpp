#include "GameState.h"

//Alan Duong, 03/31/19
//Represents a game state (Main Menu, Main Stage, etc).

void GameState::init(EntitySystem * _ents, ResourceManager * _rm, Input * _input, View * _view, GameState** _curGameState)
{
	ents = _ents;
	rm = _rm;
	input = _input;
	view = _view;
	curGameState = _curGameState;
}

void GameState::changeState(GameState * newGameState)
{
	changeGameState(newGameState, ents, rm, input, view, curGameState);
}

void changeGameState(GameState * newGameState, EntitySystem* ents, ResourceManager* rm, Input* input, View* view, GameState** curGameState)
{
	if (*curGameState != nullptr)
	{
		GameState* oldGameState = *curGameState;
		*curGameState = newGameState;
		delete oldGameState;
		oldGameState = nullptr;
	}
	else
	{
		*curGameState = newGameState;
	}
	(*curGameState)->init(ents, rm, input, view, curGameState);
	(*curGameState)->setup();
}
