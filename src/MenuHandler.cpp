#include "../include/MenuHandler.h"

//-----------------------------
void MenuHandler::draw() {
	for (int i = 0; i < menu_map.size(); i++) {
		if (menu_map[i].second.show) {
			menu_map[i].first->draw();
		}
	}
}

//-----------------------------
void MenuHandler::updateState(GameState state) {
	for (int i = 0; i < menu_map.size(); i++) {
		if (menu_map[i].second.menuState == state) {
			menu_map[i].second.show = !menu_map[i].second.show;
			break;
		}
	}
}