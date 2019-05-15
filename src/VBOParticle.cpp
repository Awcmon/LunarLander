#include "VBOParticle.h"

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
	sizes->push_back(ofVec3f(5.0f));
}
