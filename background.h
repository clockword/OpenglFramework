#pragma once
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "solo_sprite.h"
#include "sprite_renderer.h"

class Background
{
protected:
    std::vector<SoloSprite> objects;
public:
    bool IsMoving;

    Background();

    void PushSprite();
    void Update(SpriteRenderer& renderer, float deltatime);
};

