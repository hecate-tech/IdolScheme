#pragma once

#ifndef NOTE_H
#define NOTE_H

#ifndef OFMAIN_H
	#define OFMAIN_H
	#include "../ofMain.h"
#endif //!OFMAIN_H

#ifndef ERRORCODES_H
	#include "ErrorCodes.h"
#endif //!ERRORCODES_H

#ifndef CONDUCTOR_H
#define CONDUCTOR_H
    #include "Conductor.h"
#endif

#ifndef NOTEINFO_H
	#include "NoteInfo.h"
#endif


/* @brief - Shadow
 * The Shadow class is the second
 * half of the note object and is
 * essential that it does not move.
 * (Amazing brief)
 */
class Shadow {
public:
	ofImage shadowSprite;
	const char *shadow_dir = "images/shadow.png";

	Shadow() {}
	void resize(GLint width, GLint height);
	void load();
	void draw(GLfloat x, GLfloat y);
private:
	const GLchar *sprite_dir = "images/shadow.png";
};

/* @brief - Note
 * The Note class is what stores
 * all the characteristics that
 * makes a note a note. These
 * include the note size, the
 * note color, and the note image.
 */
class Note {
public:
	/// Note settings
	/// -------------
	noteInfo noteSettings;

	bool restNote = false;
	int number;
	float noteAngle;
	int lengthInBeats = BAD_LENGTH;
	GLint note_size = (ofGetWindowWidth() + ofGetWindowHeight()) * 0.08; // for width and the height.
	GLint note_color[4] = { 255, 255, 255, 255 };
	const GLchar *sprite_dir = "images/note.png";
	int noteBPM = 30;

	ofVec2f startPos;
	ofVec2f distToShadow;
	GLfloat notex, notey, shadowX, shadowY; // positions
	NoteType type; // The note type. Ex. Axis or Button.
	NoteButton button; // the assigned button.
	ofImage noteSprite;

	/// Constructors/Desconstructor
	/// ---------------------------
	Note() {}
	Note(GLfloat xInit, GLfloat yInit, GLfloat xShadow, GLfloat yShadow, NoteType type_, NoteButton button_);
	Note(GLfloat xInit, GLfloat yInit, GLfloat xShadow, GLfloat yShadow, NoteType type_);
	Note(ofPoint initCoords, ofPoint shadowCoords, NoteType type_, NoteButton button_);
	Note(ofPoint initCoords, ofPoint shadowCoords, NoteType type_);
	~Note();

	void setup(ofPoint initCoords = ofPoint(0,0), ofPoint shadowCoords = ofPoint(0,0),
		NoteType type_ = BUTTON, NoteButton button_ = BUTTON_EMPTY);

	void calcNoteParams();
	void setBeatRest(int num, int bpm, int lengthInBeats_);
	void setBeatNote(int num, int bpm, int off, int len, float angle, NoteType type, NoteButton btn);
	bool destroy();
	void setSize(GLint newSize);
	void setPosition(GLfloat x = 0, GLfloat y = 0, GLfloat xS = 0, GLfloat yS = 0);
	void init();
	void draw(GLfloat nX = 0, GLfloat nY = 0, GLfloat sX = 0, GLfloat sY = 0); // draws the note and shadow objects.
	void moveByBeats(GLfloat currBeat);
	void update(); // to be ran in the update method of IdolScheme.cpp
	void hit(); // For catching key presses.
	void setColor(GLfloat r = 0, GLfloat g = 0, GLfloat b = 0, GLfloat a = 255);
	ofPoint calcPointsFromAngle(float angle);
	Shadow *getptr();
private:
	Shadow *shadow; // The note shadow. (This object shouldn't move)
};


#endif //!NOTE_H
