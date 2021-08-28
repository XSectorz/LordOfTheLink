#include "Effect.h"
#include "GameHandler.h"

Effect::Effect(sf::Texture* texture, sf::Vector2u imageCount, float switchTime) :
	animation(texture, imageCount, switchTime, 80, 100) {
	body.setSize(sf::Vector2f(32.0f, 32.0f));
	body.setOrigin(this->body.getSize() / 2.0f);
	body.setTexture(texture);
	body.setTextureRect(sf::IntRect(0, 0, 50, 50));
	body.setPosition(player.getBody().getPosition());

}