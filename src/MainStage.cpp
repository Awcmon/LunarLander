#include "MainStage.h"

//Alan Duong, 05/16/19
//Gamestate for the main stage of the game

void MainStage::setup()
{
	terrain = new Terrain(rm->getModel("models\\moon-houdini.obj"));
	ents->add(terrain);

	lander = new Lander(rm->getModel("models\\lander.obj"), input, terrain, &points, &sizes);
	ents->add(lander);

	//view->curCam->setPosition(ofVec3f(50.0f, 50.0f, 50.0f));

	//set up the landing area
	ofVec3f min = ofVec3f(-24.0f, -2.0f, -24.0f);
	ofVec3f max = ofVec3f(24.0f, 1.5f, 24.0f);
	landingArea = Box(Vector3(min.x, min.y, min.z), Vector3(max.x, max.y, max.z));

	//set up the lights
	keyLight.setup();
	keyLight.enable();
	keyLight.setAreaLight(1, 1);
	keyLight.setAmbientColor(ofFloatColor(1, 1, 1)*0.5f);
	keyLight.setDiffuseColor(ofFloatColor(1, 1, 1)*0.5f);
	keyLight.setSpecularColor(ofFloatColor(1, 1, 1)*0.5f);
	keyLight.setScale(0);
	keyLight.rotate(45, ofVec3f(0, 1, 0));
	keyLight.rotate(-45, ofVec3f(1, 0, 0));
	keyLight.setPosition(200.0f, 400.0f, 200.0f);

	spotlight.setup();
	spotlight.enable();
	spotlight.setSpotlight();
	spotlight.setScale(0);
	spotlight.setSpotlightCutOff(30);
	spotlight.setAttenuation(.2, .001, .001);
	spotlight.setAmbientColor(ofFloatColor(1, 1, 1));
	spotlight.setDiffuseColor(ofFloatColor(1, 1, 1));
	spotlight.setSpecularColor(ofFloatColor(1, 1, 1));
	spotlight.rotate(-45, ofVec3f(1, 0, 0));
	spotlight.setPosition(0, 0, 0);

	init();
}

//init the things that get reset every game restart
void MainStage::init()
{
	lander->setPos(ofVec3f(0.0f, 100.0f, 0.0f));
	lander->setVel(ofVec3f(0.0f, -0.05f, 0.0f));

	landed = false;
	inZone = false;
	crashed = false;
	startTime = ofGetElapsedTimef();
}

void MainStage::update()
{
	//view->cam.setPosition(lander->getPos() + ofVec3f(10.0f, 10.0f, 10.0f));
	//view->cam.lookAt(lander->getPos());

	//update the views
	view->setCenterPos(lander->getPos() + ofVec3f(0.0f, 4.0f, 0.0f));
	view->frontCam.setPosition(lander->getPos() + ofVec3f(0.0f, 0.75f, -0.5f));
	view->downCam.setPosition(lander->getPos() + ofVec3f(0.0f, 0.75f, 0.0f));

	//update agl
	agl = (terrain->oct.trace(Ray(Vector3(lander->getPos().x, lander->getPos().y, lander->getPos().z), Vector3(0.0f, -1.0f, 0.0f))) - lander->getPos()).length();

	//do right when landed
	if (lander->onGround() && !landed)
	{
		//calculate score
		timeElapsed = ofGetElapsedTimef() - startTime;
		score = 200.0f - timeElapsed;
		if (landingArea.inside(lander->getLegPoints()))
		{
			inZone = true;
		}
		else
		{
			score *= 0.5f;
		}
		if (lander->getVel().length() > 0.05f)
		{
			score = 0.0f;
			crashed = true;
		}
		landed = true;
	}

	//allow restarting when landed
	if (landed && input->keyPressed('r'))
	{
		init();
	}

}

void MainStage::draw()
{
	
	//ofDrawSphere(terrain->oct.trace(Ray(Vector3(lander->getPos().x, lander->getPos().y, lander->getPos().z), Vector3(0.0f, -1.0f, 0.0f))), 0.75f);

	view->curCam->begin();

	//draw the landing zone
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

	//draw the lights
	keyLight.draw();
	spotlight.setPosition(lander->getPos() + ofVec3f(0.0f, 0.75f, 0.0f));
	spotlight.draw();

	//draw the VBO particles
	int total = (int)points.size();
	vbo.clear();
	vbo.setVertexData(&points[0], total, GL_STATIC_DRAW);
	vbo.setNormalData(&sizes[0], total, GL_STATIC_DRAW);

	ofEnablePointSprites();
	ofEnableAlphaBlending();
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	glDepthMask(GL_FALSE);

	rm->getShader("shaders/shader")->begin();
	rm->getTexture("images\\smokepuff1.png")->bind();
	ofSetColor(ofColor::white);
	vbo.draw(GL_POINTS, 0, (int)points.size());
	rm->getTexture("images\\smokepuff1.png")->unbind();
	rm->getShader("shaders/shader")->end();

	//ofDisablePointSprites();
	//ofDisableBlendMode();
	glDepthMask(GL_TRUE);

	points.clear();
	sizes.clear();

	/*draw the leg points
	std::vector<Vector3> legPoints = lander->getLegPoints();
	for (size_t i = 0; i < legPoints.size(); i++)
	{
		ofDrawSphere(ofVec3f(legPoints[i].x(), legPoints[i].y(), legPoints[i].z()), 0.2f);
	}
	*/

	view->curCam->end();

	//screenspace text
	ofSetColor(ofColor::white);
	ofDrawBitmapString("AGL: " + std::to_string(agl), 15, 15);
	float speed = lander->getVel().length();
	ofDrawBitmapString("SPD: " + std::to_string(speed), 15, 30);
	if (speed > 0.05f && agl < 20.0f)
	{
		ofDrawBitmapString("REDUCE SPEED BEFORE LANDING", 15, 45);
	}

	if (landed)
	{
		ofDrawBitmapString("YOU LANDED IN " + std::to_string(timeElapsed) + " SECONDS", 500, 500);
		ofDrawBitmapString("SCORE: " + std::to_string(score), 500, 515);
		if (!inZone)
		{
			ofDrawBitmapString("SCORE HALVED FOR LANDING OUTSIDE THE ZONE", 500, 530);
		}
		if (crashed)
		{
			ofDrawBitmapString("NO SCORE FOR CRASHING", 500, 545);
		}
		ofDrawBitmapString("PRESS R TO RESTART", 500, 560);
	}
}
