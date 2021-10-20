#pragma once

class WaveHandler
{

	static const int monsterCount = 2;

public:
	WaveHandler();
	int getCurrentWave() { return this->CurrentWave; }
	void AddWave() { this->CurrentWave = this->CurrentWave + 1; }
	void setWave(int Wave) { this->CurrentWave = Wave; }
	void NextRoundUpdate(int cWave);
	int getMonsterCount() { return monsterCount; }
	int getMonsterCountByIndex(int index) { return this->arrayMonster[index]; }
	int getMonsterMultipleByIndex(int index) { return this->multipleBy[index]; }

private:
	int CurrentWave = 0;
	int arrayMonster[monsterCount] = { 0,0 }; //0 = MELEE // 1 = RANGED (Count of monster)
	int multipleBy[monsterCount] = {2,1}; //Added count of mob by (x)
};

