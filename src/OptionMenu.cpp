#include "../include/OptionMenu.h"

//----------------------------------------------------------------------------------
OptionMenu::OptionMenu() {
    winAspect = WIN_ASPECT_4_3;

    gui.setup();
    gui.add(screenRes.setup("resolution", (ofToString(ofGetWindowWidth()) + "x" + ofToString(ofGetWindowHeight()))));
    /// 4:3 resolutions
    gui.add(res_640x480.setup("640x480"));
    gui.add(res_800x600.setup("800x600"));
    gui.add(res_960x720.setup("960x720"));
    /// 16:9 resolutions
    gui.add(res_1280x768.setup("1280x768"));
    gui.add(res_1600x900.setup("1600x900"));
    gui.add(res_1920x1080.setup("1920x1080"));
    /// 16:10 resolutions
    gui.add(res_1280x720.setup("1280x720"));
    gui.add(res_1280x800.setup("1280x800"));
    gui.add(res_1366x768.setup("1366x768"));
    gui.add(res_1920x1200.setup("1920x1200"));
}

//----------------------------------------------------------------------------------
void OptionMenu::draw() {
    
    checkButtonPress();

    gui.draw();
}

//----------------------------------------------------------------------------------
void OptionMenu::windowResized(int w, int h) {
    screenRes = (ofToString(w) + "x" + ofToString(h));
}

//----------------------------------------------------------------------------------
void OptionMenu::checkButtonPress() {
    /// 4:3 resolutions
    if(res_640x480) {
        if(winSize != RES_640x480) {
            if(winAspect != WIN_ASPECT_4_3) {
                winAspect = WIN_ASPECT_4_3;
            }
            ofSetWindowShape(640, 480);
            winSize = RES_640x480;
        }
    }
    if(res_800x600) {
        if(winSize != RES_800X600) {
            if(winAspect != WIN_ASPECT_4_3) {
                winAspect = WIN_ASPECT_4_3;
            }
            ofSetWindowShape(800, 600);
            winSize = RES_800X600;
        }
    }
    if(res_960x720) {
        if(winSize != RES_960X720) {
            if(winAspect != WIN_ASPECT_4_3) {
                winAspect = WIN_ASPECT_4_3;
            }
            ofSetWindowShape(960, 720);
            winSize = RES_960X720;
        }
    }

    /// 16:9 resolutions
    if(res_1280x768) {
        if(winSize != RES_1280x768) {
            if(winAspect != WIN_ASPECT_16_9) {
                winAspect = WIN_ASPECT_16_9;
            }
            ofSetWindowShape(1280, 768);
            winSize = RES_1280x768;
        }
    }
    if(res_1600x900) {
        if(winSize != RES_1600x900) {
            if(winAspect != WIN_ASPECT_16_9) {
                winAspect = WIN_ASPECT_16_9;
            }
            ofSetWindowShape(1600, 900);
            winSize = RES_1600x900;
        }
    }
    if(res_1920x1080) {
        if(winSize != RES_1920x1080) {
            if(winAspect != WIN_ASPECT_16_9) {
                winAspect = WIN_ASPECT_16_9;
            }
            ofSetWindowShape(1920, 1080);
            winSize = RES_1920x1080;
        }
    }

    /// 16:10 resolutions
    if(res_1280x720) {
        if(winSize != RES_1280x720) {
            if(winAspect != WIN_ASPECT_16_10) {
                winAspect = WIN_ASPECT_16_10;
            }
            ofSetWindowShape(1280, 720);
            winSize = RES_1280x720;
        }
    }
    if(res_1280x800) {
        if(winSize != RES_1280x800) {
            if(winAspect != WIN_ASPECT_16_10) {
                winAspect = WIN_ASPECT_16_10;
            }
            ofSetWindowShape(1280, 800);
            winSize = RES_1280x800;
        }
    }
    if(res_1366x768) {
        if(winSize != RES_1366x768) {
            if(winAspect != WIN_ASPECT_16_10) {
                winAspect = WIN_ASPECT_16_10;
            }
            ofSetWindowShape(1366, 768);
            winSize = RES_1366x768;
        }
    }
    if(res_1920x1200) {
        if(winSize != RES_1920x1200) {
            if(winAspect != WIN_ASPECT_16_10) {
                winAspect = WIN_ASPECT_16_10;
            }
            ofSetWindowShape(1920, 1200);
            winSize = RES_1920x1200;
        }
    }
}