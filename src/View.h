#pragma once

//Alan Duong, 03/31/19
//This is a wrapper for ofCamera to help do screenshake.

#include "ofMain.h"
#include "util.h"

class View
{
public:
	View();
	
	ofCamera cam;

	void posViewPunch(ofVec3f pos);
	void update();
	ofVec3f getTotalOffset();

	ofVec3f punchPos;

	ofVec3f offset; //used for screenshake and stuff
};
