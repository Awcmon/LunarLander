#include "VBOParticle.h"

//Alan Duong, 05/16/19
//A particle meant to be drawn with a VBO

VBOParticle::VBOParticle(std::vector<ofVec3f>* _points, std::vector<ofVec3f>* _sizes)
{
	points = _points;
	sizes = _sizes;
}

void VBOParticle::update()
{
	Entity::update();
}

void VBOParticle::draw()
{
	Entity::draw();
	points->push_back(getPos());
	sizes->push_back(ofVec3f(scale));
}
