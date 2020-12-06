#include "bullet.h"

Bullet::Bullet() : CollObject()
{
}

Bullet::Bullet(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity) :
	CollObject(pos, size, color, velocity)
{
}

void Bullet::Create(Collider* coll)
{
	collider = coll;
	collider->CreateBorder();
	collider->gameObject = this;
	collider->SetPos(Position.x, Position.y);
}

void Bullet::Create(SpriteAnimation anim, Texture2D sprite, Collider* coll)
{
	CollObject::Create(anim, sprite, coll);
}

void Bullet::Update(SpriteRenderer& renderer, float deltatime)
{
	if (anim != nullptr && Sprite != nullptr)
		anim->UpdateAnim(deltatime);

	Draw(renderer);
}

void Bullet::Draw(SpriteRenderer& renderer)
{
	if(anim != nullptr && Sprite != nullptr)
		GameObject::Draw(renderer);
#if _DEBUG
	collider->Draw(renderer);
#endif
}
