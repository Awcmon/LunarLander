#pragma once

//Alan Duong, 05/16/19
//An entity with a 3d model

#include "Entity.h"
#include <string>

class Prop : public Entity
{
public:
	Prop(ofxAssimpModelLoader* _model);
	void update();
	void draw();
	void setModel(std::string _modelstr);
	ofxAssimpModelLoader* getModel();
	//ofMesh* getMesh();

	ofxAssimpModelLoader* model;
	//ofMesh* mesh;
};
