#pragma once
#include "enemy.h"

enum class BarbarianAnimStatus
{
	ATK = 0,
	SWOON = 2,
	RUN = 3
};

class EnBarbarian : public Enemy
{
public:
	EnBarbarian();
	EnBarbarian(glm::vec2 pos, glm::vec2 size, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

	virtual void Update(SpriteRenderer& renderer, float deltatime);

	virtual void Init();

	virtual void CollisionStepped(std::vector<CollObject*> obj);
	virtual void CollisionSticked(std::vector<CollObject*> obj);
};

