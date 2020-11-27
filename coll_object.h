#pragma once
#include "collider.h"
#include "game_object.h"

enum class TYPE {
	DEFAULT = 0,
	PLAYER = 1,
	WALL = 2,
	ENEMY = 3,
	P_BULLET = 4,
	E_BULLET = 5
};

class Collider;
class CollObject : public GameObject
{
public:
	TYPE type;
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