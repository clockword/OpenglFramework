#include "en_archer.h"

EnArcher::EnArcher() : Enemy()
{
}

EnArcher::EnArcher(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity) :
	Enemy(pos, size, color, velocity)
{
}

void EnArcher::Update(SpriteRenderer& renderer, float deltatime)
{
	if (!Active || IsDestroyed)
		return;

	if (currentHp <= 0.0f) {
		Active = false;
		IsDestroyed = true;
		return;
	}

	int status = anim->GetAnimStatus();
	bool isContinuous = true;
	float speed = 200.0f;

	if (isControl)
	{
		glm::vec2 moveDirection = moveDir;
		status = (int)ArcherAnimStatus::RUN;
		glm::vec2 direction(glm::normalize(player->Position - Position));
		float distance = glm::length(player->Position - Position);

		shootInterval += deltatime;

		if (distance <= 300.0f)
		{
			xFlip = direction.x > 0.0f ? false : true;
			moveDirection.x = xFlip ? speed : -speed;
		}
		else if (distance <= 600.0f)
			moveDirection.x = 0.0f;

		if (distance <= 600.0f && shootInterval >= ShootDelay)
		{
			xFlip = direction.x > 0.0f ? true : false;
			shootInterval = 0.0f;
			ShootBullets("arrow", true, true, 1.0f, glm::vec2(0.0f, 0.0f), 10.0f, glm::vec2(2000.0f, -400.0f), 3000.0f);
			status = (int)ArcherAnimStatus::SHOOT;
			isContinuous = false;
		}

		Move(moveDirection);
	}
	else
	{
		status = (int)ArcherAnimStatus::SWOON;
	}

	if (status != anim->GetAnimStatus())
		anim->SetAnimStatus(status, isContinuous);

	CollObject::Update(renderer, deltatime);
	for (auto bullet : bullets) {
		bullet.second->Update(renderer, deltatime);
	}
}

void EnArcher::Init()
{
	Enemy::Init();
	anim->SetAnimStatus((int)ArcherAnimStatus::RUN);
	ShootDelay = 1.5f;
	shootInterval = ShootDelay;
	MaxHp = 100.0f;
	currentHp = MaxHp;
}