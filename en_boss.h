#pragma once
#include "enemy.h"

enum class BossAnimStatus
{
	ATKDWN_ORBIT = 0,
	SHOOT_ORBIT,
	ATKFWD_ORBIT,
	ATKFWD_SWD,
	ATKDWN_SWD,
	ATKUP_SWD,
	PWRUP,
	HNDUP,
	DASH,
	DASHATK,
	FALDWN,
	JUMP,
	SWOON,
	IDLE,
	GTH_ORBIT,
	WALK
};

class EnBoss : public Enemy
{
public:
	EnBoss();
	EnBoss(glm::vec2 pos, glm::vec2 size, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

	virtual void Update(SpriteRenderer& renderer, float deltatime);

	virtual void Init();
};