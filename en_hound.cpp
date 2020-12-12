#include "en_hound.h"

EnHound::EnHound() : Enemy()
{
}

EnHound::EnHound(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity) :
	Enemy(pos, size, color, velocity)
{
}

void EnHound::Update(SpriteRenderer& renderer, float deltatime)
{
}

void EnHound::Init()
{
}

void EnHound::CollisionStepped(std::vector<CollObject*> obj)
{
}

void EnHound::CollisionSticked(std::vector<CollObject*> obj)
{
}
