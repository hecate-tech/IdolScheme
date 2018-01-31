#pragma once

#ifndef OFMAIN_H
	#define OFMAIN_H
	#include "../ofMain.h"
#endif //!OFMAIN_H

#ifndef NOTE_H
	#include "Note.h"
#endif //NOTE_H


#ifndef IDOLSCHEME_H
#define IDOLSCHEME_H


enum GameState {
	GAME_ACTIVE,
	GAME_PAUSE,
	GAME_LOSE,
	GAME_WIN,
	GAME_MENU,
};

class IdolScheme : public ofBaseApp {
	public:
		GameState IdolScheme_State;
		ofTrueTypeFont textOut;
		Note testingNote;
		
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
};

#endif //!IDOLSCHEME_H