#pragma once

#ifndef MENUITEMS_H
#define MENUITEMS_H

#ifndef OFMAIN_H
	#define OFMAIN_H
#include <utility>
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
struct IdolChoice {
	ofxToggle toggle;
	string name;
	bool chosen = false;
	bool prevState = false;
	bool currState = false;
	IdolChoice() = default;
	IdolChoice(string name_, const bool chosen_ = false) : name(std::move(name_)), chosen(chosen_) {}
};

/* @brief - idolDropDown
 * idolDropDown is a structure of
 * choices that can only hold one
 * true value at a time. 
 * Acts like a folding radio!
 */
struct IdolDropDown {
	ofxGuiGroup panel;
	bool folded = true;
	template<typename T>
	using choice_vec = vector<T>;
	IdolDropDown() = default;
};

namespace ISGUI {
	/* @brief - idolSchemeButton
	* this is a new type of button that
	* takes an image and turns it into a
	* functional button. This DOES NOT
	* connect to an ofxGui panel!
	*/
	class IdolButton {
	public:
		IdolButton();
		IdolButton(string normdir, string hoverdir, ofPoint pos, float w, float h);
		virtual ~IdolButton();

		virtual void draw();
		void setImagePosition(ofPoint pos);
		void setImagePosition(float x_, float y_);
		void setImageDirectory(const string& directory);
		void setBounds(const ofPoint xy, float width, float height);
		void set(string normdir, const string &hoverdir, ofPoint pos, float w, float h);
		
		virtual bool mouseDown();

		ofPoint getPosition() const;
		string getImageDirectory() const;
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
		virtual bool isInBounds(float x, float y);
	};


	/* @brief - idolGuiGroup
	 * the ofxGuiGroup of ISGui
	 * it acts like a group of
	 * buttons and other idolScheme
	 * objects.
	 */
	class IdolGuiGroup : public Menu {
	public:
		IdolGuiGroup() = default;

		void draw() override {
			for (auto& button : buttons) {
				button->draw();
			}
		}
		void add(IdolButton* btn) {
			buttons.push_back(btn);
		}
		void add(vector<IdolButton*> btns) {
			for (auto a : btns)
				add(a);
		}
		void clear() {
			buttons.clear();
			buttons.shrink_to_fit();
		}
		vector<IdolButton*> getButtons() const {
			return buttons;
		}
		IdolButton *getButton(const unsigned int index) {
			if (index > buttons.size())
				return new IdolButton();
			return buttons.at(index);
		}
	private:
		vector<IdolButton*> buttons;
	};

	
	class IdolVecButton : public IdolButton {
	public:
		IdolVecButton();
		IdolVecButton(ofVec2f pos, ofVec2f size, string btnText, ofColor nColor = ofColor(255, 255, 255, 255), ofColor hColor = ofColor(0, 0, 0, 255));
		~IdolVecButton();

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

		int getFontSize() const;
		bool mouseDown() override;
		double getFontKerning() const;
		string getText() const;
		string getFontFile() const;
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
		bool isInBounds(float x, float y) const; // purposefully shadowing
	};
}


#endif //!MENUITEMS_H
