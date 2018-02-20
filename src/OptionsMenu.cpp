#include "../include/OptionsMenu.h"

///////////////////////////////////////////////////////////////
    /////////////////      Constructor      ///////////////
///////////////////////////////////////////////////////////////
OptionMenu::OptionMenu() {
	currentWindowResolution = "800x600";   // default resolution.
	currentWindowAspectRatio = ASPECT_4_3; // default aspect ratio.

	gui.setup("Options"); // "Options" is the ID given to the gui.
	gui.setName("Options"); // setName() is used to create the label.
	gui.add(graphics.setup("Graphics"));
	gui.add(controls.setup("Options"));

	/// Setting up the Controls category.
	controls.setName("Controls");
	controls.setBorderColor(ofColor::cadetBlue);

	/// Setting up the Graphics category.
	graphics.setName("Graphics");
	graphics.setBorderColor(ofColor::cadetBlue);

	/// Adding and setting up the dropdown menu.
	graphics.add(windowMode.panel.setup("Window Mode"));
	windowMode.panel.setName("Window Mode");
	windowMode.panel.setHeaderBackgroundColor(ofColor::orange);

	/// Adding the dropdown menu contents
	for (unsigned int k = 0; k < windowMode.choices.size(); k++) {
		windowMode.panel.add(windowMode.choices.at(k).toggle.setup(windowMode.choices.at(k).name, windowMode.choices.at(k).chosen));
	}

	/// Adding all Ratios
	for (unsigned int j = 0; j < ratioGroups.size(); j++) {
		if (confirmValidRatio((WindowAspect)j))
			graphics.add(ratioGroups.at(j).setup(ofToString(j)));
		
		/// Settings Names/Labels
		ratioGroups.at(j).setName(
			 j == ASPECT_4_3   ? "4:3"
			:j == ASPECT_16_9  ? "16:9"
			:j == ASPECT_16_10 ? "16:10"
			:j == ASPECT_21_9  ? "21:9"
			:					 "ERROR"
		);

		/// Setting Colors
		ratioGroups.at(j).setHeaderBackgroundColor(
			 j == ASPECT_4_3   ? ofColor(249.F, 59.F, 69.F)
			:j == ASPECT_16_9  ? ofColor(45.F, 125.F, 210.F)
			:j == ASPECT_16_10 ? ofColor(104.F, 178.F, 0.F)
			:j == ASPECT_21_9  ? ofColor::goldenRod
			:					 ofColor::white
		);
	}
	
	/// Adding all resolutions
	for (unsigned int i = 0; i < resolutions.size(); i++) {
		// if the button res is equal or smaller than the monitor res.
		if (resolutions.at(i).h <= mode->height && resolutions.at(i).w <= mode->width) {
			ratioGroups.at((int)resolutions.at(i).ratio).add(resolutions.at(i).button.setup(resolutions.at(i).getName()));
			resolutions.at(i).button.setName(resolutions.at(i).getName());
		}
	}
	cout << endl; // this is just to separate the warnings
	graphics.minimizeAll();
	gui.minimizeAll();
}

//-------------------------------------------
void OptionMenu::draw() {
	gui.setPosition((0.5 * ofGetWidth()) - (gui.getWidth() / 2),(0.5 * ofGetHeight()) - (gui.getHeight() / 2));

	buttonCheck(); // checks all button presses.

	gui.draw(); // draws all the menus.
}

//-------------------------------------------
void OptionMenu::buttonCheck() {
	if (ofGetWindowMode() == OF_WINDOW) { // only check when windowed.
		for (unsigned int i = 0; i < resolutions.size(); i++) {
			// if the resolution button is equal or smaller than monitor resolution.
			if (resolutions.at(i).h <= mode->height && resolutions.at(i).w <= mode->width) {
				if (resolutions.at(i).button) { // if the button is pressed
					// if the current res isn't equal to the button's res.
					if (getResolution().compare(resolutions.at(i).getName()) != 0)
						setResolution(resolutions.at(i).getName());

					// if the current ratio isn't equal to the button's ratio.
					if (resolutions.at(i).ratio != getAspectRatio())
						setAspectRatio(resolutions.at(i).ratio);

					// sets the resolution of the window to the button you pressed.
					ofSetWindowShape(resolutions.at(i).w, resolutions.at(i).h);
				}
			}
		}
	}

	for (unsigned int j = 0; j < windowMode.choices.size(); j++) {
		windowMode.choices.at(j).prevState = windowMode.choices.at(j).currState;
		windowMode.choices.at(j).currState = windowMode.choices.at(j).toggle;

		/// On MouseDown
		if (windowMode.choices.at(j).prevState == false 
			&& windowMode.choices.at(j).currState == true) {
			windowMode.choices.at(j).chosen = true;
			
			/// If the window modes are not equal to the toggle you pressed.
			if (ofGetWindowMode() != windowMode.choices.at(j).windowMode)
				switch(windowMode.choices.at(j).windowMode) {
					case OF_WINDOW:
						ofGetWindowPtr()->setFullscreen(false);
						break;
					case OF_FULLSCREEN:
						ofGetWindowPtr()->setFullscreen(true);
						break;
					case OF_GAME_MODE:
						//ofExit();
						//ofSetAppPtr(new IdolScheme());
						//::resetGameMode(OF_GAME_MODE);
						//ofExit();
						//ofSetupOpenGL(mode->width, mode->height, OF_GAME_MODE);
						//ofGetWindowPtr()->setWindowShouldClose();
						//ofGetWindowPtr()->close();
						//ofWindowSettings settings;
						//settings.height = 1080;
						//settings.width = 1920;
						//settings.windowMode = OF_GAME_MODE;
						//std::cout << "DEBUG GAME_MODE MODE" << std::endl;
						
						//ofCreateWindow(settings);
						//*ofGetWindowPtr() = *ofCreateWindow(settings);
						//ofSetupOpenGL(1920, 1080, OF_WINDOW);
						//ofGetWindowPtr()->setup(settings);
						//ofSetupOpenGL(500, 200, OF_WINDOW);
						//ofSetupOpenGL(1920,  1080, OF_GAME_MODE);
						//ofGetWindowPtr()->setup(settings);
						break;
					default:
						break;
				}
				//ofGetWindowPtr()->setFullscreen(windowMode.choices.at(j).fullScrn());
			
			for (unsigned int k = 0; k < windowMode.choices.size(); k++) {
				/// deselecting the rest of the toggles in the dropdown menu.
				if (k != j) {
					windowMode.choices.at(k).chosen = false;
					windowMode.choices.at(k).toggle = false;
				}
			}
		} else {
			/// Makes sure you don't deselect the toggle you pressed.
			windowMode.choices.at(j).toggle = windowMode.choices.at(j).chosen;
		}
	}
}

//-------------------------------------------
bool OptionMenu::confirmValidRatio(WindowAspect ratio) {
	bool result = false;

	for (unsigned int i = 0; i < resolutions.size(); i++) {
		if    (resolutions.at(i).h     <= mode->height 
			&& resolutions.at(i).w     <= mode->width
			&& resolutions.at(i).ratio == ratio) {
			result = true;
		}
	}
	
	return result;
}

/////////////////////////////////////////////////////////////////
   /////////////////      Getters/Setters      ///////////////
/////////////////////////////////////////////////////////////////

WindowAspect OptionMenu::getAspectRatio() {
	return currentWindowAspectRatio;
}

//-------------------------------------------
string OptionMenu::getResolution() {
	return currentWindowResolution;
}

//-------------------------------------------
void OptionMenu::setAspectRatio(WindowAspect ratio) {
	currentWindowAspectRatio = ratio;
}

//-------------------------------------------
void OptionMenu::setResolution(string resolution) {
	currentWindowResolution = resolution;
}

//-------------------------------------------
WindowAspect OptionMenu::getRatioOnMonitor() {
	for (unsigned int i = 0; i < resolutions.size(); i++) {
		if (resolutions.at(i).h == mode->height && resolutions.at(i).w == mode->width) {
			return resolutions.at(i).ratio;
		}
	}
	
	return ASPECT_4_3;
}

//-------------------------------------------
int OptionMenu::getWinWidth() {
	return getWinRes().x;
}

//-------------------------------------------
int OptionMenu::getWinHeight() {
	return getWinRes().y;
}

//-------------------------------------------
ofPoint OptionMenu::getWinRes() {
	for(unsigned int i = 0; i < resolutions.size(); i++) {
		if(resolutions.at(i).getName().compare(getResolution()) == 0) {
			return ofPoint(resolutions.at(i).w, resolutions.at(i).h);
		}
	}
	return ofPoint(1,1);
}
