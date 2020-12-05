#include "collider.h"
#include "resource_manager.h"
#include "camera.h"

#include <fstream>

Collider::Collider()
{
	gameObject = nullptr;
	CollX = 0.0f;
	CollY = 0.0f;
	X = 0.0f;
	Y = 0.0f;
	Width = 0.0f;
	Height = 0.0f;
}

Collider::Collider(float x, float y, float w, float h)
{
	gameObject = nullptr;
	this->CollX = 0.0f;
	this->CollY = 0.0f;
	this->X = x;
	this->Y = y;
	this->Width = w;
	this->Height = h;
}

Collider::~Collider()
{
}

void Collider::CreateBorder()
{
	colorBorder = ResourceManager::LoadTexture("./Resource/Image/collider.png", true, "collider");
}

void Collider::Draw(SpriteRenderer& renderer)
{
	glm::vec2 pos(CollX + X - (this->Width * 0.5f),CollY + Y - (this->Height * 0.5f));
	glm::vec2 size(this->Width / colorBorder.Width, this->Height / colorBorder.Height);

	pos.x -= Camera::posX - Camera::startX;

	renderer.DrawSprite(colorBorder, pos, size);
}
