#include "collider.h"
#include "resource_manager.h"


#include <fstream>

Collider::Collider()
{
	obj_x = 0.0f;
	obj_y = 0.0f;
	gameObject = nullptr;
	X = 0.0f;
	Y = 0.0f;
	Width = 0.0f;
	Height = 0.0f;
}

Collider::Collider(float x, float y, float w, float h)
{
	obj_x = 0.0f;
	obj_y = 0.0f;
	gameObject = nullptr;
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
	glm::vec2 pos(obj_x + this->X - (this->Width * 0.5f), obj_y + this->Y - (this->Height * 0.5f));
	glm::vec2 size(this->Width / colorBorder.Width, this->Height / colorBorder.Height);

	renderer.DrawSprite(colorBorder, pos, size);
}
