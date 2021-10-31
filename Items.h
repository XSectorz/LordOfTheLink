#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"

class Items
{

public:
	//ITEM TYPE 0 = HPPotion 1 = Strength Potion 2 = Speed Potion 3 = Nuke 4 = Shield

	Items(sf::Texture* texture,sf::Vector2f position,int type);
	sf::RectangleShape getBody() { return this->body; }
	Collider GetCollinder() { return Collider(this->body); }
	int GetItemType() { return this->ItemType; }

private:
	sf::RectangleShape body;
	int ItemType;
};

