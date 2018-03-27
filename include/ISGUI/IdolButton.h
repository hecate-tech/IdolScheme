#pragma once

#ifndef MENU_H
	#include "../Menu.h"
#endif //!MENU_H

#ifndef OFMAIN_H
	#include "ofMain.h"
#endif //!OFMAIN_H

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
		IdolButton(const string& normdir, const string& hoverdir, ofPoint pos, float w, float h);
		virtual ~IdolButton();

		virtual void draw();
		void setImagePosition(ofPoint pos);
		void setImagePosition(float x, float y);
		void setImageDirectory(const string& directory);
		void setBounds(ofPoint xy, float w, float h);
		void set(const string& normdir, const string& hoverdir, ofPoint pos, float w, float h);

		virtual bool mouseDown();

		ofPoint getPosition() const;
		string getImageDirectory() const;
	protected:
		ofImage buttonImage;
		ofPoint imagePos;
		ofRectangle bound;
		float width{}, height{};

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
}
