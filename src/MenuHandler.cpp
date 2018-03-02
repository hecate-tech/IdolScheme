#include "../include/MenuHandler.h"

//-----------------------------
void MenuHandler::draw() {
	for (unsigned int i = 0; i < menu_vec.size(); i++) {
		if (menu_vec.at(i).second.show) {
			menu_vec.at(i).first->draw();
		}
	}
}

//-----------------------------
void MenuHandler::updateState(GameState state) {
	for (unsigned int i = 0; i < menu_vec.size(); i++) {
		if (menu_vec.at(i).second.menuState == state) {
			menu_vec.at(i).second.show = !menu_vec.at(i).second.show;
			break;
		}
	}
}