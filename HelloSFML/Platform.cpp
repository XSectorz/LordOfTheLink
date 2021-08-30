#include "Platform.h"
#include "SFML/Graphics.hpp"

Platform::Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position) {
	body.setSize(size);
	body.setTexture(texture);
	body.setPosition(position);
}

void Platform::Draw(sf::RenderWindow& window) {
	window.draw(body);
}