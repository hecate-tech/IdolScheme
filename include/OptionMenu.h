#ifndef OPTIONMENU_H
#define OPTIONMENU_H

#include "ofMain.h"
#include "ofxGui.h"

enum WindowAspect {
	WIN_ASPECT_4_3,
	WIN_ASPECT_16_9,
	WIN_ASPECT_16_10,
	WIN_ASPECT_16_10_ALT,
};
enum WindowSize {
    RES_640x480,
    RES_800x600,
    RES_960x720,

	RES_43_COUNT,

    RES_1280x720,
    // RES_1366x768,
    RES_1600x900,
    RES_1920x1080,
    RES_2560x1440,
    RES_3840x2160,

	RES_169_COUNT,

    RES_1280x800,
	RES_1600x1000,
    RES_1920x1200,

	RES_1610_COUNT,

	RES_1440x900, 
	RES_1680x1050, 

	RES_1610_ALT_COUNT,
};

class OptionMenu {
public:
    WindowAspect winAspect;
    WindowSize  winSize;

    void draw();
    void windowResized(int w, int h);
	void setWindowAspect(WindowAspect);
	void setWindowSize(WindowSize);
	WindowAspect getWindowAspect();
	WindowSize getWindowSize();
private:
	ofPoint getRes(int j);
	void checkButtonPress();

	bool prevMouseState = false;
	bool currMouseState = false;

    ofxLabel screenRes; // debugging label
	
	ofxToggle fullscreen;
	
	/// categories
	ofxGuiGroup resolutions;
	ofxGuiGroup group_4_3;
	ofxGuiGroup group_16_9;
	ofxGuiGroup group_16_10;

    /// 4:3 resolutions
    ofxButton res_640x480;
    ofxButton res_800x600;
    ofxButton res_960x720;

    /// 16:9 resolutions
    ofxButton res_1280x720;
    ofxButton res_1600x900;
    ofxButton res_1920x1080;
	ofxButton res_2560x1440;
	ofxButton res_3840x2160;

    /// 16:10 resolutions
    ofxButton res_1280x800;
	ofxButton res_1600x1000;
	ofxButton res_1920x1200;

	ofxButton res_1440x900;
	ofxButton res_1680x1050;

    ofxPanel gui;
public:
    OptionMenu();
};

#endif //!OPTIONMENU_H