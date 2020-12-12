#pragma once
#include "enemy.h"

enum class VMageAnimStatus
{
	APPEAR = 0,
	SHOOT = 1,
	CAST = 2,
	DISAPPEAR = 3,
	IDLE = 6
};

class EnVmage : public Enemy
{
public:
	EnVmage();
	EnVmage(glm::vec2 pos, glm::vec2 size, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

	virtual void Update(SpriteRenderer& renderer, float deltatime);

	virtual void Init();

	virtual void CollisionStepped(std::vector<CollObject*> obj);
	virtual void CollisionSticked(std::vector<CollObject*> obj);
protected:
	virtual void ShootBullets(std::string name, bool isIndependent, bool gravity, float damage,
		glm::vec2 pos = glm::vec2(0.0f, 0.0f), float time = 10.0f, glm::vec2 speed = glm::vec2(0.0f, 0.0f), float distance = 1000.0f);
};

