#include "ofApp.h"

//Alan Duong, 05/12/19
//Main app class.



//--------------------------------------------------------------
void ofApp::setup(){
	ofSeedRandom();

	ents.setResourceManager(&rm);
	ents.setView(&view);

	//input.setView(&view);
	view.setInput(&input);

	ofEnableSmoothing();
	ofEnableDepthTest();
	initLightingAndMaterials();

	//cam.setupPerspective();
	view.cam.setPosition(ofVec3f(0.0f, 0.0f, 0.0f));
	//view.cam.setDistance(10);
	view.cam.setNearClip(.1);
	view.cam.setFov(65.5);
	//view.cam.enableOrtho();

	curGameState = nullptr;
	changeGameState(new MainStage(), &ents, &rm, &input, &view, &curGameState);
}

//--------------------------------------------------------------
void ofApp::update(){
	//cam.setPosition(ofVec3f(ofRandomf(), ofRandomf(), 1000));
	if (curGameState == nullptr) { return; }
	/*
	if (input.keyPressed('f'))
	{
		ofToggleFullscreen();
	}
	*/
	view.update();
	ents.update();
	curGameState->update();
	input.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (curGameState == nullptr) { return; }
	//ofSetBackgroundColor(ofColor::cadetBlue);
	ofSetBackgroundColor(ofColor::navy);

	view.cam.begin();
	ofEnableLighting();              // shaded mode

	/*
	ofSetColor(ofColor::dimGrey);
	ofDrawGrid(32.0f, 24, true, false, false, true);
	*/

	/*
	ofSetColor(0, 255, 0);
	ofDrawCircle(glm::vec3(0.0f, 0.0f, 10.0f), 10);

	ofSetColor(255, 0, 0);
	ofDrawCircle(glm::vec3(0.0f, 0.0f, -10.0f), 8);

	ofSetColor(0, 0, 255);
	ofDrawCircle(input.getMouseWorldPos(), 8);
	*/

	ents.draw();

	/*
	ofSetColor(ofColor::dimGrey);
	ofDrawGrid(32.0f, 24, true, false, false, true);
	*/

	curGameState->draw();

	//rm.getModel("models\\moon-houdini.obj")->drawFaces();

	view.cam.end();

	/*
	ofSetColor(ofColor::white);
	ofDrawBitmapString("Frame Rate: " + std::to_string(ofGetFrameRate()), ofGetWindowWidth() - 170, 15);
	ofDrawBitmapString("Entities: " + std::to_string(ents.size()), ofGetWindowWidth() - 170, 35);
	*/

	ofSetColor(ofColor::white);
	ofDrawBitmapString("Frame Rate: " + std::to_string(ofGetFrameRate()), ofGetWindowWidth() - 170, 15);
}

void ofApp::exit()
{
	if (curGameState == nullptr) { return; }
	delete curGameState;
	curGameState = nullptr;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	input.setKeyDown(key, true);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	input.setKeyDown(key, false);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	input.setMousePos(ofVec2f(x, y));
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	input.setMousePos(ofVec2f(x, y));
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	input.setMouseDown(button, true);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	input.setMouseDown(button, false);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::initLightingAndMaterials() {

	static float ambient[] =
	{ .5f, .5f, .5, 1.0f };
	static float diffuse[] =
	{ 1.0f, 1.0f, 1.0f, 1.0f };

	static float position[] =
	{ 5.0, 5.0, 5.0, 0.0 };

	static float lmodel_ambient[] =
	{ 1.0f, 1.0f, 1.0f, 1.0f };

	static float lmodel_twoside[] =
	{ GL_TRUE };


	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, position);


	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, lmodel_twoside);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//	glEnable(GL_LIGHT1);
	glShadeModel(GL_SMOOTH);
}
