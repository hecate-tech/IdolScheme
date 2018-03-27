#pragma once

#ifndef SHADOW_H
#define SHADOW_H

#ifndef OFMAIN_H
	#define OFMAIN_H
	#include "ofMain.h"
#endif //!OFMAIN_H

/* @brief - Shadow
* The Shadow class is the second
* half of the note object and is
* essential that it does not move.
* (Amazing brief)
*/
class Shadow {
public:
	Shadow() = default;
	~Shadow() = default;

	string shadowDir = ofToDataPath("images/shadow.png");
	ofImage shadowSprite;

	void resize(int width, int height);
	void load();
	void draw(float x, float y) const;
};

#endif //!SHADOW_H