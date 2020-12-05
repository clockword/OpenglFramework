#pragma once
#include "collider.h"
#include "game_object.h"

class Collider;
class CollObject : public GameObject
{
public:
	Collider* collider;

	CollObject();
	CollObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

	virtual ~CollObject();

	virtual void Create(SpriteAnimation anim);
	virtual void Create(SpriteAnimation anim, Collider* coll);
	virtual void Update(SpriteRenderer& renderer, float deltatime);
protected:
	virtual void Draw(SpriteRenderer& renderer);
};