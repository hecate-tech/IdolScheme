#pragma once

#ifndef BEATMAPREADER_H
#define BEATMAPREADER_H

#include "ofMain.h"

struct noteInfo {
	int lineNum;
	int bpm;
	int offset;
	double length;
	vector<string> args;
	void convert() {
		bpm    = ofToInt(args.at(1));
		offset = ofToInt(args.at(2));
		length = ofToDouble(args.at(3));
	}
	noteInfo(int lineNumber) { lineNum = lineNumber; }
};

struct beatMap {
	string name;
	vector<noteInfo> noteParams;
};

class BeatMapReader {
public:
	vector<beatMap> activeNoteParameters;
private:
	vector<beatMap> beatMaps;
	const string delimiter = "|";
	const string commentPrefix = "#";
	const string noteText = "note";
	const string nameText = "beatname";

	vector<string> getBeatMapDirectories(const string &path);
	beatMap setNoteParameters(string path);
public:
	BeatMapReader();
};

#endif !BEATMAPREADER_H