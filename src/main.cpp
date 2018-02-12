#ifndef OFMAIN_H
	#define OFMAIN_H
	#include "ofMain.h"
#endif //!OFMAIN_H

#ifndef IDOLSCHEME_H
	#include "../include/IdolScheme.h"
#endif //!IDOLSCHEME_H

//========================================================================
int main() {	
	ofGLFWWindowSettings settings;
	
	/// settings
	/// --------
	settings.width = 800;
	settings.height = 600;
	settings.title = "Idol Scheme";
	settings.resizable = false;

	/// creating the window
	/// -------------------
	ofCreateWindow(settings);

	/// other settings
	/// --------------
	ofSetVerticalSync(false);

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	return ofRunApp(new IdolScheme());
}
