#pragma once

#ifndef BEATMAPHANDLER_H
#define BEATMAPHANDLER_H

#ifndef OFMAIN_H
	#define OFMAIN_H
	#include "ofMain.h"
#endif //OFMAIN_H

namespace fs = filesystem;
using note_info = map<int, map<int, map<int, pair<string, string>>>>;

class BeatMapHandler {
private:
	static void get_notevals(ofXml map, note_info &ret);
	static int get_tagnum(const string &tag, ofXml &map);
	static void get_all(const fs::path &root, const string &ext, vector<fs::path> &ret);
public:
	static vector<note_info> noteInformation;
	static void readBeatMaps();
};

#endif //!BEATMAPHANDLER_H