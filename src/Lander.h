#pragma once

#include "Prop.h"
#include "Input.h"
#include "Terrain.h"

class Lander : public Prop
{
public:
	Lander(ofxAssimpModelLoader* _model, Input* _input, Terrain* _terrain) : Prop(_model) 
	{ 
		input = _input; 
		terrain = _terrain; 
		onGround = false;
	}
	void update();
	void draw();

private:
	Input* input;
	Terrain* terrain;
	bool onGround;
};
