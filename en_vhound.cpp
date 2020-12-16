#include "en_vhound.h"

EnVhound::EnVhound() : Enemy(), dash(0.0f)
{
}

EnVhound::EnVhound(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity) :
	Enemy(pos, size, color, velocity), dash(0.0f)
{
}

void EnVhound::Update(SpriteRenderer& renderer, float deltatime)
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
	float speed = 450.0f;

	if (isControl)
	{
		glm::vec2 moveDirection = moveDir;
		status = (int)VHoundAnimStatus::RUN;
		glm::vec2 direction(glm::normalize(player->Position - Position));
		float distance = glm::length(player->Position - Position);

		if (moveDirection.y == 0.0f)
			dash = 1.0f;

		if (xFlip ? Position.x > player->Position.x - 300.0f && Position.x < player->Position.x + 50.0f :
		Position.x > player->Position.x - 50.0f && Position.x < player->Position.x + 300.0f && Velocity.y == 0.0f) {
			moveDirection.y = -600.0f;
			dash = 3.0f;
		}

		if (dash == 3.0f)
			status = (int)VHoundAnimStatus::DASH;

		moveDirection.x = xFlip ? speed * dash : -speed * dash;

		Move(moveDirection);
	}
	else
	{
		status = (int)VHoundAnimStatus::SWOON;
	}

	if (status != anim->GetAnimStatus())
		anim->SetAnimStatus(status, isContinuous);


	if (currentHp >= 0.0f)
		hpBar->Size.x = currentHp / MaxHp;
	hpBar->Position = Position + glm::vec2(0.0f, -60.0f);
	hpBar->Update(renderer, deltatime);
	CollObject::Update(renderer, deltatime);
}

void EnVhound::Init()
{
	Enemy::Init();
	enType = EnemyType::V_HOUND;
	anim->SetAnimStatus((int)VHoundAnimStatus::RUN);
	AtkDelay = 1.0f;
	atkInterval = AtkDelay;
	MaxHp = 100.0f;
	currentHp = MaxHp;
	damage = 10.0f;
}

void EnVhound::CollisionStepped(std::vector<CollObject*> obj)
{
	if (obj.size() == 1)
	{
		if (Position.x > obj[0]->Position.x + obj[0]->collider->Width * 0.5f && xFlip && moveDir.y == 0.0f && isControl ||
			Position.x < obj[0]->Position.x - obj[0]->collider->Width * 0.5f && !xFlip && moveDir.y == 0.0f && isControl) {
			xFlip = !xFlip;
		}
	}
}

void EnVhound::CollisionSticked(std::vector<CollObject*> obj)
{
	if (obj.size() > 0)
		xFlip = !xFlip;
}
