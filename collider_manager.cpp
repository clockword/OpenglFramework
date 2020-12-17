#include "collider_manager.h"
#include <fstream>
#include "rect.h"
#include "bullet.h"
#include "enemy.h"

std::map<std::string, Collider*> ColliderManager::Colliders;

Collider *ColliderManager::LoadCollider(const char* file, std::string name)
{
	int index = 0;
	while(index >= 0)
	{
		name += std::to_string(index++);
		if (Colliders.find(name) == Colliders.end())
			return Colliders[name] = LoadColliderFromFile(file);
	}
	return nullptr;
}

Collider *ColliderManager::GetCollider(std::string name)
{
	return Colliders[name];
}

void ColliderManager::FixedUpdate(float deltatime)
{
	float gravity = 58.86f;
	for (auto iter : Colliders)
	{
		if (!iter.second->gameObject->Active ||
			iter.second->gameObject->IsDestroyed)
			continue;

		ObjectType type = iter.second->gameObject->Type;
		if(iter.second->gameObject->IsGravity())
			iter.second->gameObject->Velocity.y += gravity;

		float collX = iter.second->CollX;
		float collY = iter.second->CollY;
		float width = iter.second->Width;
		float height = iter.second->Height;
		glm::vec2 velocity = iter.second->gameObject->Velocity * deltatime;
		if (iter.second->gameObject->GetIsControl())
			velocity += iter.second->gameObject->GetMoveDir() * deltatime;
		glm::vec2 position = glm::vec2(iter.second->X, iter.second->Y) + velocity;
		Rect rect(position.x + collX - width * 0.5f, position.x + collX + width * 0.5f,
			position.y + collY - height * 0.5f, position.y + collY + height * 0.5f);

		switch (type)
		{
		case ObjectType::PLAYER:
		case ObjectType::ENEMY:
		{
			bool isHit = false;

			if (rect.Bottom > 645.0f) {
				position.y = 645.0f - collY - height * 0.5f;
				iter.second->gameObject->Velocity = glm::vec2(0.0f, 0.0f);
				iter.second->gameObject->SetMoveDir(glm::vec2(iter.second->gameObject->GetMoveDir().x, 0.0f));
				iter.second->gameObject->SetIsControl(true);
			}

			std::vector<CollObject*> step;
			std::vector<CollObject*> stick;
			std::vector<CollObject*> enter;

			for (auto other : Colliders)
			{
				if (other.second == iter.second ||
					!other.second->gameObject->Active ||
					other.second->gameObject->IsDestroyed)
					continue;

				Rect othRect(other.second->X + other.second->CollX - other.second->Width * 0.5f,
					other.second->X + other.second->CollX + other.second->Width * 0.5f,
					other.second->Y + other.second->CollY - other.second->Height * 0.5f,
					other.second->Y + other.second->CollY + other.second->Height * 0.5f);

				switch (other.second->gameObject->Type)
				{
				case ObjectType::ENEMY:
				{
					if (type == ObjectType::ENEMY || !iter.second->gameObject->GetIsControl() ||
						!other.second->gameObject->GetIsControl() || other.second->gameObject->GetEnemyType() == (int)EnemyType::BOSS)
						break;

					if (rect.Left < othRect.Right && rect.Right > othRect.Left &&
						rect.Top < othRect.Bottom && rect.Bottom > othRect.Top)
					{
						iter.second->gameObject->SetIsControl(false);
						iter.second->gameObject->Velocity = glm::vec2((iter.second->gameObject->xFlip ? -300.0f : 300.0f), -500.0f);
						iter.second->gameObject->SetHp(iter.second->gameObject->GetHp() - other.second->gameObject->GetDamage());
						isHit = true;
					}
				}break;
				case ObjectType::WALL:
				{
					bool isStep = false;
					bool isStick = false;
					bool isEnter = false;

					if (rect.Left < othRect.Right && rect.Right > othRect.Left &&
						rect.Top < othRect.Bottom && rect.Bottom > othRect.Top)
						isEnter = true;

					if (velocity.y > 0.0f && rect.Bottom > othRect.Top &&
						rect.Left < othRect.Right && rect.Right > othRect.Left &&
						iter.second->Y + collY + height * 0.5f <= othRect.Top) {
						position.y = othRect.Top - height * 0.5f - collY;
						if (!isHit)
						{
							iter.second->gameObject->Velocity = glm::vec2(0.0f, 0.0f);
							iter.second->gameObject->SetIsControl(true);
						}
						iter.second->gameObject->SetMoveDir(glm::vec2(iter.second->gameObject->GetMoveDir().x, 0.0f));
						isStep = true;
					}
					else if (velocity.y < 0.0f && rect.Top < othRect.Bottom &&
						rect.Left < othRect.Right && rect.Right > othRect.Left &&
						iter.second->Y + collY - height * 0.5f >= othRect.Bottom) {
						position.y = othRect.Bottom + height * 0.5f - collY;
						iter.second->gameObject->Velocity = glm::vec2(0.0f, 1.0f);
						iter.second->gameObject->SetMoveDir(glm::vec2(iter.second->gameObject->GetMoveDir().x, 0.0f));
					}
					else if (velocity.x < 0.0f && rect.Left < othRect.Right &&
						rect.Top < othRect.Bottom && rect.Bottom > othRect.Top &&
						rect.Left > othRect.Left) {
						position.x = othRect.Right + width * 0.5f - collX;
						isStick = true;
					}
					else if (velocity.x > 0.0f && rect.Right > othRect.Left &&
						rect.Top < othRect.Bottom && rect.Bottom > othRect.Top &&
						rect.Right < othRect.Right) {
						position.x = othRect.Left - width * 0.5f - collX;
						isStick = true;
					}

					if (isStep)
						step.push_back(other.second->gameObject);
					if (isStick)
						stick.push_back(other.second->gameObject);
					if (isEnter)
						enter.push_back(other.second->gameObject);
				}break;
				}
			}

			isHit = false;

			iter.second->gameObject->CollisionStepped(step);
			iter.second->gameObject->CollisionSticked(stick);
			iter.second->gameObject->CollisionEntered(enter);

		}break;
		case ObjectType::P_HITBOX:
		case ObjectType::E_HITBOX:
		case ObjectType::E_BULLET:
		case ObjectType::P_BULLET:
		{
			if (rect.Bottom > 645.0f) {
				iter.second->gameObject->Active = false;
			}

			for (auto other : Colliders)
			{
				if (other.second == iter.second ||
					!other.second->gameObject->Active ||
					other.second->gameObject->IsDestroyed)
					continue;

				Rect othRect(other.second->X + other.second->CollX - other.second->Width * 0.5f,
					other.second->X + other.second->CollX + other.second->Width * 0.5f,
					other.second->Y + other.second->CollY - other.second->Height * 0.5f,
					other.second->Y + other.second->CollY + other.second->Height * 0.5f);

				switch (other.second->gameObject->Type)
				{
				case ObjectType::WALL:
				{
					if (type == ObjectType::P_HITBOX || type == ObjectType::E_HITBOX)
						break;

					if (rect.Left < othRect.Right && rect.Right > othRect.Left &&
						rect.Top < othRect.Bottom && rect.Bottom > othRect.Top)
						iter.second->gameObject->Active = false;
				}break;
				case ObjectType::ENEMY:
				{
					if (type == ObjectType::E_BULLET || type == ObjectType::E_HITBOX)
						break;

					if (rect.Left < othRect.Right && rect.Right > othRect.Left &&
						rect.Top < othRect.Bottom && rect.Bottom > othRect.Top) {
						if (other.second->gameObject->GetEnemyType() == (int)EnemyType::BOSS &&
							!other.second->gameObject->GetIsControl())
							break;

						other.second->gameObject->Velocity = glm::vec2((iter.second->gameObject->xFlip ? 300.0f : -300.0f), -500.0f);
						other.second->gameObject->SetIsControl(false);
						iter.second->gameObject->Active = false;
						other.second->gameObject->SetHp(other.second->gameObject->GetHp() - iter.second->gameObject->GetDamage());
					}
				}break;
				case ObjectType::PLAYER:
				{
					if (type == ObjectType::P_BULLET || type == ObjectType::P_HITBOX ||
						!other.second->gameObject->GetIsControl())
						break;

					if (rect.Left < othRect.Right && rect.Right > othRect.Left &&
						rect.Top < othRect.Bottom && rect.Bottom > othRect.Top) {
						if(type == ObjectType::E_BULLET)
							other.second->gameObject->Velocity = glm::vec2((iter.second->gameObject->Velocity.x < 0.0f ? -300.0f : 300.0f), -500.0f);
						else
							other.second->gameObject->Velocity = glm::vec2((iter.second->gameObject->xFlip ? 300.0f : -300.0f), -500.0f);
						other.second->gameObject->SetIsControl(false);
						iter.second->gameObject->Active = false;
						other.second->gameObject->SetHp(other.second->gameObject->GetHp() - iter.second->gameObject->GetDamage());
					}
				}break;
				}
			}
		}
		}

		iter.second->X = position.x;
		iter.second->Y = position.y;
		iter.second->gameObject->Position = position;
	}
}

void ColliderManager::Delete()
{
	for (auto iter : Colliders)
		delete iter.second;
	Colliders.clear();
}

Collider *ColliderManager::LoadColliderFromFile(const char* filename)
{
	Collider* coll = new Collider;
	char ch[256];
	std::ifstream file(filename);
	std::string str;

	file.getline(ch, 256);
	int order = 0;
	for (int i = 0; i < 256; ++i)
	{
		if (ch[i] == ' ' || ch[i] == '\0')
		{
			switch (order++)
			{
			case 0: coll->CollX = std::stof(str); break;
			case 1: coll->CollY = std::stof(str); break;
			case 2: coll->Width = std::stof(str); break;
			case 3: coll->Height = std::stof(str); break;
			}
			str.clear();
		}
		else
			str += ch[i];
		if (ch[i] == '\0')
			break;
	}

	file.close();
	return coll;
}
