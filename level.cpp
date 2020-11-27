#include <fstream>
#include "level.h"
#include "collider_manager.h"
#include "resource_manager.h"

Level::Level()
{
}

Level::~Level()
{
	for (auto obj : objects)
		delete obj.second;
	objects.clear();
	Clear();
}

void Level::Create(std::string file)
{
	std::ifstream fileopen(file.c_str());
	char ch[256];
	std::string str;
	std::vector<std::string> arrstr;

	while (!fileopen.eof())
	{
		std::string name;
		int sort_order;
		int x, y;

		char t = '\0';
		int index = 0;
		fileopen.getline(ch, 256);
		while (index < 256)
		{
			while (index < 256)
			{
				t = ch[index];
				if (t == ' ' || t == '\0')
					break;
				str += t;
			}
			arrstr.push_back(str);
			str.clear();
			if (t == '\0')
				break;
		}
		name = arrstr[0];
		sort_order = std::stoi(arrstr[1]);
		x = std::stoi(arrstr[2]);
		y = std::stoi(arrstr[3]);

		std::string species;
		species = name[0] + name[1];
		std::string obj_name = name;
		obj_name.erase(0, 3);
		if (species == "so") {
			//objects[sort_order] = new GameObject({x,y},{1.0f,1.0f},)
		}
		else if (species == "sc") {

		}
		else if (species == "bg") {

		}
		else if (species == "pl") {

		}
		else if (species == "en") {
			/*nop*/
		}

		//objects[sort_order] = new GameObject();
		//objects[sort_order]->Create();
	}

	this->name = file;
}

void Level::Update(SpriteRenderer & renderer, float deltatime)
{
	//std::map<int, GameObject*>::iterator iter = objects.begin();
	//for (; iter != objects.end(); iter++)
	//{
	//}
	for (auto iter : objects)
		iter.second->Update(renderer, deltatime);
}

void Level::FixedUpdate(float deltatime)
{
	ColliderManager::FixedUpdate(deltatime);
}

void Level::Clear()
{
	ResourceManager::Clear();
	ColliderManager::Delete();
}
