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
	float getHealth() { return this->health;  }
	float getCDShot() { return this->cd_shot; }
	float getStrengthTimer() { return this->strength_timer; }
	float getSpeedTimer() { return this->speed_timer; }
	void setCDShot(float cd_shot) { this->cd_shot = cd_shot; }
	void setStrengthTimer(float strength_timer) { this->strength_timer = strength_timer ; }
	void setSpeedTimer(float speed_timer) { this->speed_timer = speed_timer; }
	void addHealth(float health) { 
		this->health += health;
		if (this->health >= 100) {
			this->health = 100;
		}
	}
	void setHealth(float health) { this->health = health;  }
	int getScore() { return this->score;  }
	void addScore(int score) { this->score += score; }
	void addItem(int index) { this->ItemCount[index] += 1; }
	void removeItem(int index) { this->ItemCount[index] -= 1; }
	void setSpeed(float speed) { this->speed = speed; }
	float getSpeed() { return this->speed; }
	float getInvincibleTimer() { return this->invincible_timer; }
	void setInvincibleTimer(float invincible_timer) { this->invincible_timer = invincible_timer; }
	int getItems(int index) { return this->ItemCount[index]; }
	int getSelectedItems() { return this->selectedItems;  }
	void nextSelectedItems();
	void previousSelectedItems();
	void reStartPlayer();
	bool isDead() { return this->Death; }
	void setIsDead(bool isDead) { this->Death = isDead; }

	sf::Vector2f getCurrentPosition() { return body.getPosition(); }

	Collider GetCollinder() { return Collider(hitbox); }

private:
	sf::RectangleShape body;
	sf::RectangleShape hitbox;
	unsigned int row;
	float strength_timer = 0.0f;
	float speed_timer = 0.0f;
	float invincible_timer = 0.0f;
	float speed;
	float health = 100;
	float cd_shot = 0.25;
	bool Death = false;
	int score = 0;
	int selectedItems = 0;
	int ItemCount[5] = {0,0,0,0,0};
	sf::Vector2f prevPos;
	Animation animation;
};

