#include "Lander.h"

/*
Lander::Lander(ofxAssimpModelLoader* _model)
{
	Prop::Prop(_model);
}
*/

void Lander::update()
{
	Prop::update();
	applyForce(ofVec3f(0.0f, -0.001f, 0.0f)); //apply gravity

	if (input->keyDown(' '))
	{
		applyForce(ofVec3f(0.0f, 0.004f, 0.0f));
	}

	if (input->keyDown('w'))
	{
		applyForce(ofVec3f(0.0f, 0.0f, -0.004f));
	}
	if (input->keyDown('s'))
	{
		applyForce(ofVec3f(0.0f, 0.004f, 0.004f));
	}
	if (input->keyDown('a'))
	{
		applyForce(ofVec3f(-0.004f, 0.0f, 0.0f));
	}
	if (input->keyDown('d'))
	{
		applyForce(ofVec3f(0.004f, 0.004f, -0.0f));
	}
}

void Lander::draw()
{
	Prop::draw();
}
