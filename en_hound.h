#pragma once
#include "enemy.h"

enum class HoundAnimStatus
{
	ATK = 0,
	DASH,
	SWOON,
	RUN
};

class EnHound : public Enemy
{
	float dash;
public:
	EnHound();
	EnHound(glm::vec2 pos, glm::vec2 size, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

	virtual void Update(SpriteRenderer& renderer, float deltatime);

	virtual void Init();

	virtual void CollisionStepped(std::vector<CollObject*> obj);
	virtual void CollisionSticked(std::vector<CollObject*> obj);
};

