#pragma once

#ifndef BEATMAPHANDLER_H
#define BEATMAPHANDLER_H

#include "ofXml.h"

namespace fs = filesystem;

/* note_info = [section][note][data] (first = data name) (second = data) */
typedef map<int, map<int, map<int, pair<string, string>>>> note_info;
/* vale_map = [section] (data) */
typedef map<int, int> val_map;

class BeatMapHandler {
private:
	static int  getNumOfTags(ofXml &doc, const string &tag);
	static void getPaths(const fs::path &root, const string &ext, vector<fs::path> &ret);
public:
	static vector<ofXml> getXml(); // gets all xml files in beatmaps directory.
	static vector<string> getMapNames(); // gets all beatmap names available.
	static int getMapRating(ofXml &doc);
	static string getMapName(ofXml &doc);
	static note_info getNoteVals(ofXml doc);
	static ofXml getMap(const string &mapName);
	static val_map getSectionVals(ofXml &doc, const string& value);
};

#endif //!BEATMAPHANDLER_H