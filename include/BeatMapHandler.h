#pragma once

#ifndef BEATMAPHANDLER_H
#define BEATMAPHANDLER_H

#include "ofXml.h"

namespace fs = ::filesystem;
using note_info = map<int, map<int, map<int, pair<string, string>>>>;
using bpm_map   = map<int, string>;

class BeatMapHandler {
private:
	static vector<ofXml> get_xml(vector<fs::path> paths_);
	static int get_tagnum(const string &tag, ofXml &doc);
	static void get_all(const fs::path &root, const string &ext, vector<fs::path> &ret);
public:
	static bpm_map get_sectionbpm(ofXml &doc);
	static note_info get_notevals(ofXml doc);
	static void readBeatMaps();
};

#endif //!BEATMAPHANDLER_H