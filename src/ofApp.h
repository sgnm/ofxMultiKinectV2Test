#pragma once

#include "ofMain.h"
#include "ofxMultiKinectV2.h"
#include "ofxGui.h"
#include "ofxOpenCv.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

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
    
    ofxMultiKinectV2 kinect;
    ofTexture colorTex;
    ofTexture depthTex;
    
    ofShader depthShader;
    
    ofImage thresImg;
    
    ofxPanel gui;
    ofParameter<int> near;
    ofParameter<int> far;
    ofParameter<int> threshold;
    
    ofFbo depthFbo;
    
    ofxCvContourFinder contour;
    ofxCvGrayscaleImage grayImg;
		
};
