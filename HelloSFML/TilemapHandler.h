#pragma once
#include <iostream>
#include <vector>

using namespace std;

class TilemapHandler
{

public:
	TilemapHandler(int mapID, float height, float width);
	void setMapID(int mapID);
	void setVect(vector<vector<int>> vect);
	vector<vector<int>> getVect();
	int getMapID();
	float getHeight() { return this->height; }
	float getWidth() { return this->width; }

private:
	int mapID;
	float height;
	float width;
	vector<vector<int>> vect;

};

