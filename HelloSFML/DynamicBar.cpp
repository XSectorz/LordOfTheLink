#include "DynamicBar.h"
#include "GameHandler.h"

DynamicBar::DynamicBar(sf::Texture* texture, sf::Vector2f size, float rectX, float rectY) {
	body.setSize(size);
	body.setTexture(texture);
	body.setTextureRect(sf::IntRect(0, 0, rectX, rectY));
}

void DynamicBar::Update() {
	body.setPosition(windowRender.mapPixelToCoords(sf::Vector2i(10, 0)));
}