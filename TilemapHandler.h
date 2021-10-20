#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

class TilemapHandler
{

public:
	TilemapHandler(int mapID, float height, float width, vector<string> data);
	void setMapID(int mapID);
	void setVect(vector<vector<int>> vect);
	vector<vector<int>> getVect() { return this->vect; }
	float getHeight() { return this->height; }
	float getWidth() { return this->width; }
	int getMapID() { return this->mapID; }

private:
	int mapID;
	float height;
	float width;
	vector<vector<int>> vect;

};

