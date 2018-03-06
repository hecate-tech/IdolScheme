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

	/// debug beatmap picker
	/// --------------------
	beatMap currBeatMap = bmHandler.beatMapMenu();
	vector<beatMap>().swap(bmHandler.beatMaps); // clears bmh

	for (noteInfo &a : currBeatMap.noteParams) {
		if (!a.rest) {
			mainConductor._bpm = a.bpm;
			mainConductor._offsetInMs = a.offset;
			//mainConductor._lengthInS = a.length;
			break;
		}
	}
	
	for (unsigned int i = 0; i < currBeatMap.noteParams.size(); i++) {
		notes.push_back(Note()); // loads all notes at once.
		//! TODO refactor this so we load 3 notes in advance and not all at once.
		
		if (currBeatMap.noteParams.at(i).rest) {
			notes.at(i).setBeatRest(currBeatMap.noteParams.at(i));
		}
		else if (!currBeatMap.noteParams.at(i).rest) {
			notes.at(i).setBeatNote(currBeatMap.noteParams.at(i));
			notes.at(i).calcNoteParams();
			notes.at(i).scoreKeeper = &scoreKeeper;
			notes.at(i).conductor = &mainConductor;
		}
	}
	mainConductor.startTimer();
	// something is going on with the formula and it doesn't work properly
	// unless the note is in its sepcial position.
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
	if (notes.size() != 0) {
		for (unsigned int i = 0; i < notes.size(); i++) {
			if (mainConductor.currBeat >(notes.at(i).noteSettings.noteNum + 3)) {
				notes.erase(notes.begin()); // erases finished note
			} else if (mainConductor.currBeat >= notes.at(i).noteSettings.noteNum && !notes.at(i).noteSettings.rest) {
				notes.at(i).moveByBeats(mainConductor.currBeat); // draws the note
				activeNote = &(notes.at(i));
			} else { // if the note isn't active yet
				break;
			}
		}
	}
	newVecBtn.draw();
	//gui.draw();
	menuHandler.draw(); // menu handler
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
			activeNote->hit(BUTTON_A);	
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
