#include "bullet.h"
#include <glm/gtx/norm.hpp>

Bullet::Bullet() : CollObject(), timeInterval(0.0f), startPosition({0.0f,0.0f}), TimeDuration(0.0f), DistDuration(0.0f), IsBreakable(false)
{
}

Bullet::Bullet(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity) :
	CollObject(pos, size, color, velocity), timeInterval(0.0f), startPosition({ 0.0f,0.0f }), TimeDuration(0.0f), DistDuration(0.0f), IsBreakable(false)
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
	if (!Active || IsDestroyed)
		return;

	//timeInterval += deltatime;
	//if (timeInterval >= TimeDuration)
	//{
	//	timeInterval = 0.0f;
	//	Active = false;
	//}

	//if (glm::length2(Position - startPosition) >= DistDuration)
	//	Active = false;

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
