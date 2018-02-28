#pragma once

#ifndef MENU_H
#define MENU_H

class Menu {
public:
	virtual void draw()=0; // pure virtual method
	Menu() {}
};

#endif //!MENU_H