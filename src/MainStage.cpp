#include "MainStage.h"

//Alan Duong, 03/31/19
//Gamestate for the main stage of the game

void MainStage::setup()
{
	Prop* terrain = new Prop(rm->getModel("models\\moon-houdini.obj"));
	ents->add(terrain);

	lander = new Lander(rm->getModel("models\\lander.obj"), input);
	ents->add(lander);
	lander->setPos(ofVec3f(0.0f, 100.0f, 0.0f));
	lander->setVel(ofVec3f(0.0f, -0.05f, 0.0f));

	view->cam.setPosition(ofVec3f(50.0f, 50.0f, 50.0f));

	ofDisableArbTex();     // disable rectangular textures

// load textures
//
	if (!ofLoadImage(particleTex, "images/dot.png")) {
		cout << "Particle Texture File: images/dot.png not found" << endl;
		ofExit();
	}
	shader.load("shaders/shader");
}

void MainStage::update()
{
	//view->cam.setPosition(lander->getPos() + ofVec3f(10.0f, 10.0f, 10.0f));
	//view->cam.lookAt(lander->getPos());
	view->setCenterPos(lander->getPos() + ofVec3f(0.0f, 4.0f, 0.0f));
}

void MainStage::draw()
{
	ofVbo vbo;

	vector<ofVec3f> sizes;
	vector<ofVec3f> points;
	for (int i = 0; i < 200; i++) {
		points.push_back(ofVec3f(0.0f, i, 0.0f));
		sizes.push_back(ofVec3f(500.0f));
	}
	// upload the data to the vbo
	//
	int total = (int)points.size();
	vbo.clear();
	vbo.setVertexData(&points[0], total, GL_STATIC_DRAW);
	vbo.setNormalData(&sizes[0], total, GL_STATIC_DRAW);

	//ofSetColor(ofColor::dimGrey);
	//glDepthMask(GL_FALSE);
	ofEnablePointSprites();
	/*
	rm->getShader("shaders/shader")->begin();
	rm->getTexture("images\\dot.png")->bind();
	vbo.draw(GL_POINTS, 0, 200);
	rm->getTexture("images\\dot.png")->unbind();
	rm->getShader("shaders/shader")->end();
	*/

	shader.begin();

	// draw particle emitter here..
	//
	particleTex.bind();
	vbo.draw(GL_POINTS, 0, 200);
	particleTex.unbind();

	shader.end();

	ofDisablePointSprites();
	ofEnableAlphaBlending();
	//glDepthMask(GL_TRUE);

	rm->getTexture("images\\dot.png")->draw(0,0);
}
