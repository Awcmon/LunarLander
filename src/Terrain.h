#pragma once

#include "Prop.h"
#include "Octree.h"

class Terrain : public Prop
{
public:
	Terrain(ofxAssimpModelLoader* _model) : Prop(_model) {}
	void update();
	void draw();

	Octree oct;
};
