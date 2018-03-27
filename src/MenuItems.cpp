#include "../include/MenuItems.h"

//////////////////////////////////////////////////////////////////////////////////
   //////////////////      Constructors/Desconstructors      //////////////////
//////////////////////////////////////////////////////////////////////////////////

ISGUI::IdolButton::IdolButton() {
	ofAddListener(ofEvents().mousePressed, this, &IdolButton::mouseDownEvent);
	ofAddListener(ofEvents().mouseMoved, this, &IdolButton::mouseMoveEvent);
	ofAddListener(ofEvents().mouseReleased, this, &IdolButton::mouseUpEvent);
	buttonImage.setAnchorPercent(.5, .5);
}

//-------------------------------------------------------------------------------------------
ISGUI::IdolButton::IdolButton(string normdir, string hoverdir, ofPoint pos, float w, float h) {
	ofAddListener(ofEvents().mousePressed, this, &IdolButton::mouseDownEvent);
	ofAddListener(ofEvents().mouseMoved, this, &IdolButton::mouseMoveEvent);
	ofAddListener(ofEvents().mouseReleased, this, &IdolButton::mouseUpEvent);
	set(std::move(normdir), std::move(hoverdir), pos, w, h);
	buttonImage.setAnchorPercent(.5, .5);
}

//-------------------------------------------------------------------------------------------
ISGUI::IdolButton::~IdolButton() {
	ofRemoveListener(ofEvents().mousePressed, this, &IdolButton::mouseDownEvent);
	ofRemoveListener(ofEvents().mouseMoved, this, &IdolButton::mouseMoveEvent);
	ofRemoveListener(ofEvents().mouseReleased, this, &IdolButton::mouseUpEvent);
}

////////////////////////////////////////////////////////////////
   /////////////////      Main Functions      ///////////////
////////////////////////////////////////////////////////////////

bool ISGUI::IdolButton::mouseDown() {
	if (pressed) {
		pressed = false;
		return true;
	}
	return false;
}

//-------------------------------------------------------------------------------------------
void ISGUI::IdolButton::draw() {
	buttonImage.draw(imagePos.x, imagePos.y);
}

/////////////////////////////////////////////////////////////////
   /////////////////      Getters/Setters      ///////////////
/////////////////////////////////////////////////////////////////

void ISGUI::IdolButton::setBounds(const ofPoint xy, float width, float height) {
	bound.set(xy, width, height);
	width = width;
	height = height;
}

//-------------------------------------------------------------------------------------------
void ISGUI::IdolButton::setImageDirectory(const string& directory) {
	buttonImage.load(directory);
	buttonImage.resize(width, height);
	imageDirectory = directory;
}

//-------------------------------------------------------------------------------------------
void ISGUI::IdolButton::setImagePosition(ofPoint pos) {
	imagePos = pos;
	bound.setPosition(ofPoint(pos.x - (width / 2), pos.y - (height / 2)));
}

//-------------------------------------------------------------------------------------------
void ISGUI::IdolButton::setImagePosition(float x_, float y_) {
	setImagePosition(ofPoint(x_, y_));
}

//-------------------------------------------------------------------------------------------
void ISGUI::IdolButton::set(string normdir, const string &hoverdir, ofPoint pos, float w, float h) {
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
ofPoint ISGUI::IdolButton::getPosition() const {
	return imagePos;
}

//-------------------------------------------------------------------------------------------
string ISGUI::IdolButton::getImageDirectory() const {
	return imageDirectory;
}

///////////////////////////////////////////////////////////////////
   /////////////////      Private Functions      ///////////////
///////////////////////////////////////////////////////////////////

void ISGUI::IdolButton::mouseDownEvent(ofMouseEventArgs &mouse) {
	if (mouse.button == OF_MOUSE_BUTTON_1) {
		if (isInBounds(mouse.x, mouse.y)) {
			pressed = true;
		}
	}
}

//-------------------------------------------------------------------------------------------
void ISGUI::IdolButton::mouseMoveEvent(ofMouseEventArgs &mouse) {
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

//-------------------------------------------------------------------------------------------
void ISGUI::IdolButton::mouseUpEvent(ofMouseEventArgs &mouse) {
	if (pressed) pressed = false;
}

//-------------------------------------------------------------------------------------------
bool ISGUI::IdolButton::isInBounds(float x, float y) {
	return x <= bound.getRight() && x >= bound.getLeft() && y <= bound.getBottom() && y >= bound.getTop();
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

///////////////////////////-idolVecButton-///////////////////////////

ISGUI::IdolVecButton::IdolVecButton() {
	ofAddListener(ofEvents().mouseMoved, this, &IdolVecButton::onMouseMove);
	ofAddListener(ofEvents().mousePressed, this, &IdolVecButton::onMouseDown);
	ofAddListener(ofEvents().mouseReleased, this, &IdolVecButton::onMouseUp);
}

//-------------------------------------------------------------------------------------------
ISGUI::IdolVecButton::IdolVecButton(const ofVec2f pos, const ofVec2f size, string btnText, const ofColor nColor, const ofColor hColor) {
	ofAddListener(ofEvents().mouseMoved, this, &IdolVecButton::onMouseMove);
	ofAddListener(ofEvents().mousePressed, this, &IdolVecButton::onMouseDown);
	ofAddListener(ofEvents().mouseReleased, this, &IdolVecButton::onMouseUp);
	set(pos, size, std::move(btnText), nColor, hColor);
}

//-------------------------------------------------------------------------------------------
ISGUI::IdolVecButton::~IdolVecButton() {
	ofRemoveListener(ofEvents().mouseMoved, this, &IdolVecButton::onMouseMove);
	ofRemoveListener(ofEvents().mousePressed, this, &IdolVecButton::onMouseDown);
	ofRemoveListener(ofEvents().mouseReleased, this, &IdolVecButton::onMouseUp);
}

//-------------------------------------------------------------------------------------------
void ISGUI::IdolVecButton::draw() {
	ofSetColor(currColor);
	ofDrawRectangle(bounds);

	ofSetColor(textColor);
	label.drawString(text, textPosition.x, textPosition.y);
	
	ofSetColor(255, 255, 255, 255); // resets color to white
}

/////////////////////////////////////////////////////////////////
   /////////////////      Getters/Setters      ///////////////
/////////////////////////////////////////////////////////////////

void ISGUI::IdolVecButton::set(ofVec2f pos, ofVec2f size, string btnText, ofColor nColor, ofColor hColor) {
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

//-------------------------------------------------------------------------------------------
void ISGUI::IdolVecButton::setFontSize(const int size) {
	fontSize = size;
}

//-------------------------------------------------------------------------------------------
void ISGUI::IdolVecButton::setText(string newText) {
	text = std::move(newText);
}

//-------------------------------------------------------------------------------------------
void ISGUI::IdolVecButton::setTextPos(ofVec2f pos) {
	const double percHeight = label.stringHeight(text) * 0.15625;
	const double percWidth = percHeight * 0.7;

	textPosition.x = (bounds.getCenter().x - (label.stringWidth(text) / 2.f) - percWidth);
	textPosition.y = (bounds.getCenter().y + (label.stringHeight(text) / 2.f) - percHeight);
}

//-------------------------------------------------------------------------------------------
void ISGUI::IdolVecButton::setBoundPos(const ofVec2f pos) {
	bounds.setPosition(pos);
}

//-------------------------------------------------------------------------------------------
void ISGUI::IdolVecButton::setButtonPos(const ofVec2f pos) {
	setBoundPos(pos);
	setTextPos(pos); // not centered text
}

//-------------------------------------------------------------------------------------------
void ISGUI::IdolVecButton::setBoundSize(const ofVec2f size) {
	bounds.setSize(size.x, size.y);
}

//-------------------------------------------------------------------------------------------
void ISGUI::IdolVecButton::setFontKerning(const double kern) {
	kerning = kern;
}

//-------------------------------------------------------------------------------------------
void ISGUI::IdolVecButton::setFontFile(string fontDir) {
	fontFile = std::move(fontDir);
}

//-------------------------------------------------------------------------------------------
void ISGUI::IdolVecButton::setTextColor(const ofColor color) {
	textColor = color;
}

//-------------------------------------------------------------------------------------------
void ISGUI::IdolVecButton::setNormColor(const ofColor color) {
	normColor = color;
}

//-------------------------------------------------------------------------------------------
void ISGUI::IdolVecButton::setHoverColor(const ofColor color) {
	hoverColor = color;
}

//-------------------------------------------------------------------------------------------
int ISGUI::IdolVecButton::getFontSize() const {
	return fontSize;
}

//-------------------------------------------------------------------------------------------
bool ISGUI::IdolVecButton::mouseDown() {
	if (pressed) {
		pressed = false;
		return true;
	}
	return false;
}

//-------------------------------------------------------------------------------------------
double ISGUI::IdolVecButton::getFontKerning() const {
	return kerning;
}

//-------------------------------------------------------------------------------------------
string ISGUI::IdolVecButton::getText() const {
	return text;
}

//-------------------------------------------------------------------------------------------
string ISGUI::IdolVecButton::getFontFile() const {
	return fontFile;
}

///////////////////////////////////////////////////////////////////
  /////////////////      Private Functions      ///////////////
///////////////////////////////////////////////////////////////////

void ISGUI::IdolVecButton::onMouseMove(ofMouseEventArgs &mouse) {
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

//-------------------------------------------------------------------------------------------
void ISGUI::IdolVecButton::onMouseDown(ofMouseEventArgs &mouse) {
	if (mouse.button == OF_MOUSE_BUTTON_1) {
		if (isInBounds(mouse.x, mouse.y)) {
			pressed = true;
		}
	}
}

//-------------------------------------------------------------------------------------------
void ISGUI::IdolVecButton::onMouseUp(ofMouseEventArgs &mouse) {
	if (pressed) pressed = false;
}

//-------------------------------------------------------------------------------------------
bool ISGUI::IdolVecButton::isInBounds(const float x, const float y) const {
	return x <= bounds.getRight() && x >= bounds.getLeft() && y <= bounds.getBottom() && y >= bounds.getTop();
}