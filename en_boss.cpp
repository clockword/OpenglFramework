#include "en_boss.h"

EnBoss::EnBoss() : Enemy()
{
}

EnBoss::EnBoss(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity) :
	Enemy(pos, size, color, velocity)
{
}

void EnBoss::Update(SpriteRenderer& renderer, float deltatime)
{
	if (!Active || IsDestroyed)
		return;

	if (currentHp <= 0.0f) {
		Active = false;
		IsDestroyed = true;
		return;
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

void EnBoss::Init()
{
	Enemy::Init();
	enType = EnemyType::BOSS;
	anim->SetAnimStatus((int)BossAnimStatus::IDLE);
	ShootDelay = 1.0f;
	shootInterval = ShootDelay;
	AtkDelay = 0.5f;
	atkInterval = AtkDelay;
	MaxHp = 500.0f;
	currentHp = MaxHp;
}