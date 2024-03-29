#include "Lander.h"
#include "box.h"

//Alan Duong, 05/16/19
//The class for the lander, or the player. Because the player is the lander.

/*
Lander::Lander(ofxAssimpModelLoader* _model)
{
	Prop::Prop(_model);
}
*/

void Lander::update()
{
	Prop::update(); //update parent class

	if (!onGround())
	{
		applyForce(ofVec3f(0.0f, -0.001f, 0.0f)); //apply gravity when not on ground
	}
	
	//apply thrust when pressing motion keys
	if (input->keyDown(' '))
	{
		applyForce(ofVec3f(0.0f, 0.004f, 0.0f));
		ents->rm->playSoundLoop("soundloops\\afterburner.wav");
	}
	if (input->keyDown('w'))
	{
		applyForce(ofVec3f(0.0f, 0.0f, -0.004f));
		ents->rm->playSoundLoop("soundloops\\afterburner.wav");
	}
	if (input->keyDown('s'))
	{
		applyForce(ofVec3f(0.0f, 0.0f, 0.004f));
		ents->rm->playSoundLoop("soundloops\\afterburner.wav");
	}
	if (input->keyDown('a'))
	{
		applyForce(ofVec3f(-0.004f, 0.0f, 0.0f));
		ents->rm->playSoundLoop("soundloops\\afterburner.wav");
	}
	if (input->keyDown('d'))
	{
		applyForce(ofVec3f(0.004f, 0.0f, -0.0f));
		ents->rm->playSoundLoop("soundloops\\afterburner.wav");
	}
	
	//If not moving, stop the thruster sound
	if (!input->keyDown(' ') && !input->keyDown('w') && !input->keyDown('a') && !input->keyDown('s') && !input->keyDown('d'))
	{
		ents->rm->stopSoundLoop("soundloops\\afterburner.wav");
	}
	else //if we are pressing any sort of movement button
	{
		VBOParticle* smokepuff = new VBOParticle(points, sizes);
		smokepuff->setPos(getPos());
		smokepuff->setVel(ofVec3f(0.0f, -0.3f, 0.0f));
		smokepuff->setScale(25.0f+ofRandom(75.0f));
		smokepuff->lifespan = 75;
		ents->add(smokepuff);
	}

	applyForce(-getVel() * 0.005f); //dampening force

	ofVec3f min = getModel()->getSceneMin(); //+ getPos();
	ofVec3f max = getModel()->getSceneMax(); //+ getPos();

	//calculate collisions at the legs of the lander
	ofVec3f N = ofVec3f(0.0f, min.y + epsilon, max.z) + getPos();
	ofVec3f S = ofVec3f(0.0f, min.y + epsilon, min.z) + getPos();
	ofVec3f E = ofVec3f(max.x, min.y + epsilon, 0.0f) + getPos();
	ofVec3f W = ofVec3f(min.x, min.y + epsilon, 0.0f) + getPos();
	legPoints.clear();
	legPoints.push_back(Vector3(N.x, N.y, N.z));
	legPoints.push_back(Vector3(S.x, S.y, S.z));
	legPoints.push_back(Vector3(E.x, E.y, E.z));
	legPoints.push_back(Vector3(W.x, W.y, W.z));

	ofVec3f contactN = terrain->oct.trace(Ray(Vector3(N.x, N.y, N.z), Vector3(0.0f, -1.0f, 0.0f)));
	ofVec3f contactS = terrain->oct.trace(Ray(Vector3(S.x, S.y, S.z), Vector3(0.0f, -1.0f, 0.0f)));
	ofVec3f contactE = terrain->oct.trace(Ray(Vector3(E.x, E.y, E.z), Vector3(0.0f, -1.0f, 0.0f)));
	ofVec3f contactW = terrain->oct.trace(Ray(Vector3(W.x, W.y, W.z), Vector3(0.0f, -1.0f, 0.0f)));


	bool onGroundN, onGroundS, onGroundE, onGroundW;
	
	//handle collisions for each leg
	handleCollision(N, contactN, onGroundN);
	handleCollision(S, contactS, onGroundS);
	handleCollision(E, contactE, onGroundE);
	handleCollision(W, contactW, onGroundW);

	//when any leg is on the ground
	if (onGroundN || onGroundE || onGroundS || onGroundW)
	{
		//std::cout << "on ground\n";
		applyForce(-getVel() * 0.1f); //more dampening to help stop it from sliding around on the surface
		isOnGround = true;
	}
	else
	{
		isOnGround = false;
	}
}

void Lander::draw()
{
	Prop::draw();
	
	/*draw bounding box
	ofVec3f min = getModel()->getSceneMin() + getPos();
	ofVec3f max = getModel()->getSceneMax() + getPos();
	Box bounds = Box(Vector3(min.x, min.y, min.z), Vector3(max.x, max.y, max.z));

	Vector3 bmin = bounds.parameters[0];
	Vector3 bmax = bounds.parameters[1];
	Vector3 size = bmax - bmin;
	Vector3 center = size / 2 + bmin;
	ofVec3f p = ofVec3f(center.x(), center.y(), center.z());
	float w = size.x();
	float h = size.y();
	float d = size.z();
	ofNoFill();
	ofDrawBox(p, w, h, d);
	*/

	/*
	ofVec3f min = getModel()->getSceneMin(); //+ getPos();
	ofVec3f max = getModel()->getSceneMax(); //+ getPos();

	//calculate collisions at the legs of the lander
	ofVec3f N = ofVec3f(0.0f, min.y + epsilon, max.z) + getPos();
	ofVec3f S = ofVec3f(0.0f, min.y + epsilon, min.z) + getPos();
	ofVec3f E = ofVec3f(max.x, min.y + epsilon, 0.0f) + getPos();
	ofVec3f W = ofVec3f(min.x, min.y + epsilon, 0.0f) + getPos();
	ofVec3f contactN = terrain->oct.trace(Ray(Vector3(N.x, N.y, N.z), Vector3(0.0f, -1.0f, 0.0f)));
	ofVec3f contactS = terrain->oct.trace(Ray(Vector3(S.x, S.y, S.z), Vector3(0.0f, -1.0f, 0.0f)));
	ofVec3f contactE = terrain->oct.trace(Ray(Vector3(E.x, E.y, E.z), Vector3(0.0f, -1.0f, 0.0f)));
	ofVec3f contactW = terrain->oct.trace(Ray(Vector3(W.x, W.y, W.z), Vector3(0.0f, -1.0f, 0.0f)));
	ofDrawSphere(contactN, 0.2f);
	ofDrawSphere(contactS, 0.2f);
	ofDrawSphere(contactE, 0.2f);
	ofDrawSphere(contactW, 0.2f);
	*/
}

bool Lander::onGround()
{
	return isOnGround;
}

std::vector<Vector3> Lander::getLegPoints()
{
	return legPoints;
}

//resolve the collision
void Lander::handleCollision(const ofVec3f & pt, const ofVec3f & contactPt, bool & groundStatus)
{
	if ((pt - contactPt).length() <= epsilon || pt.y < contactPt.y)
	{
		ofVec3f normal = (pt - contactPt).getNormalized();
		ofVec3f impulse = (e + 1.0f) * (-getVel()).dot(normal) * normal;
		if (impulse.y >= 0.0f)
		{
			applyForce(impulse);
		}
		groundStatus = true;
	}
	else
	{
		groundStatus = false;
	}
}
