#include "en_vhound.h"

EnVhound::EnVhound() : Enemy()
{
}

EnVhound::EnVhound(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity) :
	Enemy(pos, size, color, velocity)
{
}

void EnVhound::Update(SpriteRenderer& renderer, float deltatime)
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
}

void EnVhound::CollisionSticked(std::vector<CollObject*> obj)
{
}
