#ifndef Animation_H
#define Animation_H
#include <SFML/Graphics.hpp>

class Animation
{
public:
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, int uvRectWidth, int uvRectHeight);

	void ChangeImageCount(int imageCount);
	bool Update(int row, float deltaTime, int uvRectLeft, int uvRectTop);

public:
	sf::IntRect uvRect;

private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;

	float totalTime;
	float switchTime;
};
#endif



