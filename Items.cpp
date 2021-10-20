#include "Items.h"

Items::Items(sf::Texture* texture, sf::Vector2f position, int type) {

	body.setSize(sf::Vector2f(35.0f, 55.0f));
	body.setTexture(texture);
	body.setPosition(position);
	body.setOrigin(body.getSize() / 2.0f);
	this->ItemType = type;

	
}