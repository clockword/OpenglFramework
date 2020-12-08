#pragma once
#include "coll_object.h"

enum class BulletType
{
	PL_ORBIT = 0,
	PL_SWD,
	PL_DASHSWD
};

class Bullet : public CollObject
{
protected:
	float timeInterval;
	glm::vec2 startPosition;
public:
	float TimeDuration;
	float DistDuration;
	bool IsBreakable;

	Bullet();
	Bullet(glm::vec2 pos, glm::vec2 size, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

	virtual void Create(Collider* coll);
	virtual void Create(SpriteAnimation anim, Texture2D sprite, Collider* coll);

	virtual void Update(SpriteRenderer& renderer, float deltatime);
protected:
	virtual void Draw(SpriteRenderer& renderer);
};

