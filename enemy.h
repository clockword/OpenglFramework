#pragma once
#include "player.h"

enum class EnemyType
{

};

class Enemy : public Player
{
protected:
	Player* player;
public:
	Enemy();
	Enemy(glm::vec2 pos, glm::vec2 size, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

	virtual void Update(SpriteRenderer& renderer, float deltatime) = 0;

	virtual void Init();
};

