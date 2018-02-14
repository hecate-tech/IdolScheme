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

	string test;
	ifstream infile;

	infile.open("beatmaps/test.txt");
	int lineNum = 1;
	
	size_t pos  = 0;
	size_t last = 0;
	size_t next = 0;

	string token;
	string delimiter = "|";
	string cmtPrefix = "#";
	while(!infile.eof()) {
		getline(infile, test);
		
		if(test.find_first_not_of(' ') != std::string::npos
			&& test.compare(0, cmtPrefix.size(), cmtPrefix)) {
			
			string resa = test.substr(last);
			for(int i = 0; i < resa.length(); i++)
				if(resa[i] == ' ')  resa.erase( remove( resa.begin(), resa.end(), ' ' ), resa.end() );
			
			while((pos = resa.find(delimiter)) != string::npos) {
				token = resa.substr(0, pos);
				std::cout << lineNum << ": " << token << std::endl;
				resa.erase(0, pos + delimiter.length());
			}
			
			std::cout << lineNum << ": " << resa << std::endl;
		}
		lineNum++;
	}
	infile.close();


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

#ifdef TARGET_LINUX
	int w = ofGetWidth();			  
	int h = ofGetHeight();  

	if(w != optionMenu.getWinHeight() || h != optionMenu.getWinWidth()) ofSetWindowShape(optionMenu.getWinWidth(), optionMenu.getWinHeight());
#endif
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

	note.draw(0.5 * ofGetWidth(), (cos(a) * 150) + (ofGetHeight() / 2), (ofGetWidth() / 2), (ofGetHeight() / 2));

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
	//optionMenu.windowResized(w, h);
}

//--------------------------------------------------------------
void IdolScheme::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void IdolScheme::dragEvent(ofDragInfo dragInfo) { 

}
