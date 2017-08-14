#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Vector3.h"
#include "../GameObject.h"

using namespace std;

class Reader
{
private:
	string fileName;
	string type;
	Vector3 position;
	Vector3 scale;
	Vector3 direction;

public:
	Reader();
	Reader(string fileName);
	~Reader();

	//Getters
	string getType();
	Vector3 getPosition();
	Vector3 getScale();
	Vector3 getDirection();

	//Voids
	bool readFile(string fileName, vector<GameObject*>& inputVec, int& objectCount, float offsetX, float offsetY);
};