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
	vector<pair<Menu*, menuSettings>> menu_vec;
public:
	void draw();
	void updateState(GameState state);
	void add(Menu *menu, bool showing, GameState state) {
		menu_vec.push_back(make_pair(menu, menuSettings(showing, state)));
	}
	MenuHandler() {
		menu_vec.push_back(make_pair((Menu*)new OptionMenu(), menuSettings(false, GAME_OPTIONSMENU)));
	}
};

#endif //!MENUHANDLER_H