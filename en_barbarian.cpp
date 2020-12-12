#include "en_barbarian.h"

EnBarbarian::EnBarbarian() : Enemy()
{
}

EnBarbarian::EnBarbarian(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity) :
	Enemy(pos, size, color, velocity)
{
}

void EnBarbarian::Update(SpriteRenderer& renderer, float deltatime)
{
}

void EnBarbarian::Init()
{
}

void EnBarbarian::CollisionStepped(std::vector<CollObject*> obj)
{
}

void EnBarbarian::CollisionSticked(std::vector<CollObject*> obj)
{
}
