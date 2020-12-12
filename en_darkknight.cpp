#include "en_darkknight.h"

EnDarkknight::EnDarkknight() : Enemy()
{
}

EnDarkknight::EnDarkknight(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity) :
	Enemy(pos, size, color, velocity)
{
}

void EnDarkknight::Update(SpriteRenderer& renderer, float deltatime)
{
}

void EnDarkknight::Init()
{
}

void EnDarkknight::CollisionStepped(std::vector<CollObject*> obj)
{
}

void EnDarkknight::CollisionSticked(std::vector<CollObject*> obj)
{
}
