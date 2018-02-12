#include "../include/OptionsMenu.h"

///////////////////////////////////////////////////////////////
    /////////////////      Constructor      ///////////////
///////////////////////////////////////////////////////////////
OptionMenu::OptionMenu() {
	currentWindowResolution = "800x600";
	currentWindowAspectRatio = ASPECT_4_3;

	gui.setup("Options");
	gui.setName("Options");
	gui.add(graphics.setup("Graphics"));

	graphics.setName("Graphics");
	graphics.setBorderColor(ofColor::cadetBlue);
	graphics.add(windowMode.panel.setup("Window Mode"));
	windowMode.panel.setName("Window Mode");
	windowMode.panel.setHeaderBackgroundColor(ofColor::orange);

	for (int k = 0; k < windowMode.choices.size(); k++) {
		windowMode.panel.add(windowMode.choices.at(k).toggle.setup(windowMode.choices.at(k).name, windowMode.choices.at(k).chosen));
	}

	/// Adding all Ratios
	for (int j = 0; j < ratioGroups.size(); j++) {
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
	for (int i = 0; i < resolutions.size(); i++) {
		if (resolutions.at(i).h <= mode->height && resolutions.at(i).w <= mode->width) {
			ratioGroups.at((int)resolutions.at(i).ratio).add(resolutions.at(i).button.setup(resolutions.at(i).getName()));
			resolutions.at(i).button.setName(resolutions.at(i).getName());
		}
	}

	graphics.minimizeAll();
	gui.minimizeAll();
}

//-------------------------------------------
void OptionMenu::draw() {
	gui.setPosition((ofGetWidth() / 2) - (gui.getWidth() / 2),(ofGetHeight() / 2) - (gui.getHeight() / 2));

	buttonCheck();

	gui.draw();
}

//-------------------------------------------
void OptionMenu::buttonCheck() {
	if (ofGetWindowMode() == OF_WINDOW) {
		for (int i = 0; i < resolutions.size(); i++) {
			if (resolutions.at(i).h <= mode->height && resolutions.at(i).w <= mode->width) {
				if (resolutions.at(i).button) {
					if (getResolution().compare(resolutions.at(i).getName()) != 0)
						setResolution(resolutions.at(i).getName());

					if (resolutions.at(i).ratio != getAspectRatio())
						setAspectRatio(resolutions.at(i).ratio);

					ofSetWindowShape(resolutions.at(i).w, resolutions.at(i).h);
				}
			}
		}
	}

	for (int j = 0; j < windowMode.choices.size(); j++) {
		windowMode.choices.at(j).prevState = windowMode.choices.at(j).currState;
		windowMode.choices.at(j).currState = windowMode.choices.at(j).toggle;

		if (windowMode.choices.at(j).prevState == false 
			&& windowMode.choices.at(j).currState == true) {
			windowMode.choices.at(j).chosen = true;
			
			if (ofGetWindowMode() != windowMode.choices.at(j).windowMode)
				ofGetWindowPtr()->setFullscreen(windowMode.choices.at(j).fullScrn());
			
			for (int k = 0; k < windowMode.choices.size(); k++) {
				if (k != j) {
					windowMode.choices.at(k).chosen = false;
					windowMode.choices.at(k).toggle = false;
				}
			}
		} else {
			windowMode.choices.at(j).toggle = windowMode.choices.at(j).chosen;
		}
	}
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
	for (int i = 0; i < resolutions.size(); i++) {
		if (resolutions.at(i).h == mode->height && resolutions.at(i).w == mode->width) {
			return resolutions.at(i).ratio;
		}
	}
	
	return ASPECT_4_3;
}

//-------------------------------------------
bool OptionMenu::confirmValidRatio(WindowAspect ratio) {
	bool result = false;

	for (int i = 0; i < resolutions.size(); i++) {
		if (resolutions.at(i).h <= mode->height 
			&& resolutions.at(i).w <= mode->width
			&& resolutions.at(i).ratio == ratio) {
			result = true;
		}
	}
	
	return result;
}