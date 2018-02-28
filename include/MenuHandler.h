#pragma once

#ifndef MENU_H
	#include "Menu.h"
#endif //!MENU_H

#ifndef OPTIONSMENU_H
	#include "OptionMenu.h"
#endif //!OPTIONSMENU_H

#ifndef GAMESTATES_H
	#include "GameStates.h"
#endif //!GAMESTATES_H

#ifndef MENUHANDLER_H
#define MENUHANDLER_H

struct menuSettings {
	bool show = false;
	GameState menuState;
	menuSettings() {}
	menuSettings(bool s, GameState state) {
		menuState = state;
		show = s;
	}
};

class MenuHandler {
private:
	map<int, pair<Menu*, menuSettings>> menu_map;
	// maps become faster than vectors once there are around 5-30 elements.
public:
	void draw();
	void updateState(GameState state);
	MenuHandler() {
		menu_map.emplace(0, make_pair((Menu*)new OptionMenu(),
			menuSettings(false, GAME_OPTIONSMENU)));
	}
};

#endif //!MENUHANDLER_H