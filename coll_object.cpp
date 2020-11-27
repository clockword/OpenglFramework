#include "coll_object.h"

CollObject::CollObject() : GameObject(), collider(nullptr)
{
	type = TYPE::DEFAULT;
}

CollObject::CollObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity)
	: GameObject(pos, size, sprite, color, velocity), collider(nullptr)
{
	type = TYPE::DEFAULT;
}

CollObject::~CollObject()
{
}

void CollObject::Create(SpriteAnimation anim)
{
}

void CollObject::Create(SpriteAnimation anim, Collider* coll)
{
	GameObject::Create(anim);
	collider = coll;
	collider->CreateBorder();
	collider->gameObject = this;
	collider->SetObjPos(Position.x, Position.y);
}

void CollObject::Update(SpriteRenderer& renderer, float deltatime)
{
	anim->UpdateAnim(deltatime);

	Draw(renderer);
}

void CollObject::Draw(SpriteRenderer& renderer)
{
	GameObject::Draw(renderer);
#if _DEBUG
	collider->Draw(renderer);
#endif
}
