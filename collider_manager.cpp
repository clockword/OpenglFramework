#include "collider_manager.h"
#include <fstream>

std::map<std::string, Collider*> ColliderManager::Colliders;

Collider *ColliderManager::LoadCollider(const char* file, std::string name)
{
	int index = 0;
	while(index >= 0)
	{
		name += std::to_string(index++);
		if (Colliders.find(name) == Colliders.end())
			return Colliders[name] = LoadColliderFromFile(file);
	}
	return nullptr;
}

Collider *ColliderManager::GetCollider(std::string name)
{
	return Colliders[name];
}

void ColliderManager::FixedUpdate(float deltatime)
{
	float gravity = 29.43f;
	for (auto iter : Colliders)
	{
		iter.second->gameObject->Velocity.y += gravity;

		glm::vec2 velocity = iter.second->gameObject->Velocity * deltatime;
		glm::vec2 position = glm::vec2(iter.second->X, iter.second->Y) + velocity;

		if (position.y + iter.second->CollY + iter.second->Height * 0.5f > 645.0f) {
			position.y = 645.0f - iter.second->CollY - iter.second->Height * 0.5f;
			iter.second->gameObject->Velocity.y = 0.0f;
		}

		iter.second->X = position.x;
		iter.second->Y = position.y;
		iter.second->gameObject->Position = position;
	}
}

void ColliderManager::Delete()
{
	for (auto iter : Colliders)
		delete iter.second;
	Colliders.clear();
}

Collider *ColliderManager::LoadColliderFromFile(const char* filename)
{
	Collider* coll = new Collider;
	char ch[256];
	std::ifstream file(filename);
	std::string str;

	file.getline(ch, 256);
	int order = 0;
	for (int i = 0; i < 256; ++i)
	{
		if (ch[i] == ' ' || ch[i] == '\0')
		{
			switch (order++)
			{
			case 0: coll->CollX = std::stof(str); break;
			case 1: coll->CollY = std::stof(str); break;
			case 2: coll->Width = std::stof(str); break;
			case 3: coll->Height = std::stof(str); break;
			}
			str.clear();
		}
		else
			str += ch[i];
		if (ch[i] == '\0')
			break;
	}

	file.close();
	return coll;
}
