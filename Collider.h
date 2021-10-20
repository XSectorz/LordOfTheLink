#pragma once
#include <SFML/Graphics.hpp>

class Collider
{

public:
	Collider(sf::RectangleShape body);

	bool CheckCollision(Collider other);
	sf::Vector2f GetPosition() { return body.getPosition(); }
	sf::RectangleShape GetBody() { return body; }
	sf::Vector2f GetHalfSize() { return body.getSize() / 2.0f; }

private:
	sf::RectangleShape body;
};

