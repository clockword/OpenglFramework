#include "en_barbarian.h"

EnBarbarian::EnBarbarian() : Enemy(), startPos()
{
}

EnBarbarian::EnBarbarian(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity) :
	Enemy(pos, size, color, velocity), startPos()
{
}

void EnBarbarian::Update(SpriteRenderer& renderer, float deltatime)
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
		glm::vec2 direction(glm::normalize(player->Position - Position));
		glm::vec2 moveDirection = moveDir;
		if (status == (int)BarbarianAnimStatus::SWOON)
			xFlip = direction.x < 0.0f ? false : true;
		status = (int)BarbarianAnimStatus::RUN;
		float distance = glm::length(player->Position - Position);

		atkInterval += deltatime;

		if (distance <= 147.0f && (xFlip ? Position.x < player->Position.x : Position.x > player->Position.x))
		{
			if (atkInterval >= AtkDelay)
			{
				atkInterval = 0.0f;
				ShootBullets("barbarian_swd", false, false, 15.0f, glm::vec2(40.0f, 0.0f), 0.5f);
				status = (int)BarbarianAnimStatus::ATK;
				isContinuous = false;
			}
			moveDirection.x = 0.0f;
		}
		else if (distance <= 400.0f && Position.y < player->Position.y + 100.0f && Position.y > player->Position.y - 100.0f &&
			(xFlip ? Position.x < player->Position.x : Position.x > player->Position.x))
		{
			moveDirection.x = direction.x < 0.0f ? -speed : speed;
			xFlip = direction.x < 0.0f ? false : true;
		}
		else
		{
			direction = glm::normalize(startPos - Position);
			if (Position.x < startPos.x + 10.0f && Position.x > startPos.x - 10.0f) {
				moveDirection.x = 0.0f;
			}
			else {
				moveDirection.x = direction.x < 0.0f ? -speed : speed;
				xFlip = direction.x < 0.0f ? false : true;
			}
		}

		Move(moveDirection);
	}
	else
	{
		status = (int)BarbarianAnimStatus::SWOON;
	}

	if (status != anim->GetAnimStatus())
		anim->SetAnimStatus(status, isContinuous);

	if (currentHp >= 0.0f)
		hpBar->Size.x = currentHp / MaxHp;
	hpBar->Position = Position + glm::vec2(0.0f, -100.0f);
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

void EnBarbarian::Init()
{
	Enemy::Init();
	enType = EnemyType::BARBARIAN;
	anim->SetAnimStatus((int)BarbarianAnimStatus::ATK);
	AtkDelay = 1.0f;
	atkInterval = AtkDelay;
	MaxHp = 200.0f;
	currentHp = MaxHp;
	damage = 5.0f;

	startPos = Position;
}

void EnBarbarian::CollisionStepped(std::vector<CollObject*> obj)
{
	if (obj.size() == 1)
	{
		if (Position.x > obj[0]->Position.x + obj[0]->collider->Width * 0.5f && xFlip && moveDir.y == 0.0f && isControl ||
			Position.x < obj[0]->Position.x - obj[0]->collider->Width * 0.5f && !xFlip && moveDir.y == 0.0f && isControl &&
			moveDir.y == 0.0f) {
			moveDir.y += -1000.0f;
		}
	}
}

void EnBarbarian::CollisionSticked(std::vector<CollObject*> obj)
{
	for (auto coll : obj)
	{
		if (Position.x < coll->Position.x && moveDir.x > 0.0f && moveDir.y == 0.0f && isControl ||
			Position.x > coll->Position.x && moveDir.x < 0.0f && moveDir.y == 0.0f && isControl &&
			moveDir.y == 0.0f)
			moveDir.y += -1000.0f;
	}
}
