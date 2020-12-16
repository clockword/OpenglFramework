#include "coll_object.h"

CollObject::CollObject() : GameObject(), collider(nullptr), moveDir(glm::vec2(0.0f, 0.0f)), gravity(false), damage(0.0f)
{
}

CollObject::CollObject(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity)
	: GameObject(pos, size, color, velocity), collider(nullptr), moveDir(glm::vec2(0.0f, 0.0f)), gravity(false), damage(0.0f)
{
}

CollObject::~CollObject()
{
}

void CollObject::Init()
{
}

void CollObject::Create(SpriteAnimation anim)
{
	return;
}

void CollObject::Create(SpriteAnimation anim, Texture2D sprite, Collider* coll)
{
	GameObject::Create(anim, sprite);
	collider = coll;
	collider->CreateBorder();
	collider->gameObject = this;
	collider->SetPos(Position.x, Position.y);
}

void CollObject::Update(SpriteRenderer& renderer, float deltatime)
{
	if (!Active || IsDestroyed)
		return;

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