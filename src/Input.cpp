#include "Input.h"

//Alan Duong, 03/31/19
//A class to make handling input easier.

Input::Input()
{
	mPos = ofVec2f(0.0f, 0.0f);
	for (size_t i = 0; i < keysDown.size(); ++i)
	{
		keysDown[i] = false;
	}
	oldKeysDown = keysDown;
}

void Input::setView(View * _view)
{
	view = _view;
}

ofVec2f Input::getMouseScreenPos()
{
	return mPos;
}

ofVec2f Input::getMouseWorldPos()
{
	glm::vec3 worldPos = view->cam.screenToWorld(glm::vec3(mPos.x, mPos.y, 0.0f));
	return ofVec2f(worldPos.x, worldPos.y) - view->getTotalOffset();
}

bool Input::keyDown(int key)
{
	return keysDown[key];
}

bool Input::keyPressed(int key)
{
	return keysDown[key] && !oldKeysDown[key];
}

bool Input::keyReleased(int key)
{
	return !keysDown[key] && oldKeysDown[key];
}

bool Input::mouseDown(int button)
{
	return mouseButtonsDown[button];
}

bool Input::mousePressed(int button)
{
	return mouseButtonsDown[button] && !oldMouseButtonsDown[button];
}

bool Input::mouseReleased(int button)
{
	return !mouseButtonsDown[button] && oldMouseButtonsDown[button];
}

void Input::setMousePos(ofVec2f _mPos)
{
	mPos = _mPos;
}

void Input::setKeyDown(int key, bool down)
{
	keysDown[key] = down;
	//std::cout << keysDown[key] << " " << oldKeysDown[key] << "\n";
}

void Input::setMouseDown(int button, bool down)
{
	mouseButtonsDown[button] = down;
}

void Input::update()
{
	oldKeysDown = keysDown;
	oldMouseButtonsDown = mouseButtonsDown;
}
