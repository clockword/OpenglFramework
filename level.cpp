#include <fstream>
#include "level.h"
#include "collider_manager.h"
#include "resource_manager.h"
#include "en_archer.h"
#include "en_bandit.h"
#include "en_barbarian.h"
#include "en_bomber.h"
#include "en_boss.h"
#include "en_darkknight.h"
#include "en_hound.h"
#include "en_mage.h"
#include "en_shielder.h"
#include "en_varcher.h"
#include "en_vhound.h"
#include "en_vmage.h"
#include "camera.h"

Level::Level() : name(), IsCleared(false), scrWidth(0), scrHeight(0)
{
}

Level::~Level()
{
	for (auto obj : objects)
		delete obj.second;
	objects.clear();
	Clear();
}

void Level::Init()
{
	for (auto obj : objects) {
		obj.second->Init();
		obj.second->Active = true;
	}
}

void Level::Create(std::string filename)
{
	this->name = filename;
	std::string file = "./Resource/Level/" + filename + ".txt";
	std::ifstream fileopen(file.c_str());
	char ch[256];
	std::string str;
	std::vector<std::string> arrstr;
	std::vector<Texture2D> backgrounds;
	bool loadObj = false;

	while (!fileopen.eof())
	{
		char t = '\0';
		int index = 0;
		fileopen.getline(ch, 256);
		while (index < 256)
		{
			while (index < 256)
			{
				t = ch[index++];
				if (t == ' ' || t == '\0')
					break;
				str += t;
			}
			arrstr.push_back(str);
			str.clear();
			if (t == '\0')
				break;
		}
		if (arrstr[0] == "~" || arrstr[0] == "-") {
			if (arrstr[0] == "-")
				back.IsMoving = true;
			loadObj = true;
			arrstr.clear();
			continue;
		}
		if (loadObj)
		{
			std::string name;
			int sort_order;
			int x, y;

			sort_order = std::stoi(arrstr[0]);
			name = arrstr[1];
			x = std::stoi(arrstr[2]);
			y = std::stoi(arrstr[3]);

			std::string species = name;
			species.erase(2, species.size() - 2);
			std::string obj_name = name;
			obj_name.erase(0, 3);

			std::string imagePathBase = "./Resource/Image/";
			std::string vertexPathBase = "./Resource/VertexData/";
			std::string colliderPathBase = "./Resource/ColliderData/";

			std::string imagePath = imagePathBase + obj_name + ".png";
			std::string vertexPath = vertexPathBase + obj_name + ".txt";
			std::string colliderPath = colliderPathBase + obj_name + ".txt";

			if (species == "sc") {
				std::string cPath = colliderPathBase + obj_name + arrstr[4] + ".txt";
				std::string dName = obj_name + arrstr[4];
				objects[sort_order] = new CollObject(glm::vec2(x, y), glm::vec2(2.0f, 2.0f));
				objects[sort_order]->Create(ResourceManager::LoadAnims(vertexPath.c_str(), ResourceManager::GetTexture(obj_name), obj_name),
					ResourceManager::LoadTexture(imagePath.c_str(), true, obj_name), ColliderManager::LoadCollider(cPath.c_str(), dName.c_str()));
				objects[sort_order]->SetAnimStatus(std::stoi(arrstr[4]));

				objects[sort_order]->Type = ObjectType::WALL;
			}
			else if (species == "pl") {
				int size = arrstr.size();
				objects[sort_order] = Camera::player = new Player(glm::vec2(x, y), glm::vec2(2.0f, 2.0f));
				objects[sort_order]->Create(ResourceManager::LoadAnims(vertexPath.c_str(), ResourceManager::GetTexture(obj_name), obj_name),
					ResourceManager::LoadTexture(imagePath.c_str(), true, obj_name), ColliderManager::LoadCollider(colliderPath.c_str(), obj_name));
				for (int i = 4; i < size; i += 3)
				{
					std::string vPath = vertexPathBase + arrstr[i] + ".txt";
					std::string cPath = colliderPathBase + arrstr[i] + ".txt";
					int bSize = std::stoi(arrstr[i + 1]);
					for (int j = 0; j < bSize; ++j) {
						if (arrstr[i + 2] == "B") {
							objects[sort_order]->CreateBullets(arrstr[i], ResourceManager::LoadAnims(vPath.c_str(), ResourceManager::GetTexture(obj_name), arrstr[i]),
								ResourceManager::LoadTexture(imagePath.c_str(), true, obj_name), ColliderManager::LoadCollider(cPath.c_str(), arrstr[i]), ObjectType::P_BULLET, j);
						}
						else if (arrstr[i + 2] == "H") {
							objects[sort_order]->CreateBullets(arrstr[i], ColliderManager::LoadCollider(cPath.c_str(), arrstr[i]), ObjectType::P_HITBOX, j);
						}
					}
				}
			}
			else if (species == "en") {
				int size = arrstr.size();
				if (obj_name == "archer")
					objects[sort_order] = new EnArcher(glm::vec2(x, y), glm::vec2(2.0f, 2.0f));
				else if (obj_name == "bandit")
					objects[sort_order] = new EnBandit(glm::vec2(x, y), glm::vec2(2.0f, 2.0f));
				else if (obj_name == "barbarian")
					objects[sort_order] = new EnBarbarian(glm::vec2(x, y), glm::vec2(2.0f, 2.0f));
				else if (obj_name == "bomber") 
					objects[sort_order] = new EnBomber(glm::vec2(x, y), glm::vec2(2.0f, 2.0f));
				else if (obj_name == "darkknight")
					objects[sort_order] = new EnDarkknight(glm::vec2(x, y), glm::vec2(2.0f, 2.0f));
				else if (obj_name == "hound")
					objects[sort_order] = new EnHound(glm::vec2(x, y), glm::vec2(2.0f, 2.0f));
				else if (obj_name == "mage") 
					objects[sort_order] = new EnMage(glm::vec2(x, y), glm::vec2(2.0f, 2.0f));
				else if (obj_name == "shielder") 
					objects[sort_order] = new EnShielder(glm::vec2(x, y), glm::vec2(2.0f, 2.0f));
				else if (obj_name == "varcher")
					objects[sort_order] = new EnVarcher(glm::vec2(x, y), glm::vec2(2.0f, 2.0f));
				else if (obj_name == "vhound")
					objects[sort_order] = new EnVhound(glm::vec2(x, y), glm::vec2(2.0f, 2.0f));
				else if (obj_name == "vmage")
					objects[sort_order] = new EnVmage(glm::vec2(x, y), glm::vec2(2.0f, 2.0f));
				else if (obj_name == "boss")
					objects[sort_order] = new EnBoss(glm::vec2(x, y), glm::vec2(2.0f, 2.0f));

				objects[sort_order]->Create(ResourceManager::LoadAnims(vertexPath.c_str(), ResourceManager::GetTexture(obj_name), obj_name),
					ResourceManager::LoadTexture(imagePath.c_str(), true, obj_name), ColliderManager::LoadCollider(colliderPath.c_str(), obj_name));

				for (int i = 4; i < size; i += 3)
				{
					std::string vPath = vertexPathBase + arrstr[i] + ".txt";
					std::string cPath = colliderPathBase + arrstr[i] + ".txt";
					int bSize = std::stoi(arrstr[i + 1]);
					for (int j = 0; j < bSize; ++j) {
						if (arrstr[i + 2] == "B") {
							objects[sort_order]->CreateBullets(arrstr[i], ResourceManager::LoadAnims(vPath.c_str(), ResourceManager::GetTexture(obj_name), arrstr[i]),
								ResourceManager::LoadTexture(imagePath.c_str(), true, obj_name), ColliderManager::LoadCollider(cPath.c_str(), arrstr[i]), ObjectType::E_BULLET, j);
						}
						else if (arrstr[i + 2] == "H") {
							objects[sort_order]->CreateBullets(arrstr[i], ColliderManager::LoadCollider(cPath.c_str(), arrstr[i]), ObjectType::E_HITBOX, j);
						}
					}
				}
			}
		}
		else
		{
			bool order = std::stoi(arrstr[0]);
			std::string backgroundPath = "./Resource/Backgrounds/" + arrstr[1] + '/' + arrstr[2] + ".png";
			bool alpha = std::stoi(arrstr[3]);
			std::string name = arrstr[2];

			backgrounds.push_back(ResourceManager::LoadTexture(backgroundPath.c_str(), alpha, name));
			if (arrstr.size() > 4)
			{
				if (arrstr.size() == 7)
					vBack.PushSprite(backgrounds, glm::vec2(std::stof(arrstr[4])), std::stof(arrstr[5]));
				else if (!order)
					back.PushSprite(backgrounds, glm::vec2(std::stof(arrstr[4])), std::stof(arrstr[5]));
				else
					front.PushSprite(backgrounds, glm::vec2(std::stof(arrstr[4])), std::stof(arrstr[5]));
				backgrounds.clear();
			}
		}
		arrstr.clear();
	}

	this->name = filename;
}

void Level::Update(SpriteRenderer & renderer, float deltatime)
{
	back.Update(renderer, deltatime);
	vBack.Update(renderer, deltatime);
	for (auto iter : objects) {
		if (iter.second->Position.x > Camera::posX - (float)scrWidth&&
			iter.second->Position.x < Camera::posX + (float)scrWidth)
			iter.second->Active = true;
		else
			iter.second->Active = false;
		iter.second->Update(renderer, deltatime);
	}
	front.Update(renderer, deltatime);
	if (Camera::player->Position.x >= 10800.0f)
		IsCleared = true;
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
