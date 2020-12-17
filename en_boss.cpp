#include "en_boss.h"

EnBoss::EnBoss() : Enemy(), isPowerUp(false), sleep(false)
{
}

EnBoss::EnBoss(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity) :
	Enemy(pos, size, color, velocity), isPowerUp(false), sleep(false)
{
}

void EnBoss::Update(SpriteRenderer& renderer, float deltatime)
{
	if (!Active || IsDestroyed)
		return;

	if (isPowerUp && currentHp <= 0.0f) {
		Active = false;
		IsDestroyed = true;
		return;
	}
	else if (currentHp <= 0.0f) {
		isPowerUp = true;
		MaxHp = 300.0f;
		currentHp = MaxHp;
		Size *= 1.5f;
		collider->Width *= 1.5f;
		collider->Height *= 1.5f;
		Velocity.y -= 1000.0f;
		sleep = true;
		AtkDelay = 1.0f;
		atkInterval = -1.0f;
	}

	float dash = 1.0f;
	int status = anim->GetAnimStatus();
	bool isContinuous = true;
	float speed = isPowerUp ? 400.0f : 300.0f;

	atkInterval += deltatime;
	shootInterval += deltatime;
	
	if (isControl)
		sleep = false;

	if (isPowerUp)
	{
		if (sleep)
		{
			status = (int)BossAnimStatus::PWRUP;
		}
		else
		{
			glm::vec2 moveDirection = moveDir;
			status = (int)BossAnimStatus::IDLE;
			glm::vec2 direction(glm::normalize(player->Position - Position));
			float distance = glm::length(player->Position - Position);

			if (distance >= 600.0f)
				dash = 1.5f;
			else if (distance >= 500.0f)
				dash = 1.125f;

			if (dash == 1.0f)
				status = (int)BossAnimStatus::WALK;
			else
				status = (int)BossAnimStatus::DASH;

			if (player->GetIsControl())
			{
				xFlip = direction.x > 0.0f ? true : false;
				moveDirection.x = xFlip ? speed * dash : -(speed * dash);

				if (distance <= 450.0f) {
					if (atkInterval >= AtkDelay)
					{
						atkInterval = 0.0f;
						status = (int)BossAnimStatus::ATKDWN_ORBIT;
						isContinuous = false;
						ShootBullets("boss_atk", false, false, 50.0f, glm::vec2(20.0f, 0.0f), 0.3f);
						for (int i = 0; i < 5; ++i)
							ShootBullets("boss_orbit", true, true, 30.0f, glm::vec2(70.0f, 0.0f), 10.0f,
								glm::vec2((float)(rand() % 801 + 200), (float)(rand() % 801 - 1200)));
					}
					moveDirection.x = 0.0f;
				}
			}
			else
			{
				xFlip = direction.x > 0.0f ? false : true;
				moveDirection.x = xFlip ? speed * dash : -(speed * dash);
			}

			Move(moveDirection);
		}
	}
	else if (isControl)
	{
		glm::vec2 moveDirection = moveDir;
		status = (int)BossAnimStatus::IDLE;
		glm::vec2 direction(glm::normalize(player->Position - Position));
		float distance = glm::length(player->Position - Position);

		if (distance >= 500.0f)
			dash = 1.5f;

		if (moveDirection.x != 0.0f)
		{
			if (dash == 1.0f)
				status = (int)BossAnimStatus::WALK;
			else
				status = (int)BossAnimStatus::DASH;
		}
		
		if (player->GetIsControl())
		{
			xFlip = direction.x > 0.0f ? true : false;
			moveDirection.x = xFlip ? speed * dash : -(speed * dash);

			if (distance <= 90.0f && atkInterval >= AtkDelay) {
				atkInterval = 0.0f;
				moveDirection.x = 0.0f;
				if (Velocity.y == 0.0f)
					status = (int)BossAnimStatus::ATKDWN_SWD;
				else
					status = (int)BossAnimStatus::ATKUP_SWD;
				isContinuous = false;
				ShootBullets("boss_swd", false, false, 20.0f, glm::vec2(25.0f, 0.0f), 0.3f);
			}
			else if(distance >= 350.0f && shootInterval >= ShootDelay && 
				Position.y > player->Position.y - 50.0f && Position.y < player->Position.y + 50.0f)
			{
				shootInterval = 0.0f;
				status = (int)BossAnimStatus::SHOOT_ORBIT;
				isContinuous = false;
				ShootBullets("boss_orbit", true, false, 30.0f, glm::vec2(70.0f, -15.0f), 10.0f, glm::vec2(600.0f, 0.0f));
			}

		}
		else
		{
			xFlip = direction.x > 0.0f ? false : true;
			moveDirection.x = xFlip ? speed * dash : -(speed * dash);
		}

		if (moveDirection.y == 0.0f && rand() % 100 == 0)
			moveDirection.y = -900.0f;

		Move(moveDirection);
	}
	else
	{
		status = (int)BossAnimStatus::SWOON;
	}

	if (status == (int)BossAnimStatus::ATKUP_SWD ||
		status == (int)BossAnimStatus::ATKDWN_SWD)
		atkInterval = 0.0f;

	if (status != anim->GetAnimStatus())
		anim->SetAnimStatus(status, isContinuous);

	if (currentHp >= 0.0f)
		hpBar->Size.x = currentHp / MaxHp;
	hpBar->Position = Position + glm::vec2(0.0f, isPowerUp ? -90.0f : -60.0f);
	hpBar->Update(renderer, deltatime);
	CollObject::Update(renderer, deltatime);
	for (auto bullet : bullets) {
		if (!bullet.second->IsIndependent) {
			bullet.second->playerPos = Position;
			bullet.second->xFlip = xFlip;
		}
		else {
			bullet.second->Rotation += xFlip ? 40.0f : -40.0f;
		}
		bullet.second->Update(renderer, deltatime);
	}
}

void EnBoss::Init()
{
	Enemy::Init();
	enType = EnemyType::BOSS;
	anim->SetAnimStatus((int)BossAnimStatus::IDLE);
	ShootDelay = 2.0f;
	shootInterval = 0.0f;
	AtkDelay = 0.5f;
	atkInterval = AtkDelay;
	MaxHp = 300.0f;
	currentHp = MaxHp;
}