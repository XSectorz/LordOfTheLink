#pragma once

#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"

enum class WalkTypes { LEFT, RIGHT, FORWARD, BACKWARD, FORWARD_LEFT, FORWARD_RIGHT, BACKWARD_LEFT, BACKWARD_RIGHT, IDLE};

class Player
{

public:
	Player(sf::Texture* texture,sf::Vector2u imageCount,float switchTime,float speed);
	//Player(sf::Texture* texture);
	
	WalkTypes Update(float deltaTime,int rotationType);
	void setPrevposition(sf::Vector2f prevPos);
	sf::Vector2f getArrayPosition();
	sf::Vector2f getPrevposition();
	sf::RectangleShape getBody() { return body; }
	sf::RectangleShape getHitbox() { return hitbox; }
	float getHelath() { return this->health;  }
	void setHealth(float health) { this->health = health;  }

	sf::Vector2f getCurrentPosition() { return body.getPosition(); }

	Collider GetCollinder() { return Collider(hitbox); }

private:
	sf::RectangleShape body;
	sf::RectangleShape hitbox;
	unsigned int row;
	float speed;
	float health = 100;
	sf::Vector2f prevPos;
	Animation animation;
};

