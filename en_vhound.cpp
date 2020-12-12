#include "en_vhound.h"

EnVhound::EnVhound() : Enemy()
{
}

EnVhound::EnVhound(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity) :
	Enemy(pos, size, color, velocity)
{
}

void EnVhound::Update(SpriteRenderer& renderer, float deltatime)
{
}

void EnVhound::Init()
{
}

void EnVhound::CollisionStepped(std::vector<CollObject*> obj)
{
}

void EnVhound::CollisionSticked(std::vector<CollObject*> obj)
{
}
