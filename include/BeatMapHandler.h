#pragma once

#ifndef BEATMAPHANDLER_H
#define BEATMAPHANDLER_H

#include "ofMain.h"
#include "Note.h"

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

	float xS, yS;  // the X and Y position of the note shadow.
	float angle; // possible angle where the note comes from.

	NoteType type;
	NoteButton button;
	
	vector<string> args;
	void convert() {
		offset = ofToInt(args.at(1));
		length = ofToDouble(args.at(2));
		type   = (NoteType)ofToInt(args.at(3));
		button = (NoteButton)ofToInt(args.at(4));
		xS     = ofToFloat(args.at(5));
		yS 	   = ofToFloat(args.at(6));
		angle  = ofToFloat(args.at(7));
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
	const string bpmText 	   = "bpm";

	vector<string> getBeatMapDirectories(const string &path);
	beatMap setNoteParameters(string path);
public:
	BeatMapHandler();
};

#endif //!BEATMAPHANDLER_H