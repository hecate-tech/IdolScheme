#include "../include/IdolScheme.h"

//--------------------------------------------------------------
void IdolScheme::setup() {
	ofSetWindowShape(800, 600);
	ofBackground(45, 45, 190, 255);

	testingNote.note_color[1] = 0;
	testingNote.note_color[2] = 0;
	ofTrueTypeFont::setGlobalDpi(60);
	textOut.load("verdana.ttf", 12, true, false);
	textOut.setLetterSpacing(1.037);
	testingNote.setup(ofPoint(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2), ofPoint(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2), BUTTON, BUTTON_EMPTY);
	
	cout << "Enter a bpm: ";
	cin >> mainConductor._bpm;
	cout << "Enter an offset (ms): ";
	cin >> mainConductor._offsetInMs;
	cout << "Enter a song length: ";
	cin >> mainConductor._lengthInS;
	mainConductor.startTimer();
}

///////////////////////////////////////////////////////////////
   //////////////////      Game Loop      //////////////////
///////////////////////////////////////////////////////////////

void IdolScheme::update() {
	testingNote.update();
	mainConductor.refreshMembers();
	mainConductor.beatSinceRefresh = mainConductor.currBeat;
}

//=============================================================
void IdolScheme::draw() {
	ofFill();
		
	ofSetHexColor(0x00FF33);
	ofDrawRectangle(450, 450, 100, 100);
	ofEnableAlphaBlending();
	ofSetColor(255, 255, 255, 255);
	
	testingNote.draw();

	ofSetColor(255, 0, 0, 127);
	ofDrawRectangle(500, 530, 100, 33);
	ofDrawRectangle(500, 470, 100, 33);
	ofDisableAlphaBlending();
	
	ofSetHexColor(0x000000);
	textOut.drawString("TRANSPARENCY!!!", 100, 500);

	string currBeatString = "Current beat: " + std::to_string(mainConductor.currBeat) + "/" + std::to_string(mainConductor.totalBeats); 	
	textOut.drawString(currBeatString, 10, 40);
	string lengthString = "Current time: " + std::to_string(((float) mainConductor.timeDiff.count()) / 1000) + "/" + std::to_string(mainConductor._lengthInS);
	textOut.drawString(lengthString, 10, 60);
	string beatDiffString = "Beats since last refresh: " + std::to_string(mainConductor.numBeatsSinceRefresh);
	textOut.drawString(beatDiffString, 10, 80);
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
