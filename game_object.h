/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "sprite_renderer.h"
#include "sprite_animation.h"

enum class ObjectType {
    DEFAULT = 0,
    PLAYER = 1,
    WALL = 2,
    ENEMY = 3,
    P_BULLET = 4,
    E_BULLET = 5,
    P_HITBOX = 6,
    E_HITBOX = 7
};

class Collider;
class CollObject;
class GameObject
{
protected:
    SpriteAnimation* anim;
public:
    // object state
    ObjectType  Type;
    glm::vec2   Position, Size, Velocity;
    glm::vec3   Color;
    float       Rotation;
    bool        xFlip;
    bool        yFlip;
    bool        Active;
    bool        IsDestroyed;

    // render state
    Texture2D   *Sprite;
    // constructor(s)
    GameObject();
    GameObject(glm::vec2 pos, glm::vec2 size, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
    virtual ~GameObject();

    virtual void Init();

    // draw sprite
    virtual void Create(SpriteAnimation anim, Texture2D sprite);
    virtual void Create(SpriteAnimation anim, Texture2D sprite, Collider* coll) {}
    virtual void Update(SpriteRenderer& renderer, float deltatime);

    virtual void CreateBullets(std::string name, Collider* coll, ObjectType type, int index) {}
    virtual void CreateBullets(std::string name, SpriteAnimation anim, Texture2D sprite, Collider* coll, ObjectType type, int index) {}

    virtual void SetAnimStatus(int status) { anim->SetAnimStatus(status); }

    virtual bool GetIsControl() { return false; }
    virtual void SetIsControl(bool control) {}
    virtual glm::vec2 GetMoveDir() { return glm::vec2(0.0f, 0.0f); }
    virtual void SetMoveDir(glm::vec2 direction) {}
    virtual bool IsGravity() { return false; }
    virtual float GetHp() { return 0.0f; }
    virtual void SetHp(float hp) {}
    virtual float GetDamage() { return 0.0f; }
    virtual void SetDamage(float damage) {}
    virtual int GetEnemyType() { return 0; }

    virtual void CollisionStepped(std::vector<CollObject*> obj) {}
    virtual void CollisionSticked(std::vector<CollObject*> obj) {}
    virtual void CollisionEntered(std::vector<CollObject*> obj) {}
protected:
    virtual void Draw(SpriteRenderer& renderer);
};

#endif