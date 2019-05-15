#pragma once

//Alan Duong, 03/31/19
//Gamestate for the main stage of the game

#include "GameState.h"
#include "unordered_set"
#include "Prop.h"
#include "Lander.h"
#include "util.h"
#include <array>
#include "VBOParticle.h"

class MainStage : public GameState
{
public:
	void setup();
	void update();
	void draw();

	Lander* lander;

	std::vector<ofVec3f> points;
	std::vector<ofVec3f> sizes;
	ofVbo vbo;
	ofShader shader;
	ofTexture  particleTex;
};
