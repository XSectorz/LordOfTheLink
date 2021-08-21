#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"

class Enemies
{

public:

	Enemies(float size_x, float size_y, float pos_x, float pos_y, sf::Vector2f speed);

	void Update(sf::Vector2f playerPosition);

	sf::RectangleShape getBody() { return this->body; }
	sf::Vector2f getArrayPosition();

	Collider GetCollinder() { return Collider(body); }
private:
	sf::RectangleShape body;
	sf::Vector2f speed;
	sf::Vector2f prevPos;
};

