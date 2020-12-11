#include "enemy.h"
#include "camera.h"

Enemy::Enemy() : Player(), player(nullptr), enType(EnemyType::NOTEN)
{
}

Enemy::Enemy(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity) :
	Player(pos, size, color, velocity), player(nullptr), enType(EnemyType::NOTEN)
{
}

void Enemy::Init()
{
	Type = ObjectType::ENEMY;
	player = Camera::player;
	gravity = true;
}
