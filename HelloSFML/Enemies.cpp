#include "Enemies.h"
#include "GameHandler.h"
#include <math.h>
#include <iostream>

using namespace std;

Enemies::Enemies(float size_x, float size_y, float pos_x, float pos_y, sf::Vector2f speed) {
	this->body.setSize(sf::Vector2f(size_x, size_y));
	body.setPosition(pos_x, pos_y);
	body.setOrigin(this->body.getSize()/2.0f);
	body.setFillColor(sf::Color::Red);
	this->speed = speed;
	this->prevPos = sf::Vector2f(pos_x, pos_y);
}

sf::Vector2f Enemies::getArrayPosition() {
	sf::Vector2f ArrayPosition;

	ArrayPosition.x = ((this->body.getPosition().x + (this->body.getSize().x/2.0f)) / 64) - 1;
	ArrayPosition.y = ((this->body.getPosition().y + (this->body.getSize().y/2.0f)) / 64) - 1;

	return ArrayPosition;
}

void Enemies::Update(sf::Vector2f playerPosition) {

	sf::Vector2f dir;
	sf::Vector2f EnemyPosition = body.getPosition();

	dir.x = playerPosition.x - EnemyPosition.x;
	dir.y = playerPosition.y - EnemyPosition.y;


	float hyp = sqrt(dir.x * dir.x + dir.y * dir.y);
	dir.x /= hyp;
	dir.y /= hyp;

	EnemyPosition.x += dir.x * this->speed.x;
	EnemyPosition.y += dir.y * this->speed.y;

	if (EnemyPosition.x == this->prevPos.x && EnemyPosition.y == this->prevPos.y) {
		//cout << "NOT MOVE" << endl;
	} else {

		WalkTypes walk = LEFT;

		int temp_EnemyX = round(EnemyPosition.x);
		int temp_EnemyY = round(EnemyPosition.y);
		int temp_prevPosEnemyX = round(this->prevPos.x);
		int temp_prevPosEnemyY = round(this->prevPos.y);

		//cout << "Move: " << temp_EnemyX << "," << temp_EnemyY << endl;
		//cout << "PrevMove: " << temp_prevPosEnemyX << "," << temp_prevPosEnemyY << endl;

		if (temp_EnemyX > temp_prevPosEnemyX && temp_EnemyY == temp_prevPosEnemyY) { //เคลื่อนที่ไปทางขวา
			//cout << "Move Right" << endl;
			walk = RIGHT;
		}
		else if (temp_EnemyX > temp_prevPosEnemyX && temp_EnemyY < temp_prevPosEnemyY) { //เคลื่อนที่ไปทางขวาเฉียงขึ้น
			//cout << "Move UP AND Right" << endl;
			walk = BACKWARD_RIGHT;
		}
		else if (temp_EnemyX > temp_prevPosEnemyX && temp_EnemyY > temp_prevPosEnemyY) { //เคลื่อนที่ไปทางขวาเฉียงลง
			//cout << "Move DOWN AND Right" << endl;
			walk = FORWARD_RIGHT;
		}
		else if (temp_EnemyX == temp_prevPosEnemyX && temp_EnemyY > temp_prevPosEnemyY) { //เคลื่อนที่ลง
			//cout << "Move DOWN" << endl;
			walk = FORWARD;
		}
		else if (temp_EnemyX == temp_prevPosEnemyX && temp_EnemyY < temp_prevPosEnemyY) { //เคลื่อนที่ขึ้น
			//cout << "Move UP" << endl;
			walk = BACKWARD;
		}
		else if (temp_EnemyX< temp_prevPosEnemyX && temp_EnemyY > temp_prevPosEnemyY) { //เคลื่อนที่ไปทางซ้ายเฉียงลง
			//cout << "Move DOWN AND LEFT" << endl;
			walk = FORWARD_LEFT;
		}
		else if (temp_EnemyX < temp_prevPosEnemyX && temp_EnemyY < temp_prevPosEnemyY) { //เคลื่อนที่ไปทางซ้ายเฉียงขึ้น
		//	cout << "Move UP AND LEFT" << endl;
			walk = BACKWARD_LEFT;
		}
		else if (temp_EnemyX < temp_prevPosEnemyX && temp_EnemyY == temp_prevPosEnemyY) { //เคลื่อนที่ไปทางซ้าย
			//cout << "Move LEFT" << endl;
			walk = LEFT;
		}

		vector<sf::Vector2i> Coordition;
		int indexX = 0;
		int indexY = 0;
		sf::Vector2f vectArr = getArrayPosition();

		int x = (int)round(abs(vectArr.x));
		int y = (int)round(abs(vectArr.y));

		for (int i = 1; i <= 3; i++) { //Forward hitbox

			if (walk == LEFT || walk == RIGHT || walk == FORWARD || walk == BACKWARD) {
				if (i == 1) {
					continue;
				}
			}
			if (walk == LEFT) {
				indexX = (x - 1);
				indexY = (y - 2) + i;
			}
			else if (walk == RIGHT) {
				indexX = (x + 1);
				indexY = (y - 2) + i;
			}
			else if (walk == FORWARD || walk == FORWARD_LEFT || walk == FORWARD_RIGHT) {
				indexX = (x - 2) + i;
				indexY = (y + 1);
			}
			else if (walk == BACKWARD || walk == BACKWARD_LEFT || walk == BACKWARD_RIGHT) {
				indexX = (x - 2) + i;
				indexY = (y - 1);
			}
			sf::Vector2i temp_Coordition(indexX, indexY);
			Coordition.push_back(temp_Coordition);
		}

		TilemapHandler Map = Maps[0];

		for (sf::Vector2i coord : Coordition) {

			if (Map.getVect().size() <= coord.y) {
				continue;
			}

			if (Map.getVect()[0].size() <= coord.x) {
				continue;
			}

			int BLOCK_STATS = Map.getVect()[coord.y][coord.x];

			if (BLOCK_STATS == 1) {
				Platform Barrier2(nullptr, sf::Vector2f(64.0f, 64.0f), sf::Vector2f((0.0f) + (64.0f * coord.x), (0.0f) + (64.0f * coord.y)));

				if (Barrier2.GetCollinder().CheckCollision(GetCollinder())) { //Intersect Barrier
					return;
				}
			}
		}
	}

	this->prevPos = EnemyPosition;

	if (GetCollinder().CheckCollision(player.GetCollinder())) {
		//cout << "Attack. " << endl;
		return;
	}

	body.setPosition(sf::Vector2f(EnemyPosition.x, EnemyPosition.y));

}
