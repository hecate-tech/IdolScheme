#pragma once

#ifndef BEATMAPREADER_H
#define BEATMAPREADER_H

#include "ofMain.h"

/* @brief - noteInfo
 * What makes up a note is quite a bit more.
 * A note holds all its arguments and in order
 * for it to be instantiated in-game.
 */
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

/* @brief - beatMap
 * What makes up a beat map is pretty small.
 * At the moment what makes it up is just a collection
 * of notes and a name for it.
 */
struct beatMap {
	string name;
	vector<noteInfo> noteParams;
};

/* @brief - BeatMapHandler
 * This class reads and contains all available
 * beatmaps located in 'bin/beatmaps' of the game
 * directory.
 */
class BeatMapHandler {
public:
	vector<beatMap> beatMaps;
private:
	const string delimiter     = "|";
	const string commentPrefix = "#";
	const string noteText      = "note";
	const string nameText      = "beatname";

	vector<string> getBeatMapDirectories(const string &path);
	beatMap setNoteParameters(string path);
public:
	BeatMapHandler();
};

#endif !BEATMAPREADER_H