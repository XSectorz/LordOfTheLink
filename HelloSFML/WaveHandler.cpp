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
	speed_x = (float) (rand() % (5) + 1.25);
	speed_y = (float)(rand() % (5) + 1.25);

	Index = (int) (rand() % (6) + 0);

	sf::Vector2f spawnPos[6] = { {830.5,166.5},{125.4,973.4},{953.3,1768.4},{1793.5,1448.3},{1624.4,458.3},{171.2,1615.3}};
	
	//cout << "Spawn at: " << spawnPos[Index].x << "," << spawnPos[Index].y << endl;

	if (mobsType == 0) {
		Enemies enemy(&mobTexture, sf::Vector2u(3, 10), 0.3f, 80.0f, 100.0f, spawnPos[Index].x, spawnPos[Index].y, sf::Vector2f(speed_x-0.5f, speed_y-0.5f), 50, 50, 10, 800, EnemyType::NORMAL); //Enemy Type 1
		enemies_list.push_back(enemy);
	}
	else if (mobsType == 1) {
		Enemies enemy(&mobTexture_2, sf::Vector2u(3, 10), 0.3f, 80.0f, 100.0f, spawnPos[Index].x, spawnPos[Index].y, sf::Vector2f(speed_x+0.25f, speed_y+0.25f), 10, 10, 1, 10, EnemyType::RANGED); //Enemy Type 2
		enemies_list.push_back(enemy);
	}
}

void WaveHandler::NextRoundUpdate(int cWave) {
	
	int mobC = getMonsterCount();

	cout << "NEXT WAVE: " << cWave << endl;

	for (int i = 0; i < mobC ; i++) {
		int MobCountIndex = getMonsterCountByIndex(i);

		int spawnAmount = MobCountIndex + (cWave*getMonsterMultipleByIndex(i));
		
		cout << "SPAWN MOB: " << i << " Amount: " << spawnAmount << endl;
		for (int j = 0; j < spawnAmount; j++) {
			spawnEnemies(enemies_list, i);
		}
	}

}
