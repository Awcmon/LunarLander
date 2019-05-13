#include "ofApp.h"

//Alan Duong, 05/12/19
//Main app class.



//--------------------------------------------------------------
void ofApp::setup(){
	ofSeedRandom();

	ents.setResourceManager(&rm);
	ents.setView(&view);

	input.setView(&view);

	//cam.setupPerspective();
	view.cam.setPosition(ofVec3f(0.0f, 0.0f, 1000));
	view.cam.enableOrtho();

	//changeGameState(new MenuState(), &ents, &rm, &input, &view, &curGameState);
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

	view.cam.end();

	/*
	ofSetColor(ofColor::white);
	ofDrawBitmapString("Frame Rate: " + std::to_string(ofGetFrameRate()), ofGetWindowWidth() - 170, 15);
	ofDrawBitmapString("Entities: " + std::to_string(ents.size()), ofGetWindowWidth() - 170, 35);
	*/
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
	input.setMousePos(glm::vec3(x, y, 0.0f));
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	input.setMousePos(glm::vec3(x, y, 0.0f));
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
