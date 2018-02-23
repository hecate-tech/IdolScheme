#pragma once

#ifndef NOTEINFO_H
#define NOTEINFO_H

#ifndef NOTE_H
	#include "Note.h"
#endif //!NOTE_H

#define BAD_LENGTH -934025


/* @brief - NoteType
*
* defines the type of note this is
* whether it is a button note or
* an axis note. An axis note is
* something that uses the joysticks
* or the triggers on the controller.
*/
enum NoteType {
	BUTTON,
	AXIS,
};


/* @brief - NoteButton
*
* NoteButton stores the
* available buttons that the note
* can use. There is also a
* `BUTTON_EMPTY` for when you
* are not using the buttons and
* instead using the axis.
*/
enum NoteButton {
	BUTTON_A,
	BUTTON_B,
	BUTTON_X,
	BUTTON_Y,
	BUTTON_LBUMPER,
	BUTTON_RBUMPER,
	BUTTON_BACK,
	BUTTON_START,
	BUTTON_LJOY,
	BUTTON_RJOY,
	BUTTON_DPAD_UP,
	BUTTON_DPAD_RIGHT,
	BUTTON_DPAD_DOWN,
	BUTTON_DPAD_LEFT,
	BUTTON_EMPTY,
};


/* @brief - noteInfo
* What makes up a note is quite a bit more.
* A note holds all its arguments and in order
* for it to be instantiated in-game.
*/
struct noteInfo {
public:

	int noteNum;
	int lineNum;   // note's line number in its .isbm file.
	int bpm;	   // note's bpm (only used if diff from last note's)
	int offset;	   // note's offset (Milliseconds)
	double length; // length of song? (seconds)
	float xS, yS;  // the X and Y position of the note shadow.
	float angle;   // possible angle where the note comes from.
				   // if the note is a rest.
	bool rest = false;
	int restSize = 1;

	NoteType type;       // Note type (Axis or Button)
	NoteButton button;   // Note's assigned button (A, B, X, Y)
	vector<string> args; // temporary args vector

	void convert() {
		offset = ofToInt(args.at(1));
		length = ofToDouble(args.at(2));
		type   = (NoteType)ofToInt(args.at(3));
		button = (NoteButton)ofToInt(args.at(4));
		xS     = ofToFloat(args.at(5));
		yS     = ofToFloat(args.at(6));
		angle  = ofToFloat(args.at(7));

		vector<string>().swap(args); // releases memory from args
	}

	noteInfo& operator= (const noteInfo &a) {
		lineNum  = a.lineNum;
		offset	 = a.offset;
		length	 = a.length;
		type	 = a.type;
		button	 = a.button;
		xS		 = a.xS;
		yS		 = a.yS;
		angle	 = a.angle;
		rest	 = a.rest;
		restSize = a.restSize;
		bpm		 = a.bpm;
		noteNum  = a.noteNum;
		
		return *this;
	}

	noteInfo() {}
	noteInfo(int lineNumber) { lineNum = lineNumber; }
};

#endif //!NOTEINFO_H