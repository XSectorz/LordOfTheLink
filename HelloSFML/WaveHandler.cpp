#include "WaveHandler.h"
#include "GameHandler.h"
#include <iostream>
#include <vector>
#include "Enemies.h"

using namespace std;

WaveHandler::WaveHandler() {

}

void spawnEnemies(vector<Enemies>& enemies_list, int mobsType) {
	float CoordX, CoordY;
	CoordX = (float)(rand() % ((int)Maps[0].getWidth()) + 0);
	CoordY = (float)(rand() % ((int)Maps[0].getHeight()) + 0);

	if (mobsType == 0) {
		Enemies enemy(&mobTexture, sf::Vector2u(3, 10), 0.3f, 80.0f, 100.0f, CoordX, CoordY, sf::Vector2f(2.0f, 2.0f), 50, 50, 10, 800, EnemyType::NORMAL); //Enemy Type 1
		enemies_list.push_back(enemy);
	}
	else if (mobsType == 1) {
		Enemies enemy(&mobTexture_2, sf::Vector2u(3, 10), 0.3f, 80.0f, 100.0f, CoordX, CoordY, sf::Vector2f(5.0f, 5.0f), 10, 10, 1, 10, EnemyType::RANGED); //Enemy Type 2
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
