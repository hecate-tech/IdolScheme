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
		idolButton();
		idolButton(string normdir, string hoverdir, ofPoint pos, float w, float h);
		~idolButton();

		virtual void draw();
		void setImagePosition(ofPoint pos);
		void setImagePosition(float x_, float y_);
		void setImageDirectory(const string directory);
		void setBounds(const ofPoint xy, float width, float height);
		void set(string normdir, string hoverdir, ofPoint pos, float w, float h);
		
		virtual bool mouseDown();

		ofPoint getPosition();
		string getImageDirectory();
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

		void mouseDownEvent(ofMouseEventArgs &mouse);
		void mouseMoveEvent(ofMouseEventArgs &mouse);
		void mouseUpEvent(ofMouseEventArgs &mouse);
		bool isInBounds(float x, float y);
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
		idolButton *getButton(unsigned int index) {
			if (index > buttons.size())
				return new idolButton();
			return buttons.at(index);
		}
	private:
		vector<idolButton*> buttons;
	};

	
	class idolVecButton : public idolButton {
	public:
		idolVecButton();
		idolVecButton(ofVec2f pos, ofVec2f size, string btnText, ofColor nColor = ofColor(255, 255, 255, 255), ofColor hColor = ofColor(0, 0, 0, 255));
		~idolVecButton();

		void draw() override;
		void setFontSize(int size);
		void setText(string newText);
		void setTextPos(ofVec2f pos);
		void setBoundPos(ofVec2f pos);
		void setButtonPos(ofVec2f pos);
		void setBoundSize(ofVec2f size);
		void setFontKerning(double kern);
		void setFontFile(string fontDir);
		void setTextColor(ofColor color);
		void setNormColor(ofColor color);
		void setHoverColor(ofColor color);
		void set(ofVec2f pos, ofVec2f size, string btnText, ofColor nColor, ofColor hColor);

		int getFontSize();
		bool mouseDown() override;
		double getFontKerning();
		string getText();
		string getFontFile();
	protected:
		double kerning = 1.037;
		int fontSize = 20;
		bool hovering = false;
		bool pressed  = false;

		string text = "";
		ofColor normColor;
		ofColor hoverColor;
		ofRectangle bounds;
		ofTrueTypeFont label;
		ofVec2f textPosition;
		ofColor textColor = ofColor(255, 255, 255, 255);
		string fontFile = "verdana.ttf";
	private:
		ofColor currColor;

		void onMouseMove(ofMouseEventArgs &mouse);
		void onMouseDown(ofMouseEventArgs &mouse);
		void onMouseUp(ofMouseEventArgs &mouse);
		bool isInBounds(float x, float y);
	};
}


#endif //!MENUITEMS_H
