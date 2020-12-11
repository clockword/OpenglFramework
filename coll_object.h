#pragma once
#include "collider.h"
#include "game_object.h"

class Collider;
class CollObject : public GameObject
{
protected:
	bool gravity;
	glm::vec2 moveDir;
	float damage;
public:
	Collider* collider;

	CollObject();
	CollObject(glm::vec2 pos, glm::vec2 size, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

	virtual ~CollObject();

	virtual void Init();

	virtual void Create(SpriteAnimation anim);
	virtual void Create(SpriteAnimation anim, Texture2D sprite, Collider* coll);
	virtual void Update(SpriteRenderer& renderer, float deltatime);

	virtual glm::vec2 GetMoveDir() { return moveDir; }
	virtual void SetMoveDir(glm::vec2 direction) { moveDir = direction; }
	virtual bool IsGravity() { return gravity; }
	virtual float GetDamage() { return damage; }
	virtual void SetDamage(float damage) { this->damage = damage; }
protected:
	virtual void Draw(SpriteRenderer& renderer);
	virtual void Move(glm::vec2 direction) { this->moveDir = direction; }
};