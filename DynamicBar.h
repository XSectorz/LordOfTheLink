#pragma once
#include <SFML/Graphics.hpp>

class DynamicBar
{
public:
	DynamicBar(sf::Texture* texture,sf::Vector2f size,float rectX,float rectY,int type);

	sf::RectangleShape getBody() { return this->body;  }
	int getType() { return this->type_bar; }
	void Update();

private:
	int type_bar = 0; //TYPE 0 = HP_BAR , 1 = MANA_BAR
	sf::RectangleShape body;
	sf::Vector2f rect;
};

