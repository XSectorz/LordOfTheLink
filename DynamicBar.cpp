#include "DynamicBar.h"
#include "GameHandler.h"
#include <math.h>

DynamicBar::DynamicBar(sf::Texture* texture, sf::Vector2f size, float rectX, float rectY,int type) {
	body.setSize(size);
	body.setTexture(texture);
	rect.x = rectX;
	rect.y = rectY;
	this->type_bar = type;
	body.setTextureRect(sf::IntRect(0, 500, rect.x, rect.y));
}

void DynamicBar::Update() {

	if (this->type_bar == 0) {
		if (player.getHealth() <= 0) {
			body.setTextureRect(sf::IntRect(0, 0, rect.x, rect.y));
		}
		else {

			if (ceil(player.getHealth() / 10) * 50 >= 500) {
				body.setTextureRect(sf::IntRect(0, 500, rect.x, rect.y));
			}
			else {
				body.setTextureRect(sf::IntRect(0, ceil(player.getHealth() / 10) * 50, rect.x, rect.y));
			}
		}
		body.setPosition(windowRender.mapPixelToCoords(sf::Vector2i(10, 0)));
	} else if (this->type_bar == 1) {
		if (player.getMana() <= 0) {
			body.setTextureRect(sf::IntRect(0, 0, rect.x, rect.y));
		}
		else {

			if (ceil(player.getMana() / 10) * 50 >= 750) {
				body.setTextureRect(sf::IntRect(0, 750, rect.x, rect.y));
			}
			else {
				body.setTextureRect(sf::IntRect(0, ceil(player.getMana() / 10) * 50, rect.x, rect.y));
			}
		}
		body.setPosition(windowRender.mapPixelToCoords(sf::Vector2i(40, 50)));
	}
}