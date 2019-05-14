#include "MainStage.h"

//Alan Duong, 03/31/19
//Gamestate for the main stage of the game

void MainStage::setup()
{
	Prop* terrain = new Prop(rm->getModel("models\\moon-houdini.obj"));
	ents->add(terrain);

	lander = new Prop(rm->getModel("models\\lander.obj"));
	ents->add(lander);
	lander->setPos(ofVec3f(0.0f, 100.0f, 0.0f));
	lander->setVel(ofVec3f(0.0f, -0.1f, 0.0f));

}

void MainStage::update()
{
	view->cam.setPosition(lander->getPos());
}

void MainStage::draw()
{
	
}
