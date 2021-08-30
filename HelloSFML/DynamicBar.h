#pragma once
#include <SFML/Graphics.hpp>

class DynamicBar
{
public:
	DynamicBar(sf::Texture* texture,sf::Vector2f size,float rectX,float rectY);

	sf::RectangleShape getBody() { return this->body;  }
	void Update();

private:
	sf::RectangleShape body;
	sf::Vector2f rect;
};

