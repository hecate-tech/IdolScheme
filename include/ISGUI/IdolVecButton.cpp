#include "IdolVecButton.h"

//////////////////////////////////////////////////////////////////////////////////
   //////////////////      Constructors/Desconstructors      //////////////////
//////////////////////////////////////////////////////////////////////////////////

ISGUI::IdolVecButton::IdolVecButton() {
	ofAddListener(ofEvents().mouseMoved, this, &IdolVecButton::onMouseMove);
	ofAddListener(ofEvents().mousePressed, this, &IdolVecButton::onMouseDown);
	ofAddListener(ofEvents().mouseReleased, this, &IdolVecButton::onMouseUp);
}

//-------------------------------------------------------------------------------------------
ISGUI::IdolVecButton::IdolVecButton(const ofVec2f pos, const ofVec2f size, const string& btnText, const ofColor nColor, const ofColor hColor) {
	ofAddListener(ofEvents().mouseMoved, this, &IdolVecButton::onMouseMove);
	ofAddListener(ofEvents().mousePressed, this, &IdolVecButton::onMouseDown);
	ofAddListener(ofEvents().mouseReleased, this, &IdolVecButton::onMouseUp);
	set(pos, size, btnText, nColor, hColor);
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

void ISGUI::IdolVecButton::set(const ofVec2f pos, const ofVec2f size, const string& btnText, const ofColor nColor, const ofColor hColor) {
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
	} else {
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