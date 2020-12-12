#include "en_boss.h"

EnBoss::EnBoss() : Enemy()
{
}

EnBoss::EnBoss(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity) :
	Enemy(pos, size, color, velocity)
{
}

void EnBoss::Update(SpriteRenderer& renderer, float deltatime)
{
}

void EnBoss::Init()
{
}

void EnBoss::CollisionStepped(std::vector<CollObject*> obj)
{
}

void EnBoss::CollisionSticked(std::vector<CollObject*> obj)
{
}
