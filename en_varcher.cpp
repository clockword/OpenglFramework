#include "en_varcher.h"

EnVarcher::EnVarcher() : Enemy()
{
}

EnVarcher::EnVarcher(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity) :
	Enemy(pos, size, color, velocity)
{
}

void EnVarcher::Update(SpriteRenderer& renderer, float deltatime)
{
}

void EnVarcher::Init()
{
}

void EnVarcher::CollisionStepped(std::vector<CollObject*> obj)
{
}

void EnVarcher::CollisionSticked(std::vector<CollObject*> obj)
{
}
