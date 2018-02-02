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

///////////////////////////////////////////////////////////////
   //////////////////      Functions      //////////////////
///////////////////////////////////////////////////////////////

void Note::init() {
	shadow = new Shadow();
	shadow->load();
	
	noteSprite.setAnchorPercent(.5, .5);
	noteSprite.resize(note_size, note_size);
	shadow->resize(note_size, note_size);
}

//----------------------------------------------------------------------------------
void Note::update() {
	a += ofGetLastFrameTime() * 3.5f;
	notex = (cos(a) * ((ofGetWindowWidth() / 2) - note_size / 2)) + ((ofGetWindowWidth() / 2));
}

//----------------------------------------------------------------------------------
void Note::hit() {

}

//----------------------------------------------------------------------------------
void Note::draw(GLfloat *x, GLfloat *y) {
	getptr()->draw(shadowX, shadowY);
	if (x != nullptr && y != nullptr) {
		noteSprite.draw(*x, *y);
	} else {
		noteSprite.draw(notex, notey);
	}
}

//----------------------------------------------------------------------------------
void Note::moveByBeats(GLfloat beats) {

}

//----------------------------------------------------------------------------------
void Note::setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {

}

//----------------------------------------------------------------------------------
void Note::setPosition(GLfloat x, GLfloat y, GLfloat xS, GLfloat yS) {
	notex = x;
	notey = y;
	shadowX = xS;
	shadowY = yS;
}

//----------------------------------------------------------------------------------
void Note::setSize(GLint newSize) {
	note_size = newSize;
	noteSprite.load(sprite_dir);
	noteSprite.resize(note_size, note_size);
	getptr()->shadowSprite.load(getptr()->shadow_dir);
	getptr()->shadowSprite.resize(note_size, note_size);
}

//----------------------------------------------------------------------------------
Shadow *Note::getptr() {
	return shadow;
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