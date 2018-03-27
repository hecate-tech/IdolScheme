#pragma once

#ifndef MENUITEMS_H
#define MENUITEMS_H

#ifndef OFMAIN_H
	#define OFMAIN_H
	#include "ofMain.h"
#endif //!OFMAIN_H

#ifndef OFXGUI_H
	#define OFXGUI_H
	#include "ofxGui.h"
#endif // !OFXGUI_H

#ifndef MENU_H
	#include "Menu.h"
#endif

/* @brief - idolChoice
 * a component of idolDropDown.
 * used as a button inside of it.
 */
struct IdolChoice {
	ofxToggle toggle;
	string name;
	bool chosen = false;
	bool prevState = false;
	bool currState = false;
	IdolChoice() = default;
	IdolChoice(string name_, const bool chosen_ = false) : name(std::move(name_)), chosen(chosen_) {}
};

/* @brief - idolDropDown
 * idolDropDown is a structure of
 * choices that can only hold one
 * true value at a time. 
 * Acts like a folding radio!
 */
struct IdolDropDown {
	ofxGuiGroup panel;
	bool folded = true;
	template<typename T>
	using choice_vec = vector<T>;
	IdolDropDown() = default;
};


#endif //!MENUITEMS_H
