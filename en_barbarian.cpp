#include "en_barbarian.h"

EnBarbarian::EnBarbarian() : Enemy()
{
}

EnBarbarian::EnBarbarian(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity) :
	Enemy(pos, size, color, velocity)
{
}

void EnBarbarian::Update(SpriteRenderer& renderer, float deltatime)
{
	atkInterval += deltatime;
	if (atkInterval >= AtkDelay)
	{
		atkInterval = 0.0f;
		ShootBullets("barbarian_swd", false, false, 10.0f, glm::vec2(-40.0f, 0.0f), 0.5f);
		xFlip = !xFlip;
	}

	if (currentHp >= 0.0f)
		hpBar->Size.x = currentHp / MaxHp;
	hpBar->Position = Position + glm::vec2(0.0f, -100.0f);
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

void EnBarbarian::Init()
{
	Enemy::Init();
	enType = EnemyType::BARBARIAN;
	anim->SetAnimStatus((int)BarbarianAnimStatus::ATK);
	AtkDelay = 1.0f;
	atkInterval = AtkDelay;
	MaxHp = 200.0f;
	currentHp = MaxHp;
	damage = 3.0f;
}

void EnBarbarian::CollisionStepped(std::vector<CollObject*> obj)
{
}

void EnBarbarian::CollisionSticked(std::vector<CollObject*> obj)
{
}
