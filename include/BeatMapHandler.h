#pragma once

#ifndef BEATMAPHANDLER_H
#define BEATMAPHANDLER_H

#include <boost\filesystem.hpp>
#include "ofXml.h"
#include <string>
#include <map>

using std::map;
using std::pair;
using std::string;
namespace fs = boost::filesystem;
using note_info = map<int, map<int, map<int, pair<string, string>>>>;
using bpm_map   = map<int, string>;

class BeatMapHandler {
private:
	static vector<ofXml> get_xml(vector<fs::path> paths_);
	static bpm_map get_sectionbpm(ofXml &doc);
	static void get_notevals(ofXml doc, note_info &ret);
	static int get_tagnum(const string &tag, ofXml &doc);
	static void get_all(const fs::path &root, const string &ext, vector<fs::path> &ret);
public:
	static vector<note_info> noteInformation;
	static void readBeatMaps();
};

#endif //!BEATMAPHANDLER_H