#include "Enemies.h"
#include "GameHandler.h"
#include "WaveHandler.h"
#include <math.h>
#include <iostream>

using namespace std;

Enemies::Enemies(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float size_x, float size_y, float pos_x, float pos_y, sf::Vector2f speed, float MaxHP, float CurrentHP,float damage,int score, EnemyType enemyType,float luckycharm) :
	animation(texture, imageCount, switchTime, 80, 100)
{
	this->body.setSize(sf::Vector2f(size_x, size_y));
	hitbox.setSize(sf::Vector2f(48.0f, 64.0f));
	body.setPosition(pos_x, pos_y);
	hitbox.setPosition(pos_x, pos_y);
	body.setOrigin(this->body.getSize()/2.0f);
	body.setTexture(texture);
	body.setTextureRect(sf::IntRect(0, 0, 60, 100));
	hitbox.setOrigin(hitbox.getSize() / 2.0f);
	this->speed = speed;
	this->prevPos = sf::Vector2f(pos_x, pos_y);
	this->CurrentHP = CurrentHP;
	this->MaxHP = MaxHP;
	this->enemyType = enemyType;
	this->damage = damage;
	this->score = score;
	this->luckycharm = luckycharm;
}

void Enemies::deathEvent() {
	
	int chance = (int)(rand() % (100) + 0);

	if (chance >= (95-this->luckycharm)) { //ITEM DROP
		WaveController.spawnItemsPosition(body.getPosition().x, body.getPosition().y);
		cout << "ITEM DROP" << endl;
	}

	if (enemies_list.size() == 1) { //DEATH LAST GO TO NEXT ROUND
		isNext = true;
		cooldownNext = 4.0f;
		sound_nextR.play();
		WaveController.setAgressiveMode(false);
		WaveController.setAgressiveModeTimer(30);

		if (music_Hard.getStatus() == sf::SoundSource::Status::Playing) {
			music_day.play();
			music_Hard.stop();
		}
	}
	if (!WaveController.isAgressiveMode()) {
		WaveController.setAgressiveModeTimer(30);
	}
	cout << "DEAD ! CURRENT: " << enemies_list.size() << endl;
}

sf::Vector2f Enemies::getArrayPosition() {
	sf::Vector2f ArrayPosition;

	ArrayPosition.x = ((this->body.getPosition().x + (this->body.getSize().x/2.0f)) / 48) - 1;
	ArrayPosition.y = ((this->body.getPosition().y + (this->body.getSize().y/2.0f)) / 48) - 1;

	return ArrayPosition;
}

int Enemies::getAnimationType(sf::Vector2f EnemyPosition, sf::Vector2f playerPosition) {

	if (EnemyPosition.x < playerPosition.x) { // ENEMY -> PLAYER
		if (ISAttack()) {
			if (enemyType == EnemyType::NORMAL) {
				animation.ChangeImageCount(4);
			} else if (enemyType == EnemyType::RANGED) {
				animation.ChangeImageCount(6);
			} else if (enemyType == EnemyType::MINI_BOSS) {
				animation.ChangeImageCount(4);
			} else if (enemyType == EnemyType::KNIGHT) {
				animation.ChangeImageCount(4);
			} else if (enemyType == EnemyType::WIZARD) {
				animation.ChangeImageCount(4);
			}
			return 6;
		}

		if (enemyType == EnemyType::NORMAL) {
			animation.ChangeImageCount(3);
		} else if (enemyType == EnemyType::RANGED) {
			animation.ChangeImageCount(5);
		} else if (enemyType == EnemyType::MINI_BOSS) {
			animation.ChangeImageCount(6);
		} else if (enemyType == EnemyType::KNIGHT) {
			animation.ChangeImageCount(3);
		} else if (enemyType == EnemyType::WIZARD) {
			animation.ChangeImageCount(4);
		}
		return 2;
	} else if (EnemyPosition.x >= playerPosition.x) { // PLAYER <- ENEMY
		if (ISAttack()) {
			if (enemyType == EnemyType::NORMAL) {
				animation.ChangeImageCount(4);
			} else if (enemyType == EnemyType::RANGED) {
				animation.ChangeImageCount(6);
			} else if (enemyType == EnemyType::MINI_BOSS) {
				animation.ChangeImageCount(4);
			} else if (enemyType == EnemyType::KNIGHT) {
				animation.ChangeImageCount(4);
			} else if (enemyType == EnemyType::WIZARD) {
				animation.ChangeImageCount(4);
			}
			return 4;
		}

		if (enemyType == EnemyType::NORMAL) {
			animation.ChangeImageCount(3);
		} else if (enemyType == EnemyType::RANGED) {
			animation.ChangeImageCount(5);
		} else if (enemyType == EnemyType::MINI_BOSS) {
			animation.ChangeImageCount(6);
		} else if (enemyType == EnemyType::KNIGHT) {
			animation.ChangeImageCount(3);
		} else if (enemyType == EnemyType::WIZARD) {
			animation.ChangeImageCount(4);
		}
		return 0;
	}
}

int Enemies::getAnimationHit(int currentAnimation) {
	if (currentAnimation == 0) { //LEFT
		if (enemyType == EnemyType::NORMAL) {
			animation.ChangeImageCount(3);
		} else if (enemyType == EnemyType::RANGED) {
			animation.ChangeImageCount(5);
		} else if (enemyType == EnemyType::MINI_BOSS) {
			animation.ChangeImageCount(6);
		} else if (enemyType == EnemyType::KNIGHT) {
			animation.ChangeImageCount(3);
		} else if (enemyType == EnemyType::WIZARD) {
			animation.ChangeImageCount(4);
		}
		return 1;
	} else if (currentAnimation == 2) { //RIGHT
		if (enemyType == EnemyType::NORMAL) {
			animation.ChangeImageCount(3);
		} else if (enemyType == EnemyType::RANGED) {
			animation.ChangeImageCount(5);
		} else if (enemyType == EnemyType::MINI_BOSS) {
			animation.ChangeImageCount(6);
		} else if (enemyType == EnemyType::KNIGHT) {
			animation.ChangeImageCount(3);
		} else if (enemyType == EnemyType::WIZARD) {
			animation.ChangeImageCount(4);
		}
		return 3;
	} else if (currentAnimation == 4) { //ATTACK LEFT
		if (enemyType == EnemyType::NORMAL) {
			animation.ChangeImageCount(4);
		} else if (enemyType == EnemyType::RANGED) {
			animation.ChangeImageCount(6);
		} else if (enemyType == EnemyType::MINI_BOSS) {
			animation.ChangeImageCount(4);
		} else if (enemyType == EnemyType::KNIGHT) {
			animation.ChangeImageCount(4);
		} else if (enemyType == EnemyType::WIZARD) {
			animation.ChangeImageCount(4);
		}
		return 5;
	} else if (currentAnimation == 6) { //ATTACK RIGHT
		if (enemyType == EnemyType::NORMAL) {
			animation.ChangeImageCount(4);
		} else if (enemyType == EnemyType::RANGED) {
			animation.ChangeImageCount(6);
		} else if (enemyType == EnemyType::MINI_BOSS) {
			animation.ChangeImageCount(4);
		} else if (enemyType == EnemyType::KNIGHT) {
			animation.ChangeImageCount(4);
		} else if (enemyType == EnemyType::WIZARD) {
			animation.ChangeImageCount(4);
		}
		return 7;
	}
}


void Enemies::Test(float deltaTime_Enemy) {
	sf::Vector2f EnemyPosition = body.getPosition();
	sf::Vector2f playerPosition = player.getBody().getPosition();
	animation.Update(7, deltaTime_Enemy, 80, 100);
	//animation.Update(getAnimationType(EnemyPosition, playerPosition), deltaTime_Enemy, 80, 100);

	body.setTextureRect(animation.uvRect);
}

void Enemies::Update(sf::Vector2f playerPosition,float deltaTime_Enemy) {

	sf::Vector2f dir;
	sf::Vector2f EnemyPosition = body.getPosition();

	dir.x = playerPosition.x - EnemyPosition.x;
	dir.y = playerPosition.y - EnemyPosition.y;


	float hyp = sqrt(dir.x * dir.x + dir.y * dir.y);
	dir.x /= hyp;
	dir.y /= hyp;

	EnemyPosition.x += dir.x * this->speed.x;
	EnemyPosition.y += dir.y * this->speed.y;
	
	body.setTextureRect(animation.uvRect);

	if (ISAttack()) {
		bool isAttack_Success = false;
		if (hitCount > 0 && !isDead) {
			if (animation.Update(getAnimationHit(getAnimationType(EnemyPosition, playerPosition)), deltaTime_Enemy, 80, 100)) {
				setIsAttack(false);
				isAttack_Success = true;
			}
			hitCount--;
		} else if (isDead) {
			if (animation.Update(currentDeathAnimation, deltaTime_Enemy * 1.5f, 80, 100)) {
				if (currentDeathAnimation == 9) {
					//cout << "REMOVE" << endl;
					setIsCanremove(true);
					deathEvent();
				}
				currentDeathAnimation = 9;
			}
			return;
		} else {
			if (animation.Update(getAnimationType(EnemyPosition, playerPosition), deltaTime_Enemy, 80, 100)) {
				setIsAttack(false);
				isAttack_Success = true;
			}
		}
		if (isAttack_Success) {
			if (enemyType == EnemyType::RANGED) {
				Effect effect(&particles, sf::Vector2u(3, 10), 0.3f, 0, player.getCurrentPosition());
				effect_list.push_back(effect);
			} else if (enemyType == EnemyType::WIZARD) {
				sf::Vector2f tempPos(player.getCurrentPosition().x, player.getCurrentPosition().y+20);
				Effect effect(&particles, sf::Vector2u(7, 10), 0.3f, 1, tempPos);
				effect_list.push_back(effect);
			}

			if (enemyType != EnemyType::WIZARD) {
				//cout << "ATTACK SUCCESSFUL" << endl;

				float multiple = 1;

				if (WaveController.isAgressiveMode()) {
					multiple = 2;
				}

				if (player.getInvincibleTimer() <= 0) {
					player.setHealth(player.getHealth() - (damage*multiple));
					//cout << "HEALTH: " << player.getHealth() << endl;
					sound_hit_person.play();

					if (player.getHealth() <= 0) {
						player.setIsDead(true);
						sound_lose.play();
					}

				} else {
					sound_block.play();
				}
			}
		}
		return;
	} else {
		if (hitCount > 0 && !isDead) {
			animation.Update(getAnimationHit(getAnimationType(EnemyPosition, playerPosition)), deltaTime_Enemy, 80, 100);
			hitCount--;
		} else if (!isDead) {
			animation.Update(getAnimationType(EnemyPosition, playerPosition), deltaTime_Enemy, 80, 100);
		} else {
			if (animation.Update(currentDeathAnimation, deltaTime_Enemy * 1.5f, 80, 100)) {
				if (currentDeathAnimation == 9) {
					//cout << "REMOVE" << endl;
					setIsCanremove(true);
					deathEvent();
				}
				currentDeathAnimation = 9;
			}
			return;
		}
	}

	double distance = sqrt(pow((playerPosition.x - EnemyPosition.x), 2) + pow((playerPosition.y - EnemyPosition.y), 2));

	if (enemyType == EnemyType::RANGED) {
		if (distance <= 200) {
			if (ISAttack()) { //Attack cant move
				return;
			}
			setIsAttack(true);
			return;
		}
	} else if (enemyType == EnemyType::WIZARD) {
		if (distance <= 299) {
			if (ISAttack()) { //Attack cant move
				return;
			}
			setIsAttack(true);
			return;
		}
	}

	WalkTypes walk = WalkTypes::LEFT;

	if (EnemyPosition.x == this->prevPos.x && EnemyPosition.y == this->prevPos.y) {
		//cout << "NOT MOVE" << endl;
	} else {
		int temp_EnemyX = round(EnemyPosition.x);
		int temp_EnemyY = round(EnemyPosition.y);
		int temp_prevPosEnemyX = round(this->prevPos.x);
		int temp_prevPosEnemyY = round(this->prevPos.y);

		//cout << "Move: " << temp_EnemyX << "," << temp_EnemyY << endl;
		//cout << "PrevMove: " << temp_prevPosEnemyX << "," << temp_prevPosEnemyY << endl;

		if (temp_EnemyX > temp_prevPosEnemyX && temp_EnemyY == temp_prevPosEnemyY) { //เคลื่อนที่ไปทางขวา
			//cout << "Move Right" << endl;
			walk = WalkTypes::RIGHT;
		}
		else if (temp_EnemyX > temp_prevPosEnemyX && temp_EnemyY < temp_prevPosEnemyY) { //เคลื่อนที่ไปทางขวาเฉียงขึ้น
			//cout << "Move UP AND Right" << endl;
			walk = WalkTypes::BACKWARD_RIGHT;
		}
		else if (temp_EnemyX > temp_prevPosEnemyX && temp_EnemyY > temp_prevPosEnemyY) { //เคลื่อนที่ไปทางขวาเฉียงลง
			//cout << "Move DOWN AND Right" << endl;
			walk = WalkTypes::FORWARD_RIGHT;
		}
		else if (temp_EnemyX == temp_prevPosEnemyX && temp_EnemyY > temp_prevPosEnemyY) { //เคลื่อนที่ลง
			//cout << "Move DOWN" << endl;
			walk = WalkTypes::FORWARD;
		}
		else if (temp_EnemyX == temp_prevPosEnemyX && temp_EnemyY < temp_prevPosEnemyY) { //เคลื่อนที่ขึ้น
			//cout << "Move UP" << endl;
			walk = WalkTypes::BACKWARD;
		}
		else if (temp_EnemyX< temp_prevPosEnemyX && temp_EnemyY > temp_prevPosEnemyY) { //เคลื่อนที่ไปทางซ้ายเฉียงลง
			//cout << "Move DOWN AND LEFT" << endl;
			walk = WalkTypes::FORWARD_LEFT;
		}
		else if (temp_EnemyX < temp_prevPosEnemyX && temp_EnemyY < temp_prevPosEnemyY) { //เคลื่อนที่ไปทางซ้ายเฉียงขึ้น
		//	cout << "Move UP AND LEFT" << endl;
			walk = WalkTypes::BACKWARD_LEFT;
		}
		else if (temp_EnemyX < temp_prevPosEnemyX && temp_EnemyY == temp_prevPosEnemyY) { //เคลื่อนที่ไปทางซ้าย
			//cout << "Move LEFT" << endl;
			walk = WalkTypes::LEFT;
		}

		vector<sf::Vector2i> Coordition;
		int indexX = 0;
		int indexY = 0;
		sf::Vector2f vectArr = getArrayPosition();

		int x = (int)round(abs(vectArr.x));
		int y = (int)round(abs(vectArr.y));

		//cout << "ARRAY: " << x << "," << y << endl;
		//cout << "POSITION: " << this->body.getPosition().x << "," << this->body.getPosition().y << endl;
		//cout << "----------------" << endl;

		for (int i = 1; i <= 3; i++) { //Forward hitbox

			if (walk == WalkTypes::LEFT || walk == WalkTypes::RIGHT || walk == WalkTypes::FORWARD || walk == WalkTypes::BACKWARD) {
				if (i == 1) {
					continue;
				}
			}
			if (walk == WalkTypes::LEFT) {
				indexX = (x - 1);
				indexY = (y - 2) + i;
			}
			else if (walk == WalkTypes::RIGHT) {
				indexX = (x + 1);
				indexY = (y - 2) + i;
			}
			else if (walk == WalkTypes::FORWARD || walk == WalkTypes::FORWARD_LEFT || walk == WalkTypes::FORWARD_RIGHT) {
				indexX = (x - 2) + i;
				indexY = (y + 1);
			}
			else if (walk == WalkTypes::BACKWARD || walk == WalkTypes::BACKWARD_LEFT || walk == WalkTypes::BACKWARD_RIGHT) {
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
			if (walk == WalkTypes::FORWARD_LEFT || walk == WalkTypes::FORWARD_RIGHT || walk == WalkTypes::BACKWARD_LEFT || walk == WalkTypes::BACKWARD_RIGHT) {
				indexX = (x - 2) + i;
				indexY = y;
			}
			else {
				break;
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
				Platform Barrier2(nullptr, sf::Vector2f(48.0f, 48.0f), sf::Vector2f((0.0f) + (48.0f * coord.x), (0.0f) + (48.0f * coord.y)));

				if (Barrier2.GetCollinder().CheckCollision(GetCollinder())) { //Intersect Barrier

					/* INTELLIGENT MOVEMENT */
					int BLOCK_STATS_2 = 0;
					int BLOCK_STATS_CURRENT_POSITION = 0;

					WalkTypes walkT = WalkTypes::LEFT;

					if (x < 0 || x >= Map.getVect()[0].size()) {
						return;
					}
					if (y < 0 || y >= Map.getVect().size()) {
						return;
					}

					BLOCK_STATS_CURRENT_POSITION = Map.getVect()[y][x];

					if (EnemyPosition.x < player.getCurrentPosition().x) {
						//cout << " Player are right! ";
						BLOCK_STATS_2 = Map.getVect()[y][x+1];
						walkT = WalkTypes::RIGHT;

					} else if (EnemyPosition.x > player.getCurrentPosition().x) {
						//cout << " Player are left! ";
						BLOCK_STATS_2 = Map.getVect()[y][x-1];
						walkT = WalkTypes::LEFT;
					}
					sf::Vector2f Intelligent_Movement(temp_prevPosEnemyX, temp_prevPosEnemyY);

					if (BLOCK_STATS_2 == 0 && BLOCK_STATS_CURRENT_POSITION == 0) { // Check left And Right

						if (walkT == WalkTypes::RIGHT) {
							Intelligent_Movement.x = Intelligent_Movement.x + 2;
						} else if (walkT == WalkTypes::LEFT) {
							Intelligent_Movement.x = Intelligent_Movement.x - 2;
						}
						
						hitbox.setPosition(sf::Vector2f(Intelligent_Movement.x, Intelligent_Movement.y));
						body.setPosition(sf::Vector2f(Intelligent_Movement.x, Intelligent_Movement.y));
						
						this->prevPos = Intelligent_Movement;
						return;
					} else {
						if (EnemyPosition.y < player.getCurrentPosition().y) {
							BLOCK_STATS_2 = Map.getVect()[y+1][x];
							walkT = WalkTypes::BACKWARD;

						} else if (EnemyPosition.y > player.getCurrentPosition().y) {
							BLOCK_STATS_2 = Map.getVect()[y-1][x];
							walkT = WalkTypes::FORWARD;
						}

						if (BLOCK_STATS_2 == 0 && BLOCK_STATS_CURRENT_POSITION == 0) { // Check lup & Down
							if (walkT == WalkTypes::BACKWARD) {
								Intelligent_Movement.y = Intelligent_Movement.y + 2;
							}
							else if (walkT == WalkTypes::FORWARD) {
								Intelligent_Movement.y = Intelligent_Movement.y - 2;
							}
							
							hitbox.setPosition(sf::Vector2f(Intelligent_Movement.x, Intelligent_Movement.y));
							body.setPosition(sf::Vector2f(Intelligent_Movement.x, Intelligent_Movement.y));
				
							this->prevPos = Intelligent_Movement;
							return;
						}

						return;
					}
				}
			}
		}
 	}

	this->prevPos = EnemyPosition;

	if (GetCollinder().CheckCollision(player.GetCollinder())) {
		setIsAttack(true);
		return;
	} else {
		if (ISAttack()) { //Attack cant move
			return;
		}
	}

	body.setPosition(sf::Vector2f(EnemyPosition.x, EnemyPosition.y));
	hitbox.setPosition(sf::Vector2f(EnemyPosition.x, EnemyPosition.y));

}
