#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
		ofBackground(0,0,0);
		ofEnableSmoothing();
		ofSetVerticalSync(true);
		fbo.allocate( ofGetWidth(), ofGetHeight(), GL_RGBA32F_ARB, 8);
		image.loadImage("c_outline2.png");
		rectangleImage.set(0, 0, image.getWidth(), ofGetHeight());
		ofEnableAlphaBlending();
		ofSetLineWidth(1);
		firstBackground = true;
		fbo.begin();
		ofClear(255,255,255, 0);
		fbo.end();
		ofSetBackgroundAuto(false);
		
		//gui
		hideGui = false;
		gui.setup();
		gui.setPosition(10, 20);
		gui.add(toggleFill.setup("fill", false));
		gui.add(toggleFullScreen.setup("fullscreen", false));
		gui.add(toggleWireColorFromPhoto.setup("wire color from photo", true));
		gui.add(toggleDrawImage.setup("draw image", false));
		gui.add(sliderWireColor.setup("wire color", ofColor::white, ofColor(0, 0), ofColor(255, 255)));
		gui.add(sliderWireLineWidth.setup("wire line width", 1., 0., 10.));
		gui.add(sliderPalseLineWidth.setup("palse line width", 1., 0., 10.));
		gui.add(buttonReset.setup("triangulation reset"));
		gui.add(sliderFrameRate.setup("framerate", 60, 1, 60));
		
		// listener for gui
		buttonReset.addListener(this, &ofApp::resetTriangulation);
		toggleFullScreen.addListener(this, &ofApp::fullScreen);
		sliderFrameRate.addListener(this, &ofApp::setFrameRate);
		
		//sound
		//		soundPlayer.loadSound("");
}

void ofApp::setFrameRate(int & sliderFrameRate){
		ofSetFrameRate(sliderFrameRate);
}

void ofApp::resetTriangulation(){
		triangulation.reset();
}

void ofApp::fullScreen(){
		ofToggleFullscreen();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
		// reset screen
		ofSetColor(0, 0, 0, 255);
		ofRect(0, 0, ofGetWidth(), ofGetHeight());
		ofSetColor(255, 255, 255, 255);
		if (toggleDrawImage) {
				image.draw(0, 0, image.width, image.height);
		}
		
		// draw mesh
		ofPushStyle();
		toggleFill ? ofFill() : ofNoFill();
		ofSetLineWidth(sliderWireLineWidth);
		ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    triangulation.draw();
		ofPopStyle();
		
		// palse layer
		fbo.begin();
		// screen update
		ofEnableBlendMode(OF_BLENDMODE_ALPHA);
		ofSetColor(0, 0, 0, 5);
		ofRect(0, 0, ofGetWidth(), ofGetHeight());
		ofSetColor(255, 255, 255, 255);
		
		if (ofGetFrameNum()%60 == 1 && ofRandom(2)>1) {
				ofEnableBlendMode(OF_BLENDMODE_ADD);
				ofMesh mesh;
				mesh.setMode(OF_PRIMITIVE_LINES);
				mesh.enableColors();
				mesh.enableIndices();
				ofVec2f start(ofRandom(0, image.width-1), ofRandom(0, image.height-1));
				ofVec2f end(start.x+ofRandom(-1000, 1000), start.y+ofRandom(-1000, 1000));
				
				//mesh
				for (int i = 0; i<ofRandom(10, 100); i++) {
						float theta = ofRandom(0, 2*PI);
						float amplitude = 300*pow(ofRandom(0,1), 2);
						ofPoint meshPoint(sin(theta)*amplitude+start.x, cos(theta)*amplitude+start.y, 0);
						triangulation.addPoint(meshPoint);
				}
				triangulation.triangulate(image);
				
				// palse
				if (rectangleImage.inside(end)){ // end.x>=0 && end.y>=0 && end.x<image.width && end.y<image.height)
						mesh.addVertex(start);
						mesh.addColor(image.getColor(start.x, start.y));
						mesh.addVertex(end);
						ofColor endColor =  image.getColor(end.x, end.y);
						mesh.addColor(ofColor(endColor.r, endColor.g, endColor.b, 0));
						int indexNum = mesh.getIndices().size();
						mesh.addIndex(indexNum);
						mesh.addIndex(indexNum+1);
				}else{
						mesh.addVertex(start);
						ofColor color = image.getColor(start.x, start.y);
						mesh.addColor(color);
						mesh.addVertex(end);
						mesh.addColor(ofColor(color.r, color.g, color.b, 0));
						int indexNum = mesh.getIndices().size();
						mesh.addIndex(indexNum);
						mesh.addIndex(indexNum+1);
				}
				ofSetLineWidth(sliderPalseLineWidth);
				ofEnableBlendMode(OF_BLENDMODE_ADD);
				mesh.draw();
				
		}
		fbo.end();
		ofEnableBlendMode(OF_BLENDMODE_ALPHA);
		fbo.draw(0, 0);
		
		// hide below for live
		if (!hideGui) {
				// gui
				gui.draw();
				
				// debug
				stringstream ss;
				ss << "framerate: " << ofToString(ofGetFrameRate(), 0);
				ofDrawBitmapString(ss.str(), 10, 15);
				
				// guide line
				ofPushStyle();
				ofSetColor(255, 255, 0);
				ofLine(0, ofGetHeight()/2., ofGetWidth(), ofGetHeight()/2.);
				ofLine(ofGetWidth()/2., 0, ofGetWidth()/2., ofGetHeight());
				ofSetColor(255, 0, 255);
				ofLine(image.getWidth(), 0, image.getWidth(), ofGetHeight());
				ofLine(0, image.getHeight(), ofGetWidth(), image.getHeight());
				ofPopStyle();
		}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
		switch (key) {
				case 'r':
						triangulation.reset();
						break;
				case 'h':
						hideGui = !hideGui;
				default:
						break;
		}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
