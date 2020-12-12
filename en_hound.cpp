#include "en_hound.h"

EnHound::EnHound() : Enemy()
{
}

EnHound::EnHound(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity) :
	Enemy(pos, size, color, velocity)
{
}

void EnHound::Update(SpriteRenderer& renderer, float deltatime)
{
	atkInterval += deltatime;
	if (atkInterval >= AtkDelay)
	{
		atkInterval = 0.0f;
	}

	if (currentHp >= 0.0f)
		hpBar->Size.x = currentHp / MaxHp;
	hpBar->Position = Position + glm::vec2(0.0f, -60.0f);
	hpBar->Update(renderer, deltatime);
	CollObject::Update(renderer, deltatime);
}

void EnHound::Init()
{
	Enemy::Init();
	enType = EnemyType::HOUND;
	anim->SetAnimStatus((int)HoundAnimStatus::RUN);
	AtkDelay = 1.0f;
	atkInterval = AtkDelay;
	MaxHp = 50.0f;
	currentHp = MaxHp;
	damage = 5.0f;
}

void EnHound::CollisionStepped(std::vector<CollObject*> obj)
{
}

void EnHound::CollisionSticked(std::vector<CollObject*> obj)
{
}
