#pragma once

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