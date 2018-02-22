#include "../include/Note.h"

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
			y_ -= x_ * -1;
			x_ = 0;
		}
		if(y_ < 0) {
			x_ += y_ * -1;
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
