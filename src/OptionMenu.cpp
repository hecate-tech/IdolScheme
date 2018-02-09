#include "../include/OptionMenu.h"
#include <vector>
#include <string>
#include <sstream>

//----------------------------------------------------------------------------------
OptionMenu::OptionMenu() {
    winAspect = WIN_ASPECT_4_3;
	winSize = RES_800x600;

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
	group_16_9.add(res_1280x720.setup("1280x720"));
	group_16_9.add(res_1600x900.setup("1600x900"));
	group_16_9.add(res_1920x1080.setup("1920x1080"));
	group_16_9.add(res_2560x1440.setup("2560x1440"));
	group_16_9.add(res_3840x2160.setup("3840x2160"));

	/// 16:10 resolutions
	group_16_10.add(res_1280x800.setup("1280x800"));
	group_16_10.add(res_1600x1000.setup("1600x1000"));
	group_16_10.add(res_1920x1200.setup("1920x1200"));

	group_16_10.add(res_1440x900.setup("1440x900"));
	group_16_10.add(res_1680x1050.setup("1680x1050"));

	/// minimizing menus
	resolutions.minimizeAll(); // minimizes contents
	resolutions.minimize(); // minimizes resolutions

	gui.setPosition(((ofGetWidth() / 2) - (gui.getWidth() / 2)), ((ofGetHeight() / 2) - (gui.getHeight() / 2)));
	
	auto getAspect = [&](int k) {
		return (k < RES_43_COUNT ? WIN_ASPECT_4_3 : k < RES_169_COUNT ? WIN_ASPECT_16_9 : k < RES_1610_COUNT ? WIN_ASPECT_16_10 : WIN_ASPECT_16_10_ALT);
	};
}

//----------------------------------------------------------------------------------
void OptionMenu::draw() {
    checkButtonPress();
	prevMouseState = currMouseState;
	currMouseState = ofGetMousePressed(OF_MOUSE_BUTTON_LEFT);
	if (gui.getPosition() != ofPoint(((ofGetWidth() / 2) - (gui.getWidth() / 2)), ((ofGetHeight() / 2) - (gui.getHeight() / 2))))
		gui.setPosition(((ofGetWidth() / 2) - (gui.getWidth() / 2)), ((ofGetHeight() / 2) - (gui.getHeight() / 2)));
    
	gui.draw();
}

//----------------------------------------------------------------------------------
void OptionMenu::checkButtonPress() {
	if (fullscreen) {
		if (ofGetWindowMode() != OF_FULLSCREEN) {
			ofToggleFullscreen();
		}
	} else if (!fullscreen) {
		if (ofGetWindowMode() != OF_WINDOW) {
			ofToggleFullscreen();
		}

		auto getAspect = [&](int k) {
			return (k < RES_43_COUNT ? WIN_ASPECT_4_3 : k < RES_169_COUNT ? WIN_ASPECT_16_9 : k < RES_1610_COUNT ? WIN_ASPECT_16_10 : WIN_ASPECT_16_10_ALT);
		};

		auto getWH = [&](int n, auto mod, auto offset = 0, auto mod2 = 1, auto offset2 = 0) {
			return (mod * (n + (offset)) + offset2) * mod2;
		};

		auto getMods = [&](int n) {
			int numOfMods = 4;
			int s_169 = (RES_169_COUNT - RES_43_COUNT) - 1;
			int s_1610 = (RES_1610_COUNT - RES_169_COUNT) - 1;
			switch (getAspect(n)) {
				case WIN_ASPECT_4_3:
					return new float[numOfMods * 2]
					{ 160.F,4.F,1.F,0.F,
						120.F,4.F,1.F,0.F };
					break;
				case WIN_ASPECT_16_9:
					return new float[numOfMods * 2]
					{ 320.F,n == 7 ? 1.F : 0.F,n == 8 ? 1.5F : 1.F,0.F,
						180.F,n == 7 ? 1.F : 0.F,n == 8 ? 1.5F : 1.F,0.F };
					break;
				case WIN_ASPECT_16_10:
					return new float[numOfMods * 2]
					{ 320.F,(-1.F*(RES_1610_COUNT - RES_169_COUNT) + (s_1610 - s_169)),1.F,0.F,
						320.F,(-1.F * (RES_1610_COUNT - RES_169_COUNT) + (s_1610 - s_169)),0.625F,0.F };
					break;
				case WIN_ASPECT_16_10_ALT:
					return new float[numOfMods * 2]
					{ 150.F,(-1.F*(RES_1610_COUNT + 1.F)),1.6F,900.F,
						150.F,(-1.F * (RES_1610_COUNT + 1.F)),1.F,900.F };
					break;
				default:
					break;
			}
		};

		for (int n = 0; n < RES_1610_ALT_COUNT; n++) {
			if (n != RES_43_COUNT && n != RES_169_COUNT && n != RES_1610_COUNT && n != RES_1610_ALT_COUNT) {
				float *a = getMods(n);
				ofPoint res;

				res.x = getWH(n, a[0], a[1], a[2], a[3]);
				res.y = getWH(n, a[4], a[5], a[6], a[7]);

				if ((getAspect(n) == WIN_ASPECT_4_3 ? group_4_3
					: getAspect(n) == WIN_ASPECT_16_9 ? group_16_9
					: group_16_10).getButton(ofToString(res.x) + "x" + ofToString(res.y))) {
					if (currMouseState == true && prevMouseState == false) {
						std::cout << ofToString(res.x) + "x" + ofToString(res.y) << std::endl;
						if (winSize != n) {
							if (winAspect != getAspect(n))
								winAspect = getAspect(n);
							std::cout << winAspect << std::endl;
							ofSetWindowShape(res.x, res.y);
							winSize = (WindowSize)n;
						}
					}

				}
			}
		}
	}
}

//----------------------------------------------------------------------------------
void OptionMenu::windowResized(int w, int h) {
	screenRes = (ofToString(w) + "x" + ofToString(h));
}

/////////////////////////////////////////////////////////////////
   /////////////////      Getters/Setters      ///////////////
/////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------------
WindowAspect OptionMenu::getWindowAspect() {
	return winAspect;
}

//----------------------------------------------------------------------------------
WindowSize OptionMenu::getWindowSize() {
	return winSize;
}

//----------------------------------------------------------------------------------
void OptionMenu::setWindowAspect(WindowAspect newAspect) {
	winAspect = newAspect;
}

//----------------------------------------------------------------------------------
void OptionMenu::setWindowSize(WindowSize newSize) {
	winSize = newSize;
}