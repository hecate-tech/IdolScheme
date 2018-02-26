#pragma once

#ifndef OPTIONSMENU_H
	#include "OptionMenu.h"
#endif //!OPTIONSMENU_H

#ifndef GAMESTATES_H
	#include "GameStates.h"
#endif //!GAMESTATES_H

#ifndef OFMAIN_H
	#define OFMAIN_H
	#include "ofMain.h"
#endif //!OFMAIN_H

#ifndef MENUHANDLER_H
#define MENUHANDLER_H

class MenuHandler {
public:
	static void draw();
private:
	GameState currState;
	void changeState(int state);
	//OptionMenu optionsMenu;
};

#endif //!MENUHANDLER_H