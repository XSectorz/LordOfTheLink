#include "Animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime) {

	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;

	uvRect.width = 60;
	uvRect.height = 66;
}

void Animation::ChangeImageCount(int imageCount) {
	this->imageCount.x = imageCount;
}

Animation::~Animation() {

}

void Animation::Update(int row, float deltaTime) {
	currentImage.y = row;
	totalTime += deltaTime;

	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		currentImage.x++;
		if (currentImage.x >= imageCount.x) {
			currentImage.x = 0;
		}
	}

	//printf("Y = %d, X = %d || IMG Count: %d\n",currentImage.y,currentImage.x,imageCount.x);

	if (currentImage.x >= imageCount.x) {
		currentImage.x = 0;
	}

	uvRect.left = currentImage.x * 60;
	uvRect.top = currentImage.y * 65;
}