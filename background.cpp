#include "background.h"

#include "resource_manager.h"

Background::Background()
{
    IsMoving = false;
}

void Background::PushSprite()
{
    objects.push_back(SoloSprite());
    objects[0].PushSprite();
}

void Background::Update(SpriteRenderer& renderer, float deltatime)
{
    if (IsMoving)
    {

    }
    else
    {
        for (auto obj : objects)
            obj.Update(renderer, deltatime);
    }
}
