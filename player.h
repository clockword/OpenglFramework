#pragma once
#include <map>
#include <string>
#include "coll_object.h"
#include "bullet.h"

enum class PlayerAnimStatus
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

class Player : public CollObject
{
protected:
	std::map<std::string ,Bullet*> bullets;
	float shootInterval;
	float atkInterval;
public:
	float ShootDelay;
	float AtkDelay;

	Player();
	Player(glm::vec2 pos, glm::vec2 size, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

	virtual ~Player();

	virtual void Update(SpriteRenderer& renderer, float deltatime);

	virtual void Init();

	virtual void CreateBullets(std::string name, Collider* coll, int index);
	virtual void CreateBullets(std::string name, SpriteAnimation anim, Texture2D sprite, Collider* coll, int index);
protected:
	virtual void ShootBullets(std::string name, float speed, glm::vec2 pos, float time = 10.0f, float distance = 1000.0f);
};

