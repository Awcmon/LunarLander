#include "MainStage.h"

//Alan Duong, 03/31/19
//Gamestate for the main stage of the game

void MainStage::setup()
{
	if (!ofLoadImage(particleTex, "images/dot.png")) {
		cout << "Particle Texture File: images/dot.png not found" << endl;
		ofExit();
	}

	// load the shader
	//
#ifdef TARGET_OPENGLES
	shader.load("shaders_gles/shader");
#else
	shader.load("shaders/shader");
#endif


	Prop* terrain = new Prop(rm->getModel("models\\moon-houdini.obj"));
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

	VBOParticle* smokepuff = new VBOParticle(&points, &sizes);
	smokepuff->setPos(lander->getPos());
	smokepuff->setVel(ofVec3f(2.0f, 2.0f, 2.0f));
	smokepuff->setScale(5.0f);
	//smokepuff->lifespan = 200;
	ents->add(smokepuff);

}

void MainStage::draw()
{
	//the draw func of the particles fill the points and sizes vectors
	

	view->cam.end();
	/*
	int total = (int)points.size();
	vbo.clear();
	vbo.setVertexData(&points[0], total, GL_STATIC_DRAW);
	vbo.setNormalData(&sizes[0], total, GL_STATIC_DRAW);
	//std::cout << total << "\n";

	glDepthMask(GL_FALSE);

	ofSetColor(255, 100, 90);

	// this makes everything look glowy :)
	//
	ofDisableAlphaBlending();
	//ofEnableBlendMode(OF_BLENDMODE_ADD);
	ofEnablePointSprites();

	rm->getShader("shaders/particle")->begin();
	view->cam.begin();
	rm->getTexture("images\\smokepuff1.png")->bind();
	vbo.draw(GL_POINTS, 0, (int)points.size());
	rm->getTexture("images\\smokepuff1.png")->unbind();
	view->cam.end();
	rm->getShader("shaders/particle")->end();

	ofDisablePointSprites();
	ofDisableBlendMode();
	ofEnableAlphaBlending();

	// set back the depth mask
	//
	glDepthMask(GL_TRUE);
	*/

	int total = (int)points.size();
	vbo.clear();
	vbo.setVertexData(&points[0], total, GL_STATIC_DRAW);
	vbo.setNormalData(&sizes[0], total, GL_STATIC_DRAW);

	glDepthMask(GL_FALSE);

	ofSetColor(255, 100, 90);

	// this makes everything look glowy :)
	//
	//ofEnableBlendMode(OF_BLENDMODE_ADD);
	ofEnablePointSprites();


	// begin drawing in the camera
	//
	shader.begin();
	view->cam.begin();

	// draw particle emitter here..
	//
//	emitter.draw();
	particleTex.bind();
	vbo.draw(GL_POINTS, 0, (int)points.size());
	particleTex.unbind();

	//  end drawing in the camera
	// 
	view->cam.end();
	shader.end();

	ofDisablePointSprites();
	//ofDisableBlendMode();
	ofEnableAlphaBlending();

	// set back the depth mask
	//
	glDepthMask(GL_TRUE);


	view->cam.begin();

	//sizes.clear();
	//points.clear();
}
