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
	shootInterval += deltatime;
	if (shootInterval >= ShootDelay)
	{
		shootInterval = 0.0f;
		ShootBullets("varcher_arrow", true, true, 5.0f, glm::vec2(0.0f, 0.0f), 10.0f, glm::vec2(2000.0f, -400.0f), 3000.0f);
		ShootBullets("varcher_arrow", true, true, 5.0f, glm::vec2(0.0f, 0.0f), 10.0f, glm::vec2(2000.0f, -600.0f), 3000.0f);
		ShootBullets("varcher_arrow", true, true, 5.0f, glm::vec2(0.0f, 0.0f), 10.0f, glm::vec2(2000.0f, -200.0f), 3000.0f);
	}

	if (currentHp >= 0.0f)
		hpBar->Size.x = currentHp / MaxHp;
	hpBar->Position = Position + glm::vec2(0.0f, -60.0f);
	hpBar->Update(renderer, deltatime);
	CollObject::Update(renderer, deltatime);
	for (auto bullet : bullets) {
		bullet.second->Update(renderer, deltatime);
	}
}

void EnVarcher::Init()
{
	Enemy::Init();
	enType = EnemyType::ARCHER;
	anim->SetAnimStatus((int)VArcherAnimStatus::RUN);
	ShootDelay = 1.0f;
	shootInterval = ShootDelay;
	MaxHp = 100.0f;
	currentHp = MaxHp;
	damage = 1.0f;
}

void EnVarcher::CollisionStepped(std::vector<CollObject*> obj)
{
}

void EnVarcher::CollisionSticked(std::vector<CollObject*> obj)
{
}
