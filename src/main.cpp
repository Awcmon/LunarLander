#include "ofMain.h"
#include "ofApp.h"

//Alan Duong, 03/31/19
//Main function.

//========================================================================
int main( ){
	/*
	ofSetupOpenGL(1280,960,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());
	*/

	ofGLFWWindowSettings settings;
	settings.resizable = false;
	settings.setSize(1280, 960);
	ofCreateWindow(settings);
	return ofRunApp(new ofApp);
}
