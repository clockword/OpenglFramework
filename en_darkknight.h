#pragma once
#include "enemy.h"

enum class DarkknightAnimStatus
{
	ATK = 0,
	ATK_SHD = 1,
	SWOON = 2,
	SWOON_SHD = 3,
	RUN = 4,
	RUN_SHD = 5
};

class EnDarkknight : public Enemy
{
public:
	EnDarkknight();
	EnDarkknight(glm::vec2 pos, glm::vec2 size, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

	virtual void Update(SpriteRenderer& renderer, float deltatime);

	virtual void Init();

	virtual void CollisionStepped(std::vector<CollObject*> obj);
	virtual void CollisionSticked(std::vector<CollObject*> obj);
};

