#pragma once

#include "ofMain.h"
//#include "View.h"
#include <array>

//Alan Duong, 03/31/19
//A class to make handling input easier.

class Input
{
	ofVec2f mPos;
	std::array<bool, 100000> keysDown;
	std::array<bool, 100000> oldKeysDown;
	std::array<bool, 3> mouseButtonsDown;
	std::array<bool, 3> oldMouseButtonsDown;
	ofVec2f mPosOld;
	//View* view;
public:
	Input();

	//void setView(View* _cam);

	ofVec2f getMouseScreenPos();
	//ofVec2f getMouseWorldPos();
	bool keyDown(int key);
	bool keyPressed(int key);
	bool keyReleased(int key);
	bool mouseDown(int button);
	bool mousePressed(int button);
	bool mouseReleased(int button);
	ofVec2f mouseDelta();

	void setMousePos(ofVec2f _mPos);
	void setKeyDown(int key, bool down);
	void setMouseDown(int button, bool down);

	void update();
};
