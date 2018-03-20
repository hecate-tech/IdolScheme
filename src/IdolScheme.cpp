#include "../include/IdolScheme.h"

////////////////////////////////////////////////////////////////
   /////////////////      Initialization      ///////////////
////////////////////////////////////////////////////////////////

void IdolScheme::setup() {
	ofBackground(45, 45, 190, 255);
	IdolScheme_State = GAME_ACTIVE;

	ofTrueTypeFont::setGlobalDpi(60);
	textOut.load("verdana.ttf", 20, true, false);
	textOut.setLetterSpacing(1.037);
	
	gui.add(mainMenuBtns);
	menuHandler.add((Menu*)&gui, false, GAME_MAINMENU);
	
	vector<string> bmNames = BeatMapHandler::getMapNames();
	
	// debug menu select
	for (string &a : bmNames)
		cout << a << endl;
	
	ofXml bm = BeatMapHandler::getMap(bmNames.at(0));
	cout << BeatMapHandler::getMapName(bm) << endl;


	//BeatMapHandler::readBeatMaps();

	mainConductor.startTimer();
	// something is going on with the formula and it doesn't work properly
	// unless the note is in its sepcial position.
}


///////////////////////////////////////////////////////////////
   //////////////////      Game Loop      //////////////////
///////////////////////////////////////////////////////////////

void IdolScheme::update() {
	for (unsigned int i = 0; i < gui.getButtons().size(); i++)
		if (gui.getButton(i)->getMouseDown())
			cout << "Pressed Button " + ofToString(i) << endl;

	mainConductor.refreshMembers();
	mainConductor.beatSinceRefresh = mainConductor.currBeat;
}

//--------------------------------------------------------------
void IdolScheme::draw() {
	textOut.drawString("Current beat: " + ofToString(mainConductor.currBeat, 2) + "/" + ofToString(mainConductor.totalBeats), 10, 20);
	textOut.drawString("Active Note TBEAT: " + (activeNote ? ofToString(activeNote->noteSettings.noteNum) : "None"), 10, 40);
	textOut.drawString("Current time: " + ofToString(((float) mainConductor.timeDiff.count()) / 1000, 2) + "/" + ofToString(mainConductor._lengthInS), 10, 60);
	textOut.drawString("Beats since last refresh: " + ofToString(mainConductor.numBeatsSinceRefresh, 5), 10, 80);
	textOut.drawString("FPS: " + ofToString(ofGetFrameRate()), 10, 100);
	textOut.drawString("Score: " + ofToString(scoreKeeper.score), 400, 20);
	textOut.drawString("WONDERFUL: " + ofToString(scoreKeeper.wonderfulCount), 400, 40);
	textOut.drawString("GOOD: " + ofToString(scoreKeeper.goodCount), 400, 60);
	textOut.drawString("MEDICORE: " + ofToString(scoreKeeper.mediocreCount), 400, 80);
	textOut.drawString("BAD: " + ofToString(scoreKeeper.badCount), 400, 100);
	textOut.drawString("GARBAGE: " + ofToString(scoreKeeper.garbageCount), 400, 120);
	textOut.drawString("WRONG: " + ofToString(scoreKeeper.wrongCount), 400, 140);

	menuHandler.draw();
}

///////////////////////////////////////////////////////////////
   ///////////////      Misc. Functions      ///////////////
///////////////////////////////////////////////////////////////

float IdolScheme::yCoord(float coordinate) {
	return coordinate * ofGetHeight();
}

//--------------------------------------------------------------
float IdolScheme::xCoord(float coordinate) {
	return coordinate * ofGetWidth();
}

//--------------------------------------------------------------
ofPoint IdolScheme::qSetCoords(ofPoint coordinates) {
	return ofPoint(coordinates.x * ofGetWidth(), coordinates.y * ofGetHeight());
}

///////////////////////////////////////////////////////////////
   //////////////////      Callbacks      //////////////////
///////////////////////////////////////////////////////////////

void IdolScheme::keyPressed(int key) {
	switch (key) {
		case 'o':
			menuHandler.updateState(GAME_OPTIONSMENU);
			break;
		case 'm':
			menuHandler.updateState(GAME_MAINMENU);
			break;
		default:
			//activeNote->hit(BUTTON_A);	
			break;
	}
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
