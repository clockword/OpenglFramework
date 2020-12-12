#include "en_mage.h"

EnMage::EnMage() : Enemy()
{
}

EnMage::EnMage(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity) :
	Enemy(pos, size, color, velocity)
{
}

void EnMage::Update(SpriteRenderer& renderer, float deltatime)
{
	shootInterval += deltatime;
	if (shootInterval >= ShootDelay)
	{
		shootInterval = 0.0f;
		ShootBullets("mage_fire", true, false, 10.0f, glm::vec2(0.0f, 0.0f), 10.0f, glm::vec2(300.0f, 0.0f));
	}

	if (currentHp >= 0.0f)
		hpBar->Size.x = currentHp / MaxHp;
	hpBar->Position = Position + glm::vec2(0.0f, -60.0f);
	hpBar->Update(renderer, deltatime);
	CollObject::Update(renderer, deltatime);
	for (auto bullet : bullets)
		bullet.second->Update(renderer, deltatime);
}

void EnMage::Init()
{
	Enemy::Init();
	enType = EnemyType::MAGE;
	anim->SetAnimStatus((int)MageAnimStatus::IDLE);
	ShootDelay = 3.0f;
	shootInterval = ShootDelay;
	MaxHp = 50.0f;
	currentHp = MaxHp;
	damage = 1.0f;
}

void EnMage::CollisionStepped(std::vector<CollObject*> obj)
{
}

void EnMage::CollisionSticked(std::vector<CollObject*> obj)
{
}

void EnMage::ShootBullets(std::string name, bool isIndependent, bool gravity, float damage, glm::vec2 pos, float time, glm::vec2 speed, float distance)
{
	size_t size = bullets.size();
	for (size_t i = 0;i < size;++i)
	{
		std::string str = name + std::to_string(i);
		if (bullets.find(str) == bullets.end())
			break;
		if (!bullets[str]->Active)
		{
			glm::vec2 position(Position.x + (xFlip ? pos.x : -pos.x), Position.y + pos.y);
			bullets[str]->IsIndependent = isIndependent;
			bullets[str]->SetGravity(gravity);
			bullets[str]->SetDamage(damage);
			bullets[str]->Position = position;
			bullets[str]->collider->SetPos(position.x, position.y);
			bullets[str]->shootPos = pos;
			bullets[str]->StartPosition = position;
			bullets[str]->TimeDuration = time;
			bullets[str]->DistDuration = distance;
			bullets[str]->xFlip = xFlip;
			bullets[str]->Velocity.x = (xFlip ? speed.x : -speed.x);
			bullets[str]->Velocity.y = speed.y;
			bullets[str]->Active = true;
			break;
		}
	}
}
