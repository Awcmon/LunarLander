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

		float epsilon = 0.5f; //epsilon for a contact
		float e = 0.2f; //restitution
	}
	void update();
	void draw();

private:
	void handleCollision(const ofVec3f &pt, const ofVec3f &contactPt, bool &groundStatus);

	float epsilon;
	float e;

	Input* input;
	Terrain* terrain;
	bool onGround;
};
