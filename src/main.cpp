#ifndef OFMAIN_H
	#define OFMAIN_H
	#include "ofMain.h"
#endif //!OFMAIN_H

#ifndef IDOLSCHEME_H
	#include "../include/IdolScheme.h"
#endif //!IDOLSCHEME_H

//========================================================================
int main() {	
#ifdef TARGET_WIN32
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
#elif defined(TARGET_LINUX) // linux needs to be treated differently for now.

	ofSetupOpenGL(800, 600, OF_WINDOW);
#endif
	/// other settings
	/// --------------
	ofSetVerticalSync(false);

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new IdolScheme());
}
