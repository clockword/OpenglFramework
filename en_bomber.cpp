#include "en_bomber.h"

EnBomber::EnBomber() : Enemy()
{
}

EnBomber::EnBomber(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity) :
	Enemy(pos, size, color, velocity)
{
}

void EnBomber::Update(SpriteRenderer& renderer, float deltatime)
{
}

void EnBomber::Init()
{
}

void EnBomber::CollisionStepped(std::vector<CollObject*> obj)
{
}

void EnBomber::CollisionSticked(std::vector<CollObject*> obj)
{
}
