#include "Effect.h"
#include "GameHandler.h"

Effect::Effect(sf::Texture* texture, sf::Vector2u imageCount, float switchTime,int effectType,sf::Vector2f tempPos) :
	animation(texture, imageCount, switchTime, 60, 64) {
	body.setSize(sf::Vector2f(64.0f, 64.0f));
	body.setOrigin(this->body.getSize() / 2.0f);
	body.setTexture(texture);
	body.setTextureRect(sf::IntRect(0, 0, 64, 60));
	body.setPosition(player.getBody().getPosition());

	this->tempPos = tempPos;
	this->effectType = effectType;

}

void Effect::update(float deltaTime_Enemy) {
	if (animation.Update(this->effectType, deltaTime_Enemy*1.5f, 64, 60)) {

		if (this->effectType == 1) {

			double distance = sqrt(pow((player.getCurrentPosition().x - this->tempPos.x), 2) + pow((player.getCurrentPosition().y - this->tempPos.y), 2));

			if (distance <= 120) {
				player.setHealth(player.getHealth() - Damage_Wizard);

				sound_hit_person.play();

				if (player.getHealth() <= 0) {
					player.setIsDead(true);
					sound_lose.play();
				}
			}
		}

		setISCanRemove(true);
	}
	this->body.setTextureRect(animation.uvRect);
	if (this->effectType == 0) {
		this->body.setPosition(sf::Vector2f(player.getBody().getPosition().x, player.getBody().getPosition().y + 8));
	} else if(this->effectType == 1) {
		this->body.setPosition(this->tempPos);
	}
}