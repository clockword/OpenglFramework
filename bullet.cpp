#include "bullet.h"
#include <glm/gtx/norm.hpp>
#include <glm/gtx/vector_angle.hpp>

Bullet::Bullet() : CollObject(), timeInterval(0.0f), StartPosition({ 0.0f,0.0f }), TimeDuration(0.0f),
DistDuration(0.0f), IsIndependent(false), playerPos(glm::vec2(0.0f, 0.0f)), shootPos(glm::vec2(0.0f, 0.0f))
{
}

Bullet::Bullet(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity) :
	CollObject(pos, size, color, velocity), timeInterval(0.0f), StartPosition({ 0.0f,0.0f }), TimeDuration(0.0f), 
	DistDuration(0.0f), IsIndependent(false), playerPos(glm::vec2(0.0f, 0.0f)), shootPos(glm::vec2(0.0f, 0.0f))
{
}

void Bullet::Init()
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
	{
		timeInterval = 0.0f;
		return;
	}

	if (!IsIndependent)
	{
		Position.x = playerPos.x + (xFlip ? shootPos.x : -shootPos.x);
		Position.y = playerPos.y + shootPos.y;
		collider->SetPos(Position.x, Position.y);
	}

	//if (gravity) {
	//	Rotation = Velocity.y > 0.0f ? acosf(Velocity.y / Velocity.x) / 3.14159265f * 180.0f - 45.0f : acosf(Velocity.y / Velocity.x) / 3.14159265f * -180.0f + 45.0f;
	//}
	if (Type == ObjectType::P_BULLET)
		Rotation += xFlip ? -40.0f : 40.0f;

	timeInterval += deltatime;
	if (timeInterval >= TimeDuration)
	{
		timeInterval = 0.0f;
		Active = false;
	}

	if (glm::length(Position - StartPosition) >= DistDuration)
		Active = false;

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
