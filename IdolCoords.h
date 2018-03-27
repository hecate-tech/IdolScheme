#pragma once

#ifndef IDOLCOORDS_H
#define IDOLCOORDS_H

#ifndef OFMAIN_H
	#define OFMAIN_H
	#include "ofMain.h"
#endif //!OFMAIN_H

// ReSharper disable once CppInconsistentNaming
inline float coord_y(const float perc) {
	return perc * ofGetHeight();
}

// ReSharper disable once CppInconsistentNaming
inline float coord_x(const float perc) {
	return perc * ofGetWidth();
}

// ReSharper disable once CppInconsistentNaming
inline ofPoint coord_xy(const ofPoint percents) {
	return { percents.x * ofGetHeight(), percents.y * ofGetHeight() };
}

#endif //!IDOLCOORDS_H