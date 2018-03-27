#pragma once

#ifndef OFMAIN_H
	#define OFMAIN_H
	#include "ofMain.h"
#endif //!OFMAIN_H

#ifndef SCOREKEEPER_H
	#include "ScoreKeeper.h"
#endif

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
		GameState idolSchemeState; // describes what the game is doing.
		ofTrueTypeFont textOut;

		ofImage myImage;
		
		/// Game Objects
		/// ------------
		MenuHandler menuHandler;
		Conductor mainConductor; // This will keep time.
        deque<Note> notes;
		ScoreKeeper scoreKeeper;
		Note *activeNote;

		ISGUI::IdolVecButton newVecBtn = ISGUI::IdolVecButton(ofVec2f(200, 300), ofVec2f(200, 100), "My Button", ofColor(255, 0, 0, 255), ofColor(200, 0, 0, 255));
		vector<ISGUI::IdolButton*> mainMenuBtns = {
			new ISGUI::IdolButton("images/btn0.png", "images/btn0hov.png", ofPoint(100, 175), 100, 50),
			new ISGUI::IdolButton("images/btn1.png", "images/btn1hov.png", ofPoint(100, 250), 100, 50),
			new ISGUI::IdolButton("images/btn2.png", "images/btn2hov.png", ofPoint(100, 320), 100, 50),
			new ISGUI::IdolButton("images/btn3.png", "images/btn3hov.png", ofPoint(100, 395), 100, 50),
			static_cast<ISGUI::IdolButton*>(&newVecBtn)
		};
		ISGUI::IdolGuiGroup gui;

		/// initialization
		/// --------------
		void setup() override;

		/// game loop
		/// ---------
		void update() override;
		void draw() override;

		/// callbacks
		/// ---------
		void keyPressed(int key) override;
		void keyReleased(int key) override;
		void mouseMoved(int x, int y) override;
		void mouseDragged(int x, int y, int button) override;
		void mousePressed(int x, int y, int button) override;
		void mouseReleased(int x, int y, int button) override;
		void mouseEntered(int x, int y) override;
		void mouseExited(int x, int y) override;
		void windowResized(int w, int h) override;
		void dragEvent(ofDragInfo dragInfo) override;
		void gotMessage(ofMessage msg) override;
};

#endif //!IDOLSCHEME_H
