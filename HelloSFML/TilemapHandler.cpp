#include "TilemapHandler.h"
#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"

using namespace std;

TilemapHandler::TilemapHandler(int mapID,float height,float width,vector<string> data) {
	this->mapID = mapID;
	this->height = height;
	this->width = width;

	for (int i = 0; i < height / 64; i++) { //i = y ���������ŧ�� j = x ������ array ���价ҧ��� * �ѹ���
		vector<int> temp_vect;
		for (int j = 0; j < width / 64; j++) {
			temp_vect.push_back(0); //0 IS NORMAL AREA
			/*if (i == j) {
				temp_vect.push_back(1); //1 IS NORMAL AREA
			} else if ((i % (j+1) == 0)) {
				temp_vect.push_back(1); //1 IS NORMAL AREA
			} else {
				temp_vect.push_back(0); //0 IS NORMAL AREA
			}*/
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