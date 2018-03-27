#include "IdolGuiGroup.h"

//---------------------------------------------------------------------------
void ISGUI::IdolGuiGroup::draw() {
	for (auto& button : buttons)
		button->draw();
}

//---------------------------------------------------------------------------
void ISGUI::IdolGuiGroup::add(IdolButton* btn) {
	buttons.push_back(btn);
}

//---------------------------------------------------------------------------
void ISGUI::IdolGuiGroup::add(vector<IdolButton*> btns) {
	for (auto a : btns)
		add(a);
}

//---------------------------------------------------------------------------
void ISGUI::IdolGuiGroup::clear() {
	buttons.clear();
	buttons.shrink_to_fit();
}

//---------------------------------------------------------------------------
vector<ISGUI::IdolButton*> ISGUI::IdolGuiGroup::getButtons() const {
	return buttons;
}

//---------------------------------------------------------------------------
ISGUI::IdolButton* ISGUI::IdolGuiGroup::getButton(const unsigned int index) {
	if (index > buttons.size())
		return new IdolButton();
	return buttons.at(index);
}