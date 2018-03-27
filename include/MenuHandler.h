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

struct MenuSettings {
	bool show = false;
	GameState menuState;

	MenuSettings() : menuState() {}
	MenuSettings(const bool s, const GameState state) : show(s), menuState(state) {}
};

class MenuHandler {
	vector<pair<Menu*, MenuSettings>> menu_vec;
public:
	void draw();
	void updateState(GameState state);
	
	void add(Menu *menu, const bool showing, const GameState state) {
		menu_vec.emplace_back(menu, MenuSettings(showing, state));
	}
	MenuHandler() {
		menu_vec.emplace_back(static_cast<Menu*>(new OptionMenu()), MenuSettings(false, GAME_OPTIONSMENU));
	}
};

#endif //!MENUHANDLER_H