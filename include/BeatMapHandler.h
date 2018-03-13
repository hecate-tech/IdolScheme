#pragma once

#ifndef BEATMAPHANDLER_H
#define BEATMAPHANDLER_H

#include "ofXml.h"

namespace fs = ::filesystem;
/* note_info = [section][note][data] (first = data name) (second = data) */
using note_info = map<int, map<int, map<int, pair<string, string>>>>;
using val_map   = map<int, int>;

class BeatMapHandler {
private:
	static vector<ofXml> getXml(vector<fs::path> paths_);
	static val_map getSectionVals(ofXml &doc, string value);
	static note_info getNoteVals(ofXml doc);
	static string getMapName(ofXml &doc);
	static int getMapRating(ofXml &doc);
	static int getNumOfTags(ofXml &doc, const string &tag);
	static void get_paths(const fs::path &root, const string &ext, vector<fs::path> &ret);
public:
	static void readBeatMaps();
};

#endif //!BEATMAPHANDLER_H