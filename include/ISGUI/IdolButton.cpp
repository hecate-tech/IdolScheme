#include "IdolButton.h"

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
ISGUI::IdolButton::IdolButton(const string& normdir, const string& hoverdir, const ofPoint pos, const float w, const float h) {
	ofAddListener(ofEvents().mousePressed, this, &IdolButton::mouseDownEvent);
	ofAddListener(ofEvents().mouseMoved, this, &IdolButton::mouseMoveEvent);
	ofAddListener(ofEvents().mouseReleased, this, &IdolButton::mouseUpEvent);
	set(normdir, hoverdir, pos, w, h);
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

void ISGUI::IdolButton::setBounds(const ofPoint xy, const float w, const float h) {
	bound.set(xy, w, h);
	width = w;
	height = h;
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
void ISGUI::IdolButton::setImagePosition(const float x, const float y) {
	setImagePosition(ofPoint(x, y));
}

//-------------------------------------------------------------------------------------------
void ISGUI::IdolButton::set(const string& normdir, const string& hoverdir, const ofPoint pos, const float w, const float h) {
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
	} else {
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