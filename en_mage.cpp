#include "en_mage.h"

EnMage::EnMage() : Enemy()
{
}

EnMage::EnMage(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity) :
	Enemy(pos, size, color, velocity)
{
}

void EnMage::Update(SpriteRenderer& renderer, float deltatime)
{
}

void EnMage::Init()
{
}

void EnMage::CollisionStepped(std::vector<CollObject*> obj)
{
}

void EnMage::CollisionSticked(std::vector<CollObject*> obj)
{
}
