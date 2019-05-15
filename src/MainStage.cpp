#include "MainStage.h"

//Alan Duong, 03/31/19
//Gamestate for the main stage of the game

void MainStage::setup()
{
	terrain = new Terrain(rm->getModel("models\\moon-houdini.obj"));
	ents->add(terrain);

	lander = new Lander(rm->getModel("models\\lander.obj"), input);
	ents->add(lander);
	lander->setPos(ofVec3f(0.0f, 100.0f, 0.0f));
	lander->setVel(ofVec3f(0.0f, -0.05f, 0.0f));

	view->cam.setPosition(ofVec3f(50.0f, 50.0f, 50.0f));

}

void MainStage::update()
{
	//view->cam.setPosition(lander->getPos() + ofVec3f(10.0f, 10.0f, 10.0f));
	//view->cam.lookAt(lander->getPos());
	view->setCenterPos(lander->getPos() + ofVec3f(0.0f, 4.0f, 0.0f));
}

void MainStage::draw()
{
	//ofDrawSphere(terrain->oct.trace(Ray(Vector3(lander->getPos().x, lander->getPos().y, lander->getPos().z), Vector3(0.0f, -1.0f, 0.0f))), 0.75f);
}
