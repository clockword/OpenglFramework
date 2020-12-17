#include "player.h"
#include <Windows.h>
#include "camera.h"
#include "resource_manager.h"

Player::Player() : CollObject(), ShootDelay(0.0f), shootInterval(0.0f), AtkDelay(0.0f), atkInterval(0.0f), isControl(true), MaxHp(0.0f), currentHp(0.0f), hpBar(nullptr)
{
}

Player::Player(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity)
	: CollObject(pos, size, color, velocity), ShootDelay(0.0f), shootInterval(0.0f), AtkDelay(0.0f), atkInterval(0.0f), isControl(true), MaxHp(0.0f), currentHp(0.0f), hpBar(nullptr)
{
}

Player::~Player()
{
	for (auto bullet : bullets)
		delete bullet.second;
	if (hpBar != nullptr)
		delete hpBar;
}

void Player::Create(SpriteAnimation anim, Texture2D sprite, Collider* coll)
{
	CollObject::Create(anim, sprite, coll);
	hpBar = new GameObject(Position, glm::vec2(1.0f, 0.5f));
	hpBar->Create(ResourceManager::LoadAnims("./Resource/VertexData/hpbar.txt", ResourceManager::GetTexture("player"), "hpbar"), ResourceManager::GetTexture("player"));
	hpBar->Active = true;
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

	atkInterval += deltatime;
	shootInterval += deltatime;

	if (isControl)
	{
		glm::vec2 moveDirection = moveDir;

		if (key[VK_SHIFT] & 0x80)
			dash = 1.5f;

		if (key[VK_LEFT] & 0x80)
		{
			moveDirection.x = -speed * dash;
			xFlip = false;
			status = (int)PlayerAnimStatus::WALK;
			if (dash > 1.0f)
				status = (int)PlayerAnimStatus::DASH;
		}
		else if (key[VK_RIGHT] & 0x80)
		{
			moveDirection.x = speed * dash;
			xFlip = true;
			status = (int)PlayerAnimStatus::WALK;
			if (dash > 1.0f)
				status = (int)PlayerAnimStatus::DASH;
		}
		else
		{
			moveDirection.x = 0.0f;
			status = (int)PlayerAnimStatus::IDLE;
		}

		if (key[0x58] & 0x80 && atkInterval >= AtkDelay) {
			status = (int)PlayerAnimStatus::ATKDWN_SWD;
			isContinuous = false;
			ShootBullets("player_swd", false, false, 20.0f, glm::vec2(30.0f, 0.0f), 0.3f);
		}

		if (key[0x5A] & 0x80 && Velocity.y == 0.0f) {
			moveDirection.y = -900.0f;
		}

		if (Velocity.y != 0.0f)
		{
			status = (int)PlayerAnimStatus::JUMP;
			if (key[0x58] & 0x80 && atkInterval >= AtkDelay) {
				status = (int)PlayerAnimStatus::ATKUP_SWD;
				isContinuous = false;
			}
			else if (dash > 1.0f && moveDirection.x != 0.0f)
				status = (int)PlayerAnimStatus::DASH;
		}

		if (key[0x43] & 0x80 && shootInterval >= ShootDelay) {
			shootInterval = 0.0f;
			status = (int)PlayerAnimStatus::SHOOT_ORBIT;
			isContinuous = false;
			ShootBullets("player_orbit", true, false, 30.0f, glm::vec2(70.0f, -15.0f), 10.0f, glm::vec2(600.0f, 0.0f));
		}

		Move(moveDirection);
	}
	else
	{
		status = (int)PlayerAnimStatus::SWOON;
	}

	if (status == (int)PlayerAnimStatus::ATKUP_SWD ||
		status == (int)PlayerAnimStatus::ATKDWN_SWD)
		atkInterval = 0.0f;

	if(anim->GetAnimStatus() != status)
		anim->SetAnimStatus(status, isContinuous);

	if (currentHp >= 0.0f) {
		currentHp += deltatime * 3.0f;
		hpBar->Size.x = currentHp / MaxHp;
	}
	if (currentHp >= MaxHp)
		currentHp = MaxHp;
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

void Player::Init()
{
	Type = ObjectType::PLAYER;
	gravity = true;
	ShootDelay = 1.0f;
	shootInterval = ShootDelay;
	AtkDelay = 0.5f;
	atkInterval = AtkDelay;
	MaxHp = 300.0f;
	currentHp = MaxHp;

	Camera::startX = Position.x;
	Camera::posX = Position.x;
	Camera::prevX = Position.x;
}

void Player::CreateBullets(std::string name, Collider* coll, ObjectType type, int index)
{
	std::string str = name + std::to_string(index);
	bullets[str] = new Bullet(Position, glm::vec2(2.0f, 2.0f));
	bullets[str]->Create(coll);
	bullets[str]->Type = type;
}

void Player::CreateBullets(std::string name, SpriteAnimation anim, Texture2D sprite, Collider* coll, ObjectType type, int index)
{
	std::string str = name + std::to_string(index);
	bullets[str] = new Bullet(Position, glm::vec2(2.0f, 2.0f));
	bullets[str]->Create(anim, sprite, coll);
	bullets[str]->Type = type;
}

void Player::ShootBullets(std::string name, bool isIndependent, bool gravity, float damage, glm::vec2 pos, float time, glm::vec2 speed, float distance)
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
			bullets[str]->xFlip = !xFlip;
			bullets[str]->Velocity.x = (xFlip ? speed.x : -speed.x);
			bullets[str]->Velocity.y = speed.y;
			bullets[str]->Active = true;
			break;
		}
	}
}
