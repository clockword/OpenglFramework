#include "player.h"
#include <Windows.h>

Player::Player() : CollObject()
{
	type = TYPE::PLAYER;
}

Player::Player(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity)
	: CollObject(pos, size, sprite, color, velocity)
{
	type = TYPE::PLAYER;
}

void Player::Update(SpriteRenderer& renderer, float deltatime)
{
	BYTE key[256];
	float speed = 300.0f;

	bool err = 0;
	err = ::GetKeyboardState(key);
	if (!err)
		return;

	if (key[VK_LEFT] & 0x80)
	{
		Velocity = { -speed, 0.0f };
	}
	else if (key[VK_RIGHT] & 0x80)
	{
		Velocity = { speed, 0.0f };
	}
	else if (key[VK_UP] & 0x80)
	{
		Velocity = { 0.0f, -speed };
	}
	else if (key[VK_DOWN] & 0x80)
	{
		Velocity = { 0.0f, speed };
	}
	else
	{
		Velocity = { 0.0f,0.0f };
	}

	CollObject::Update(renderer, deltatime);
}
