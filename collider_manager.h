#pragma once

#include <map>
#include <string>

#include "collider.h"

class ColliderManager
{
public:
	static std::map<std::string, Collider*> Colliders;

	static Collider* LoadCollider(const char* file, std::string name);
	static Collider* GetCollider(std::string name);

	static void FixedUpdate(float deltatime);

	static void Delete();
private:
	ColliderManager() {}

	static Collider* LoadColliderFromFile(const char* filename);
};

