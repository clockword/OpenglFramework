/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "game_object.h"


GameObject::GameObject()
    : anim(nullptr), Position(0.0f, 0.0f), Size(1.0f, 1.0f), 
    Velocity(0.0f), Color(1.0f), Rotation(0.0f), Sprite(), IsSolid(false), Destroyed(false), xFlip(false), yFlip(false) { }

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity) 
    : anim(nullptr), Position(pos), Size(size),
    Velocity(velocity), Color(color), Rotation(0.0f), Sprite(sprite), IsSolid(false), Destroyed(false), xFlip(false), yFlip(false) { }

GameObject::~GameObject()
{
    if (anim != nullptr)
    {
        anim->DeleteAnim();
        delete anim;
    }
}

void GameObject::Create(SpriteAnimation anim)
{
    this->anim = new SpriteAnimation();
    *this->anim = anim;
}

void GameObject::Update(SpriteRenderer& renderer, float deltatime)
{
    anim->UpdateAnim(deltatime);

    this->Position += this->Velocity * deltatime;

    Draw(renderer);
}

void GameObject::Draw(SpriteRenderer& renderer)
{
    glm::vec2 pos(this->Position);
    glm::vec2 size(this->Size);

    if (xFlip)
    {
        size.x = -size.x;
        pos.x += anim->GetCenterX() * this->Size.x;
    }
    else
    {
        pos.x -= anim->GetCenterX() * this->Size.x;
    }
    if (yFlip)
    {
        size.y = -size.y;
        pos.y += anim->GetCenterY() * this->Size.y;
    }
    else
    {
        pos.y -= anim->GetCenterY() * this->Size.y;
    }


    renderer.DrawSprite(this->Sprite, *anim, pos, size, this->Rotation, this->Color);
}