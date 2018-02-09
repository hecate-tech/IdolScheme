#include "../include/IdolScheme.h"



////////////////////////////////////////////////////////////////
   /////////////////      Initialization      ///////////////
////////////////////////////////////////////////////////////////

void IdolScheme::setup() {
	ofBackground(45, 45, 190, 255);

	IdolScheme_State = GAME_ACTIVE;
	IdolScheme_WindowAspect = optionMenu.getWindowAspect();
	IdolScheme_WindowSize = optionMenu.getWindowSize();

	ofTrueTypeFont::setGlobalDpi(60);
	textOut.load("verdana.ttf", 20, true, false);
	textOut.setLetterSpacing(1.037);

	cout << "Enter a bpm: ";
	cin  >> mainConductor._bpm;
	cout << "Enter an offset (ms): ";
	cin  >> mainConductor._offsetInMs;
	cout << "Enter a song length: ";
	cin  >> mainConductor._lengthInS;
	
	mainConductor.startTimer();
	note.setup(ofPoint(),ofPoint(0,(ofGetHeight() / 2)),BUTTON,BUTTON_A);
}



///////////////////////////////////////////////////////////////
   //////////////////      Game Loop      //////////////////
///////////////////////////////////////////////////////////////

void IdolScheme::update() {
	mainConductor.refreshMembers();
	mainConductor.beatSinceRefresh = mainConductor.currBeat;
	a += ofGetLastFrameTime() * 3.5f;
}

//--------------------------------------------------------------
void IdolScheme::draw() {
	string currBeatString = "Current beat: " + std::to_string(mainConductor.currBeat) + "/" + std::to_string(mainConductor.totalBeats); 	
	textOut.drawString(currBeatString, 10, 20);
	string lengthString = "Current time: " + std::to_string(((float) mainConductor.timeDiff.count()) / 1000) + "/" + std::to_string(mainConductor._lengthInS);
	textOut.drawString(lengthString, 10, 40);
	string beatDiffString = "Beats since last refresh: " + std::to_string(mainConductor.numBeatsSinceRefresh);
	textOut.drawString(beatDiffString, 10, 60);
	textOut.drawString(ofToString(ofGetFrameRate()), 10, 80);

	note.draw((ofGetWidth() / 2), (cos(a) * 150) + (ofGetHeight() / 2), (ofGetWidth() / 2), (ofGetHeight() / 2));

	if(optionMenuShow)
		optionMenu.draw();
}

void IdolScheme::drawOptionMenu() {
	optionMenu.draw();
}

///////////////////////////////////////////////////////////////
   //////////////////      Callbacks      //////////////////
///////////////////////////////////////////////////////////////

void IdolScheme::keyPressed(int key) {

}

//--------------------------------------------------------------
void IdolScheme::keyReleased(int key) {
	switch (key) {
		case 'o':
			optionMenuShow = !optionMenuShow;
	}
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
	optionMenu.windowResized(w, h);
}

//--------------------------------------------------------------
void IdolScheme::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void IdolScheme::dragEvent(ofDragInfo dragInfo) { 

}
