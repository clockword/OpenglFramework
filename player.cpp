#include "player.h"
#include <Windows.h>
#include "camera.h"

Player::Player() : CollObject(), ShootDelay(0.0f), shootInterval(0.0f), AtkDelay(0.0f), atkInterval(0.0f)
{
}

Player::Player(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity)
	: CollObject(pos, size, color, velocity), ShootDelay(0.0f), shootInterval(0.0f), AtkDelay(0.0f), atkInterval(0.0f)
{
}

Player::~Player()
{
	for (auto bullet : bullets)
		delete bullet.second;
}

void Player::Update(SpriteRenderer& renderer, float deltatime)
{
	BYTE key[256];
	float speed = 300.0f;
	float dash = 1.0f;
	int status = anim->GetAnimStatus();
	bool isContinuous = true;

	bool err = 0;
	err = ::GetKeyboardState(key);
	if (!err)
		return;
	
	Camera::prevX = Camera::posX;
	Camera::posX = Position.x;

	if (key[VK_SHIFT] & 0x80)
		dash = 1.5f;

	if (key[VK_LEFT] & 0x80)
	{
		Velocity.x = -speed * dash;
		xFlip = false;
		status = (int)PlayerAnimStatus::WALK;
		if (dash > 1.0f)
			status = (int)PlayerAnimStatus::DASHATK;
	}
	else if (key[VK_RIGHT] & 0x80)
	{
		Velocity.x = speed * dash;
		xFlip = true;
		status = (int)PlayerAnimStatus::WALK;
		if (dash > 1.0f)
			status = (int)PlayerAnimStatus::DASHATK;
	}
	else
	{
		Velocity.x = 0.0f;
		status = (int)PlayerAnimStatus::IDLE;
	}

	atkInterval += deltatime;
	if (key[0x58] & 0x80 && atkInterval >= AtkDelay) {
		status = (int)PlayerAnimStatus::ATKDWN_SWD;
		isContinuous = false;
		ShootBullets("swd", 0.0f, glm::vec2(30.0f, 0.0f), 0.1f);
	}

	if (key[0x5A] & 0x80 && Velocity.y == 0.0f) {
		Velocity.y += -900.0f;
	}

	if (Velocity.y != 0.0f)
	{
		status = (int)PlayerAnimStatus::JUMP;
		if (key[0x58] & 0x80 && atkInterval >= AtkDelay) {
			status = (int)PlayerAnimStatus::ATKUP_SWD;
			isContinuous = false;
		}
		else if (dash > 1.0f)
			status = (int)PlayerAnimStatus::DASHATK;
	}

	shootInterval += deltatime;
	if (key[0x43] & 0x80 && shootInterval >= ShootDelay) {
		shootInterval = 0.0f;
		status = (int)PlayerAnimStatus::SHOOT_ORBIT;
		isContinuous = false;
		ShootBullets("orbit", 600.0f, glm::vec2(70.0f, -15.0f));
	}

	if (status == (int)PlayerAnimStatus::ATKUP_SWD ||
		status == (int)PlayerAnimStatus::ATKDWN_SWD)
		atkInterval = 0.0f;

	if(anim->GetAnimStatus() != status)
		anim->SetAnimStatus(status, isContinuous);

	CollObject::Update(renderer, deltatime);
	for (auto bullet : bullets)
		bullet.second->Update(renderer, deltatime);
}

void Player::Init()
{
	Type = ObjectType::PLAYER;
	ShootDelay = 1.0f;
	shootInterval = ShootDelay;
	AtkDelay = 0.5f;
	atkInterval = AtkDelay;

	Camera::player = this;
	Camera::startX = Position.x;
	Camera::posX = Position.x;
	Camera::prevX = Position.x;
}

void Player::CreateBullets(std::string name, Collider* coll, int index)
{
	std::string str = name + std::to_string(index);
	bullets[str] = new Bullet(Position, glm::vec2(2.0f, 2.0f));
	bullets[str]->Create(coll);
	bullets[str]->Type = ObjectType::P_HITBOX;
}

void Player::CreateBullets(std::string name, SpriteAnimation anim, Texture2D sprite, Collider* coll, int index)
{
	std::string str = name + std::to_string(index);
	bullets[str] = new Bullet(Position, glm::vec2(2.0f, 2.0f));
	bullets[str]->Create(anim, sprite, coll);
	bullets[str]->Type = ObjectType::P_BULLET;
}

void Player::ShootBullets(std::string name, float speed, glm::vec2 pos, float time, float distance)
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
			bullets[str]->Position = position;
			bullets[str]->collider->SetPos(position.x, position.y);
			bullets[str]->StartPosition = position;
			bullets[str]->TimeDuration = time;
			bullets[str]->DistDuration = distance;
			bullets[str]->xFlip = xFlip;
			bullets[str]->Velocity.x = xFlip ? speed : -speed;
			bullets[str]->Active = true;
			break;
		}
	}
}
