#pragma once

//Alan Duong, 03/31/19
//This is a wrapper for ofCamera to help do screenshake.

#include "ofMain.h"
#include "util.h"
#include "Input.h"

class View
{
public:
	View();
	void setInput(Input* _input);

	Input* input;
	
	ofCamera cam;
	//ofEasyCam cam;

	void posViewPunch(ofVec3f pos);
	void update();
	ofVec3f getTotalOffset();

	ofVec3f punchPos;

	ofVec3f offset; //used for screenshake and stuff
};
