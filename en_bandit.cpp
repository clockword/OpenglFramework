#include "en_bandit.h"

EnBandit::EnBandit() : Enemy()
{
}

EnBandit::EnBandit(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity) :
	Enemy(pos, size, color, velocity)
{
}

void EnBandit::Update(SpriteRenderer& renderer, float deltatime)
{
	atkInterval += deltatime;
	if (atkInterval >= AtkDelay)
	{
		atkInterval = 0.0f;
		ShootBullets("bandit_swd", false, false, 3.0f, glm::vec2(-15.0f, 0.0f), 0.5f);
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

void EnBandit::Init()
{
	Enemy::Init();
	enType = EnemyType::BANDIT;
	anim->SetAnimStatus((int)BanditAnimStatus::ATK_UP);
	AtkDelay = 1.0f;
	atkInterval = AtkDelay;
	MaxHp = 100.0f;
	currentHp = MaxHp;
	damage = 1.0f;
}

void EnBandit::CollisionStepped(std::vector<CollObject*> obj)
{
}

void EnBandit::CollisionSticked(std::vector<CollObject*> obj)
{
}
