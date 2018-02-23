#pragma once

#ifndef BEATMAPHANDLER_H
#define BEATMAPHANDLER_H

#ifndef OFMAIN_H
	#define OFMAIN_H
	#include "ofMain.h"
#endif //!OFMAIN_H

#ifndef NOTE_H
	#include "Note.h"
#endif //!NOTE_H

#ifndef NOTEINFO_H
	#include "NoteInfo.h"
#endif //!NOTEINFO_H


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
	beatMap beatMapMenu();
private:
	/// beatmap language properties
	/// ---------------------------
	const string DELIMITER = "|";
	const string CMTPREFIX = "#";
	const string NOTEKEY   = "note";
	const string NAMEKEY   = "beatname";
	const string BPMKEY    = "bpm";
	const string RESTKEY   = "rest";
	
	/// Misc Beat Map management methods
	/// --------------------------------
	vector<string> getBeatMapDirectories(const string &path);
	beatMap setNoteParameters(string path);
public:
	BeatMapHandler();
};

#endif //!BEATMAPHANDLER_H