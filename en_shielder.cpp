#include "en_shielder.h"

EnShielder::EnShielder() : Enemy()
{
}

EnShielder::EnShielder(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity) :
	Enemy(pos, size, color, velocity)
{
}

void EnShielder::Update(SpriteRenderer& renderer, float deltatime)
{
}

void EnShielder::Init()
{
}

void EnShielder::CollisionStepped(std::vector<CollObject*> obj)
{
}

void EnShielder::CollisionSticked(std::vector<CollObject*> obj)
{
}
