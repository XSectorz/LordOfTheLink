#pragma once

#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "Animation.h"

class Enemies
{

public:

	Enemies(sf::Texture* texture, sf::Vector2u imageCount, float switchTime,float size_x, float size_y, float pos_x, float pos_y, sf::Vector2f speed);

	void Update(sf::Vector2f playerPosition, float deltaTime_Enemy);
	void Test(float deltaTime_Enemy);
	bool isIntersectOther();

	sf::RectangleShape getBody() { return body; }
	sf::RectangleShape getHitbox() { return hitbox; }
	sf::Vector2f getArrayPosition();

	Collider GetCollinder() { return Collider(hitbox); }
private:
	sf::RectangleShape body;
	sf::RectangleShape hitbox;
	sf::Vector2f speed;
	sf::Vector2f prevPos;
	Animation animation;
};


