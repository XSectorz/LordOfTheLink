#include "Player.h"
#include "TilemapHandler.h"
#include "Items.h"
#include <iostream>
#include "GameHandler.h"
#include <cmath>

using namespace std;

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
	animation(texture,imageCount,switchTime,60,65)
{
	this->speed = speed;
	this->prevPos = sf::Vector2f(0, 0);
	row = 0;

	body.setSize(sf::Vector2f(57.0f, 64.0f));
	hitbox.setSize(sf::Vector2f(32.0f, 54.0f));
	body.setTexture(texture);
	body.setOrigin(body.getSize() / 2.0f);
	hitbox.setOrigin(hitbox.getSize() / 2.0f);
	body.setTextureRect(sf::IntRect(0, 0, 60, 66));
}



sf::Vector2f randPosition() {
	vector<string> spawnPoint = { "700,480","1159,1109","1200,542","875,974","780,1397"};
	sf::Vector2f position;

	int ran = (rand() % (5) + 0);

	int data_X = stoi(spawnPoint[ran].substr(0, spawnPoint[ran].find(',')));
	int data_Y = stoi(spawnPoint[ran].substr(spawnPoint[ran].find(',') + 1, spawnPoint[ran].length() - 1));

	position.x = data_X;
	position.y = data_Y;

	return position;

}

void Player::reStartPlayer() {

	sf::Vector2f pos = randPosition();

	body.setPosition(pos.x, pos.y);
	hitbox.setPosition(pos.x, pos.y);
	this->speed = 200.0f;
	this->health = 100.0f;
	this->speed_timer = 0.0f;
	this->strength_timer = 0.0f;
	this->cd_shot = 0.25;
	this->score = 0;
	this->Death = false;
	this->selectedItems = 0;
	this->ItemCount[0] = 0;
	this->ItemCount[1] = 0;
	this->ItemCount[2] = 0;
	this->ItemCount[3] = 0;
	body.setTextureRect(sf::IntRect(0, 0, 60, 66));
	row = 0;

}

void Player::nextSelectedItems() {
	this->selectedItems += 1;
	if (this->selectedItems > 3) {
		this->selectedItems = 0;
	}
}

void Player::previousSelectedItems() {
	this->selectedItems -= 1;
	if (this->selectedItems < 0) {
		this->selectedItems = 3;
	}
}

sf::Vector2f Player::getArrayPosition() {
	sf::Vector2f ArrayPosition;
	
	ArrayPosition.x = ((this->body.getPosition().x+28) / 48) -1;
	ArrayPosition.y = ((this->body.getPosition().y+32) / 48) - 1;

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
	WalkTypes WalkType = WalkTypes::IDLE;

	/*if (health <= 0) {
		cout << "DEAD" << endl;
		return WalkType;
	}*/


	//row is Index of animation

	int DataX = 0;
	int DataY = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		row = 5; //Walking left
		isWalking = true;
		DataX = -1;
		WalkType = WalkTypes::LEFT;
	} 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		row = 7; //Walking right
		isWalking = true;
		DataX = +1;
		WalkType = WalkTypes::RIGHT;
	} 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		row = 6; //Walking backward
		isWalking = true;
		DataY = -1;
		WalkType = WalkTypes::BACKWARD;
	} 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		isWalking = true;
		DataY = +1;
		row = 4; //Walking forward
		WalkType = WalkTypes::FORWARD;
	} 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		row = 6;
		isWalking = true;
		DataY = -1;
		WalkType = WalkTypes::BACKWARD_LEFT;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		row = 6;
		isWalking = true;
		DataY = -1;
		WalkType = WalkTypes::BACKWARD_RIGHT;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		row = 4;
		isWalking = true;
		DataY = +1;
		WalkType = WalkTypes::FORWARD_LEFT;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		row = 4;
		isWalking = true;
		DataY = +1;
		WalkType = WalkTypes::FORWARD_RIGHT;
	}

	if (isWalking) {
		//printf("ARRAY: %.1f,%.1f \n", round(abs(vectArr.x)), round(abs(vectArr.y)));

		TilemapHandler Map = Maps[0];

		int x = (int) round(abs(vectArr.x));
		int y = (int) round(abs(vectArr.y));

		//cout << "(" << x << "," << y << ") -> Your position" << endl;
		//cout << "(" << vect.x << "," << vect.y << ") || ARRAY : " << BLOCK_STATS << endl;

		//cout << "X---->" << (0.0f) + (64.0f * vect.x) << "," << (0.0f) + (64.0f * vect.y) << endl;

		bool isCanWalk = true;

		int indexX = 0;
		int indexY = 0;

		vector<sf::Vector2i> Coordition;

		for (int i = 1; i <= 3; i++) { //Forward hitbox

			if (WalkType == WalkTypes::LEFT || WalkType == WalkTypes::RIGHT || WalkType == WalkTypes::FORWARD || WalkType == WalkTypes::BACKWARD) {
				if (i == 1) {
					continue; //เช็คเเค่ 2 บล็อคกันผู้เล่นเดินระหว่างตรงกลาง
				}
			}

			if (WalkType == WalkTypes::LEFT) {
				indexX = (x - 1);
				indexY = (y - 2) + i;
			} else if (WalkType == WalkTypes::RIGHT) {
				indexX = (x + 1);
				indexY = (y - 2 ) + i;
			} else if (WalkType == WalkTypes::FORWARD || WalkType == WalkTypes::FORWARD_LEFT || WalkType == WalkTypes::FORWARD_RIGHT) {
				indexX = (x - 2) + i;
				indexY = (y + 1);
			} else if (WalkType == WalkTypes::BACKWARD || WalkType == WalkTypes::BACKWARD_LEFT || WalkType == WalkTypes::BACKWARD_RIGHT) {
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
			if (WalkType == WalkTypes::FORWARD_LEFT || WalkType == WalkTypes::FORWARD_RIGHT || WalkType == WalkTypes::BACKWARD_LEFT || WalkType == WalkTypes::BACKWARD_RIGHT) {
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
				Platform Barrier2(nullptr, sf::Vector2f(48.0f, 48.0f), sf::Vector2f((0.0f) + (48.0f * coord.x), (0.0f) + (48.0f * coord.y)));

				//Barrier2.Draw(windowRender);

				if (Barrier2.GetCollinder().CheckCollision(player.GetCollinder())) { //Intersect Barrier
					isCanWalk = false;
					break;
				}
			}

			//cout << endl;
		}

		if (isCanWalk) {
			if (WalkType == WalkTypes::LEFT) {
				movement.x -= speed * deltaTime;
			} else if (WalkType == WalkTypes::RIGHT) {
				movement.x += speed * deltaTime;
			} else if (WalkType == WalkTypes::FORWARD) {
				movement.y += speed * deltaTime;
			} else if (WalkType == WalkTypes::BACKWARD) {
				movement.y -= speed * deltaTime;
			} else if (WalkType == WalkTypes::FORWARD_LEFT) {
				movement.x -= speed * deltaTime;
				movement.y += speed * deltaTime;
			} else if (WalkType == WalkTypes::FORWARD_RIGHT) {
				movement.x += speed * deltaTime;
				movement.y += speed * deltaTime;
			} else if (WalkType == WalkTypes::BACKWARD_LEFT) {
				movement.x -= speed * deltaTime;
				movement.y -= speed * deltaTime;
			} else if (WalkType == WalkTypes::BACKWARD_RIGHT) {
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

	animation.Update(row, deltaTime,60,65);
	body.setTextureRect(animation.uvRect);

	for (int i = 0; i < (int)items_list.size(); i++) {
		if (GetCollinder().CheckCollision(items_list[i].GetCollinder())) {
			addItem(items_list[i].GetItemType());
			sound_pickup.play();
			items_list.erase(items_list.begin() + i);
		}
	}

	hitbox.move(movement);
	body.move(movement);
	
	return WalkType;
}
