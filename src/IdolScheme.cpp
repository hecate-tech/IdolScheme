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

	/// debug beatmap picker
	/// --------------------
	beatMap currBeatMap = bmh.beatMapMenu();
	

	for (noteInfo &a : currBeatMap.noteParams) {
		if (!a.rest) {
			mainConductor._bpm = a.bpm;
			mainConductor._offsetInMs = a.offset;
			mainConductor._lengthInS = a.length;
			break;
		}
	}
	
	for (unsigned int i = 0; i < currBeatMap.noteParams.size(); i++) {
		
		notes.push_back(Note());
		
		if (currBeatMap.noteParams.at(i).rest) {
			notes.at(i).setBeatRest(currBeatMap.noteParams.at(i));
		}
		else if (!currBeatMap.noteParams.at(i).rest) {
			notes.at(i).setBeatNote(currBeatMap.noteParams.at(i));
			notes.at(i).calcNoteParams();
		}
	}

	for (Note a : notes) {
		cout << a.noteSettings.noteNum << endl;
	}

	mainConductor.startTimer();
	// something is going on with the formula and it doesn't work properly
	// unless the note is in its sepcial position.
}


///////////////////////////////////////////////////////////////
   //////////////////      Game Loop      //////////////////
///////////////////////////////////////////////////////////////

void IdolScheme::update() {
	mainConductor.refreshMembers();
	mainConductor.beatSinceRefresh = mainConductor.currBeat;

#ifdef TARGET_LINUX
	int w = ofGetWidth();
	int h = ofGetHeight();
	if(w != optionMenu.getWinHeight() || h != optionMenu.getWinWidth())
		ofSetWindowShape(optionMenu.getWinWidth(), optionMenu.getWinHeight());
#endif
}

//--------------------------------------------------------------
void IdolScheme::draw() {
	string currBeatString = "Current beat: " + ofToString(mainConductor.currBeat, 2) + "/" + ofToString(mainConductor.totalBeats);
	textOut.drawString(currBeatString, 10, 20);
	string lengthString = "Current time: " + ofToString(((float) mainConductor.timeDiff.count()) / 1000, 2) + "/" + ofToString(mainConductor._lengthInS);
	textOut.drawString(lengthString, 10, 40);
	string beatDiffString = "Beats since last refresh: " + ofToString(mainConductor.numBeatsSinceRefresh, 5);
	textOut.drawString(beatDiffString, 10, 60);
	textOut.drawString(ofToString(ofGetFrameRate()), 10, 80);

	for (unsigned int i = 0; i < notes.size(); i++) {
		if (mainConductor.currBeat > (notes.at(i).noteSettings.noteNum + 2)) {
			notes.pop_front(); // removes the finished note.
		} else if (mainConductor.currBeat >= notes.at(i).noteSettings.noteNum
			&& !notes.at(i).noteSettings.rest) {
			notes.at(i).moveByBeats(mainConductor.currBeat);
		} else {
			break;
		}
	}

	if(optionMenuShow)
		optionMenu.draw();
}

///////////////////////////////////////////////////////////////
   ///////////////      Misc. Functions      ///////////////
///////////////////////////////////////////////////////////////

float IdolScheme::qSetHCoord(float coordinate) {
	return coordinate * ofGetHeight();
}

//--------------------------------------------------------------
float IdolScheme::qSetWCoord(float coordinate) {
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
			optionMenuShow = !optionMenuShow;
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
