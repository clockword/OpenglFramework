#include "player.h"
#include <Windows.h>
#include "camera.h"

Player::Player() : CollObject()
{
	Type = ObjectType::PLAYER;
}

Player::Player(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity)
	: CollObject(pos, size, color, velocity)
{
	Type = ObjectType::PLAYER;
	Camera::startX = pos.x;
	Camera::posX = pos.x;
	Camera::prevX = pos.x;
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

	if (key[0x5A] & 0x80) {
		status = (int)PlayerAnimStatus::ATKDWN_SWD;
		isContinuous = false;
	}

	if (key[0x58] & 0x80 && Velocity.y == 0.0f) {
		Velocity.y += -900.0f;
	}

	if (Velocity.y != 0.0f)
	{
		status = (int)PlayerAnimStatus::JUMP;
		if (key[0x5A] & 0x80) {
			status = (int)PlayerAnimStatus::ATKUP_SWD;
			isContinuous = false;
		}
		else if(dash > 1.0f)
			status = (int)PlayerAnimStatus::DASHATK;
	}

	if(anim->GetAnimStatus() != status)
		anim->SetAnimStatus(status, isContinuous);

	CollObject::Update(renderer, deltatime);
}
