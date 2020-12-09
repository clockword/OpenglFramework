#include "enemy.h"
#include "camera.h"

Enemy::Enemy() : Player(), player(nullptr)
{
}

Enemy::Enemy(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity) :
	Player(pos, size, color, velocity), player(nullptr)
{
}

void Enemy::Update(SpriteRenderer& renderer, float deltatime)
{
	CollObject::Update(renderer, deltatime);
}

void Enemy::Init()
{
	Type = ObjectType::ENEMY;
	player = Camera::player;
	anim->SetAnimStatus(3);
}
