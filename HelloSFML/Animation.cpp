#include "Animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime,int uvRectWidth,int uvRectHeight) {

	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;

	uvRect.width = uvRectWidth;
	uvRect.height = uvRectHeight;
}

void Animation::ChangeImageCount(int imageCount) {
	this->imageCount.x = imageCount;
}

void Animation::Update(int row, float deltaTime,int uvRectLeft,int uvRectTop) {
	currentImage.y = row;
	totalTime += deltaTime;

	//printf("TOTAL: %f/%f\n", deltaTime, switchTime);

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

	uvRect.left = currentImage.x * uvRectLeft;
	uvRect.top = currentImage.y * uvRectTop;
	//printf("CUT AT: %d|%d\n", uvRect.left, uvRect.top);
}
