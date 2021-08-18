#include "TilemapHandler.h"
#include <iostream>
#include <vector>

using namespace std;

TilemapHandler::TilemapHandler(int mapID,float height,float width) {
	this->mapID = mapID;
	this->height = height;
	this->width = width;

	for (int i = 0; i < height / 64; i++) {
		vector<int> temp_vect;
		for (int j = 0; j < width / 64; j++) {
			if (i == j) {
				temp_vect.push_back(1); //1 IS NORMAL AREA
			} else if ((i % (j+1) == 0)) {
				temp_vect.push_back(1); //1 IS NORMAL AREA
			} else {
				temp_vect.push_back(0); //0 IS NORMAL AREA
			}
			
		}
		this->vect.push_back(temp_vect);
	}
}

vector<vector<int>> TilemapHandler::getVect() {
	return this->vect;
}

void TilemapHandler::setVect(vector<vector<int>> vect) {
	this->vect = vect;
}

void TilemapHandler::setMapID(int mapID) {
	this->mapID = mapID;
}

int TilemapHandler::getMapID() {
	return this->mapID;
}