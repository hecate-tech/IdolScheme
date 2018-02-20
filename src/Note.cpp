#include "../include/Note.h"

////////////////////////////////////////////////////////////////////////////////////////
       //////////////////      Constructors/Desconstructors      //////////////////
////////////////////////////////////////////////////////////////////////////////////////

Note::Note(GLfloat xInit, GLfloat yInit, GLfloat xShadow, GLfloat yShadow, NoteType type_, NoteButton button_)
	: notex(xInit), notey(yInit), shadowX(xShadow), shadowY(yShadow), type(type_), button(button_) {
	
	noteSprite.load(sprite_dir);
	init();
}

//----------------------------------------------------------------------------------
Note::Note(GLfloat xInit, GLfloat yInit, GLfloat xShadow, GLfloat yShadow, NoteType type_) 
	: notex(xInit), notey(yInit), shadowX(xShadow), shadowY(yShadow), type(type_), button(BUTTON_EMPTY) {

	noteSprite.load(sprite_dir);
}

//----------------------------------------------------------------------------------
Note::Note(ofPoint initCoords, ofPoint shadowCoords, NoteType type_, NoteButton button_) 
	: notex(initCoords[0]), notey(initCoords[1]), shadowX(shadowCoords[0]), shadowY(shadowCoords[1]), type(type_), button(button_) {

	noteSprite.load(sprite_dir);
	init();
}

//----------------------------------------------------------------------------------
Note::Note(ofPoint initCoords, ofPoint shadowCoords, NoteType type_) 
	: notex(initCoords[0]), notey(initCoords[1]), shadowX(shadowCoords[0]), shadowY(shadowCoords[1]), type(type_), button(BUTTON_EMPTY) {

	noteSprite.load(sprite_dir);
	init();
}

//----------------------------------------------------------------------------------
Note::Note(bool rest, int bpm, int num, int lengthInBeats_) {
	restNote = rest;
	number = num;
	lengthInBeats = lengthInBeats_;
	noteConductor._bpm = bpm;
	noteConductor._offsetInMs = 0;
	noteConductor._lengthInS = 2;
	noteConductor.startTimer();
}

//----------------------------------------------------------------------------------
Note::Note(bool rest, int num, int bpm, int off, int len, float angle, NoteType type, NoteButton btn) {
	restNote = rest;
	number = num;
	noteAngle = angle;
	noteConductor._bpm = bpm;
	noteConductor._offsetInMs = 0;
	noteConductor._lengthInS = len;
	noteConductor.startTimer();
	calcNoteParams();
	init();
}

//----------------------------------------------------------------------------------
void Note::setBeatRest(int num, int bpm, int lengthInBeats_) {
	restNote = true;
	number = num;
	lengthInBeats = lengthInBeats_;
	noteConductor._bpm = bpm;
	noteConductor._offsetInMs = 0;
	noteConductor._lengthInS = 2;
	noteConductor.startTimer();
	init();
}

//----------------------------------------------------------------------------------
void Note::setBeatNote(int num, int bpm, int off, int len, float angle, NoteType type_, NoteButton btn) {
	restNote = false;
	number = num;
	noteAngle = angle;
	noteConductor._bpm = bpm;
	noteConductor._offsetInMs = off;
	noteConductor._lengthInS = len;
	type = type_;
	button = btn;
	noteConductor.startTimer();
	init();
}

//----------------------------------------------------------------------------------
void Note::setup(ofPoint initCoords, ofPoint shadowCoords, NoteType type_, NoteButton button_) {
	setPosition(initCoords[0], initCoords[1], shadowCoords[0], shadowCoords[1]);

	noteSprite.load(sprite_dir);

	type = type_;
	button = button_;
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
void Note::moveByBeats(GLfloat beats) {
	noteConductor.refreshMembers();
	noteConductor.beatSinceRefresh = noteConductor.currBeat;

	float Vy = beats * (dY * 2.0f);
	float Vx = beats * (dX * 2.0f);
	// the notes may need more conductors to keep
	// up with supplying the correct 'beats'
	// parameter.
	notex += Vx / 2.0f; // you may ask why this works
	notey += Vy / 2.0f; // and I can't answer that.
	
	getptr()->draw(shadowX, shadowY);
	noteSprite.draw(notex, notey);
}

//----------------------------------------------------------------------------------
void Note::calcNoteParams() {
	dX = shadowX - notex;
	dY = shadowY - notey;
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
	int x_ = (ofGetWidth() * angle);
	int y_ = 0;

	while(x_ > ofGetWidth() || x_ < 0 || y_ > ofGetHeight() || y_ < 0) {
		if(x_ > ofGetWidth()) {
			y_ += x_ - ofGetWidth();
			x_ = ofGetWidth();
		}
		if(y_ > ofGetHeight()) {
			x_ -= y_ - ofGetHeight();
			y_ = ofGetHeight();
		}
		if(x_ < 0) {
			y_ -= x_ + ofGetWidth();
			x_ = 0;
		}
		if(y_ < 0) {
			x_ += y_ + ofGetHeight();
			y_ = 0;
		}
	}

	if(y_ == 0) {
		y_ -= note_size;
	}
	if(x_ == 0) {
		x_ -= note_size;
	}
	if(y_ == ofGetHeight()) {
		y_ += note_size;
	}
	if(x_ == ofGetWidth()) {
		x_ += note_size;
	}

	result.x = x_;
	result.y = y_;

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
