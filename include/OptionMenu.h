#ifndef OPTIONMENU_H
#define OPTIONMENU_H

#include "ofMain.h"
#include "ofxGui.h"

enum WindowMode {
    WIN_FULLSCREEN,
    WIN_WINDOWED,
    WIN_BORDERLESS,
};
enum WindowAspect {
	WIN_ASPECT_16_9,
	WIN_ASPECT_16_10,
	WIN_ASPECT_4_3,
};
enum WindowSize {
    RES_640x480,
    RES_800X600,
    RES_960X720,

    RES_1280x768,
    RES_1600x900,
    RES_1920x1080,

    RES_1280x720,
    RES_1280x800,
    RES_1366x768,
    RES_1920x1200,
};

class OptionMenu {
public:
    WindowAspect winAspect;
    WindowSize  winSize;

    void draw();
    void windowResized(int w, int h);
private:
    void checkButtonPress();

    ofxLabel screenRes; // debugging label

    /// 4:3 resolutions
    ofxButton res_640x480;
    ofxButton res_800x600;
    ofxButton res_960x720;

    /// 16:9 resolutions
    ofxButton res_1280x768;
    ofxButton res_1600x900;
    ofxButton res_1920x1080;


    /// 16:10 resolutions
    ofxButton res_1280x720;
    ofxButton res_1280x800;
    ofxButton res_1366x768;
    ofxButton res_1920x1200;

    ofxPanel gui;
public:
    OptionMenu();
};

#endif //!OPTIONMENU_H