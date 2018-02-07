#ifndef OFMAIN_H
	#define OFMAIN_H
	#include "ofMain.h"
#endif //!OFMAIN_H

#ifndef IDOLSCHEME_H
	#include "../include/IdolScheme.h"
#endif //!IDOLSCHEME_H

//========================================================================
int main() {
	ofSetupOpenGL(800,600,OF_WINDOW);	// <------ setup the GL context
	ofSetWindowTitle("Idol Scheme");
	
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new IdolScheme());
}
