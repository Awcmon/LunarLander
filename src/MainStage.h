#pragma once

//Alan Duong, 03/31/19
//Gamestate for the main stage of the game

#include "GameState.h"
#include "unordered_set"
#include "util.h"
#include <array>

class MainStage : public GameState
{
public:
	void setup();
	void update();
	void draw();
};
