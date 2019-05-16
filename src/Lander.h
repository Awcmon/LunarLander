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
		isOnGround = false;

		float epsilon = 0.5f; //epsilon for a contact
		float e = 0.2f; //restitution
	}
	void update();
	void draw();
	bool onGround();
	std::vector<Vector3> getLegPoints();

private:
	void handleCollision(const ofVec3f &pt, const ofVec3f &contactPt, bool &groundStatus);

	float epsilon;
	float e;

	Input* input;
	Terrain* terrain;
	bool isOnGround;

	std::vector<Vector3> legPoints;
};
