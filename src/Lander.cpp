#include "Lander.h"
#include "box.h"

/*
Lander::Lander(ofxAssimpModelLoader* _model)
{
	Prop::Prop(_model);
}
*/

void Lander::update()
{
	Prop::update();
	if (!onGround)
	{
		applyForce(ofVec3f(0.0f, -0.001f, 0.0f)); //apply gravity
	}
	
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
		applyForce(ofVec3f(0.0f, 0.004f, 0.004f));
		ents->rm->playSoundLoop("soundloops\\afterburner.wav");
	}
	if (input->keyDown('a'))
	{
		applyForce(ofVec3f(-0.004f, 0.0f, 0.0f));
		ents->rm->playSoundLoop("soundloops\\afterburner.wav");
	}
	if (input->keyDown('d'))
	{
		applyForce(ofVec3f(0.004f, 0.004f, -0.0f));
		ents->rm->playSoundLoop("soundloops\\afterburner.wav");
	}
	
	if (!input->keyDown(' ') && !input->keyDown('w') && !input->keyDown('a') && !input->keyDown('s') && !input->keyDown('d'))
	{
		ents->rm->stopSoundLoop("soundloops\\afterburner.wav");
	}

	applyForce(-getVel() * 0.005f); //dampening force

	ofVec3f min = getModel()->getSceneMin(); //+ getPos();
	ofVec3f max = getModel()->getSceneMax(); //+ getPos();

	float epsilon = 0.5f; //epsilon for a contact

	//calculate collisions at the legs of the lander
	ofVec3f N = ofVec3f(0.0f, min.y + epsilon, max.z) + getPos();
	ofVec3f S = ofVec3f(0.0f, min.y + epsilon, min.z) + getPos();
	ofVec3f E = ofVec3f(max.x, min.y + epsilon, 0.0f) + getPos();
	ofVec3f W = ofVec3f(min.x, min.y + epsilon, 0.0f) + getPos();

	ofVec3f contactN = terrain->oct.trace(Ray(Vector3(N.x, N.y, N.z), Vector3(0.0f, -1.0f, 0.0f)));
	ofVec3f contactS = terrain->oct.trace(Ray(Vector3(S.x, S.y, S.z), Vector3(0.0f, -1.0f, 0.0f)));
	ofVec3f contactE = terrain->oct.trace(Ray(Vector3(E.x, E.y, E.z), Vector3(0.0f, -1.0f, 0.0f)));
	ofVec3f contactW = terrain->oct.trace(Ray(Vector3(W.x, W.y, W.z), Vector3(0.0f, -1.0f, 0.0f)));

	float e = 0.1f; //restitution
	bool onGroundN, onGroundS, onGroundE, onGroundW;
	if ((N - contactN).length() <= epsilon || N.y < contactN.y)
	{
		ofVec3f normal = (N - contactN).getNormalized();
		ofVec3f impulse = (e + 1.0f) * (-getVel()).dot(normal) * normal;
		if (impulse.y >= 0.0f)
		{
			applyForce(impulse);
		}
		onGroundN = true;
	}
	else
	{
		onGroundN = false;
	}
	if ((S - contactS).length() <= epsilon || S.y < contactS.y)
	{
		ofVec3f normal = (S - contactS).getNormalized();
		ofVec3f impulse = (e + 1.0f) * (-getVel()).dot(normal) * normal;
		if (impulse.y >= 0.0f)
		{
			applyForce(impulse);
		}
		onGroundS = true;
		applyForce(-getVel() * 0.1f); //more dampening to help stop it from sliding around on the surface
	}
	else
	{
		onGroundS = false;
	}
	if ((E - contactE).length() <= epsilon || E.y < contactE.y)
	{
		ofVec3f normal = (E - contactE).getNormalized();
		ofVec3f impulse = (e + 1.0f) * (-getVel()).dot(normal) * normal;
		if (impulse.y >= 0.0f)
		{
			applyForce(impulse);
		}
		onGroundE = true;
	}
	else
	{
		onGroundE = false;
	}
	if ((W - contactW).length() <= epsilon || W.y < contactW.y)
	{
		ofVec3f normal = (W - contactW).getNormalized();
		ofVec3f impulse = (e + 1.0f) * (-getVel()).dot(normal) * normal;
		if (impulse.y >= 0.0f)
		{
			applyForce(impulse);
		}
		onGroundW = true;
	}
	else
	{
		onGroundW = false;
	}
	if (onGroundN || onGroundE || onGroundS || onGroundW)
	{
		onGround = true;
	}
	else
	{
		onGround = false;
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
}
