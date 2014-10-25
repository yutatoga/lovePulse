#pragma once

#include "ofMain.h"
#include "ofxDelaunay.h"
#include "ofxGui.h"

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
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		void resetTriangulation();
		void fullScreen();
		void setFrameRate(int & sliderFrameRate);
		
		ofxDelaunay triangulation;
		ofFbo fbo;
		ofImage image;
		bool firstBackground;
		
		//gui
		bool hideGui;//done
		ofxPanel gui; //done
		ofxToggle toggleFill; //done
		ofxButton toggleFullScreen; //done
		ofxToggle toggleWireColorFromPhoto;
		ofxColorSlider sliderWireColor;
		ofxFloatSlider sliderWireLineWidth; //done
		ofxFloatSlider sliderPalseLineWidth;
		ofxIntSlider sliderFrameRate;
		ofxButton buttonReset; //done
		ofxToggle toggleDrawImage; //done
		
		ofRectangle rectangleImage;
		ofSoundPlayer soudPlayer;
};
