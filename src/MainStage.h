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

	void init();

private:
	Terrain* terrain;
	Lander* lander;
	float agl;
	Box landingArea;

	ofLight keyLight;
	ofLight spotlight;

	bool landed;
	int startTime;
	float timeElapsed;
	bool crashed;
	bool inZone;
	float score;

	std::vector<ofVec3f> points;
	std::vector<ofVec3f> sizes;
	ofVbo vbo;
};
