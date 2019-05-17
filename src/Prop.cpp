#include "Prop.h"

//Alan Duong, 05/16/19
//An entity with a 3d model

Prop::Prop(ofxAssimpModelLoader* _model)
{
	model = _model;
}

void Prop::update()
{
	Entity::update();
}

void Prop::draw()
{
	Entity::draw();

	ofSetRectMode(OF_RECTMODE_CENTER);

	ofPushMatrix();
	ofTranslate(pos);
	//ofRotateDeg(ang);

	ofScale(scale);

	ofEnableAlphaBlending();
	ofSetColor(color, alpha);
	//image->draw(0.0f, 0.0f);
	//image->drawSubsection(0.0f, 0.0f, size.x, size.y, size.x*(frameNumber % numCols), size.y*(frameNumber / numCols));
	model->drawFaces();
	ofDisableAlphaBlending();

	ofPopMatrix();
}

void Prop::setModel(std::string _modelstr)
{
	model = ents->rm->getModel(_modelstr);
	//mesh = ents->rm->getMesh(_modelstr);
}

ofxAssimpModelLoader * Prop::getModel()
{
	return model;
}
/*
ofMesh * Prop::getMesh()
{
	return mesh;
}
*/
