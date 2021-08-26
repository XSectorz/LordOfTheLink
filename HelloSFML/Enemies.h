#pragma once

#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "Animation.h"


enum class EnemyType { NORMAL, RANGED };

class Enemies
{

public:

	Enemies(sf::Texture* texture, sf::Vector2u imageCount, float switchTime,float size_x, float size_y, float pos_x, float pos_y, sf::Vector2f speed, float MaxHP, float CurrentHP,EnemyType enemyType);

	void Update(sf::Vector2f playerPosition, float deltaTime_Enemy);
	void Test(float deltaTime_Enemy);
	void setCurrentHP(float CurrentHP) { this->CurrentHP = CurrentHP; }
	float getCurrentHP() { return this->CurrentHP; }
	void setIsDead(bool isDead) { this->isDead = isDead; }
	void setIsCanremove(bool isCanRemove) { this->isCanRemove = isCanRemove; }
	void setIsAttack(bool isAttack) { this->isAttack = isAttack; }
	bool ISDead() { return this->isDead; }
	bool ISCanRemove() { return this->isCanRemove; }
	bool ISAttack() { return this->isAttack; }
	void setHitCount(int hitCount) { this->hitCount = hitCount; }
	int getAnimationType(sf::Vector2f EnemyPosition, sf::Vector2f playerPosition);
	int getAnimationHit(int currentAnimation);
	int getCurrentDeathAnimation() { return this->currentDeathAnimation;  }
	void setCurrentDeathAnimation(int currentDeathAnimation) { this->currentDeathAnimation = currentDeathAnimation; }
	sf::RectangleShape getBody() { return body; }
	sf::RectangleShape getHitbox() { return hitbox; }
	sf::Vector2f getArrayPosition();

	Collider GetCollinder() { return Collider(hitbox); }
private:
	float MaxHP;
	float CurrentHP;
	bool isDead = false;
	bool isCanRemove = false;
	bool isAttack = false;
	int hitCount = 0;
	int currentDeathAnimation = 8;
	EnemyType enemyType;
	sf::RectangleShape body;
	sf::RectangleShape hitbox;
	sf::Vector2f speed;
	sf::Vector2f prevPos;
	Animation animation;
};


