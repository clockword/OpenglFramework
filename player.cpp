#include "player.h"
#include <Windows.h>
#include "camera.h"


Player::Player() : CollObject()
{
	type = TYPE::PLAYER;
}

Player::Player(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity)
	: CollObject(pos, size, sprite, color, velocity)
{
	type = TYPE::PLAYER;
	Camera::startX = this->Position.x;
}

void Player::Update(SpriteRenderer& renderer, float deltatime)
{
	BYTE key[256];
	float speed = 300.0f;
	int status = anim->GetAnimStatus();
	bool isContinuous = true;

	Camera::posX = this->Position.x;

	bool err = 0;
	err = ::GetKeyboardState(key);
	if (!err)
		return;

	if (key[VK_LEFT] & 0x80)
	{
		Velocity.x = -speed;
		xFlip = false;
		status = (int)PlayerAnimStatus::WALK;
	}
	else if (key[VK_RIGHT] & 0x80)
	{
		Velocity.x = speed;
		xFlip = true;
		status = (int)PlayerAnimStatus::WALK;
	}
	else
	{
		Velocity.x = 0.0f;
		status = (int)PlayerAnimStatus::IDLE;
	}

	if (key[0x5A] & 0x80) {
		status = (int)PlayerAnimStatus::ATKDWN_SWD;
		isContinuous = false;
	}

	if (key[0x58] & 0x80 && Velocity.y == 0.0f) {
		Velocity.y += -500.0f;
	}

	if (Velocity.y != 0.0f)
	{
		status = (int)PlayerAnimStatus::JUMP;
		if (key[0x5A] & 0x80) {
			status = (int)PlayerAnimStatus::ATKUP_SWD;
			isContinuous = false;
		}
	}

	if(anim->GetAnimStatus() != status)
		anim->SetAnimStatus(status, isContinuous);

	CollObject::Update(renderer, deltatime);
}
