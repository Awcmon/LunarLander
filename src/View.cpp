#include "View.h"

//Alan Duong, 03/31/19
//This is a wrapper for ofCamera to help do screenshake.

View::View()
{
	punchPos = ofVec3f(0.0f, 0.0f, 0.0f);
	ang = ofVec3f(0.0f, 0.0f, 0.0f);
	distance = 10.0f;
	mouseSens = 0.3f;

	curCam = &followCam;

	followCam.setNearClip(.1);
	followCam.setFov(65.5);

	frontCam.setOrientation(glm::vec3(0.0f, 0.0f, 0.0f));
	frontCam.setNearClip(.1);
	frontCam.setFov(65.5);

	downCam.setOrientation(glm::vec3(-90.0f, 0.0f, 0.0f));
	downCam.setNearClip(.1);
	downCam.setFov(65.5);

	trackingCam.setPosition(ofVec3f(20.0f, 20.0f, 20.0f));
	trackingCam.setNearClip(.1);
	trackingCam.setFov(65.5);

	easyCam.setDistance(10);
	easyCam.setNearClip(.1);
	easyCam.setFov(65.5);
	//easyCam.enableOrtho();
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
	if (input->keyPressed('1'))
	{
		curCam = &followCam;
	}
	else if (input->keyPressed('2'))
	{
		curCam = &frontCam;
	}
	else if (input->keyPressed('3'))
	{
		curCam = &downCam;
	}
	else if (input->keyPressed('4'))
	{
		curCam = &trackingCam;
	}
	else if (input->keyPressed('5'))
	{
		curCam = &easyCam;
	}



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

	followCam.setPosition(centerPos + ofVec3f(distance, 0.0f, 0.0f).getRotated(0.0f, ang.y, ang.z));
	followCam.lookAt(centerPos);

	trackingCam.lookAt(centerPos);

	

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
