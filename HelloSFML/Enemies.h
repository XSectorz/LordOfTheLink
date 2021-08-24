#pragma once

#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "Animation.h"

class Enemies
{

public:

	Enemies(sf::Texture* texture, sf::Vector2u imageCount, float switchTime,float size_x, float size_y, float pos_x, float pos_y, sf::Vector2f speed, float MaxHP, float CurrentHP);

	void Update(sf::Vector2f playerPosition, float deltaTime_Enemy);
	void Test(float deltaTime_Enemy);
	void setCurrentHP(float CurrentHP) { this->CurrentHP = CurrentHP; }
	float getCurrentHP() { return this->CurrentHP; }
	void setIsDead(bool isDead) { this->isDead = isDead; }
	void setIsCanremove(bool isCanRemove) { this->isCanRemove = isCanRemove; }
	bool ISDead() { return this->isDead; }
	bool ISCanRemove() { return this->isCanRemove; }
	void setHitCount(int hitCount) { this->hitCount = hitCount; }

	sf::RectangleShape getBody() { return body; }
	sf::RectangleShape getHitbox() { return hitbox; }
	sf::Vector2f getArrayPosition();

	Collider GetCollinder() { return Collider(hitbox); }
private:
	float MaxHP;
	float CurrentHP;
	bool isDead = false;
	bool isCanRemove = false;
	int hitCount = 0;
	sf::RectangleShape body;
	sf::RectangleShape hitbox;
	sf::Vector2f speed;
	sf::Vector2f prevPos;
	Animation animation;
};


