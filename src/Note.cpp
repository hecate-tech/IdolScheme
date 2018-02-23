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
	ofPoint setupParam = calcPolarPoint(noteSettings.angle);
	setup(
		ofPoint(setupParam.x, setupParam.y),
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
	sprite_dir = NULL;
	shadow = NULL;
	delete sprite_dir;
	delete shadow;

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

void Note::hit() {
	/// This is when the user pressed the assigned note button.
	/// -------------------------------------------------------
}

//----------------------------------------------------------------------------------
void Note::draw(GLfloat nX, GLfloat nY, GLfloat sX, GLfloat sY) {
	/// checking if the x and y parameters are present.
	/// -----------------------------------------------
	if (nX != BAD_COORDINATE && nY != BAD_COORDINATE && sX != BAD_COORDINATE && sY != BAD_COORDINATE) {
		getShadow()->draw(sX, sY);
		noteSprite.draw(nX, nY);
	} else {
		getShadow()->draw(shadowX, shadowY);
		noteSprite.draw(notex, notey);
	}
}

//----------------------------------------------------------------------------------
void Note::moveByBeats(GLfloat currBeat) {
	float time = currBeat - noteSettings.noteNum;
	
	notex = startPos.x + time * distToShadow.x;
	notey = startPos.y + time * distToShadow.y;

	/// draw the notes after calculating the positions
	ofSetColor(note_color);
	draw(notex, notey, shadowX, shadowY);
	ofSetColor(255, 255, 255, 255); // sets color to normal
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
	note_color.r = r;
	note_color.g = g;
	note_color.b = b;
	note_color.a = a;
}

//----------------------------------------------------------------------------------
ofColor Note::getColor() {
	return note_color;
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
	getShadow()->shadowSprite.load(getShadow()->shadow_dir); // reloads image
	getShadow()->shadowSprite.resize(note_size, note_size);
}

//----------------------------------------------------------------------------------
Shadow *Note::getShadow() {
	return shadow; // returns the shadow object attached to the note.
}


//----------------------------------------------------------------------------------
ofPoint Note::calcPolarPoint(float angle) {
	ofPoint result;
	float halfC = 3.14169f / 180.f; // modifier to turn degrees to radians
	float zMod, off = 0;

	// lambda for setting the coordinates of the result ofPoint
	auto setRes = [&](float offset, float offset2, int val, int val2) {
		result.x = offset + val;
		result.y = offset2 + val2;
	};

	if ((angle >= 60 && angle < 120) // sides of screen
		|| (angle >= 240 && angle < 300)) {
		zMod = ofGetWidth() / 2;
		off = 90 * halfC * (angle >= 240 ? 3 : 1);
	}
	else if ((angle < 60) // top and bottom of screen
		|| (angle >= 120 && angle <  240)
		|| (angle >= 300 && angle <= 360)) {
		zMod = ofGetHeight() / 2;
	}

	double m_ = zMod + note_size; // magnitude
	double x_ = tan((angle * halfC) - off) * m_; // offset from projected ray

	if ((angle >= 60 && angle < 120) // sides of screen
		|| (angle >= 240 && angle < 300)) {
		setRes((angle >= 240 ? (-1 * (note_size * 2)) : ofGetWidth()),
			(ofGetHeight() / 2), note_size,
			(angle >= 240 ? (-1 * x_) : x_));
	}
	else if ((angle < 60) // top and bottom of screen
		|| (angle >= 120 && angle <  240)
		|| (angle >= 300 && angle <= 360)) {
		setRes((ofGetWidth() / 2),
			(angle >= 120 && angle < 240 ? ofGetHeight() : (-1 * (note_size * 2))),
			(angle >= 120 && angle < 240 ? (-1 * x_) : x_), note_size);
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
