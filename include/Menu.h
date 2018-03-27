#pragma once

#ifndef MENU_H
#define MENU_H

class Menu {
public:
	virtual ~Menu();
	virtual void draw(); // pure virtual method
	Menu();
};

inline Menu::~Menu() = default;
inline void Menu::draw() {}
inline Menu::Menu() = default;

#endif //!MENU_H
