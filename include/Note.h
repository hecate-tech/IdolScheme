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
#endif //!CONDUCTOR_H

#ifndef NOTEINFO_H
	#include "NoteInfo.h"
#endif //!NOTEINFO_H


/* @brief - Shadow
 * The Shadow class is the second
 * half of the note object and is
 * essential that it does not move.
 * (Amazing brief)
 */
class Shadow {
protected:
	const GLchar *sprite_dir = "images/shadow.png";
public:
	ofImage shadowSprite;
	const char *shadow_dir = "images/shadow.png";

	Shadow() {}
	~Shadow() {
		shadow_dir = NULL;
		sprite_dir = NULL;
		delete shadow_dir;
		delete sprite_dir;
	}
	void resize(GLint width, GLint height);
	void load();
	void draw(GLfloat x, GLfloat y);
};

/* @brief - Note
 * The Note class is what stores
 * all the characteristics that
 * makes a note a note. These
 * include the note size, the
 * note color, and the note image.
 */
class Note {
protected:
	int lengthInBeats = BAD_LENGTH;
	GLint note_size = (ofGetWindowWidth() + ofGetWindowHeight()) * 0.06; // for width and the height.
	ofColor note_color = ofColor(255, 255, 255, 255);
	const GLchar *sprite_dir = "images/note.png"; // directory to note image.
	ofImage noteSprite; // object for sprite.

	ofVec2f startPos;
	ofVec2f distToShadow;
	GLfloat notex, notey, shadowX, shadowY; // current positions
	Shadow *shadow; // The note shadow. (This object shouldn't move)
public:
	/// Note settings
	/// -------------
	noteInfo noteSettings;

	/// Constructors/Desconstructor
	/// ---------------------------
	Note() {}
	Note(ofPoint initCoords, ofPoint shadowCoords, NoteType type_, NoteButton button_);
	Note(ofPoint initCoords, ofPoint shadowCoords, NoteType type_);
	~Note();

	/// Functions
	/// ---------
	void setup(ofPoint initCoords = ofPoint(0,0), ofPoint shadowCoords = ofPoint(0,0),
		NoteType type_ = BUTTON, NoteButton button_ = BUTTON_EMPTY);
	void calcNoteParams();
	void setBeatRest(noteInfo settings);
	void setBeatNote(noteInfo settings);
	void setSize(GLint newSize);
	void setPosition(GLfloat x = 0, GLfloat y = 0, GLfloat xS = 0, GLfloat yS = 0);
	void init();
	void draw(GLfloat nX = 0, GLfloat nY = 0, GLfloat sX = 0, GLfloat sY = 0); // draws the note and shadow objects.
	void moveByBeats(GLfloat currBeat);
	void hit(); // For catching key presses.
	void setColor(GLfloat r = 0, GLfloat g = 0, GLfloat b = 0, GLfloat a = 255); // not used ATM
	bool destroy();
	ofColor getColor();
	ofPoint calcPolarPoint(float angle);
	Shadow *getShadow();
};

#endif //!NOTE_H