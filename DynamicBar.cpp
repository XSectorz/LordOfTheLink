#include "DynamicBar.h"
#include "GameHandler.h"
#include <math.h>

DynamicBar::DynamicBar(sf::Texture* texture, sf::Vector2f size, float rectX, float rectY) {
	body.setSize(size);
	body.setTexture(texture);
	rect.x = rectX;
	rect.y = rectY;
	body.setTextureRect(sf::IntRect(0, 500, rect.x, rect.y));
}

void DynamicBar::Update() {

	if (player.getHealth() <= 0) {
		body.setTextureRect(sf::IntRect(0, 0, rect.x, rect.y));
	} else {

		if (ceil(player.getHealth() / 10) * 50 >= 500) {
			body.setTextureRect(sf::IntRect(0, 500, rect.x, rect.y));
		} else {
			body.setTextureRect(sf::IntRect(0, ceil(player.getHealth() / 10) * 50, rect.x, rect.y));
		}
	}
	body.setPosition(windowRender.mapPixelToCoords(sf::Vector2i(10, 0)));
}