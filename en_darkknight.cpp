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
	atkInterval += deltatime;
	if (atkInterval >= AtkDelay)
	{
		atkInterval = 0.0f;
		ShootBullets("darkknight_swd", false, false, 10.0f, glm::vec2(-40.0f, 0.0f), 0.5f);
	}

	if (currentHp >= 0.0f)
		hpBar->Size.x = currentHp / MaxHp;
	hpBar->Position = Position + glm::vec2(0.0f, -60.0f);
	hpBar->Update(renderer, deltatime);
	CollObject::Update(renderer, deltatime);
	for (auto bullet : bullets) {
		if (!bullet.second->IsIndependent) {
			bullet.second->playerPos = Position;
			bullet.second->xFlip = !xFlip;
		}
		bullet.second->Update(renderer, deltatime);
	}
}

void EnDarkknight::Init()
{
	Enemy::Init();
	enType = EnemyType::DARKKNIGHT;
	anim->SetAnimStatus((int)DarkknightAnimStatus::ATK);
	AtkDelay = 1.0f;
	atkInterval = AtkDelay;
	MaxHp = 150.0f;
	currentHp = MaxHp;
	damage = 3.0f;
}

void EnDarkknight::CollisionStepped(std::vector<CollObject*> obj)
{
}

void EnDarkknight::CollisionSticked(std::vector<CollObject*> obj)
{
}
