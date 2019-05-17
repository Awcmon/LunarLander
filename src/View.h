#pragma once

//Alan Duong, 05/16/19
//This manages all the cameras

#include "ofMain.h"
#include "autil.h"
#include "Input.h"

class View
{
public:
	View();
	void setInput(Input* _input);
	void posViewPunch(ofVec3f pos);
	void update();
	ofVec3f getTotalOffset();
	void setCenterPos(ofVec3f _centerPos);

	ofCamera* curCam;

	Input* input;

	ofCamera followCam;
	ofCamera frontCam;
	ofCamera downCam;
	ofEasyCam easyCam;
	//ofEasyCam cam;

private:
	ofVec3f punchPos;
	ofVec3f offset; //used for screenshake and stuff
	float distance;
	ofVec3f centerPos;
	ofVec3f ang;
	float mouseSens;

	ofCamera trackingCam;
};
