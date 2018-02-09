#include "../include/OptionMenu.h"
#include <vector>
#include <string>
#include <sstream>

//----------------------------------------------------------------------------------
OptionMenu::OptionMenu() {
    winAspect = ASPECT_4_3;
	winSize = RES_800x600;

    gui.setup("options menu");

	gui.add(l_screenRes.setup("resolution", (ofToString(ofGetWindowWidth()) + "x" + ofToString(ofGetWindowHeight()))));

	/// constructing the main categories
	gui.add(g_resolutions.setup("resolutions menu"));

	/// resolutions global items
	g_resolutions.add(t_fullscreen.setup("Fullscreen", false));

	/// adding categories to resolution
	g_resolutions.add(g_4_3.setup("4:3"));
	g_resolutions.add(g_16_9.setup("16:9")); // problem
	g_resolutions.add(g_16_10.setup("16:10")); // problem

	/// adding labels to categories
	g_4_3.setName("4:3");
	g_16_9.setName("16:9");
	g_16_10.setName("16:10");
	g_resolutions.setName("Graphics");
	
	/// setting colors
	g_resolutions.setBorderColor(ofColor::blueSteel);
	g_4_3.setHeaderBackgroundColor(ofColor::darkSlateBlue);
	g_16_9.setHeaderBackgroundColor(ofColor::darkGoldenRod);
	g_16_10.setHeaderBackgroundColor(ofColor::darkGreen);

	/// 4:3 resolutions
	g_4_3.add(b_640x480.setup("640x480"));
	g_4_3.add(b_800x600.setup("800x600"));
	g_4_3.add(b_960x720.setup("960x720"));

	/// 16:9 resolutions
	g_16_9.add(b_1280x720.setup("1280x720"));
	g_16_9.add(b_1600x900.setup("1600x900"));
	g_16_9.add(b_1920x1080.setup("1920x1080"));
	g_16_9.add(b_2560x1440.setup("2560x1440"));
	g_16_9.add(b_3840x2160.setup("3840x2160"));

	/// 16:10 resolutions
	g_16_10.add(b_1280x800.setup("1280x800"));
	g_16_10.add(b_1600x1000.setup("1600x1000"));
	g_16_10.add(b_1920x1200.setup("1920x1200"));

	g_16_10.add(b_1440x900.setup("1440x900"));
	g_16_10.add(b_1680x1050.setup("1680x1050"));

	/// minimizing menus
	g_resolutions.minimizeAll(); // minimizes contents
	g_resolutions.minimize(); // minimizes resolutions


	gui.setPosition(((ofGetWidth() / 2) - (gui.getWidth() / 2)), ((ofGetHeight() / 2) - (gui.getHeight() / 2)));
}

//----------------------------------------------------------------------------------
void OptionMenu::draw() {
	checkButtonPress(); // checks if any buttons were pushed.
	
	/// updates the mouse states.
	prevMouseState = currMouseState;
	currMouseState = ofGetMousePressed(OF_MOUSE_BUTTON_LEFT);
	
	/// centers the menu.
	if (gui.getPosition() != ofPoint(((ofGetWidth() / 2) - (gui.getWidth() / 2)), ((ofGetHeight() / 2) - (gui.getHeight() / 2))))
		gui.setPosition(((ofGetWidth() / 2) - (gui.getWidth() / 2)), ((ofGetHeight() / 2) - (gui.getHeight() / 2)));
    
	gui.draw();
}

//----------------------------------------------------------------------------------
void OptionMenu::checkButtonPress() {
	// fullscreen is actually borderless windowed, 
	// but I don't know how to set the window mode manually.
	if (t_fullscreen) { 
		if (ofGetWindowMode() != OF_FULLSCREEN) {
			ofToggleFullscreen();
		}
	} else if (!t_fullscreen) {
		if (ofGetWindowMode() != OF_WINDOW) {
			ofToggleFullscreen();
		}


		/* @brief - getAspect
		 * based on the 'WindowSize' this lambda function returns
		 * which 'WindowAspect' the size belongs to.
		 */
		auto getAspect = [&](int k) {
			return (k < RES_4_3_MAX ? ASPECT_4_3 : k < RES_16_9_MAX ? ASPECT_16_9 : k < RES_16_10_MAX ? ASPECT_16_10 : ASPECT_16_10_ALT);
		};


		/* @brief - getWH
		 * this is the formula used to calculate the resolutions.
		 * It's hard to explain exactly how I came up with this, because
		 * all I did was a bunch of trial and error until something worked.
		 */
		auto getWH = [&](int step, auto mod1, auto offset1 = 0, auto mod2 = 1, auto offset2 = 0) {
			return (mod1 * (step + (offset1)) + offset2) * mod2;
		};


		/* @brief - getParameters
		 * this is a tool to create the parameters needed for 'getWH'
		 * It takes the iterator and finds the aspect ratio that belongs
		 * to it. Then once the aspect ratio is found then it returns the 
		 * parameters needed to calculate the screen resolution.
		 */
		auto getParameters = [&](int n) {
			int numOfParams = 4; // the number of parameters for 'getWH'

			int size_169 = (RES_16_9_MAX - RES_4_3_MAX) - 1; // the available resolutions that are 16:9
			int size_1610 = (RES_16_10_MAX - RES_16_9_MAX) - 1; // the available resolutions that are 16:10
			// available resolutions of 4:3 are just (RES_43_COUNT - 1)

			switch (getAspect(n)) {
				case ASPECT_4_3:
					// I an array twice the size of the needed parameters to store them for the x and y 
					// individually. Using a two dimensional array is a lot of extra work and memory space.
					// I'd rather use a large float pointer instead.
					return new float[numOfParams * 2] 
					{ 160.F,4.F,1.F,0.F,	 // x - parameters
						120.F,4.F,1.F,0.F }; // y - parameters
					break;
				case ASPECT_16_9:
					// the 16:9 aspect ratio has two exceptions with the iterator.
					// When it reaches 7 and 8 I change the returned parameters to achieve the
					// desired resolution. Still making exceptions for 683:384 aspect ratio resolutions.
					return new float[numOfParams * 2]
					{ 320.F, n == 7 ? 1.F : 0.F, n == 8 ? 1.5F : 1.F, 0.F,	   // x - parameters
						180.F, n == 7 ? 1.F : 0.F, n == 8 ? 1.5F : 1.F, 0.F }; // y - parameters
					break;
				case ASPECT_16_10:
					// 16:10 resolutions were split into two, because the parameters were so different for
					// calculating from 1280x800 to 1440x900. Other than that the 16:10 resolutions are easy to
					// calculate, because the width is always 1.6 times the height. The ratio is based on the golden ratio.
					return new float[numOfParams * 2]
					{ 320.F,(-1.F*(RES_16_10_MAX - RES_16_9_MAX) + (size_1610 - size_169)),1.F,0.F,		     // x - parameters
						320.F,(-1.F * (RES_16_10_MAX - RES_16_9_MAX) + (size_1610 - size_169)),0.625F,0.F }; // y - parameters
					break;
				case ASPECT_16_10_ALT:
					// This is for the alternate resolutions of 16:10 such as 1440x900 and 1680x1050, because
					// they're so different from the other resolutions. They don't follow any sensical
					// pattern except that the 1.6 ratio is retained.
					return new float[numOfParams * 2]
					{ 150.F,(-1.F*(RES_16_10_MAX + 1.F)),1.6F,900.F,	   // x - paramater
						150.F,(-1.F * (RES_16_10_MAX + 1.F)),1.F,900.F };  // y - parameter
					break;
				default: break; // not sure what I should put for a default.
			}
		};


		for (int n = 0; n < RES_16_10_ALT_MAX; n++) { // goes through all resolutions in the 'WindowSize' enum.
			if (n != RES_4_3_MAX && n != RES_16_9_MAX && n != RES_16_10_MAX && n != RES_16_10_ALT_MAX) { // excludes seperator enum values.
				float *a = getParameters(n); // retrieves all paramaters needed for the resolution.
				ofPoint res; // what will store the resolution.

				res.x = getWH(n, a[0], a[1], a[2], a[3]); // gets the width.
				res.y = getWH(n, a[4], a[5], a[6], a[7]); // gets the height.

				if ((getAspect(n) == ASPECT_4_3 ? g_4_3
					: getAspect(n) == ASPECT_16_9 ? g_16_9
					: g_16_10).getButton(ofToString(res.x) + "x" + ofToString(res.y))) { // checks if the button is pressed
					if (currMouseState == true && prevMouseState == false) { // on mousedown (by using mouse activity stamps)
						if (winSize != n) { // if the 'WindowSize' is currently not equal to the iterator.
							if (winAspect != getAspect(n)) // if the 'WindowAspect' is not equal to the iterator.
								winAspect = getAspect(n);
							ofSetWindowShape(res.x, res.y); // sets the resolution.
							winSize = (WindowSize)n; // sets the 'WindowSize'
						}
					}
				}
			}
		}

	}


}

//----------------------------------------------------------------------------------
void OptionMenu::windowResized(int w, int h) {
	l_screenRes = (ofToString(w) + "x" + ofToString(h));
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