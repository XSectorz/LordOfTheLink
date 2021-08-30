#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"

class Effect
{

public:
	Effect(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);

	void update(float deltaTime_Enemy);
	void setISCanRemove(bool isCanRemove) { this->isCanRemove = isCanRemove;  }
	bool ISCanRemove() { return this->isCanRemove;  }
	sf::RectangleShape getBody() { return this->body;  }

private:

	Animation animation;
	bool isCanRemove = false;;
	sf::RectangleShape body;

};

