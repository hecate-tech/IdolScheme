#include "../include/IdolScheme.h"



////////////////////////////////////////////////////////////////
   /////////////////      Initialization      ///////////////
////////////////////////////////////////////////////////////////

void IdolScheme::setup() {
	ofBackground(45, 45, 190, 255);

	testingNote.note_color[1] = 0;
	testingNote.note_color[2] = 0;
	ofTrueTypeFont::setGlobalDpi(60);
	textOut.load("verdana.ttf", 12, true, false);
	ofTrueTypeFont::setGlobalDpi(72);
	textOut.load("verdana.ttf", 32, true, false);
	textOut.setLetterSpacing(1.037);
	
	cout << "Enter a bpm: ";
	cin >> mainConductor._bpm;
	cout << "Enter an offset (ms): ";
	cin >> mainConductor._offsetInMs;
	cout << "Enter a song length: ";
	cin >> mainConductor._lengthInS;
	mainConductor.startTimer();
	note.setup(ofPoint(),ofPoint(),BUTTON,BUTTON_A);
	note.setSize(100);
}



///////////////////////////////////////////////////////////////
   //////////////////      Game Loop      //////////////////
///////////////////////////////////////////////////////////////

void IdolScheme::update() {
	testingNote.update();
	mainConductor.refreshMembers();
	mainConductor.beatSinceRefresh = mainConductor.currBeat;
	a += ofGetLastFrameTime() * 3.5f;
}

//--------------------------------------------------------------
void IdolScheme::draw() {
	string currBeatString = "Current beat: " + std::to_string(mainConductor.currBeat) + "/" + std::to_string(mainConductor.totalBeats); 	
	textOut.drawString(currBeatString, 10, 40);
	string lengthString = "Current time: " + std::to_string(((float) mainConductor.timeDiff.count()) / 1000) + "/" + std::to_string(mainConductor._lengthInS);
	textOut.drawString(lengthString, 10, 60);
	string beatDiffString = "Beats since last refresh: " + std::to_string(mainConductor.numBeatsSinceRefresh);
	textOut.drawString(beatDiffString, 10, 80);

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
