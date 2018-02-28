#pragma once

#ifndef CONTROLSMENU_H
#define CONTROLSMENU_H

#ifndef OFMAIN_H
	#define OFMAIN_H
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

struct controlsGroup {
	ofxGuiGroup group;
	string name;
	controlsGroup(string name_) {
		name = name_;
	};
};

class ControlsMenu : Menu {
public:
	void draw() override;
private:
	ofxPanel gui;
	/// control categories ---------------
	vector<controlsGroup> controlsGroups {
		controlsGroup("Xbox"),
		controlsGroup("PlayStation"),
		controlsGroup("Steam"),
		controlsGroup("Keyboard")
	};
};

#endif //!CONTROLSMENU_H