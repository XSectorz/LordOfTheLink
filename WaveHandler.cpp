#include "WaveHandler.h"
#include "GameHandler.h"
#include <iostream>
#include <vector>
#include "Enemies.h"

using namespace std;

WaveHandler::WaveHandler() {

}

void spawnEnemies(vector<Enemies>& enemies_list, int mobsType) {
	int Index;
	float speed_x,speed_y;
	speed_x = (float) (rand() % (4) + 1.25);
	speed_y = (float)(rand() % (4) + 1.25);

	Index = (int) (rand() % (6) + 0);

	sf::Vector2f spawnPos[6] = { {830.5,166.5},{125.4,973.4},{953.3,1768.4},{1793.5,1448.3},{1624.4,458.3},{171.2,1615.3}};
	
	//cout << "Spawn at: " << spawnPos[Index].x << "," << spawnPos[Index].y << endl;

	if (mobsType == 0) {
		Enemies enemy(&mobTexture, sf::Vector2u(3, 10), 0.6f, 80.0f, 100.0f, spawnPos[Index].x, spawnPos[Index].y, sf::Vector2f(speed_x-0.25f, speed_y-0.25f), 40, 40, 3, 8, EnemyType::NORMAL,85); //Enemy Type 1
		enemies_list.push_back(enemy);
	} else if (mobsType == 1) {
		Enemies enemy(&mobTexture_2, sf::Vector2u(5, 10), 0.45f, 80.0f, 100.0f, spawnPos[Index].x, spawnPos[Index].y, sf::Vector2f(speed_x+0.2f, speed_y+0.2f), 30, 30, 4, 15, EnemyType::RANGED,5); //Enemy Type 2
		enemies_list.push_back(enemy);
	} else if (mobsType == 2) {
		Enemies enemy(&mobTexture_3, sf::Vector2u(6, 10), 0.3f, 80.0f, 100.0f, spawnPos[Index].x, spawnPos[Index].y, sf::Vector2f(speed_x + 0.25f, speed_y + 0.25f), 150, 150, 10, 100, EnemyType::MINI_BOSS,10); //Enemy Type 3
		enemies_list.push_back(enemy);
	} else if (mobsType == 3) {
		Enemies enemy(&mobTexture_4, sf::Vector2u(6, 10), 0.45f, 80.0f, 100.0f, spawnPos[Index].x, spawnPos[Index].y, sf::Vector2f(speed_x + 0.25f, speed_y + 0.25f), 80, 80, 5, 20, EnemyType::KNIGHT,5); //Enemy Type 4
		enemies_list.push_back(enemy);
	} else if (mobsType == 4) {
		Enemies enemy(&mobTexture_5, sf::Vector2u(4, 10), 1.f, 80.0f, 100.0f, spawnPos[Index].x, spawnPos[Index].y, sf::Vector2f(speed_x + 0.25f, speed_y + 0.25f), 70, 70, Damage_Wizard, 20, EnemyType::WIZARD,10); //Enemy Type 5
		enemies_list.push_back(enemy);
	}
}

void WaveHandler::spawnItemsPosition(float x,float y) {
	sf::Vector2f spawnPos= { x,y };

	int randItemType = (int)(rand() % (4) + 0);

	if (randItemType == 0) {
		Items items(&items_hp_potion, spawnPos, 0);
		items_list.push_back(items);
	} else if (randItemType == 1) {
		Items items(&items_strength_potion, spawnPos, 1);
		items_list.push_back(items);
	} else if (randItemType == 2) {
		Items items(&items_speed_potion, spawnPos, 2);
		items_list.push_back(items);
	} else if (randItemType == 3) {
		Items items(&items_nuke, spawnPos, 3);
		items_list.push_back(items);
	} else if (randItemType == 4) {
		Items items(&items_shield, spawnPos, 4);
		items_list.push_back(items);
	}
}

void spawnItems(int amount) {

	for (int i = 0; i < amount; i++) {
		int Index = (int)(rand() % (6) + 0);
		sf::Vector2f spawnPos[6] = { {830.5,166.5},{125.4,973.4},{953.3,1768.4},{1793.5,1448.3},{1624.4,458.3},{171.2,1615.3} };

		int randItemType = (int)(rand() % (4) + 0);

		if (randItemType == 0) {
			Items items(&items_hp_potion, spawnPos[Index], 0);
			items_list.push_back(items);
			cout << "SPAWN POTION " << " TYPE: " << 0 << endl;

		}
		else if (randItemType == 1) {
			Items items(&items_strength_potion, spawnPos[Index], 1);
			items_list.push_back(items);
			cout << "SPAWN POTION " << " TYPE: " << 1 << endl;
		}
		else if (randItemType == 2) {
			Items items(&items_speed_potion, spawnPos[Index], 2);
			items_list.push_back(items);
			cout << "SPAWN POTION " << " TYPE: " << 2 << endl;
		}
		else if (randItemType == 3) {
			Items items(&items_nuke, spawnPos[Index], 3);
			items_list.push_back(items);
			cout << "SPAWN POTION " << " TYPE: " << 3 << endl;
		}
		else if (randItemType == 4) {
			Items items(&items_shield, spawnPos[Index], 4);
			items_list.push_back(items);
			cout << "SPAWN POTION " << " TYPE: " << 4 << endl;
		}
		cout << "SPAWN2 " << " TYPE: " << randItemType << endl;
	}

}

void WaveHandler::NextRoundUpdate(int cWave) {
	
	int mobC = getMonsterCount();

	cout << "NEXT WAVE: " << cWave << endl;

	for (int i = 0; i < mobC ; i++) {

		if (cWave % 5 == 0) {
			if (i != 2) {
				continue;
			}
		}
		
		if (cWave >= 10) {
			if (i == 0 || i == 1) {
				continue;
			}
		} else if (cWave >= 1 && cWave <= 5 && cWave % 5 != 0) {
			if (i >= 2) {
				continue;
			}
		}

		int MobCountIndex = getMonsterCountByIndex(i);

		int spawnAmount = MobCountIndex + (((cWave/2)*getMonsterMultipleByIndex(i))+1);

		if (cWave % 5 == 0) {
			spawnAmount = cWave/5;
		}

		if (cWave >= 5) {
			spawnAmount = (spawnAmount / 2)-1;
			if (spawnAmount <= 0) {
				spawnAmount = 1;
			}
		}
		
		cout << "SPAWN MOB: " << i << " Amount: " << spawnAmount << endl;
		for (int j = 0; j < spawnAmount; j++) {
			spawnEnemies(enemies_list, i);
		}
	}

	spawnItems(1);

}
