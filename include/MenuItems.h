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

/* @brief - idolChoice
 * a component of idolDropDown.
 * used as a button inside of it.
 */
struct idolChoice {
public:
	ofxToggle toggle;
	string name;
	bool chosen = false;
	bool prevState = false;
	bool currState = false;
	idolChoice() {}
	idolChoice(string name_, bool chosen_ = false) : name(name_), chosen(chosen_) {}
};

/* @brief - idolDropDown
 * idolDropDown is a structure of
 * choices that can only hold one
 * true value at a time. 
 * Acts like a folding radio!
 */
struct idolDropDown {
public:
	ofxGuiGroup panel;
	bool folded = true;
	template<typename T>
	using choice_vec = vector<T>;
	idolDropDown() {}
};

#endif //!MENUITEMS_H