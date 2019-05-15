#pragma once

#include "Prop.h"
#include "Octree.h"

class Terrain : public Prop
{
public:
	Terrain(ofxAssimpModelLoader* _model) : Prop(_model) 
	{
		mesh = _model->getMesh(0);
		oct.create(mesh, 5); //octree with 5 levels
	}
	void update();
	void draw();

	Octree oct;
	ofMesh mesh;
};
