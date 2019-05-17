#pragma once

//Alan Duong, 05/16/19
//A particle meant to be drawn with a VBO

#include "Entity.h"
#include <vector>

class VBOParticle : public Entity
{
public:
	VBOParticle(std::vector<ofVec3f>* _points, std::vector<ofVec3f>* _sizes);
	void update();
	void draw();
private:
	std::vector<ofVec3f>* points; 
	std::vector<ofVec3f>* sizes;
};