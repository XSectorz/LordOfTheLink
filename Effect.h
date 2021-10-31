#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"

class Effect
{

public:
	Effect(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, int effectType,sf::Vector2f tempPos);

	void update(float deltaTime_Enemy);
	void setISCanRemove(bool isCanRemove) { this->isCanRemove = isCanRemove;  }
	bool ISCanRemove() { return this->isCanRemove;  }
	int getEffectType() { return this->effectType;  }
	float getTransparentRemove() { return this->transParentRemove; }
	void removeTransparentRemove(float removeCount) { this->transParentRemove = this->transParentRemove - removeCount; }
	sf::Vector2f getPos() { return this->tempPos; }
	sf::RectangleShape getBody() { return this->body;  }

private:

	Animation animation;
	sf::Vector2f tempPos;
	bool isCanRemove = false;
	int effectType = 0;
	float transParentRemove = 100;
	sf::RectangleShape body;

};

