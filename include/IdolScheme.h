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


/* @brief - GameState
 * an easily accessible state that the
 * game is currently in. This enum is
 * accessible by the entire class and
 * used to track where the game is.
 */
enum GameState {
	GAME_ACTIVE,
	GAME_PAUSE,
	GAME_LOSE,
	GAME_WIN,
	GAME_MENU,
	GAME_LOAD,
	GAME_ERROR,
};


/* @brief - IdolScheme
 * The IdolScheme class holds the entirety
 * of the game into a class. This gives everything
 * easy access to each other without having to use
 * confusing global pointers and work-arounds.
 */
class IdolScheme : public ofBaseApp {
	public:
		GameState IdolScheme_State; // describes what the game is doing.
		ofTrueTypeFont textOut;
		Note note; // need a better solution than making each note.
		float a = 0.f;

		/// initialization
		/// --------------
		void setup();

		/// game loop
		/// ---------
		void update();
		void draw();

		/// callbacks
		/// ---------
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