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

	/// 16:10 resolutions
	group_16_10.add(res_1280x768.setup("1280x768"));
	group_16_10.add(res_1280x800.setup("1280x800"));
	group_16_10.add(res_1366x768.setup("1366x768"));
	group_16_10.add(res_1920x1200.setup("1920x1200"));

	/// minimizing menus
	resolutions.minimizeAll(); // minimizes contents
	resolutions.minimize(); // minimizes resolutions

	gui.setPosition(((ofGetWidth() / 2) - (gui.getWidth() / 2)), ((ofGetHeight() / 2) - (gui.getHeight() / 2)));
	
	auto getAsp = [&](int k) {
		return (k < RES_43_COUNT ? WIN_ASPECT_4_3 : k < RES_169_COUNT ? WIN_ASPECT_16_9 : WIN_ASPECT_16_10);
	};

	auto testResGet = [&](int l, int mod) {
		int ad = (l + 4) * mod;
		return ad;
	};
	//std::cout << ofToString((1 + 4) * 160) + "x" + ofToString((1 + 4) * 120) << std::endl;
	for(int m = 0; m < RES_1610_COUNT; m++) {
		if(m != RES_43_COUNT && m != RES_169_COUNT && m != RES_1610_COUNT) {
			int res_169_size = (RES_169_COUNT - RES_43_COUNT) - 1;
			int res_1610_size = (RES_1610_COUNT - RES_169_COUNT) - 1;
			switch(getAsp(m)) {
				case WIN_ASPECT_4_3:
					std::cout << "4:3 " + ofToString(m) << std::endl;
					std::cout << ofToString((m + 4) * 160) + "x" + ofToString((m + 4) * 120) << std::endl;
					break;
				case WIN_ASPECT_16_9:
					if(m < 7) {
						std::cout << "16:9 " + ofToString(m) << std::endl;
					std::cout << ofToString((m) * 320) + "x" + ofToString((m) * 180) << std::endl;
					} else if(m == 7) {
						std::cout << "16:9 " + ofToString(m) << std::endl;
						std::cout << ofToString((m + 1) * 320) + "x" + ofToString((m + 1) * 180) << std::endl;
					} else if(m == 8) {
						std::cout << "16:9 " + ofToString(m) << std::endl;
						std::cout << ofToString(((m) * 320) * 1.5) + "x" + ofToString(((m) * 180) * 1.5) << std::endl;
					}
					break;
				case WIN_ASPECT_16_10:
					if(m != 9) { 
						std::cout << "16:10 " + ofToString(m) << std::endl; // arbitrary number
						std::cout << ofToString((m - (RES_1610_COUNT - RES_169_COUNT) + (res_1610_size - res_169_size)) * 320) + "x" + ofToString(((m - (RES_1610_COUNT - RES_169_COUNT) + (res_1610_size - res_169_size)) * 320) / 1.6) << std::endl;
					}
					
					if(m < 10) {
						 std::cout << "16:10 " + ofToString(m) << std::endl;
						 std::cout << ofToString((150 * (m - (RES_1610_COUNT - RES_169_COUNT) - (res_1610_size - res_169_size)) + 900) * 1.6) + "x" + ofToString((150 * (m - (RES_1610_COUNT - RES_169_COUNT) - (res_1610_size - res_169_size)) + 900)) << std::endl;
					}
					break;
				default:
					break;
			}
		}
		
	}
}

//----------------------------------------------------------------------------------
void OptionMenu::draw() {
    checkButtonPress();

	if (gui.getPosition() != ofPoint(((ofGetWidth() / 2) - (gui.getWidth() / 2)), ((ofGetHeight() / 2) - (gui.getHeight() / 2))))
		gui.setPosition(((ofGetWidth() / 2) - (gui.getWidth() / 2)), ((ofGetHeight() / 2) - (gui.getHeight() / 2)));
    
	gui.draw();
}

//----------------------------------------------------------------------------------
void OptionMenu::checkButtonPress() {

	auto getAspect = [&](int k) {
		return (k < RES_43_COUNT ? WIN_ASPECT_4_3 : k < RES_169_COUNT ? WIN_ASPECT_16_9 : WIN_ASPECT_16_10);
	};

	auto getResNew = [&](std::string a) {
		std::vector<int> vect;
		std::stringstream ss(a);
		std::string result;
		unsigned int i;
		while(ss >> i) {
			vect.push_back(i);
			if(ss.peek() == 'x')
				ss.ignore();
		}
		return vect;
	};

	
/*
	for(int i = 0; i < RES_1610_COUNT; i++) {
		if(i != RES_43_COUNT &&  i != RES_169_COUNT && i != RES_1610_COUNT) {
			switch(getAspect(i)) {
				case WIN_ASPECT_4_3: // mod = 160
					testResGet(i, 160);
					break;
				case WIN_ASPECT_16_9: // mod = 320, mody = 9 * 120 = 1080
					break;
				case WIN_ASPECT_16_10: // mod = 320, mody = 240
					break;
				default:
					break;
			}
		}
	}*/

	// I really don't know how to format this right. It looks bad no matter what.
	for (int i = 0; i < RES_1610_COUNT; i++) {
		if (i != RES_43_COUNT && i != RES_169_COUNT && i != RES_1610_COUNT) {
			if ( (getAspect(i) == WIN_ASPECT_4_3  ? group_4_3 
				: getAspect(i) == WIN_ASPECT_16_9 ? group_16_9 
				: group_16_10)
					.getButton(ofToString(getRes(i).x) + "x" + ofToString(getRes(i).y))) {
				
				if (winSize != i) {
					if (winAspect != getAspect(i))
						winAspect = getAspect(i);
					ofSetWindowShape(getRes(i).x, getRes(i).y);
					winSize = (WindowSize)i;
				}
			}
		}
	}

	if (fullscreen) {
		if (ofGetWindowMode() != OF_FULLSCREEN) {
			ofToggleFullscreen();
		}
	} else if (!fullscreen) {
		if (ofGetWindowMode() != OF_WINDOW) {
			ofToggleFullscreen();
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

ofPoint OptionMenu::getRes(int j) {
	
	switch (j) {
		case RES_640x480:
			return ofPoint(640,480);
			break;
		case RES_800x600:
			return ofPoint(800,600);
			break;
		case RES_960x720:
			return ofPoint(960,720);
			break;
		//case RES_1280x768:
		//	return ofPoint(1280,768);
		//	break;
		case RES_1600x900:
			return ofPoint(1600,900);
			break;
		case RES_1920x1080:
			return ofPoint(1920,1080);
			break;
		case RES_1280x720:
			return ofPoint(1280,720);
			break;
		case RES_1280x800:
			return ofPoint(1280,800);
			break;
		//case RES_1366x768:
		//	return ofPoint(1366,768);
		//	break;
		case RES_1920x1200:
			return ofPoint(1920,1200);
			break;
		default:
			return ofPoint(0,0,0);
			break;
	}
}

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