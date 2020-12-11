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
	bool isControl;
	float currentHp;
public:
	float ShootDelay;
	float AtkDelay;
	float MaxHp;

	Player();
	Player(glm::vec2 pos, glm::vec2 size, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

	virtual ~Player();

	virtual void Update(SpriteRenderer& renderer, float deltatime);

	virtual void Init();

	virtual void CreateBullets(std::string name, Collider* coll, ObjectType type, int index);
	virtual void CreateBullets(std::string name, SpriteAnimation anim, Texture2D sprite, Collider* coll, ObjectType type, int index);

	virtual bool GetIsControl() { return this->isControl; }
	virtual void SetIsControl(bool control) { this->isControl = control; }
	virtual float GetHp() { return currentHp; }
	virtual void SetHp(float hp) { currentHp = hp; }
protected:
	virtual void ShootBullets(std::string name, bool isIndependent, bool gravity, float damage, 
		glm::vec2 pos = glm::vec2(0.0f, 0.0f), float time = 10.0f, glm::vec2 speed = glm::vec2(0.0f, 0.0f), float distance = 1000.0f);
};

