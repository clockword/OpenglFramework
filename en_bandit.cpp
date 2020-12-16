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
	if (!Active || IsDestroyed)
		return;

	if (currentHp <= 0.0f) {
		Active = false;
		IsDestroyed = true;
		return;
	}

	int status = anim->GetAnimStatus();
	bool isContinuous = true;
	float speed = 150.0f;

	if (isControl)
	{
		glm::vec2 moveDirection = moveDir;
		status = (int)BanditAnimStatus::RUN;
		glm::vec2 direction(glm::normalize(player->Position - Position));
		float distance = glm::length(player->Position - Position);

		atkInterval += deltatime;

		if (distance <= 1400.0f)
		{
			if (distance <= 60.0f)
			{
				if (atkInterval >= AtkDelay)
				{
					xFlip = direction.x > 0.0f ? true : false;
					atkInterval = 0.0f;
					ShootBullets("bandit_swd", false, false, 5.0f, glm::vec2(15.0f, 0.0f), 0.5f);
					if (Velocity.y == 0.0f)
						status = (int)BanditAnimStatus::ATK_DWN;
					else
						status = (int)BanditAnimStatus::ATK_UP;
					isContinuous = false;
				}
				moveDirection.x = 0.0f;
			}
			else
			{
				moveDirection.x = direction.x < 0.0f ? -speed : speed;
				if(Position.x > player->Position.x + 30.0f || Position.x < player->Position.x - 30.0f)
					xFlip = direction.x < 0.0f ? false : true;
				if (Position.y > player->Position.y + 100.0f && Velocity.y == 0.0f)
					moveDirection.y = -850.0f;
			}
		}

		if (moveDir.y != 0.0f)
			moveDirection.x = xFlip ? speed : -speed;

		Move(moveDirection);
	}
	else
	{
		status = (int)BanditAnimStatus::SWOON;
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
			bullet.second->xFlip = xFlip;
		}
		bullet.second->Update(renderer, deltatime);
	}
}

void EnBandit::Init()
{
	Enemy::Init();
	enType = EnemyType::BANDIT;
	anim->SetAnimStatus((int)BanditAnimStatus::RUN);
	AtkDelay = 1.0f;
	atkInterval = AtkDelay;
	MaxHp = 100.0f;
	currentHp = MaxHp;
	damage = 1.0f;
}

void EnBandit::CollisionStepped(std::vector<CollObject*> obj)
{
	if (obj.size() == 1)
	{
		if (Position.x > obj[0]->Position.x + obj[0]->collider->Width * 0.5f && xFlip && moveDir.y == 0.0f && isControl ||
			Position.x < obj[0]->Position.x - obj[0]->collider->Width * 0.5f && !xFlip && moveDir.y == 0.0f && isControl) {
			moveDir.y += -850.0f;
		}
	}
}

void EnBandit::CollisionSticked(std::vector<CollObject*> obj)
{
	for (auto coll : obj)
	{
		if (Position.x < coll->Position.x && moveDir.x > 0.0f && moveDir.y == 0.0f && isControl ||
			Position.x > coll->Position.x && moveDir.x < 0.0f && moveDir.y == 0.0f && isControl)
			moveDir.y += -850.0f;
	}
}
