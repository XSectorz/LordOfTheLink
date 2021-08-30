#include "Effect.h"
#include "GameHandler.h"

Effect::Effect(sf::Texture* texture, sf::Vector2u imageCount, float switchTime) :
	animation(texture, imageCount, switchTime, 60, 64) {
	body.setSize(sf::Vector2f(64.0f, 64.0f));
	body.setOrigin(this->body.getSize() / 2.0f);
	body.setTexture(texture);
	body.setTextureRect(sf::IntRect(0, 0, 60, 64));
	body.setPosition(player.getBody().getPosition());

}

void Effect::update(float deltaTime_Enemy) {
	if (animation.Update(0, deltaTime_Enemy*1.5f, 60, 64)) {
		setISCanRemove(true);
	}
	this->body.setTextureRect(animation.uvRect);
	this->body.setPosition(sf::Vector2f(player.getBody().getPosition().x,player.getBody().getPosition().y+8));
}