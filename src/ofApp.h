#pragma once

#include "ofMain.h"
#include "Entity.h"
#include "Input.h"
#include "View.h"
#include "GameState.h"
#include "MainStage.h"

//Alan Duong, 03/31/19
//Main app class.

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void initLightingAndMaterials();
		
		EntitySystem ents;
		ResourceManager rm;
		Input input;
		View view;
		GameState* curGameState;

};
