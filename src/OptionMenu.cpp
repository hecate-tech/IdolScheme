#include "../include/OptionMenu.h"

//----------------------------------------------------------------------------------
OptionMenu::OptionMenu() {
    winAspect = WIN_ASPECT_4_3;

    gui.setup("options menu");

	gui.add(screenRes.setup("resolution", (ofToString(ofGetWindowWidth()) + "x" + ofToString(ofGetWindowHeight()))));

	/// constructing the main categories
	gui.add(resolutions.setup("resolutions menu"));

	/// resolutions global items
	resolutions.add(fullscreen.setup("Fullscreen", false));

	/// adding categories to resolution
	resolutions.add(group_4_3.setup("4:3"));
	resolutions.add(group_16_9.setup("16:9")); // problem
	resolutions.add(group_16_10.setup("16:10")); // problem

	/// adding labels to categories
	group_4_3.setName("4:3");
	group_16_9.setName("16:9");
	group_16_10.setName("16:10");
	resolutions.setName("Graphics");
	
	/// setting colors
	resolutions.setBorderColor(ofColor::blueSteel);
	group_4_3.setHeaderBackgroundColor(ofColor::darkSlateBlue);
	group_16_9.setHeaderBackgroundColor(ofColor::darkGoldenRod);
	group_16_10.setHeaderBackgroundColor(ofColor::darkGreen);

	/// 4:3 resolutions
	group_4_3.add(res_640x480.setup("640x480"));
	group_4_3.add(res_800x600.setup("800x600"));
	group_4_3.add(res_960x720.setup("960x720"));

	/// 16:9 resolutions
	group_16_9.add(res_1280x768.setup("1280x768"));
	group_16_9.add(res_1600x900.setup("1600x900"));
	group_16_9.add(res_1920x1080.setup("1920x1080"));

	/// 16:10 resolutions
	group_16_10.add(res_1280x720.setup("1280x720"));
	group_16_10.add(res_1280x800.setup("1280x800"));
	group_16_10.add(res_1366x768.setup("1366x768"));
	group_16_10.add(res_1920x1200.setup("1920x1200"));

	/// minimizing menus
	resolutions.minimizeAll(); // minimizes contents
	resolutions.minimize(); // minimizes resolutions

	gui.setPosition(((ofGetWidth() / 2) - (gui.getWidth() / 2)), ((ofGetHeight() / 2) - (gui.getHeight() / 2)));
}

//----------------------------------------------------------------------------------
void OptionMenu::draw() {
    checkButtonPress();

	if (gui.getPosition() != ofPoint(((ofGetWidth() / 2) - (gui.getWidth() / 2)), ((ofGetHeight() / 2) - (gui.getHeight() / 2))))
		gui.setPosition(((ofGetWidth() / 2) - (gui.getWidth() / 2)), ((ofGetHeight() / 2) - (gui.getHeight() / 2)));
    
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

	/// global resolutions buttons
	if (fullscreen) {
		if (ofGetWindowMode() != OF_FULLSCREEN) {
			ofToggleFullscreen();
		}
	}
	else if (!fullscreen) {
		if (ofGetWindowMode() != OF_WINDOW) {
			ofToggleFullscreen();
		}
	}
}