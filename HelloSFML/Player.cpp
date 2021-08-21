#include "Player.h"
#include "TilemapHandler.h"
#include <iostream>
#include "GameHandler.h"
#include <cmath>

using namespace std;

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
	animation(texture,imageCount,switchTime)
{
	this->speed = speed;
	this->prevPos = sf::Vector2f(0, 0);
	row = 0;

	body.setPosition(700.0f, 480.0f);
	hitbox.setPosition(700.0f, 480.0f);
	body.setSize(sf::Vector2f(57.0f, 64.0f));
	hitbox.setSize(sf::Vector2f(32.0f, 54.0f));
	body.setTexture(texture);
	body.setOrigin(body.getSize() / 2.0f);
	hitbox.setOrigin(hitbox.getSize() / 2.0f);
	body.setTextureRect(sf::IntRect(0, 0, 60, 66));
}

sf::Vector2f Player::getArrayPosition() {
	sf::Vector2f ArrayPosition;
	
	ArrayPosition.x = ((this->body.getPosition().x+28) / 64) -1;
	ArrayPosition.y = ((this->body.getPosition().y+32) / 64) - 1;

	return ArrayPosition;
}

void Player::setPrevposition(sf::Vector2f prevPos) {
	this->prevPos = prevPos;
}

sf::Vector2f Player::getPrevposition() {
	return this->prevPos;
}

WalkTypes Player::Update(float deltaTime,int rotationType) {
	sf::Vector2f movement(0.0f, 0.0f);
	sf::Vector2f vectArr = getArrayPosition();

	bool isWalking = false;

	WalkTypes WalkType = IDLE;

	//row is Index of animation

	int DataX = 0;
	int DataY = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		row = 5; //Walking left
		isWalking = true;
		DataX = -1;
		WalkType = LEFT;
	} 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		row = 7; //Walking right
		isWalking = true;
		DataX = +1;
		WalkType = RIGHT;
	} 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		row = 6; //Walking backward
		isWalking = true;
		DataY = -1;
		WalkType = BACKWARD;
	} 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		isWalking = true;
		DataY = +1;
		row = 4; //Walking forward
		WalkType = FORWARD;
	} 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		row = 6;
		isWalking = true;
		DataY = -1;
		WalkType = BACKWARD_LEFT;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		row = 6;
		isWalking = true;
		DataY = -1;
		WalkType = BACKWARD_RIGHT;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		row = 4;
		isWalking = true;
		DataY = +1;
		WalkType = FORWARD_LEFT;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		row = 4;
		isWalking = true;
		DataY = +1;
		WalkType = FORWARD_RIGHT;
	}

	if (isWalking) {
		//printf("ARRAY: %.1f,%.1f \n", round(abs(vectArr.x)), round(abs(vectArr.y)));

		TilemapHandler Map = Maps[0];

		int x = (int) round(abs(vectArr.x));
		int y = (int) round(abs(vectArr.y));
		
		//sf::Vector2i CoorditionChecker(x + DataX, y + DataY);
		//sf::Vector2i CoorditionChecker(x, y);
		//setBlockedCoordition(CoorditionChecker);

		//sf::Vector2i vect = getBlockedCoordition();

		//cout << "(" << x << "," << y << ") -> Your position" << endl;
		//cout << "(" << vect.x << "," << vect.y << ") || ARRAY : " << BLOCK_STATS << endl;

		//cout << "X---->" << (0.0f) + (64.0f * vect.x) << "," << (0.0f) + (64.0f * vect.y) << endl;

		bool isCanWalk = true;

		int indexX = 0;
		int indexY = 0;

		vector<sf::Vector2i> Coordition;

		for (int i = 1; i <= 3; i++) { //Forward hitbox

			if (WalkType == LEFT || WalkType == RIGHT || WalkType == FORWARD || WalkType == BACKWARD) {
				if (i == 1) {
					continue; //����� 2 ���ͤ�ѹ�������Թ�����ҧ�ç��ҧ
				}
			}

			if (WalkType == LEFT) {
				indexX = (x - 1);
				indexY = (y - 2) + i;
			} else if (WalkType == RIGHT) {
				indexX = (x + 1);
				indexY = (y - 2 ) + i;
			} else if (WalkType == FORWARD || WalkType == FORWARD_LEFT || WalkType == FORWARD_RIGHT) {
				indexX = (x - 2) + i;
				indexY = (y + 1);
			} else if (WalkType == BACKWARD || WalkType == BACKWARD_LEFT || WalkType == BACKWARD_RIGHT) {
				indexX = (x - 2) + i;
				indexY = (y - 1);
			}
			sf::Vector2i temp_Coordition(indexX, indexY);
			Coordition.push_back(temp_Coordition);
		}

		for (int i = 1; i <= 3; i++) {
			if (i == 2) {
				continue;
			}
			if (WalkType == FORWARD_LEFT || WalkType == FORWARD_RIGHT || WalkType == BACKWARD_LEFT || WalkType == BACKWARD_RIGHT) {
				indexX = (x - 2) + i;
				indexY = y;
			} else {
				break;
			}

			sf::Vector2i temp_Coordition(indexX, indexY);
			Coordition.push_back(temp_Coordition);
		}

		for (sf::Vector2i coord : Coordition) {

			if (Map.getVect().size() <= coord.y) {
				continue;
			}

			if(Map.getVect()[0].size() <= coord.x) {
				continue;
			}

			int BLOCK_STATS = Map.getVect()[coord.y][coord.x];

			//cout << coord.x << "," << coord.y << " " << " -> " << BLOCK_STATS;

			if (BLOCK_STATS == 1) {
				Platform Barrier2(nullptr, sf::Vector2f(64.0f, 64.0f), sf::Vector2f((0.0f) + (64.0f * coord.x), (0.0f) + (64.0f * coord.y)));

				//cout << "Draw: " << (64.0f * coord.x) << " " << (64.0f * coord.y) << endl;

				Barrier2.Draw(windowRender);

				if (Barrier2.GetCollinder().CheckCollision(player.GetCollinder())) { //Intersect Barrier
					isCanWalk = false;
					break;
				}
			}

			//cout << endl;
		}

		if (isCanWalk) {
			if (WalkType == LEFT) {
				movement.x -= speed * deltaTime;
			} else if (WalkType == RIGHT) {
				movement.x += speed * deltaTime;
			} else if (WalkType == FORWARD) {
				movement.y += speed * deltaTime;
			} else if (WalkType == BACKWARD) {
				movement.y -= speed * deltaTime;
			} else if (WalkType == FORWARD_LEFT) {
				movement.x -= speed * deltaTime;
				movement.y += speed * deltaTime;
			} else if (WalkType == FORWARD_RIGHT) {
				movement.x += speed * deltaTime;
				movement.y += speed * deltaTime;
			} else if (WalkType == BACKWARD_LEFT) {
				movement.x -= speed * deltaTime;
				movement.y -= speed * deltaTime;
			} else if (WalkType == BACKWARD_RIGHT) {
				movement.x += speed * deltaTime;
				movement.y -= speed * deltaTime;
			}
		}
	}


	if (this->prevPos == this->body.getPosition()) {
		if (row == 4 || rotationType == 1) {
			row = 0;
		} else if (row == 6 || rotationType == 3) {
			row = 2;
		} else if (row == 7 || rotationType == 4) {
			row = 3;
		} else if (row == 5 || rotationType == 2) {
			row = 1;
		}
	}

	setPrevposition(this->body.getPosition());

	switch (row) {
		case 0:
			animation.ChangeImageCount(3);
			break;
		case 1:
			animation.ChangeImageCount(3);
			break;
		case 2:
			animation.ChangeImageCount(1);
			break;
		case 3:
			animation.ChangeImageCount(3);
			break;
		case 5:
			animation.ChangeImageCount(10);
			break;
		case 7:
			animation.ChangeImageCount(10);
			break;
		case 6:
			animation.ChangeImageCount(10);
			break;
		case 4:
			animation.ChangeImageCount(10);
			break;
		default:
			animation.ChangeImageCount(3);
			break;
	}

	animation.Update(row, deltaTime);
	body.setTextureRect(animation.uvRect);
	body.move(movement);
	hitbox.move(movement);
	return WalkType;
}
