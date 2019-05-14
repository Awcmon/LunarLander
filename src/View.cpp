#include "View.h"

//Alan Duong, 03/31/19
//This is a wrapper for ofCamera to help do screenshake.

View::View()
{
	punchPos = ofVec3f(0.0f, 0.0f, 0.0f);
	ang = ofVec3f(0.0f, 0.0f, 0.0f);
	distance = 10.0f;
	mouseSens = 0.3f;
}

void View::setInput(Input * _input)
{
	input = _input;
}


void View::posViewPunch(ofVec3f _punchPos)
{
	if (_punchPos.lengthSquared() > punchPos.lengthSquared())
	{
		punchPos = _punchPos;
	}
}

void View::update()
{
	//reset punch pos
	//punchPos.x = approach(punchPos.x, 0, (punchPos.x) * 0.1);
	//punchPos.y = approach(punchPos.y, 0, (punchPos.y) * 0.1);
	punchPos += (-punchPos) * 0.1;

	if (input->mouseDown(0))
	{
		ofVec2f delta = input->mouseDelta();
		//std::cout << delta << "\n";
		//cam.setOrientation(cam.getOrientationEuler() + ofVec3f(0.0f, 1.0f, 0.0f)*0.2f);
		//cam.lookAt()
		ang = ofVec3f(0.0f, ang.y - delta.x * mouseSens, clamp(ang.z + delta.y * mouseSens, -89.99f, 89.99f));
	}

	cam.setPosition(centerPos + ofVec3f(distance, 0.0f, 0.0f).getRotated(0.0f, ang.y, ang.z));
	cam.lookAt(centerPos);

	//cam.setPosition(punchPos.x, punchPos.y, 10.0f);
}

ofVec3f View::getTotalOffset()
{
	return punchPos;
}

void View::setCenterPos(ofVec3f _centerPos)
{
	centerPos = _centerPos;
}
