#pragma once

#ifndef OFMAIN_H
	#define OFMAIN_H
	#include "ofMain.h"
#endif //!OFMAIN_H

#ifndef NOTE_H
	#include "Note.h"
#endif //NOTE_H

#ifndef CONDUCTOR_H
	#include "Conductor.h"
#endif

#ifndef BEATMAPREADER_H
	#include "BeatMapHandler.h"
#endif //!BEATMAPREADER_H

#ifndef MENUHANDLER_H
	#include "MenuHandler.h"
#endif //!MENUHANDLER_H

#ifndef GAMESTATES_H
	#include "GameStates.h"
#endif //GAMESTATES_H

#include "MenuItems.h"

#ifndef IDOLSCHEME_H
#define IDOLSCHEME_H

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
		
		/// Game Objects
		/// ------------
		BeatMapHandler bmHandler;
		MenuHandler menuHandler;
		Conductor mainConductor; // This will keep time.
        deque<Note> notes;
		
		ISGUI::idolButton myButton;
		vector<ISGUI::idolButton> mainMenuBtns = {
			myButton,
			ISGUI::idolButton("images/note.png", "images/shadow.png", ofPoint(200, 100), 80, 80),
			ISGUI::idolButton("images/note.png", "images/shadow.png", ofPoint(100, 200), 80, 80),
			ISGUI::idolButton("images/note.png", "images/shadow.png", ofPoint(100, 300), 80, 80),
		};
		ISGUI::idolGuiGroup gui;

		/// initialization
		/// --------------
		void setup();

		/// game loop
		/// ---------
		void update();
		void draw();

		/// misc. functions
		/// ---------------
		float yCoord(float coordinate);
		float xCoord(float coordinate);
		ofPoint qSetCoords(ofPoint coordinates);

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
