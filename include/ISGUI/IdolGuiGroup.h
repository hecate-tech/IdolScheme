#pragma once

#ifndef MENU_H
	#include "../Menu.h"
#endif //!MENU_H

#ifndef OFMAIN_H
	#include "ofMain.h"
#endif //!OFMAIN_H

#include "IdolButton.h"

namespace ISGUI {
	/* @brief - idolGuiGroup
	* the ofxGuiGroup of ISGui
	* it acts like a group of
	* buttons and other idolScheme
	* objects.
	*/
	class IdolGuiGroup : public Menu {
		vector<IdolButton*> buttons;
	public:
		IdolGuiGroup() = default;

		void draw() override;
		void add(IdolButton* btn);
		void add(vector<IdolButton*> btns);
		void clear();

		vector<IdolButton*> getButtons() const;
		IdolButton *getButton(unsigned int index);
	};
}
