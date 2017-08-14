#include "FileReader.h"

Reader::Reader()
{
	this->fileName = "";
}

Reader::Reader(string fileName)
{
	this->fileName = fileName;
}

Reader::~Reader()
{
}

string Reader::getType()
{
	return this->type;
}

Vector3 Reader::getPosition()
{
	return this->position;
}

Vector3 Reader::getScale()
{
	return this->scale;
}

Vector3 Reader::getDirection()
{
	return this->direction;
}

bool Reader::readFile(string fileName, vector<GameObject*>& inputVec, int& objectCount, float offsetX, float offsetY)
{
	if (this->fileName == "")
		this->fileName = fileName;

	ifstream myFile(this->fileName);
	string tempString;

	if (!myFile.is_open())
	{
		cout << "Unable to open file." << endl;
		return false;
	}
	while (myFile.good())
	{
		getline(myFile, tempString);
		string::size_type begin = tempString.find_first_not_of(" \f\t\v");

		//Skip empty lines
		if (begin == string::npos)
			continue;

		//Skip commentary lines
		else if (string("#").find(tempString[begin]) != string::npos)
			continue;

		//Skip commentary lines
		else if (string("+").find(tempString[begin]) != string::npos)
		{
			GameObject* go = new GameObject();
			go->type = go->inputType[this->type];
			go->pos = this->position;
			go->scale = this->scale;
			go->dir = this->direction;
			go->dir.Normalize();
			go->active = true;

			inputVec.push_back(go);
			objectCount++;
			continue;
		}

		//Parse lines
		else
		{
			for (int i = 0; i < tempString.size(); i++)
			{
				if (tempString[i] == '=')
				{
					if (tempString.substr(0, i) == "Type")
					{
						type = tempString.substr(i + 1);
					}
					else if (tempString.substr(0, i) == "Position")
					{
						string::size_type pos1, pos2;
						pos1 = tempString.find(",");
						pos2 = tempString.find(",", pos1 + 1);

						float x = stof(tempString.substr(i + 1, pos1));
						float y = stof(tempString.substr(pos1 + 1, pos2));
						float z = stof(tempString.substr(pos2 + 1));

						position.Set(offsetX + x, offsetY + y, z);
					}
					else if (tempString.substr(0, i) == "Scale")
					{
						string::size_type pos1, pos2;
						pos1 = tempString.find(",");
						pos2 = tempString.find(",", pos1 + 1);

						float x = stof(tempString.substr(i + 1, pos1));
						float y = stof(tempString.substr(pos1 + 1, pos2));
						float z = stof(tempString.substr(pos2 + 1));

						scale.Set(x, y, z);
					}
					else if (tempString.substr(0, i) == "Direction")
					{
						string::size_type pos1, pos2;
						pos1 = tempString.find(",");
						pos2 = tempString.find(",", pos1 + 1);

						float x = stof(tempString.substr(i + 1, pos1));
						float y = stof(tempString.substr(pos1 + 1, pos2));
						float z = stof(tempString.substr(pos2 + 1));
						direction.Set(x, y, z);
					}
				}
			}
		}
	}
	return true;
}