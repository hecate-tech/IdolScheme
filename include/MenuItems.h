#pragma once

#ifndef MENUITEMS_H
#define MENUITEMS_H

#ifndef OFMAIN_H
	#define OFMAIN_H
	#include "ofMain.h"
#endif //!OFMAIN_H

#ifndef OFXGUI_H
	#define OFXGUI_H
	#include "ofxGui.h"
#endif // !OFXGUI_H

#ifndef MENU_H
	#include "Menu.h"
#endif

/* @brief - idolChoice
 * a component of idolDropDown.
 * used as a button inside of it.
 */
struct idolChoice {
public:
	ofxToggle toggle;
	string name;
	bool chosen = false;
	bool prevState = false;
	bool currState = false;
	idolChoice() {}
	idolChoice(string name_, bool chosen_ = false) : name(name_), chosen(chosen_) {}
};

/* @brief - idolDropDown
 * idolDropDown is a structure of
 * choices that can only hold one
 * true value at a time. 
 * Acts like a folding radio!
 */
struct idolDropDown {
public:
	ofxGuiGroup panel;
	bool folded = true;
	template<typename T>
	using choice_vec = vector<T>;
	idolDropDown() {}
};


namespace ISGUI {
	/* @brief - idolSchemeButton
	* this is a new type of button that
	* takes an image and turns it into a
	* functional button. This DOES NOT
	* connect to an ofxGui panel!
	*/
	class idolButton {
	public:
		idolButton() {
			ofAddListener(ofEvents().mousePressed, this, &idolButton::mouseDownEvent);
			ofAddListener(ofEvents().mouseMoved, this, &idolButton::mouseMoveEvent);
			ofAddListener(ofEvents().mouseReleased, this, &idolButton::mouseUpEvent);
			buttonImage.setAnchorPercent(.5, .5);
		}
		idolButton(string normdir, string hoverdir, ofPoint pos, float w, float h) {
			ofAddListener(ofEvents().mousePressed, this, &idolButton::mouseDownEvent);
			ofAddListener(ofEvents().mouseMoved, this, &idolButton::mouseMoveEvent);
			ofAddListener(ofEvents().mouseReleased, this, &idolButton::mouseUpEvent);
			set(normdir, hoverdir, pos, w, h);
			buttonImage.setAnchorPercent(.5, .5);
		}
		~idolButton() {
			ofRemoveListener(ofEvents().mousePressed, this, &idolButton::mouseDownEvent);
			ofRemoveListener(ofEvents().mouseMoved, this, &idolButton::mouseMoveEvent);
			ofRemoveListener(ofEvents().mouseReleased, this, &idolButton::mouseUpEvent);
		}

		void setBounds(const ofPoint xy, float width, float height) {
			bound.set(xy, width, height);
			width = width;
			height = height;
		}

		void setImageDirectory(const string directory) {
			buttonImage.load(directory);
			buttonImage.resize(width, height);
			imageDirectory = directory;
		}

		void setImagePosition(ofPoint pos) {
			imagePos = pos;
			bound.setPosition(ofPoint(pos.x - (width / 2), pos.y - (height / 2)));
		}

		void setImagePosition(float x_, float y_) {
			setImagePosition(ofPoint(x_, y_));
		}

		string getImageDirectory() {
			return imageDirectory;
		}

		void draw() {
			buttonImage.draw(imagePos.x, imagePos.y);
		}

		bool mouseDown() {
			if (pressed) {
				pressed = false;
				return true;
			}
			return false;
		}

		void set(string normdir, string hoverdir, ofPoint pos, float w, float h) {
			buttonImage.load(normdir);
			buttonImage.resize(w, h);
			width = w;
			height = h;
			imagePos = pos;
			bound.set(ofPoint(pos.x - (w / 2), pos.y - (h / 2)), w, h);
			normalDirectory = normdir;
			hoverDirectory = hoverdir;
		}

		ofPoint getPosition() {
			return imagePos;
		}

	protected:
		ofImage buttonImage;
		ofPoint imagePos;
		ofRectangle bound;
		float width, height;

		bool hovering = false;
		bool pressed = false;

		string hoverDirectory;
		string normalDirectory;
	private:
		string imageDirectory; // active directory for image

		void mouseDownEvent(ofMouseEventArgs &mouse) {
			if (mouse.button == OF_MOUSE_BUTTON_1) {
				if (isInBounds(mouse.x, mouse.y)) {
					pressed = true;
				}
			}
		}
		void mouseMoveEvent(ofMouseEventArgs &mouse) {
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
		void mouseUpEvent(ofMouseEventArgs &mouse) {
			if (pressed) pressed = false;
		}
		bool isInBounds(float x, float y) {
			if (x <= bound.getRight()
				&& x >= bound.getLeft()
				&& y <= bound.getBottom()
				&& y >= bound.getTop()) {
				return true;
			}
			return false;
		}
	};

	/* @brief - idolGuiGroup
	 * the ofxGuiGroup of ISGui
	 * it acts like a group of
	 * buttons and other idolScheme
	 * objects.
	 */
	class idolGuiGroup : public Menu {
	public:
		idolGuiGroup() {}

		void draw() override {
			for (unsigned int i = 0; i < buttons.size(); i++) {
				buttons.at(i)->draw();
			}
		}
		void add(idolButton* btn) {
			buttons.push_back(btn);
		}
		void add(vector<idolButton*> btns) {
			for (idolButton* a : btns)
				add(a);
		}
		void clear() {
			buttons.clear();
			buttons.shrink_to_fit();
		}
		vector<idolButton*> getButtons() {
			return buttons;
		}
		idolButton *getButton(int index) {
			if (index > buttons.size())
				return new idolButton();
			return buttons.at(index);
		}
	private:
		vector<idolButton*> buttons;
	};
}


#endif //!MENUITEMS_H
