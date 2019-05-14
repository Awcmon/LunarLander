#pragma once

#include "Prop.h"
#include "Input.h"

class Lander : public Prop
{
public:
	Lander(ofxAssimpModelLoader* _model, Input* _input) : Prop(_model) { input = _input; }
	void update();
	void draw();

private:
	Input* input;
};
