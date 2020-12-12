#include "en_vmage.h"

EnVmage::EnVmage() : Enemy()
{
}

EnVmage::EnVmage(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity) :
	Enemy(pos, size, color, velocity)
{
}

void EnVmage::Update(SpriteRenderer& renderer, float deltatime)
{
}

void EnVmage::Init()
{
}

void EnVmage::CollisionStepped(std::vector<CollObject*> obj)
{
}

void EnVmage::CollisionSticked(std::vector<CollObject*> obj)
{
}
