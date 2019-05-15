#pragma once

//Alan Duong, 03/31/19
//Gamestate for the main stage of the game

#include "GameState.h"
#include "unordered_set"
#include "Prop.h"
#include "Lander.h"
#include "Terrain.h"
#include "autil.h"
#include <array>

class MainStage : public GameState
{
public:
	void setup();
	void update();
	void draw();

	Terrain* terrain;
	Lander* lander;
	float agl;
};
