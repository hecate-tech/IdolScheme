#pragma once

#ifndef MENU_H
	#include "../Menu.h"
#endif //!MENU_H

#ifndef OFMAIN_H
	#include "ofMain.h"
#endif //!OFMAIN_H

#include "IdolButton.h"

namespace ISGUI {
	class IdolVecButton : public IdolButton {
	public:
		IdolVecButton();
		IdolVecButton(ofVec2f pos, ofVec2f size, const string& btnText, ofColor nColor = ofColor(255, 255, 255, 255), ofColor hColor = ofColor(0, 0, 0, 255));
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
		void set(ofVec2f pos, ofVec2f size, const string& btnText, ofColor nColor, ofColor hColor);

		int getFontSize() const;
		bool mouseDown() override;
		double getFontKerning() const;
		string getText() const;
		string getFontFile() const;
	protected:
		double kerning = 1.037;
		int fontSize = 20;
		bool hovering = false;
		bool pressed = false;

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
