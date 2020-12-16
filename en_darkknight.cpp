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
	if (!Active || IsDestroyed)
		return;

	if (currentHp <= 0.0f) {
		Active = false;
		IsDestroyed = true;
		return;
	}

	int status = anim->GetAnimStatus();
	bool isContinuous = true;
	float speed = 250.0f;

	if (isControl)
	{
		glm::vec2 moveDirection = moveDir;
		status = (int)DarkknightAnimStatus::RUN;
		glm::vec2 direction(glm::normalize(player->Position - Position));
		float distance = glm::length(player->Position - Position);

		atkInterval += deltatime;


		if (distance <= 125.0f)
		{
			if (atkInterval >= AtkDelay)
			{
				xFlip = direction.x > 0.0f ? true : false;
				atkInterval = 0.0f;
				ShootBullets("darkknight_swd", false, false, 20.0f, glm::vec2(-40.0f, 0.0f), 0.5f);
				status = (int)DarkknightAnimStatus::ATK;
				isContinuous = false;
			}
			moveDirection.x = 0.0f;
		}
		else
		{
			moveDirection.x = xFlip ? speed : -speed;
		}

		Move(moveDirection);
	}
	else
	{
		status = (int)DarkknightAnimStatus::SWOON;
	}

	if (status != anim->GetAnimStatus())
		anim->SetAnimStatus(status, isContinuous);

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
	AtkDelay = 0.8f;
	atkInterval = AtkDelay;
	MaxHp = 150.0f;
	currentHp = MaxHp;
	damage = 3.0f;
}

void EnDarkknight::CollisionStepped(std::vector<CollObject*> obj)
{
	if (obj.size() == 1)
	{
		if (Position.x > obj[0]->Position.x + obj[0]->collider->Width * 0.5f && xFlip && moveDir.y == 0.0f && isControl ||
			Position.x < obj[0]->Position.x - obj[0]->collider->Width * 0.5f && !xFlip && moveDir.y == 0.0f && isControl) {
			xFlip = !xFlip;
		}
	}
}

void EnDarkknight::CollisionSticked(std::vector<CollObject*> obj)
{
	if (obj.size() > 0)
		xFlip = !xFlip;
}
