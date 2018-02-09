#ifndef OPTIONMENU_H
#define OPTIONMENU_H

#include "ofMain.h"
#include "ofxGui.h"

/* @brief - WindowAspect
 * Keeps track of the current aspect ratio
 * and helps calculate resolutions by
 * keeping track of what parameters
 * to plug into a formula.
 */
enum WindowAspect {
	ASPECT_4_3,
	ASPECT_16_9,
	ASPECT_16_10,
	ASPECT_16_10_ALT,
};

/* @brief - WindowSize
 * this enum keeps track of the window size and
 * helps calculate resolutions based on the
 * numerical value of each enum constant.
 */
enum WindowSize {
    RES_640x480,
    RES_800x600,
    RES_960x720,

	RES_4_3_MAX, // number of 4:3 is (RES_43_COUNT - 1)

    RES_1280x720,
    RES_1600x900,
    RES_1920x1080,
    RES_2560x1440,
    RES_3840x2160,

	RES_16_9_MAX, // number of 16:9 is ((RES_169_COUNT - RES_43_COUNT) - 1)

    RES_1280x800,
	RES_1600x1000,
    RES_1920x1200,

	RES_16_10_MAX, // number of 16:10 is ((RES_1610_COUNT - RES_169_COUNT) - 1)

	RES_1440x900, 
	RES_1680x1050, 

	RES_16_10_ALT_MAX, // number of 16:10(alt) is ((RES_1610_ALT_COUNT - RES_1610_COUNT) - 1)
};

class OptionMenu {
public:
    WindowAspect winAspect; // stores current window aspect ratio.
    WindowSize   winSize;   // stores current window resolution.
	bool winFullScreen;

    void draw();
    void windowResized(int w, int h);
	void setWindowAspect(WindowAspect);
	void setWindowSize(WindowSize);
	WindowAspect getWindowAspect();
	WindowSize getWindowSize();
private:
	void checkButtonPress();

	bool prevMouseState = false;
	bool currMouseState = false;
	
	/// categories
	ofxGuiGroup g_resolutions;
	ofxGuiGroup g_4_3;
	ofxGuiGroup g_16_9;
	ofxGuiGroup g_16_10;
	
	/// misc ui elements
	ofxLabel l_screenRes;
	ofxToggle t_fullscreen;

    /// 4:3 resolutions
    ofxButton b_640x480;
    ofxButton b_800x600;
    ofxButton b_960x720;

    /// 16:9 resolutions
    ofxButton b_1280x720;
    ofxButton b_1600x900;
    ofxButton b_1920x1080;
	ofxButton b_2560x1440;
	ofxButton b_3840x2160;

    /// 16:10 resolutions
    ofxButton b_1280x800;
	ofxButton b_1600x1000;
	ofxButton b_1920x1200;

	/// 16:10(alt) resolutions
	ofxButton b_1440x900;
	ofxButton b_1680x1050;


    ofxPanel gui;
public:
    OptionMenu(); // Constructor
};

#endif //!OPTIONMENU_H