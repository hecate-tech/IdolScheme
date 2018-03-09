#pragma once

#ifndef BEATMAPHANDLER_H
#define BEATMAPHANDLER_H

#ifndef OFMAIN_H
	#define OFMAIN_H
	#include "ofMain.h"
#endif //OFMAIN_H

namespace fs = filesystem;

class BeatMapHandler {
private:
	static void get_all(const fs::path &root, const string &ext, vector<fs::path> &ret);
	static void get_notevals(const int &bmnum, ofXml map, vector<string> &ret);
public:
	static void readBeatMaps();
};

#endif //!BEATMAPHANDLER_H