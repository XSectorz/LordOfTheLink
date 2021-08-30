#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"

class Platform
{

public:
	Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
	
	void Draw(sf::RenderWindow& window);

	sf::RectangleShape getBody() { return this->body; }
	
	Collider GetCollinder() { return Collider(body); }

private:
	sf::RectangleShape body;
};

