#include "MainStage.h"

//Alan Duong, 03/31/19
//Gamestate for the main stage of the game

void MainStage::setup()
{
	terrain = new Terrain(rm->getModel("models\\moon-houdini.obj"));
	ents->add(terrain);

	lander = new Lander(rm->getModel("models\\lander.obj"), input, terrain);
	ents->add(lander);
	lander->setPos(ofVec3f(0.0f, 100.0f, 0.0f));
	lander->setVel(ofVec3f(0.0f, -0.05f, 0.0f));

	view->cam.setPosition(ofVec3f(50.0f, 50.0f, 50.0f));

	ofVec3f min = ofVec3f(-24.0f, -3.0f, -24.0f);
	ofVec3f max = ofVec3f(24.0f, 3.0f, 24.0f);
	landingArea = Box(Vector3(min.x, min.y, min.z), Vector3(max.x, max.y, max.z));

}

void MainStage::update()
{
	//view->cam.setPosition(lander->getPos() + ofVec3f(10.0f, 10.0f, 10.0f));
	//view->cam.lookAt(lander->getPos());
	view->setCenterPos(lander->getPos() + ofVec3f(0.0f, 4.0f, 0.0f));
	agl = (terrain->oct.trace(Ray(Vector3(lander->getPos().x, lander->getPos().y, lander->getPos().z), Vector3(0.0f, -1.0f, 0.0f))) - lander->getPos()).length();

}

void MainStage::draw()
{
	
	//ofDrawSphere(terrain->oct.trace(Ray(Vector3(lander->getPos().x, lander->getPos().y, lander->getPos().z), Vector3(0.0f, -1.0f, 0.0f))), 0.75f);

	view->cam.begin();

	Vector3 bmin = landingArea.parameters[0];
	Vector3 bmax = landingArea.parameters[1];
	Vector3 size = bmax - bmin;
	Vector3 center = size / 2 + bmin;
	ofVec3f p = ofVec3f(center.x(), center.y(), center.z());
	float w = size.x();
	float h = size.y();
	float d = size.z();
	ofNoFill();
	if (landingArea.inside(lander->getLegPoints()))
	{
		ofSetColor(ofColor::green);
	}
	else
	{
		ofSetColor(ofColor::white);
	}
	ofDrawBox(p, w, h, d);


	/*
	std::vector<Vector3> legPoints = lander->getLegPoints();
	for (size_t i = 0; i < legPoints.size(); i++)
	{
		ofDrawSphere(ofVec3f(legPoints[i].x(), legPoints[i].y(), legPoints[i].z()), 0.2f);
	}
	*/

	view->cam.end();

	ofSetColor(ofColor::white);
	ofDrawBitmapString("AGL: " + std::to_string(agl), 15, 15);

}
