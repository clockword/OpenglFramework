#pragma once
#include "enemy.h"

enum class BanditAnimStatus
{
	ATK_UP = 0,
	ATK_DWN,
	SWOON,
	RUN
};

class EnBandit : public Enemy
{
public:
	EnBandit();
	EnBandit(glm::vec2 pos, glm::vec2 size, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

	virtual void Update(SpriteRenderer& renderer, float deltatime);

	virtual void Init();

	virtual void CollisionStepped(std::vector<CollObject*> obj);
	virtual void CollisionSticked(std::vector<CollObject*> obj);
};

