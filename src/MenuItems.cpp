#include "../include/MenuItems.h"

//////////////////////////////////////////////////////////////////////////////////
   //////////////////      Constructors/Desconstructors      //////////////////
//////////////////////////////////////////////////////////////////////////////////

ISGUI::idolButton::idolButton() {
	ofAddListener(ofEvents().mousePressed, this, &idolButton::mouseDownEvent);
	ofAddListener(ofEvents().mouseMoved, this, &idolButton::mouseMoveEvent);
	ofAddListener(ofEvents().mouseReleased, this, &idolButton::mouseUpEvent);
	buttonImage.setAnchorPercent(.5, .5);
}

//-------------------------------------------------------------------------------------------
ISGUI::idolButton::idolButton(string normdir, string hoverdir, ofPoint pos, float w, float h) {
	ofAddListener(ofEvents().mousePressed, this, &idolButton::mouseDownEvent);
	ofAddListener(ofEvents().mouseMoved, this, &idolButton::mouseMoveEvent);
	ofAddListener(ofEvents().mouseReleased, this, &idolButton::mouseUpEvent);
	set(normdir, hoverdir, pos, w, h);
	buttonImage.setAnchorPercent(.5, .5);
}

//-------------------------------------------------------------------------------------------
ISGUI::idolButton::~idolButton() {
	ofRemoveListener(ofEvents().mousePressed, this, &idolButton::mouseDownEvent);
	ofRemoveListener(ofEvents().mouseMoved, this, &idolButton::mouseMoveEvent);
	ofRemoveListener(ofEvents().mouseReleased, this, &idolButton::mouseUpEvent);
}

////////////////////////////////////////////////////////////////
   /////////////////      Main Functions      ///////////////
////////////////////////////////////////////////////////////////

bool ISGUI::idolButton::getMouseDown() {
	if (pressed) {
		pressed = false;
		return true;
	}
	return false;
}



//-------------------------------------------------------------------------------------------
void ISGUI::idolButton::draw() {
	buttonImage.draw(imagePos.x, imagePos.y);
}

/////////////////////////////////////////////////////////////////
   /////////////////      Getters/Setters      ///////////////
/////////////////////////////////////////////////////////////////

void ISGUI::idolButton::setBounds(const ofPoint xy, float width, float height) {
	bound.set(xy, width, height);
	width = width;
	height = height;
}

//-------------------------------------------------------------------------------------------
void ISGUI::idolButton::setImageDirectory(const string directory) {
	buttonImage.load(directory);
	buttonImage.resize(width, height);
	imageDirectory = directory;
}

//-------------------------------------------------------------------------------------------
void ISGUI::idolButton::setImagePosition(ofPoint pos) {
	imagePos = pos;
	bound.setPosition(ofPoint(pos.x - (width / 2), pos.y - (height / 2)));
}

//-------------------------------------------------------------------------------------------
void ISGUI::idolButton::setImagePosition(float x_, float y_) {
	setImagePosition(ofPoint(x_, y_));
}

//-------------------------------------------------------------------------------------------
void ISGUI::idolButton::set(string normdir, string hoverdir, ofPoint pos, float w, float h) {
	buttonImage.load(normdir);
	buttonImage.resize(w, h);
	width = w;
	height = h;
	imagePos = pos;
	bound.set(ofPoint(pos.x - (w / 2), pos.y - (h / 2)), w, h);
	normalDirectory = normdir;
	hoverDirectory = hoverdir;
}

//-------------------------------------------------------------------------------------------
ofPoint ISGUI::idolButton::getPosition() {
	return imagePos;
}

//-------------------------------------------------------------------------------------------
string ISGUI::idolButton::getImageDirectory() {
	return imageDirectory;
}

///////////////////////////////////////////////////////////////////
   /////////////////      Private Functions      ///////////////
///////////////////////////////////////////////////////////////////

void ISGUI::idolButton::mouseDownEvent(ofMouseEventArgs &mouse) {
	if (mouse.button == OF_MOUSE_BUTTON_1) {
		if (isInBounds(mouse.x, mouse.y)) {
			pressed = true;
		}
	}
}

void ISGUI::idolButton::mouseMoveEvent(ofMouseEventArgs &mouse) {
	if (isInBounds(mouse.x, mouse.y)) {
		if (!hovering) {
			hovering = true;
			setImageDirectory(hoverDirectory);
		}
	}
	else {
		if (hovering) {
			hovering = false;
			setImageDirectory(normalDirectory);
		}
	}
}

void ISGUI::idolButton::mouseUpEvent(ofMouseEventArgs &mouse) {
	if (pressed) pressed = false;
}

bool ISGUI::idolButton::isInBounds(float x, float y) {
	if (x <= bound.getRight()
		&& x >= bound.getLeft()
		&& y <= bound.getBottom()
		&& y >= bound.getTop()) {
		return true;
	}
	return false;
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

///////////////////////////-idolVecButton-///////////////////////////

ISGUI::idolVecButton::idolVecButton() {
	ofAddListener(ofEvents().mouseMoved, this, &idolVecButton::onMouseMove);
	ofAddListener(ofEvents().mousePressed, this, &idolVecButton::onMouseDown);
	ofAddListener(ofEvents().mouseReleased, this, &idolVecButton::onMouseUp);
}

ISGUI::idolVecButton::idolVecButton(ofVec2f pos, ofVec2f size, string btnText, ofColor nColor, ofColor hColor) {
	ofAddListener(ofEvents().mouseMoved, this, &idolVecButton::onMouseMove);
	ofAddListener(ofEvents().mousePressed, this, &idolVecButton::onMouseDown);
	ofAddListener(ofEvents().mouseReleased, this, &idolVecButton::onMouseUp);
	set(pos, size, btnText, nColor, hColor);
}

ISGUI::idolVecButton::~idolVecButton() {
	ofRemoveListener(ofEvents().mouseMoved, this, &idolVecButton::onMouseMove);
	ofRemoveListener(ofEvents().mousePressed, this, &idolVecButton::onMouseDown);
	ofRemoveListener(ofEvents().mouseReleased, this, &idolVecButton::onMouseUp);
}


void ISGUI::idolVecButton::draw() {
	ofSetColor(currColor);
	ofDrawRectangle(bounds);

	ofSetColor(textColor);
	label.drawString(text, textPosition.x, textPosition.y);
	
	ofSetColor(255, 255, 255, 255); // resets color to white
}

/////////////////////////////////////////////////////////////////
   /////////////////      Getters/Setters      ///////////////
/////////////////////////////////////////////////////////////////

void ISGUI::idolVecButton::set(ofVec2f pos, ofVec2f size, string btnText, ofColor nColor, ofColor hColor) {
	ofTrueTypeFont::setGlobalDpi(60);
	label.load("verdana.ttf", 40, true, false);
	label.setLetterSpacing(1.037);

	setBoundSize(size);
	setText(btnText);
	setButtonPos(pos);
	setNormColor(nColor);
	setHoverColor(hColor);
	currColor = nColor;
}

void ISGUI::idolVecButton::setFontSize(int size) {
	fontSize = size;
}

void ISGUI::idolVecButton::setText(string newText) {
	text = newText;
}

void ISGUI::idolVecButton::setTextPos(ofVec2f pos) {
	double percHeight = label.stringHeight(text) * 0.15625;
	double percWidth = percHeight * 0.7;

	textPosition.x = (bounds.getCenter().x - (label.stringWidth(text) / 2.f) - percWidth);
	textPosition.y = (bounds.getCenter().y + (label.stringHeight(text) / 2.f) - percHeight);
}

void ISGUI::idolVecButton::setBoundPos(ofVec2f pos) {
	bounds.setPosition(pos);
}

void ISGUI::idolVecButton::setButtonPos(ofVec2f pos) {
	setBoundPos(pos);
	setTextPos(pos); // not centered text
}

void ISGUI::idolVecButton::setBoundSize(ofVec2f size) {
	bounds.setSize(size.x, size.y);
}

void ISGUI::idolVecButton::setFontKerning(double kern) {
	kerning = kern;
}

void ISGUI::idolVecButton::setFontFile(string fontDir) {
	fontFile = fontDir;
}

void ISGUI::idolVecButton::setTextColor(ofColor color) {
	textColor = color;
}

void ISGUI::idolVecButton::setNormColor(ofColor color) {
	normColor = color;
}

void ISGUI::idolVecButton::setHoverColor(ofColor color) {
	hoverColor = color;
}

int ISGUI::idolVecButton::getFontSize() {
	return fontSize;
}

bool ISGUI::idolVecButton::getMouseDown() {
	if (pressed) {
		pressed = false;
		return true;
	}
	return false;
}

double ISGUI::idolVecButton::getFontKerning() {
	return kerning;
}

string ISGUI::idolVecButton::getText() {
	return text;
}

string ISGUI::idolVecButton::getFontFile() {
	return fontFile;
}

///////////////////////////////////////////////////////////////////
  /////////////////      Private Functions      ///////////////
///////////////////////////////////////////////////////////////////

void ISGUI::idolVecButton::onMouseMove(ofMouseEventArgs &mouse) {
	if (isInBounds(mouse.x, mouse.y)) {
		if (!hovering) {
			hovering = true;
			currColor = hoverColor;
		}
	}
	else {
		if (hovering) {
			hovering = false;
			currColor = normColor;
		}
	}
}

void ISGUI::idolVecButton::onMouseDown(ofMouseEventArgs &mouse) {
	if (mouse.button == OF_MOUSE_BUTTON_1) {
		if (isInBounds(mouse.x, mouse.y)) {
			pressed = true;
		}
	}
}

void ISGUI::idolVecButton::onMouseUp(ofMouseEventArgs &mouse) {
	if (pressed) pressed = false;
}

bool ISGUI::idolVecButton::isInBounds(float x, float y) {
	if (   x <= bounds.getRight()
		&& x >= bounds.getLeft()
		&& y <= bounds.getBottom()
		&& y >= bounds.getTop()) {
		return true;
	}
	return false;
}