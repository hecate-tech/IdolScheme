#include "../include/Shadow.h"

void Shadow::resize(const int width, const int height) {
	shadowSprite.resize(width, height);
}

//----------------------------------------------------------------------------------
void Shadow::load() {
	shadowSprite.setAnchorPercent(.5, .5);
	shadowSprite.load(shadowDir);
}

//----------------------------------------------------------------------------------
void Shadow::draw(const float x, const float y) const {
	this->shadowSprite.draw(x, y);
}