#include "../include/IdolScheme.h"

////////////////////////////////////////////////////////////////
   /////////////////      Initialization      ///////////////
////////////////////////////////////////////////////////////////

void IdolScheme::setup() {
	ofBackground(45, 45, 190, 255);
	idolSchemeState = GAME_ACTIVE;

	/*--------------------debugging out--------------------*/
	ofTrueTypeFont::setGlobalDpi(60);
	textOut.load("verdana.ttf", 20, true, false);
	textOut.setLetterSpacing(1.037);

	/*-----------------menu handle loading-----------------*/
	gui.add(mainMenuBtns);
	menuHandler.add(static_cast<Menu*>(&gui), false, GAME_MAINMENU);

	/*-------------------beatmap loading-------------------*/
	auto bmNames = BeatMapHandler::getMapNames();

	for (auto& a : bmNames)
		cout << a << endl; // writing out all available beatmaps.

	myNote.setup(ofPoint(100, 100), ofPoint(200, 200), NoteType::BUTTON, NoteButton::BUTTON_A);

	/*-----------------------conductor---------------------*/
	mainConductor.startTimer();
}

///////////////////////////////////////////////////////////////
   //////////////////      Game Loop      //////////////////
///////////////////////////////////////////////////////////////

void IdolScheme::update() {
	for (unsigned int i = 0; i < gui.getButtons().size(); i++)
		if (gui.getButton(i)->mouseDown())
			cout << "Pressed Button " + ofToString(i) << endl;

	mainConductor.refreshMembers();
	mainConductor.beatSinceRefresh = mainConductor.currBeat;
}

//--------------------------------------------------------------
void IdolScheme::draw() {
	textOut.drawString("Current beat: " + ofToString(mainConductor.currBeat, 2) + "/" + ofToString(mainConductor.totalBeats), 10, 20);
	textOut.drawString("Active Note TBEAT: " + (activeNote ? ofToString(activeNote->noteSettings.noteNum) : "None"), 10, 40);
	textOut.drawString("Current time: " + ofToString(static_cast<float>(mainConductor.timeDiff.count()) / 1000, 2) + "/" + ofToString(mainConductor._lengthInS), 10, 60);
	textOut.drawString("Beats since last refresh: " + ofToString(mainConductor.numBeatsSinceRefresh, 5), 10, 80);
	textOut.drawString("FPS: " + ofToString(ofGetFrameRate()), 10, 100);
	textOut.drawString("Score: " + ofToString(scoreKeeper.score), 400, 20);
	textOut.drawString("WONDERFUL: " + ofToString(scoreKeeper.wonderfulCount), 400, 40);
	textOut.drawString("GOOD: " + ofToString(scoreKeeper.goodCount), 400, 60);
	textOut.drawString("MEDICORE: " + ofToString(scoreKeeper.mediocreCount), 400, 80);
	textOut.drawString("BAD: " + ofToString(scoreKeeper.badCount), 400, 100);
	textOut.drawString("GARBAGE: " + ofToString(scoreKeeper.garbageCount), 400, 120);
	textOut.drawString("WRONG: " + ofToString(scoreKeeper.wrongCount), 400, 140);

	myNote.draw(200, 200, 300, 300);

	menuHandler.draw();
}

///////////////////////////////////////////////////////////////
   //////////////////      Callbacks      //////////////////
///////////////////////////////////////////////////////////////

void IdolScheme::keyPressed(const int key) {
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
