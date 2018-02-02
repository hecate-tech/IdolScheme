#include "../include/IdolScheme.h"

//--------------------------------------------------------------
void IdolScheme::setup() {
	ofBackground(45, 45, 190, 255);
	
	int w = ofGetWindowWidth();
	int h = ofGetWindowHeight();
	
	ofTrueTypeFont::setGlobalDpi(72);
	textOut.load("verdana.ttf", 32, true, false);
	textOut.setLetterSpacing(1.037);
	testingNote.setup(ofPoint(w / 2, h / 2), ofPoint(w / 2, h / 2), BUTTON, BUTTON_EMPTY);
	
	
}

///////////////////////////////////////////////////////////////
   //////////////////      Game Loop      //////////////////
///////////////////////////////////////////////////////////////

void IdolScheme::update() {
	//testingNote.update();
}

//=============================================================
void IdolScheme::draw() {
	//ofPushMatrix();
		ofTranslate( ofGetWidth() / 2, ofGetHeight() / 2 );
		//ofEnableAlphaBlending();
		ofDrawRectangle(ofPoint(0, 0), 100, 100);
		ofSetHexColor(0x00FF11);
		ofDrawRectangle(ofPoint(1, 1), 100, 100);
		ofSetHexColor(0xFFFFFF);
		//testingNote.draw(0,0);
		//std::cout << testingNote.notex << std::endl;
		//testingNote.draw();
		
		//ofDisableAlphaBlending();
	//ofPopMatrix();
}

///////////////////////////////////////////////////////////////
   //////////////////      Callbacks      //////////////////
///////////////////////////////////////////////////////////////

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
	testingNote.setPosition((w/2), (h/2), (w/2), (h/2));
	testingNote.setSize((w + h) * 0.1);
}

//--------------------------------------------------------------
void IdolScheme::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void IdolScheme::dragEvent(ofDragInfo dragInfo) { 

}
