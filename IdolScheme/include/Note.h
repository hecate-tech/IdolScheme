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

class Shadow {
public:
	ofImage shadowSprite;
	Shadow() {}
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
public:
	/// Note constants
	/// --------------
	GLint note_size = 100.f; // for width and the height.
	GLint note_color[4] = { 255, 255, 255, 255 };
	GLchar *sprite_dir = "images/note.png";

	NoteType type; // The note type. Ex. Axis or Button.
	NoteButton button; // the assigned button.
	ofImage noteSprite;
	GLfloat a = 0.f;

	/// Constructors/Desconstructor
	/// ---------------------------
	Note() {}
	Note(GLfloat xInit, GLfloat yInit, GLfloat xShadow, GLfloat yShadow, NoteType type_, NoteButton button_);
	Note(GLfloat xInit, GLfloat yInit, GLfloat xShadow, GLfloat yShadow, NoteType type_);
	Note(ofPoint initCoords, ofPoint shadowCoords, NoteType type_, NoteButton button_);
	Note(ofPoint initCoords, ofPoint shadowCoords, NoteType type_);
	~Note();

	bool destroy();
	void setPosition(GLfloat x, GLfloat y, GLfloat xS, GLfloat yS);
	void init();
	void setup(ofPoint initCoords, ofPoint shadowCoords, NoteType type_, NoteButton button_);
	void draw(GLfloat *x = nullptr, GLfloat *y = nullptr); // draws the note and shadow objects.
	void moveByBeats(GLfloat beats);
	void update(); // to be ran in the update method of IdolScheme.cpp
	void hit(); // For catching key presses.
	void setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 255);
	Shadow *getptr();
	GLfloat notex, notey, shadowX, shadowY; // coords
private:
	Shadow *shadow; // The note shadow. (This object shouldn't move)
};

#endif //!NOTE_H