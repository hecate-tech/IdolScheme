#include "../include/Note.h"
#include <complex>
////////////////////////////////////////////////////////////////////////////////////////
       //////////////////      Constructors/Desconstructors      //////////////////
////////////////////////////////////////////////////////////////////////////////////////

Note::Note(ofPoint initCoords, ofPoint shadowCoords, NoteType type_, NoteButton button_) 
	: notex(initCoords[0]), notey(initCoords[1]), shadowX(shadowCoords[0]), shadowY(shadowCoords[1]) {
	noteSettings.type = type_;
	noteSettings.button = button_;
	noteSprite.load(sprite_dir);
	init();
}

//----------------------------------------------------------------------------------
Note::Note(ofPoint initCoords, ofPoint shadowCoords, NoteType type_) 
	: notex(initCoords[0]), notey(initCoords[1]), shadowX(shadowCoords[0]), shadowY(shadowCoords[1]) {
	noteSettings.type = type_;
	noteSprite.load(sprite_dir);
	init();
}

//----------------------------------------------------------------------------------
void Note::setBeatRest(noteInfo settings) {
	noteSettings = settings;
	init();
}

//----------------------------------------------------------------------------------
void Note::setBeatNote(noteInfo settings) {
	noteSettings = settings;

	setup(
		ofPoint(calcPointsFromAngle(noteSettings.angle).x, calcPointsFromAngle(noteSettings.angle).y),
		ofPoint(noteSettings.xS * ofGetWidth(), noteSettings.yS * ofGetHeight()),
		noteSettings.type, noteSettings.button
	);
}

//----------------------------------------------------------------------------------
void Note::setup(ofPoint initCoords, ofPoint shadowCoords, NoteType type_, NoteButton button_) {
	setPosition(initCoords[0], initCoords[1], shadowCoords[0], shadowCoords[1]);

	noteSprite.load(sprite_dir);

	noteSettings.type = type_;
	noteSettings.button = button_;
	init();
}

//----------------------------------------------------------------------------------
Note::~Note() {
	destroy();
}

//----------------------------------------------------------------------------------
bool Note::destroy() {
	return false;
}

//----------------------------------------------------------------------------------
void Note::init() {
	shadow = new Shadow(); // creates the shadow.
	shadow->load(); // loads the shadow image.

	/// Setting the anchor point to the center of the note
	/// --------------------------------------------------
	noteSprite.setAnchorPercent(.5, .5);

	noteSprite.resize(note_size, note_size); // resizing the note.
	shadow->resize(note_size, note_size); // resizing the shadow.
}



///////////////////////////////////////////////////////////////
   //////////////////      Functions      //////////////////
///////////////////////////////////////////////////////////////

void Note::update() {

}

//----------------------------------------------------------------------------------
void Note::hit() {
	/// This is when the user pressed the assigned note button.
	/// -------------------------------------------------------
}

//----------------------------------------------------------------------------------
void Note::draw(GLfloat nX, GLfloat nY, GLfloat sX, GLfloat sY) {
	/// checking if the x and y parameters are present.
	/// -----------------------------------------------
	if (nX != BAD_COORDINATE && nY != BAD_COORDINATE && sX != BAD_COORDINATE && sY != BAD_COORDINATE) {
		getptr()->draw(sX, sY);
		noteSprite.draw(nX, nY);
	} else {
		getptr()->draw(shadowX, shadowY);
		noteSprite.draw(notex, notey);
	}
}

//----------------------------------------------------------------------------------
void Note::moveByBeats(GLfloat currBeat) {
	float time = currBeat - noteSettings.noteNum;
	
	notex = startPos.x + time * distToShadow.x;
	notey = startPos.y + time * distToShadow.y;

	getptr()->draw(shadowX, shadowY);
	noteSprite.draw(notex, notey);
}

//----------------------------------------------------------------------------------
void Note::calcNoteParams() {
	startPos.x = notex;
	startPos.y = notey;
	distToShadow.x = shadowX - notex;
	distToShadow.y = shadowY - notey;
}

//----------------------------------------------------------------------------------
void Note::setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	/// TODO
}

//----------------------------------------------------------------------------------
void Note::setPosition(GLfloat x, GLfloat y, GLfloat xS, GLfloat yS) {
	notex   = x;
	notey   = y;
	shadowX = xS;
	shadowY = yS;
}

//----------------------------------------------------------------------------------
void Note::setSize(GLint newSize) {
	note_size = newSize;

	/// note resizing
	/// -------------
	noteSprite.load(sprite_dir); // reloads image
	noteSprite.resize(note_size, note_size);
	
	/// shadow resizing
	/// ---------------
	getptr()->shadowSprite.load(getptr()->shadow_dir); // reloads image
	getptr()->shadowSprite.resize(note_size, note_size);
}

//----------------------------------------------------------------------------------
Shadow *Note::getptr() {
	return shadow; // returns the shadow object attached to the note.
}


//----------------------------------------------------------------------------------
ofPoint Note::calcPointsFromAngle(float angle) {
	ofPoint result;
	float halfC = 3.14169f / 180.f;
	double radAngle = angle * halfC;
	float zMod, off = 0;


	if (angle >= 60 && angle < 120) {
		zMod = ofGetWidth() / 2;
		off = 90 * halfC;
	}
	else if (angle >= 300 && angle <= 360) {
		zMod = ofGetHeight() / 2;
	}
	else if (angle < 60 || (angle >= 180 & angle < 240)) {
		zMod = ofGetHeight() / 2;
	}
	else if (angle >= 120 && angle < 180) {
		zMod = ofGetHeight() / 2;
		off = 0;
	}
	else if (angle >= 240 && angle < 300) {
		zMod = ofGetWidth() / 2;
		off = 280 * halfC;
	}

	double z_ = zMod + note_size;
	double x_ = tan(radAngle - off) * z_;

	if (angle >= 60 && angle < 120) {
		result.x = ofGetWidth() + note_size;
		result.y = ((ofGetHeight() / 2) + x_);
	}
	else if (angle < 60) {
		result.x = ((ofGetWidth() / 2) + x_);
		result.y = -1 * note_size;
	}
	else if (angle >= 120 && angle < 240) {
		result.x = ((ofGetWidth() / 2) + (-1 * x_));
		result.y = ofGetHeight() + note_size;
	}
	else if (angle >= 240 && angle < 300) {
		result.x = -1 * note_size;
		result.y = ((ofGetHeight() / 2) + (-1 * x_));
	}
	else if (angle >= 300 && angle <= 360) {
		result.x = ((ofGetWidth() / 2) + x_);
		result.y = -1 * note_size;
	}
	
	return result;
}


//////////////////////////////////////////////////////////////
    //////////////////      Shadow      //////////////////
//////////////////////////////////////////////////////////////

void Shadow::draw(GLfloat x, GLfloat y) {
	this->shadowSprite.draw(x, y);
}

//----------------------------------------------------------------------------------
void Shadow::load() {
	shadowSprite.setAnchorPercent(.5, .5);
	shadowSprite.load(shadow_dir);
}

//----------------------------------------------------------------------------------
void Shadow::resize(GLint width, GLint height) {
	shadowSprite.resize(width, height);
}
