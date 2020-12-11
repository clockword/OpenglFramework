#pragma once
#include "coll_object.h"

class Bullet : public CollObject
{
protected:
	float timeInterval;
public:
	glm::vec2 playerPos;
	glm::vec2 shootPos;
	bool IsIndependent;
	glm::vec2 StartPosition;
	float TimeDuration;
	float DistDuration;

	Bullet();
	Bullet(glm::vec2 pos, glm::vec2 size, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

	virtual void Init();

	virtual void Create(Collider* coll);
	virtual void Create(SpriteAnimation anim, Texture2D sprite, Collider* coll);

	virtual void Update(SpriteRenderer& renderer, float deltatime);

	void SetGravity(bool gravity) { this->gravity = gravity; }
protected:
	virtual void Draw(SpriteRenderer& renderer);
};

