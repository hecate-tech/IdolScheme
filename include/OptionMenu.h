#pragma once

//#include "IdolScheme.h"

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

#ifndef OPTIONSMENU_H
#define OPTIONSMENU_H

/* @brief - WindowAspect
 * an enumeration of the available
 * screen aspect ratios. This can be altered
 * if needed.
 */
enum WindowAspect {
	ASPECT_4_3,
	ASPECT_16_9,
	ASPECT_16_10,
	ASPECT_21_9,
};

/* @brief - resButton
 * This is a struct base for a resolution button.
 * This contains some extra properties.
 */
struct ResButton {
	ofxButton button;
	WindowAspect ratio;
	int w, h;
	string getName() const { return (ofToString(w) + "x" + ofToString(h)); }
	string getRatioName() const {
		return (ratio == ASPECT_4_3   ? "4:3"
			:	ratio == ASPECT_16_9  ? "16:9"
			:	ratio == ASPECT_16_10 ? "16:10"
			:	/*wowowowowowowowowow*/ "21:9");
	}
	ResButton(const int w_, const int h_, const WindowAspect r_) : ratio(r_), w(w_), h(h_) {}
};

struct WinChoice : IdolChoice {
	
	ofWindowMode windowMode;
	bool fullScrn() const { return windowMode == OF_WINDOW ? false : true; }

	explicit WinChoice(const string& name_, const bool chosen_ = false, const ofWindowMode mode = OF_WINDOW) {
		name = name_;
		chosen = chosen_;
		windowMode = mode;
	}
};

struct WinDropDown : IdolDropDown {
	choice_vec<WinChoice> choices;
	WinDropDown() {
		choices = {
			WinChoice("Fullscreen", ofGetWindowMode() == OF_FULLSCREEN ? true : false, OF_FULLSCREEN),
			WinChoice("Windowed", ofGetWindowMode() == OF_WINDOW ? true : false, OF_WINDOW),
			WinChoice("GameMode", ofGetWindowMode() == OF_GAME_MODE ? true : false, OF_GAME_MODE)
		};
	}
};

struct ControlsGroup {
	ofxGuiGroup group;
	string name;

	explicit ControlsGroup(const string &name_) {
		name = name_;
	};
};

/* @brief - OptionMenu
 * This is the class responsible for keeping track
 * of the options menu. Declare this as an object
 * and you can call it in another class. The
 * 'IdolScheme' class contains it already.
 */
class OptionMenu : public Menu {
public:
	void draw() override;
	void setAspectRatio(WindowAspect ratio = ASPECT_4_3);
	void setResolution(const string& resolution = "800x600");
	WindowAspect getAspectRatio() const;
	string getResolution() const;
	int getWinHeight();
	int getWinWidth();
	ofPoint getWinRes();
private:
	WindowAspect getRatioOnMonitor();
	WindowAspect currentWindowAspectRatio;

	ofxPanel gui;
	ofxGuiGroup graphics;
	ofxGuiGroup controls;
	WinDropDown windowMode;

	void buttonCheck();
	string currentWindowResolution;
	bool confirmValidRatio(WindowAspect ratio);
	const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	
	/// categories --------------------
	vector<ofxGuiGroup> ratioGroups = {
		ofxGuiGroup(), ofxGuiGroup(), ofxGuiGroup(), ofxGuiGroup()
	};
	
	/// control categories ------------
	vector<ControlsGroup> controlsGroups {
		ControlsGroup("Xbox"),
		ControlsGroup("PlayStation"),
		ControlsGroup("Steam"),
		ControlsGroup("Keyboard")
	};

	/// resolution buttons ------------
	vector<ResButton> resolutions = {
		
		/// 4:3 --------------------------
		ResButton(800,  600, ASPECT_4_3),
		ResButton(960,  720, ASPECT_4_3),
		ResButton(1024, 768, ASPECT_4_3),
		ResButton(1280, 960, ASPECT_4_3),
		
		/// 16:9 --------------------------
		ResButton(1024, 576,  ASPECT_16_9),
		ResButton(1152, 648,  ASPECT_16_9),
		ResButton(1280, 720,  ASPECT_16_9),
		ResButton(1366, 768,  ASPECT_16_9),
		ResButton(1600, 900,  ASPECT_16_9),
		ResButton(1920, 1080, ASPECT_16_9),
		ResButton(2560, 1440, ASPECT_16_9),
		ResButton(3840, 2160, ASPECT_16_9),

		/// 16:10 --------------------------
		ResButton(1280, 800,  ASPECT_16_10),
		ResButton(1440, 900,  ASPECT_16_10),
		ResButton(1680, 1050, ASPECT_16_10),
		ResButton(1920, 1200, ASPECT_16_10),
		ResButton(2560, 1600, ASPECT_16_10),

		/// 21:9 --------------------------
		ResButton(2560, 1080, ASPECT_21_9),
		ResButton(3440, 1440, ASPECT_21_9),
		ResButton(3840, 1600, ASPECT_21_9)
	};

public:
	OptionMenu();
};

#endif //!OPTIONSMENU_H
