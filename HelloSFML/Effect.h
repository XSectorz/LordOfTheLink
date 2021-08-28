#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"

class Effect
{

public:
	Effect(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);

private:
	Animation animation;
	sf::RectangleShape body;

};

