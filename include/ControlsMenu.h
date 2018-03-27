#pragma once

#ifndef CONTROLSMENU_H
#define CONTROLSMENU_H

#ifndef OFMAIN_H
	#define OFMAIN_H
	#include <utility>
	#include "ofMain.h"
#endif //!OFMAIN_H

#ifndef OFXGUI_H
	#define OFXGUI_H
	#include "ofxGui.h"
#endif // !OFXGUI_H

#ifndef MENUITEMS_H
	#include "MenuItems.h"
#endif //!MENUITEMS_H

#ifndef MENU_H
	#include "Menu.h"
#endif //!MENU_H

struct ControlsGroup {
	ofxGuiGroup group;
	string name;

	explicit ControlsGroup(string controlName) : name(std::move(controlName)) {};
};

class ControlsMenu : Menu {
public:
	void draw() override;
private:
	ofxPanel gui;
	/// control categories ---------------
	vector<ControlsGroup> controlsGroups {
		ControlsGroup("Xbox"),
		ControlsGroup("PlayStation"),
		ControlsGroup("Steam"),
		ControlsGroup("Keyboard")
	};
};

#endif //!CONTROLSMENU_H
