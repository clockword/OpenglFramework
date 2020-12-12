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
	atkInterval += deltatime;
	if (atkInterval >= 5.0f)
	{
		atkInterval = 0.0f;
		ShootBullets("bomber_explode", true, false, 0.0f, glm::vec2(45.0f, 0.0f), 0.83f, glm::vec2(0.0f, 0.0f), 10.0f);
	}

	if (currentHp >= 0.0f)
		hpBar->Size.x = currentHp / MaxHp;
	hpBar->Position = Position + glm::vec2(0.0f, -60.0f);
	hpBar->Update(renderer, deltatime);
	CollObject::Update(renderer, deltatime);
	for (auto bullet : bullets) {
		if (!bullet.second->IsIndependent) {
			bullet.second->playerPos = Position;
			bullet.second->xFlip = xFlip;
		}
		bullet.second->Update(renderer, deltatime);
	}
}

void EnBomber::Init()
{
	Enemy::Init();
	enType = EnemyType::BOMBER;
	anim->SetAnimStatus((int)BomberAnimStatus::RUN);
	MaxHp = 30.0f;
	currentHp = MaxHp;
	damage = 1.0f;
	ShootBullets("bomber_bomb", false, false, 0.0f, glm::vec2(45.0f, 0.0f), 10000.0f, glm::vec2(0.0f, 0.0f), 99999999.0f);
	ShootBullets("bomber_bombfire", false, false, 0.0f, glm::vec2(45.0f, -30.0f), 10000.0f, glm::vec2(0.0f, 0.0f), 99999999.0f);
}

void EnBomber::CollisionStepped(std::vector<CollObject*> obj)
{
}

void EnBomber::CollisionSticked(std::vector<CollObject*> obj)
{
}
