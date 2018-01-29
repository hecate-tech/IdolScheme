#include "../include/Note.h"

////////////////////////////////////////////////////////////////////////////////////////
       //////////////////      Constructors/Desconstructors      //////////////////
////////////////////////////////////////////////////////////////////////////////////////
Note::Note(GLfloat xInit, GLfloat yInit, GLfloat xShadow, GLfloat yShadow, NoteType type_, NoteButton button_)
	: notex(xInit - (note_size / 2)), notey(yInit - (note_size / 2)), shadowX(xShadow - (note_size / 2)), shadowY(yShadow - (note_size / 2)), type(type_), button(button_) {
	
	noteSprite.load(sprite_dir);
	init();
}

//----------------------------------------------------------------------------------
Note::Note(GLfloat xInit, GLfloat yInit, GLfloat xShadow, GLfloat yShadow, NoteType type_) 
	: notex(xInit - (note_size / 2)), notey(yInit - (note_size / 2)), shadowX(xShadow - (note_size / 2)), shadowY(yShadow - (note_size / 2)), type(type_), button(BUTTON_EMPTY) {

	noteSprite.load(sprite_dir);
}

//----------------------------------------------------------------------------------
Note::Note(ofPoint initCoords, ofPoint shadowCoords, NoteType type_, NoteButton button_) 
	: notex(initCoords[0] - (note_size / 2)), notey(initCoords[1] - (note_size / 2)), shadowX(shadowCoords[0] - (note_size / 2)), shadowY(shadowCoords[1] - (note_size / 2)), type(type_), button(button_) {

	noteSprite.load(sprite_dir);
	init();
}

//----------------------------------------------------------------------------------
Note::Note(ofPoint initCoords, ofPoint shadowCoords, NoteType type_) 
	: notex(initCoords[0] - (note_size / 2)), notey(initCoords[1] - (note_size / 2)), shadowX(shadowCoords[0] - (note_size / 2)), shadowY(shadowCoords[1] - (note_size / 2)), type(type_), button(BUTTON_EMPTY) {

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

	noteSprite.resize(note_size, note_size);
	shadow->resize(note_size, note_size);
}

void Note::update() {
	a += ofGetLastFrameTime() * 3.5f;
	if (a > 600) a -= 600;
	notex = (cos(a) * 300.f) + ((ofGetWindowWidth() / 2.) - (note_size / 2.));
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
	notex = x - (note_size / 2);
	notey = y - (note_size / 2);
	shadowX = xS - (note_size / 2);
	shadowY = yS - (note_size / 2);
}

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
	shadowSprite.load("images/shadow.png");
}

//----------------------------------------------------------------------------------
void Shadow::resize(GLint width, GLint height) {
	shadowSprite.resize(width, height);
}