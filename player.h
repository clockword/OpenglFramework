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
public:
	Player();
	Player(glm::vec2 pos, glm::vec2 size, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

	virtual void Update(SpriteRenderer& renderer, float deltatime);

	virtual void CreateBullets(std::string name, Collider* coll, int index);
	virtual void CreateBullets(std::string name, SpriteAnimation anim, Texture2D sprite, Collider* coll, int index);
protected:
	virtual void ShootBullets(std::string name);
};

