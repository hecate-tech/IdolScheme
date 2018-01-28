#include "../include/IdolScheme.h"

//--------------------------------------------------------------
void IdolScheme::setup() {
	ofSetWindowShape(800, 600);
	ofBackground(70, 70, 209, 255);
}

//--------------------------------------------------------------
void IdolScheme::update() {
	counter += 0.033f;
}

//--------------------------------------------------------------
void IdolScheme::draw() {

	ofFill();
	for (int i = 0; i < 200; i++) {
		ofSetColor((int)ofRandom(0, 255), (int)ofRandom(0, 255), (int)ofRandom(0, 255));
		ofDrawRectangle(ofRandom(100, 300), ofRandom(100, 500), ofRandom(10, 20), ofRandom(10, 20));
	}
	ofSetHexColor(0x000000);
	ofDrawBitmapString("RECTANGLESSSS!!!", 275, 500);

	ofSetHexColor(0x00FF33);
	ofDrawRectangle(400, 350, 100, 100);
	ofEnableAlphaBlending();
	ofSetColor(255, 0, 0, 127);
	ofDrawRectangle(450, 430, 100, 33);
	ofSetColor(255, 0, 0, (int)(counter * 10.f) % 255);
	ofDrawRectangle(450, 370, 100, 33);
	ofDisableAlphaBlending();

	ofSetHexColor(0x000000);
	ofDrawBitmapString("TRANSPARENCY!!!", 410, 500);
}

//--------------------------------------------------------------
void IdolScheme::keyPressed(int key) {

}

//--------------------------------------------------------------
void IdolScheme::keyReleased(int key) {

}

//--------------------------------------------------------------
void IdolScheme::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void IdolScheme::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void IdolScheme::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void IdolScheme::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void IdolScheme::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void IdolScheme::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void IdolScheme::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void IdolScheme::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void IdolScheme::dragEvent(ofDragInfo dragInfo) { 

}
