#include "TilemapHandler.h"
#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"

using namespace std;

TilemapHandler::TilemapHandler(int mapID,float height,float width,vector<string> data) {
	this->mapID = mapID;
	this->height = height;
	this->width = width;

	for (int i = 0; i < height / 48; i++) { //i = y เพราะเป็นเเนวลงมา j = x เพราะเป็น array ที่ไปทางขวา * กันลืม
		vector<int> temp_vect;
		for (int j = 0; j < width / 48; j++) {

			if (i == 0 || j == 0 || j == (width/48)-1 || i == (height/48)-1) { //กันขอบเเมพเป็น 4 เหลี่ยม
				temp_vect.push_back(1);
			} else {
				temp_vect.push_back(0);
			}

			
		}
		this->vect.push_back(temp_vect);
	}

	for (string checker : data) {
		int data_X = stoi(checker.substr(0, checker.find(',')));
		int data_Y = stoi(checker.substr(checker.find(',') + 1, checker.length() - 1));

		sf::Vector2i dataCoordition;
		dataCoordition.x = data_X;
		dataCoordition.y = data_Y;

		this->vect[data_Y][data_X] = 1;
		//cout << data_X << "," << data_Y << endl;
	}
}

void TilemapHandler::setVect(vector<vector<int>> vect) {
	this->vect = vect;
}

void TilemapHandler::setMapID(int mapID) {
	this->mapID = mapID;
}