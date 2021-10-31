#pragma once

class WaveHandler
{

	static const int monsterCount = 5;

public:
	WaveHandler();
	int getCurrentWave() { return this->CurrentWave; }
	void AddWave() { this->CurrentWave = this->CurrentWave + 1; }
	void setWave(int Wave) { this->CurrentWave = Wave; }
	void NextRoundUpdate(int cWave);
	int getMonsterCount() { return monsterCount; }
	int getMonsterCountByIndex(int index) { return this->arrayMonster[index]; }
	int getMonsterMultipleByIndex(int index) { return this->multipleBy[index]; }
	float getAgressiveModeTimer() { return this->agressiveMode; }
	void removeAgressiveModeTimer(float agressiveMode) { this->agressiveMode = this->agressiveMode - agressiveMode; }
	void setAgressiveModeTimer(float agressiveMode) { this->agressiveMode = agressiveMode; }
	bool isAgressiveMode() { return this->isOnAgressiveMode; }
	void setAgressiveMode(bool isAgress) { this->isOnAgressiveMode = isAgress; }

private:
	int CurrentWave = 0;
	float agressiveMode = 30;
	bool isOnAgressiveMode = false;
	int arrayMonster[monsterCount] = { 0,0,0,0,0 }; //0 = MELEE // 1 = RANGED //MINI_BOSS 1  //KNIGHT //WIZARD (Count of monster)
	int multipleBy[monsterCount] = {1,1,1,1,1}; //Added count of mob by (x)
};

