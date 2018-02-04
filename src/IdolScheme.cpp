#include "../include/IdolScheme.h"



////////////////////////////////////////////////////////////////
   /////////////////      Initialization      ///////////////
////////////////////////////////////////////////////////////////

void IdolScheme::setup() {
	ofBackground(45, 45, 190, 255);

	ofTrueTypeFont::setGlobalDpi(72);
	textOut.load("verdana.ttf", 32, true, false);
	textOut.setLetterSpacing(1.037);
	
	note.setup(ofPoint(),ofPoint(),BUTTON,BUTTON_A);
	note.setSize(100);
}



///////////////////////////////////////////////////////////////
   //////////////////      Game Loop      //////////////////
///////////////////////////////////////////////////////////////

void IdolScheme::update() {
	a += ofGetLastFrameTime() * 3.5f;
}

//--------------------------------------------------------------
void IdolScheme::draw() {
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2); // sets perspective to 0,0

	note.draw(-150, (sin(a) * ((ofGetHeight() / 2) - (ofGetHeight() * 0.2))), -150); // Derek helped me because I'm stupid.
	note.draw( 150, (cos(a) * ((ofGetHeight() / 2) - (ofGetHeight() * 0.2))),  150);
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
	
}

//--------------------------------------------------------------
void IdolScheme::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void IdolScheme::dragEvent(ofDragInfo dragInfo) { 

}
